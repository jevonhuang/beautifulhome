# coding:utf-8
from django.shortcuts import render
from django.http import HttpResponse

def index(request):
	return render(request, 'index.html')

def login(request):
	user = request.GET['user']
	password = request.GET['password']
	return HttpResponse(password)
	
def add(request):
	a = request.GET['a']
	b = request.GET['b']
	c = int(a) + int(b)
	
	return HttpResponse(str(c))