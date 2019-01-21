# coding:utf-8
import hashlib
from django.shortcuts import render
from django.http import HttpResponse, HttpResponseBadRequest, HttpResponseRedirect

def index(request):
	return render(request, 'index.html')

def login(request):
	user = request.GET['user']
	password = request.GET['password']
	
	#账号验证
	if user == 'admin':
		if password != hashlib.md5(b'176(love)017').hexdigest():
			return HttpResponseRedirect("/")
		#账号界面
		
	else:
		#数据库验证
		
		#系统界面
		pass
	
	return HttpResponse(password)
	
def add(request):
	a = request.GET['a']
	b = request.GET['b']
	c = int(a) + int(b)
	
	return HttpResponse(str(c))