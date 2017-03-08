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

void stack_dump(lua_State* L)
{
	int top = lua_gettop(L);
	for (int i = 1; i <= top; i++)
	{
		int t = lua_type(L, i);
		switch (t)
		{
			case LUA_TSTRING:
			{
				printf("%s", lua_tostring(L, i));
				break;
			}
			case LUA_TBOOLEAN:
			{
				printf(lua_toboolean(L, i) ? "true" : "false");
				break;
			}
			case LUA_TNUMBER:
			{
				printf("%g", lua_tonumber(L, i));
				break;
			}
			default:
			{
				printf("%s", lua_typename(L, t));
				break;
			}
		}
		printf(" ");
	}
	printf("\n");
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

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

	lua_pushboolean(L, 1);
	lua_pushnumber(L, 10);
	lua_pushnil(L);
	lua_pushstring(L, "hello");
	stack_dump(L);

	lua_pushvalue(L, -4);
	stack_dump(L);

	lua_insert(L, 3);
	stack_dump(L);

	lua_replace(L, 3);
	stack_dump(L);

	lua_settop(L, 6);
	stack_dump(L);

	lua_remove(L, -3);
	stack_dump(L);

	lua_settop(L, -5);
	stack_dump(L);

	lua_close(L);

	std::cin.get();
	return 0;
}