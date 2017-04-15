#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <lua.hpp>
#include <string>

void error(lua_State* L, const char*fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	vfprintf(stderr, fmt, arg);
	va_end(arg);
	lua_close(L);
	exit(EXIT_FAILURE);
}

static int l_sin(lua_State* L)
{
	double d = luaL_checknumber(L, 1);
	lua_pushnumber(L, sin(d));
	return 1;
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	lua_pushcfunction(L, l_sin);
	lua_setglobal(L, "mysin");

	if (luaL_loadfile(L, "config.lua") || lua_pcall(L, 0, 0, 0))
	{
		error(L, "cannot run config. file: %s", lua_tostring(L, -1));
	}


	//char buff[256] = {0};
	//while (fgets(buff, sizeof(buff), stdin) != nullptr)
	//{
	//	int error = luaL_loadstring(L, buff) || lua_pcall(L, 0, 0, 0);
	//	if (error)
	//	{
	//		fprintf(stderr, "%s\n", lua_tostring(L, -1));
	//		lua_pop(L, 1);
	//	}
	//}


	lua_close(L);

	std::cin.get();
	return 0;
}