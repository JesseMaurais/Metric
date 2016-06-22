#include "arith.hpp"
#include <lux/lux.hpp>
#include <iostream>

extern "C" int luaopen_arith(lua_State *state)
{
	arith::integer<8> i;
	i = 1234;
	std::cout << int(i) << std::endl;
	return 0;
}

