import tkinter
import http.client
import urllib.parse
import hashlib
import json
import time

class page_list(tkinter.Frame):
	def __init__(self, parent, root):
		super().__init__(parent)
		label = tkinter.Label(self, text="服务器列表", bg = 'BurlyWood', width=12)
		label.place(x=10, y=10)

		back_btn = tkinter.Button(self, text="返回", bg = 'OrangeRed', command=self.back)
		back_btn.place(x=275, y=0)				
		
		self.root = root
		
		allconfig_btn = tkinter.Button(self, text='更新所有配置', bg = 'RosyBrown', command=self.update_config_all)
		allconfig_btn.place(x=6, y=465)
		
		allscript_btn = tkinter.Button(self, text='更新所有脚本', bg = 'RosyBrown', command=self.update_script_all)
		allscript_btn.place(x=113, y=465)	

		allserver_btn = tkinter.Button(self, text='重启所有游戏', bg = 'RosyBrown', command=self.update_server_all)
		allserver_btn.place(x=219, y=465)			
		
		self.control_list = []
		
	def refresh(self, data=None):
		for control in self.control_list:
			control.destroy()
		self.control_list.clear()
	
		server_list = self.root.get_server_list()
		for i in range(len(server_list)):
			server = server_list[i].split('/')[-1]
			server_label = tkinter.Label(self, text=server, bg = 'BurlyWood', width=12)
			server_label.place(x=10, y=40+i*40)
			self.control_list.append(server_label)
			
			def index():
				index = i + 0
				return index
			
			config_btn = tkinter.Button(self, text='更新配置', bg = 'RosyBrown', command=lambda a = i: self.server_conf(a))
			config_btn.place(x=110, y=37+i*40)
			self.control_list.append(config_btn)
			
			script_btn = tkinter.Button(self, text='更新脚本', bg = 'RosyBrown', command=lambda a = i: self.update_script(a))
			script_btn.place(x=175, y=37+i*40)	
			self.control_list.append(script_btn)

			server_btn = tkinter.Button(self, text='重启游戏', bg = 'RosyBrown', command=lambda a = i: self.update_server(a))
			server_btn.place(x=240, y=37+i*40)
			self.control_list.append(server_btn)			
			
		text = '+'
		addserver_btn = tkinter.Button(self, text=text, bg = 'RosyBrown', command=self.add_server)
		addserver_btn.place(x=10, y=40+len(server_list)*40)
		self.control_list.append(addserver_btn)
		
		
	def back(self):
		self.root.show_page_main()
		
	def add_server(self):
		self.root.show_page_add_server()	
		
	def server_conf(self, index):
		conn = http.client.HTTPConnection(self.root.http_addr, 8000)	
		rkey = '1MwdxgjOYSr7aague#K6avC6qoq#*3ua'
		curr = int(time.time())
		path = self.root.get_server_list()[index]
		data = '%s%u%s' % (path, curr, rkey)
		data = data.lower()
		sign = hashlib.md5(data.encode()).hexdigest()	
		args = urllib.parse.urlencode({'path':path, 'time':curr, 'sign':sign})		

		try:			
			conn.request("GET", "/wc/server_conf?"+args)
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
			print('数据解析失败' + data)
			return
		
		if data['ret'] != 0:
			print('数据验证失败')
			return
			
		data['conf']['path'] = path
		self.root.show_page_conf(data['conf'])	
	
	def update_script(self):
		pass
		
	def update_server(self):
		pass
		
	def update_config_all(self):
		pass
		
	def update_script_all(self):
		pass
		
	def update_server_all(self):
		pass
