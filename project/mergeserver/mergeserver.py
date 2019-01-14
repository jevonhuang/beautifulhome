# -*- coding: utf-8 -*-
import os
import sys
import time
import pymysql

class mergeserver():
	not_merge_list_ = [
		'kbe_entitylog',
		'kbe_serverlog',
		'kbe_email_verification',
		'tbl_Updater',
		'tbl_GameMgr',
	]

	truncate_list_ = [
		'tbl_GameMgr_activityRankList_values_rankDataList',
		'tbl_GameMgr_activityRankList_values',
		'tbl_GameMgr_killList',
		'tbl_GameMgr_historyHeroList',
		'tbl_GameMgr_chatWorldRecords',
		'tbl_GameMgr_chatSystemRecords',
		'tbl_GameMgr_chatKuafuRecords',
		'tbl_GameMgr_broadCastMsgList_values_msg',
		'tbl_GameMgr_broadCastMsgList_values',
		'tbl_GameMgr_newHeroList',
	]

	host_ = 'localhost'
	user_ = 'root'
	passwd_ = 'root'
	
	def __init__(self):
		if len(sys.argv) < 3:
			print('python mergeserver fromdb todb')
			return

		self.fromdb_ = sys.argv[1]
		self.todb_ = sys.argv[2]
		self.connect_fromdb_ = pymysql.connect(host=self.host_, port=3306, user=self.user_, passwd=self.passwd_, db=self.fromdb_)
		self.connect_todb_ = pymysql.connect(host=self.host_, port=3306, user=self.user_, passwd=self.passwd_, db=self.todb_)
		self.tables_name_ = None
		self.tables_columns_ = {}

		if not self.issamedb():
			return
		
		if not self.issamecolumn():
			return
		
		self.process()			
		
	def gettables(self, connect, db):
		cursor = connect.cursor(cursor=pymysql.cursors.DictCursor)
		sqls = 'select table_name from information_schema.tables where table_schema=\'%s\';' % db
		cursor.execute(sqls)
		connect.commit()
		tables_name = [t['table_name'] for t in cursor.fetchall()]
		tables_name.sort()
		if self.tables_name_ is None:
			self.tables_name_ = tables_name
		
		cursor.close()
		return tables_name
	
	def getcolumns(self, connect, db, table_name):
		cursor = connect.cursor(cursor=pymysql.cursors.DictCursor)
		sqls = 'select column_name from information_schema.columns where table_name = \'%s\' and table_schema = \'%s\';' % (table_name, db)
		cursor.execute(sqls)
		connect.commit()
		columns = [t['column_name'] for t in cursor.fetchall()]
		columns.sort()
		if table_name not in self.tables_columns_:
			self.tables_columns_[table_name] = columns
		
		cursor.close()	
		return columns		
	
	def issamedb(self):
		tables_fromdb = self.gettables(self.connect_fromdb_, self.fromdb_)
		tables_todb = self.gettables(self.connect_todb_, self.todb_)

		if len(tables_fromdb) != len(tables_todb):
			print('merge fail, tables_name\'s len is not equal')
			return False
		
		for i in range(0, len(tables_fromdb)):
			if tables_fromdb[i] != tables_todb[i]:
				print('merge fail, tables_name\'s is not same from %s to %s' % (tables_fromdb[i], tables_todb[i]))
				return False

		return True
		
		
	def issamecolumn(self):
		for table_name in self.tables_name_:	
			columns_fromdb = self.getcolumns(self.connect_fromdb_, self.fromdb_, table_name)
			columns_todb = self.getcolumns(self.connect_todb_, self.todb_, table_name)

			if len(columns_fromdb) != len(columns_todb):
				print('merge fail, columns\'s len is not equal')
				return False
			
			for i in range(0, len(columns_fromdb)):
				if columns_fromdb[i] != columns_todb[i]:
					print('merge fail, columns\'s is not same from %s to %s' % (columns_fromdb[i], columns_todb[i]))
					return False

		return True
	
	def process(self):
		#备份
		fmt_str = 'mysqldump -h %s -u%s -p%s %s > %.3f_%s.sql'
		now = time.time()
		os.system(fmt_str % (self.host_, self.user_, self.passwd_, self.fromdb_, now, self.fromdb_))
		os.system(fmt_str % (self.host_, self.user_, self.passwd_, self.todb_, now, self.todb_))
		
		#合并
		cursor = self.connect_todb_.cursor(cursor=pymysql.cursors.DictCursor)
		for table_name in self.tables_name_:
			if table_name in self.not_merge_list_:
				continue
				
			if table_name in self.truncate_list_:
				cursor.execute("truncate table %s.%s" % (self.todb_, table_name))
				self.connect_todb_.commit()
				continue

			fields = ','.join(self.tables_columns_[table_name])
			sqls = 'insert into %s.%s (%s) (select %s from %s.%s);' % (self.todb_, table_name, fields, fields, self.fromdb_, table_name)
			cursor.execute(sqls)
			self.connect_todb_.commit()	

		print('merge success.')
		cursor.close()
		self.connect_fromdb_.close()
		self.connect_todb_.close()

if __name__ == "__main__":
	mergeserver()