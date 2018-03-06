import time
import tkinter
import http.client
import urllib.parse
import hashlib
import json

from page_main import page_main
from page_list import page_list
from page_conf import page_conf
from page_add_server import page_add_server

class Application(tkinter.Tk):
	def __init__(self):       
		super().__init__()

		self.geometry('309x500')
		self.resizable(0, 0)		
		self.wm_title("运维工具")
        
		container = tkinter.Frame(self)
		container.pack(side="top", fill="both", expand = True)
		container.grid_rowconfigure(0, weight=1)
		container.grid_columnconfigure(0, weight=1)

		self.frames = {}
		for F in (page_main, page_list, page_conf, page_add_server):
			frame = F(container, self)
			self.frames[F] = frame
			frame.grid(row=0, column=0, sticky="nsew")  # 四个页面的位置都是 grid(row=0, column=0), 位置重叠，只有最上面的可见！！
			
		self.frame_show(page_main)
		self.server_list = []
		
	def set_server_list(self, server_list):
		self.server_list = server_list
		
	def get_server_list(self):
		return self.server_list
        
	def frame_show(self, cont):
		frame = self.frames[cont]
		frame.tkraise() # 切换，提升当前 tkinter.Frame z轴顺序（使可见）！！此语句是本程序的点睛之处
	
	def frame_refresh(self, cont):
		frame = self.frames[cont]
		frame.refresh()
	
	def show_page_main(self):
		self.frame_show(page_main)
		
	def show_page_list(self):
		self.frame_show(page_list)
		self.frame_refresh(page_list)
	
	def show_page_conf(self):
		self.frame_show(page_conf)
		
	def show_page_add_server(self):
		self.frame_show(page_add_server)
		
if __name__ == '__main__':
	app = Application()
	app.mainloop()	
	

