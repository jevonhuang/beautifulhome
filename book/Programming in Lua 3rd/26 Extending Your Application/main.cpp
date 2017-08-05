#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <lua.hpp>
#include <string>

const int MAX_COLOR = 255;

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

int getcolorfield(lua_State* L, const char* key)
{
	//lua_pushstring(L, key);
	//lua_gettable(L, -2);

	lua_getfield(L, -1, key);//取出表里面索引的值并压入栈顶
	if (!lua_isnumber(L, -1))
		error(L, "invalid componet in background color");
	int result = (int)(lua_tonumber(L, -1) * MAX_COLOR);
	lua_pop(L, 1);
	return result;
}

void setcolorfield(lua_State* L, const char* index, int value)
{
	//lua_pushstring(L, index);
	//lua_pushnumber(L, (double)value / MAX_COLOR);
	//lua_settable(L, -3);

	lua_pushnumber(L, (double)value / MAX_COLOR);
	lua_setfield(L, -2, index);
}

struct ColorTable
{
	char* name;
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} colortable[] =
{
	{"WHITE", MAX_COLOR, MAX_COLOR, MAX_COLOR},
	{"RED", MAX_COLOR, 0, 0},
	{"GREEN", 0, MAX_COLOR, 0},
	{"BLUE", 0, 0, MAX_COLOR},
	{nullptr, 0, 0, 0}
};

void setcolor(lua_State* L, ColorTable* color)
{
	lua_newtable(L);//creates a table
	setcolorfield(L, "r", color->red);//table.r = color->r
	setcolorfield(L, "g", color->green);//table.g = color->g
	setcolorfield(L, "b", color->blue);//table.b = color->b
	lua_setglobal(L, color->name);//name = table
}

double f(lua_State* L, double x, double y)
{
	double z;
	lua_getglobal(L, "f");
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);

	if (lua_pcall(L, 2, 1, 0) != 0)
		error(L, "error running function 'f': %s", lua_tostring(L, -1));

	if (!lua_isnumber(L, -1))
		error(L, "function 'f' must return a number");
	
	z = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return z;
}

void call_va(lua_State* L, const char* function, const char* signal, ...)
{
	va_list vl;
	va_start(vl, signal);

	int narg = 0;
	int nres = 0;
	lua_getglobal(L, function);
	for ( ; *signal; ++narg)
	{
		luaL_checkstack(L, 1, "too many arguments");
		switch (*signal++)
		{
		case 'd':
			lua_pushnumber(L, va_arg(vl, double));
			break;
		case 'i':
			lua_pushinteger(L, va_arg(vl, int));
			break;
		case 's':
			lua_pushstring(L, va_arg(vl, char*));
			break;
		case '>':
			goto endargs;
		default:
			error(L, "invalid option %c", *(signal - 1));
		}
	}
	endargs:

	nres = strlen(signal);
	if (lua_pcall(L, narg, nres, 0) != 0)
		error(L, "error calling %s %s", function, lua_tostring(L, -1));

	nres = -nres;
	while (*signal)
	{
		switch (*signal++)
		{
		case 'd':
		{
			if (!lua_isnumber(L, nres))
				error(L, "wrong result type number need");

			*va_arg(vl, double*) = lua_tonumber(L, nres);
			break;
		}
		case 'i':
		{
			if (!lua_isnumber(L, nres))
				error(L, "wrong result type integer need");
			*va_arg(vl, int*) = lua_tointeger(L, nres);
			break;
		}
		case 's':
		{
			if (!lua_isstring(L, nres))
				error(L, "wrong result type string need");
			*va_arg(vl, const char**) = lua_tostring(L, nres);
			break;

		}
		default:
			error(L, "invalid option %c", *(signal - 1));
		}
		nres++;
	}

	va_end(vl);
}

int main(int argc, const char* argv[])
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	//-------------------------------------------------------------------------
	int i = 0;
	while (colortable[i].name != nullptr)
		setcolor(L, &colortable[i++]);


	//-------------------------------------------------------------------------
	int width, height;
	load(L, "config.lua", width, height);


	//-------------------------------------------------------------------------
	int red, green, blue;
	lua_getglobal(L, "background");
	if (lua_isstring(L, -1))//value is a string
	{
		const char* colorname = lua_tostring(L, -1);
		int i = 0;
		for (; colortable[i].name != nullptr; i++)
		{
			if (strcmp(colorname, colortable[i].name) == 0)
				break;
		}

		if (colortable[i].name == nullptr)
		{
			error(L, "invalid color name (%s)", colorname);
		}
		else
		{
			red = colortable[i].red;
			green = colortable[i].green;
			blue = colortable[i].blue;
		}
	}
	else if (lua_istable(L, -1))
	{
		red = getcolorfield(L, "r");
		green = getcolorfield(L, "g");
		blue = getcolorfield(L, "b");
	}
	else
	{
		error(L, "invalid value for 'backgroud'");
	}
	std::cout << "red = " << red << "green = " << green << "blue = " << blue << std::endl;


	//-------------------------------------------------------------------------
	//test call lua function
	std::cout << "function call result = " << f(L, 2, 1) << std::endl;


	//-------------------------------------------------------------------------
	//test call_va
	double res = 7.0;
	call_va(L, "f", "ii>d", 2, 1, &res);
	lua_settop(L, 1);
	std::cout << res << std::endl;


	//-------------------------------------------------------------------------
	lua_close(L);
	std::cin.get();
	return 0;
}