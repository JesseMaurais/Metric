#include "maths.hpp"
#include <lux/lux.hpp>

extern "C" int luaopen_maths(lua_State *state)
{
	using namespace maths;
	luaL_Reg regs[] =
	{
	{"fact", lux_cast(fact<lua_Integer>)},
	{"perm", lux_cast(perm<lua_Integer>)},
	{"comb", lux_cast(comb<lua_Integer>)},
	{"gcd", lux_cast(gcd<lua_Integer>)},
	{"lcm", lux_cast(lcm<lua_Integer>)},
	{"scalbn", lux_cast(scalbn<lua_Number>)},
	{"hypot", lux_cast(hypot<lua_Number>)},
	{"erf", lux_cast(erf<lua_Number>)},
	{"erfc", lux_cast(erfc<lua_Number>)},
	{"gamma", lux_cast(gamma<lua_Number>)},
	{"lgamma", lux_cast(lgamma<lua_Number>)},
	{"fma", lux_cast(fma<lua_Number>)},
	{nullptr}
	};
	luaL_newlib(state, regs);
	return 1;
}

