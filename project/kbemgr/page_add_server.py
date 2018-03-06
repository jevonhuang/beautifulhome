import time
import tkinter
import http.client
import urllib.parse
import hashlib
import json
	
class page_add_server(tkinter.Frame):
	def __init__(self, parent, root):
		super().__init__(parent)		
		self.root = root

		label = tkinter.Label(self, text="服务器创建", bg = 'BurlyWood', width=12)
		label.place(x=10, y=10)		
		
		back_btn = tkinter.Button(self, text="返回", bg = 'OrangeRed', command=self.back)
		back_btn.place(x=275, y=0)			
		
		self.mysqlhost_desc = tkinter.Label(self, text='mysql host', bg ='BurlyWood', width=12)
		self.mysqlhost_desc.place(x=10, y=40)		
		self.mysqlhost_input = tkinter.Entry(self, width=26)
		self.mysqlhost_input.place(x=110, y=42)
		# self.mysqlhost_input.insert(0, '')
	
		self.mysqlport_desc = tkinter.Label(self, text='mysql port', bg ='BurlyWood', width=12)
		self.mysqlport_desc.place(x=10, y=80)		
		self.mysqlport_input = tkinter.Entry(self, width=26)
		self.mysqlport_input.place(x=110, y=82)
		# self.mysqlport_input.insert(0, '')
		
		self.mysqluser_desc = tkinter.Label(self, text='username', bg ='BurlyWood', width=12)
		self.mysqluser_desc.place(x=10, y=120)		
		self.mysqluser_input = tkinter.Entry(self, width=26)
		self.mysqluser_input.place(x=110, y=122)
		# self.mysqluser_input.insert(0, '')
		
		self.mysqlpass_desc = tkinter.Label(self, text='password', bg ='BurlyWood', width=12)
		self.mysqlpass_desc.place(x=10, y=160)		
		self.mysqlpass_input = tkinter.Entry(self, width=26)
		self.mysqlpass_input.place(x=110, y=162)
		# self.mysqlpass_input.insert(0, '')		
		
		self.platformid_desc = tkinter.Label(self, text='platform id', bg ='BurlyWood', width=12)
		self.platformid_desc.place(x=10, y=200)		
		self.platformid_input = tkinter.Entry(self, width=26)
		self.platformid_input.place(x=110, y=202)
		# self.platformid_input.insert(0, '')		
		
		self.serverid_desc = tkinter.Label(self, text='server id', bg ='BurlyWood', width=12)
		self.serverid_desc.place(x=10, y=200)		
		self.serverid_input = tkinter.Entry(self, width=26)
		self.serverid_input.place(x=110, y=202)
		# self.serverid_input.insert(0, '')

		self.servername_desc = tkinter.Label(self, text='server name', bg ='BurlyWood', width=12)
		self.servername_desc.place(x=10, y=240)		
		self.servername_input = tkinter.Entry(self, width=26)
		self.servername_input.place(x=110, y=242)
		# self.servername_input.insert(0, '')
		
		self.servername_desc = tkinter.Label(self, text='directory', bg ='BurlyWood', width=12)
		self.servername_desc.place(x=10, y=280)		
		self.servername_input = tkinter.Entry(self, width=26)
		self.servername_input.place(x=110, y=282)
		# self.servername_input.insert(0, '')		
		
		self.create_btn = tkinter.Button(self, text='创建', bg='RosyBrown', command=self.create, width=25)
		self.create_btn.place(x=110, y=320)
	
	def back(self):
		self.root.show_page_list()
		
	def create(self):
		pass