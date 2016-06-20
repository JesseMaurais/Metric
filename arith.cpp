#include "arith.hpp"
#include <lux/lux.hpp>

extern "C" int luaopen_arith(lua_State *state)
{
	arith::integer<8> i;
	i = "1234";
	return 0;
}

