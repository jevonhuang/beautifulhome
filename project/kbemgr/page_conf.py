import time
import tkinter
import http.client
import urllib.parse
import hashlib
import json
	
class page_conf(tkinter.Frame):
	def __init__(self, parent, root):
		super().__init__(parent)		
		self.root = root
		self.path = ''
		
		label = tkinter.Label(self, text="服务器配置", bg = 'BurlyWood', width=12)
		label.place(x=10, y=10)		
		
		back_btn = tkinter.Button(self, text="返回", bg = 'OrangeRed', command=self.back)
		back_btn.place(x=275, y=0)			
		
		self.mysqlhost_desc = tkinter.Label(self, text='mysql host', bg ='BurlyWood', width=12)
		self.mysqlhost_desc.place(x=10, y=40)		
		self.mysqlhost_input = tkinter.Entry(self, width=26)
		self.mysqlhost_input.place(x=110, y=42)
		
	
		self.mysqlport_desc = tkinter.Label(self, text='mysql port', bg ='BurlyWood', width=12)
		self.mysqlport_desc.place(x=10, y=80)		
		self.mysqlport_input = tkinter.Entry(self, width=26)
		self.mysqlport_input.place(x=110, y=82)
		
		self.mysqluser_desc = tkinter.Label(self, text='username', bg ='BurlyWood', width=12)
		self.mysqluser_desc.place(x=10, y=120)		
		self.mysqluser_input = tkinter.Entry(self, width=26)
		self.mysqluser_input.place(x=110, y=122)
		
		self.mysqlpass_desc = tkinter.Label(self, text='password', bg ='BurlyWood', width=12)
		self.mysqlpass_desc.place(x=10, y=160)		
		self.mysqlpass_input = tkinter.Entry(self, width=26)
		self.mysqlpass_input.place(x=110, y=162)	
	
		self.databasename_desc = tkinter.Label(self, text='databasename', bg ='BurlyWood', width=12)
		self.databasename_desc.place(x=10, y=200)		
		self.databasename_input = tkinter.Entry(self, width=26)
		self.databasename_input.place(x=110, y=202)
		# self.mysqlpass_input.insert(0, '')
	
		self.platformid_desc = tkinter.Label(self, text='platform id', bg ='BurlyWood', width=12)
		self.platformid_desc.place(x=10, y=240)		
		self.platformid_input = tkinter.Entry(self, width=26)
		self.platformid_input.place(x=110, y=242)
		# self.platformid_input.insert(0, '')		
		
		self.serverid_desc = tkinter.Label(self, text='server id', bg ='BurlyWood', width=12)
		self.serverid_desc.place(x=10, y=280)		
		self.serverid_input = tkinter.Entry(self, width=26)
		self.serverid_input.place(x=110, y=282)
		# self.serverid_input.insert(0, '')

		self.servername_desc = tkinter.Label(self, text='server name', bg ='BurlyWood', width=12)
		self.servername_desc.place(x=10, y=320)		
		self.servername_input = tkinter.Entry(self, width=26)
		self.servername_input.place(x=110, y=322)
		# self.servername_input.insert(0, '')
		
		self.update_btn = tkinter.Button(self, text='更新', bg='RosyBrown', command=self.update, width=25)
		self.update_btn.place(x=110, y=360)
	
	def refresh(self, data=None):
		self.mysqlhost_input.delete(0, len(self.mysqlhost_input.get()))
		self.mysqlhost_input.insert(0, data['host'])
	
		self.mysqlport_input.delete(0, len(self.mysqlport_input.get()))
		self.mysqlport_input.insert(0, data['port'])	
	
		self.mysqluser_input.delete(0, len(self.mysqluser_input.get()))
		self.mysqluser_input.insert(0, data['username'])		
	
		self.mysqlpass_input.delete(0, len(self.mysqlpass_input.get()))
		self.mysqlpass_input.insert(0, data['password'])		
	
		self.databasename_input.delete(0, len(self.databasename_input.get()))
		self.databasename_input.insert(0, data['databasename'])

		self.platformid_input.delete(0, len(self.platformid_input.get()))
		self.platformid_input.insert(0, data['platform_id'])

		self.serverid_input.delete(0, len(self.serverid_input.get()))
		self.serverid_input.insert(0, data['server_id'])
		
		self.servername_input.delete(0, len(self.servername_input.get()))
		self.servername_input.insert(0, data['server_name'])	
	
		self.path = data['path']
	
	def getconf(self):
		conf = {}
		conf['host'] = self.mysqlhost_input.get()
		conf['port'] = self.mysqlport_input.get()
		conf['username'] = self.mysqluser_input.get()
		conf['password'] = self.mysqlpass_input.get()
		conf['databasename'] = self.databasename_input.get()
		conf['platform_id'] = self.platformid_input.get()
		conf['server_id'] = self.serverid_input.get()
		conf['server_name'] = self.servername_input.get()
		return conf
	
	def back(self):
		self.root.show_page_list()	
		
	def update(self):
		conn = http.client.HTTPConnection(self.root.http_addr, 8000)	
		rkey = '1MwdxgjOYSr7aague#K6avC6qoq#*3ua'
		curr = int(time.time())
		path = self.path
		conf = json.dumps(self.getconf())
		data = '%s%s%u%s' % (path, conf, curr, rkey)
		data = data.lower()
		sign = hashlib.md5(data.encode()).hexdigest()	
		args = urllib.parse.urlencode({'path':path, 'conf':conf, 'time':curr, 'sign':sign})		

		try:			
			conn.request("GET", "/wc/update_conf?"+args)
		except:
			print('连接服务失败')
			conn.close()
			return
		
		response = conn.getresponse()
		data = response.read().decode()		
		conn.close()

		if response.status != 200:
			print('请求接口失败')			
			return
			
		try:
			data = json.loads(data)
		except:
			print('数据解析失败' + str(data))
			return
		
		if data['ret'] != 0:
			print('数据验证失败' + str(data))
			return
			
		print('配置更新成功')	