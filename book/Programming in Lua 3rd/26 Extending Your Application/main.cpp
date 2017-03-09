#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <lua.hpp>

void error(lua_State* L, const char*fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	vfprintf(stderr, fmt, arg);
	va_end(arg);
	lua_close(L);
	exit(EXIT_FAILURE);
}

void load(lua_State* L, const char* file_name, int& width, int& height)
{
	if (luaL_loadfile(L, file_name) || lua_pcall(L, 0, 0, 0))
	{
		error(L, "cannot run config. file: %s", lua_tostring(L, -1));
	}

	lua_getglobal(L, "width");
	lua_getglobal(L, "height");
	if (!lua_isnumber(L, -2))
	{
		error(L, "'width' should be a number\n");
	}
	if (!lua_isnumber(L, -1))
	{
		error(L, "'height' should be a number\n");
	}

	width = lua_tointeger(L, -2);
	height = lua_tointeger(L, -1);
}

int main(int argc, const char* argv[])
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	int width, height;
	load(L, "config.lua", width, height);

	lua_close(L);
	std::cin.get();
	return 0;
}