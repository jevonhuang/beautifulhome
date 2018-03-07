import time
import tkinter
import http.client
import urllib.parse
import hashlib
import json
	
from page_list import page_list

class page_main(tkinter.Frame):
	def __init__(self, parent, root):
		super().__init__(parent)
		
		self.root = root
		
		self.error_text = tkinter.StringVar()
		self.count_fail = 0
		self.reset_fail = 0
		
		
		self.path_desc = tkinter.Label(self, text='服务器所在路径', bg ='BurlyWood', width=12)
		self.path_desc.place(x=10, y=180)		
		self.path_input = tkinter.Entry(self)
		self.path_input.place(x=110, y=181)
		self.path_input.insert(0, 'E:/nirvana')
	
		self.addr_desc = tkinter.Label(self, text='服务器所在地址', bg ='BurlyWood', width=12)
		self.addr_desc.place(x=10, y=220)		
		self.addr_input = tkinter.Entry(self)
		self.addr_input.place(x=110, y=221)
		self.addr_input.insert(0, '127.0.0.1')
		
		self.error_label = tkinter.Label(self, textvariable=self.error_text, width=64)
		self.error_label.place(anchor='center', x=155, y=300)
		
		self.go_btn = tkinter.Button(self, text='Go', bg='OrangeRed', command=self.go)
		self.go_btn.place(x=268, y=195)

	def error_msg(self, error_msg, reset_fail):
		if self.reset_fail != reset_fail:
			self.reset_fail = reset_fail
			self.count_fail = 0
	
		self.count_fail = self.count_fail + 1			
		dot = ''
		for i in range(self.count_fail):
			dot = dot + '.'		
		
		self.error_text.set(dot + error_msg + dot)
	
	def go(self):
		self.root.http_addr = self.addr_input.get()
	
		conn = http.client.HTTPConnection(self.root.http_addr, 8000)	
		rkey = '1MwdxgjOYSr7aague#K6avC6qoq#*3ua'
		curr = int(time.time())
		path = self.path_input.get()
		data = '%s%u%s' % (path, curr, rkey)
		data = data.lower()
		sign = hashlib.md5(data.encode()).hexdigest()	
		args = urllib.parse.urlencode({'path':path, 'time':curr, 'sign':sign})		

		try:			
			conn.request("GET", "/wc/server_list?"+args)
		except:
			self.error_msg('连接服务失败', 0)
			conn.close()
			return
		
		response = conn.getresponse()
		data = response.read().decode()		
		conn.close()

		if response.status != 200:
			self.error_msg('请求接口失败', 1)			
			return
			
		try:
			data = json.loads(data)
		except:
			self.error_msg('数据解析失败' + data, 2)
			return
		
		if data['ret'] != 0:
			self.error_msg('数据验证失败', 3)
			return
			
		self.root.set_server_list(data['list'])
		self.root.show_page_list()
