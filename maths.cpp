#include "maths.hpp"
#include <lux/lux.hpp>

extern "C" int luaopen_maths(lua_State *state)
{
	using namespace maths;
	luaL_Reg regs[] =
	{
	// numeric
	{"gcd", lux_cast(gcd<lua_Integer>)},
	{"lcm", lux_cast(lcm<lua_Integer>)},
	// combinatorial
	{"fact", lux_cast(fact<lua_Integer>)},
	{"perm", lux_cast(perm<lua_Integer>)},
	{"comb", lux_cast(comb<lua_Integer>)},
	// error & complement
	{"erf", lux_cast(erf<lua_Number>)},
	{"erfc", lux_cast(erfc<lua_Number>)},
	// gamma & log-gamma
	{"gamma", lux_cast(tgamma<lua_Number>)},
	{"lngamma", lux_cast(lgamma<lua_Number>)},
	// linear & hypotenuse
	{"line", lux_cast(fma<lua_Number>)},
	{"hyp", lux_cast(hypot<lua_Number>)},
	{nullptr}
	};
	luaL_newlib(state, regs);
	return 1;
}

