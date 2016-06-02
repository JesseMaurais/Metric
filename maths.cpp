#include "maths.hpp"
#include <lux/lux.hpp>

extern "C" int luaopen_maths(lua_State *state)
{
	using namespace maths;
	luaL_Reg regs[] =
	{
	// common factors
	{"gcd", lux_cast(gcd<lua_Integer>)},
	{"lcm", lux_cast(lcm<lua_Integer>)},
	// combinatorial
	{"fact", lux_cast(fact<lua_Integer>)},
	{"perm", lux_cast(perm<lua_Integer>)},
	{"comb", lux_cast(comb<lua_Integer>)},
	// error & complement
	{"erf", lux_cast(erf<lua_Number>)},
	{"erfc", lux_cast(erfc<lua_Number>)},
	// gamma & beta
	{"gamma", lux_cast(tgamma<lua_Number>)},
	{"igamma", lux_cast(igamma<lua_Number>)},
	{"igammac", lux_cast(igammac<lua_Number>)},
	{"lngamma", lux_cast(lgamma<lua_Number>)},
	{"beta", lux_cast(beta<lua_Number>)},
	// power
	{"pow", lux_cast(pow<lua_Number>)},
	{"sqrt", lux_cast(sqrt<lua_Number>)},
	{"cbrt", lux_cast(cbrt<lua_Number>)},
	{"hyp", lux_cast(hypot<lua_Number>)},
	// exponential
	{"exp", lux_cast(exp<lua_Number>)},
	{"exp2", lux_cast(exp<lua_Number>)},
	{"ldexp", lux_cast(ldexp<lua_Number>)},
	// logarithmic
	{"ln", lux_cast(log<lua_Number>)},
	{"log", lux_cast(log2<lua_Number>)},
	{"log10", lux_cast(log10<lua_Number>)},
	// trigonometric
	{"sin", lux_cast(sin<lua_Number>)},
	{"cos", lux_cast(cos<lua_Number>)},
	{"tan", lux_cast(tan<lua_Number>)},
	{"asin", lux_cast(asin<lua_Number>)},
	{"acos", lux_cast(acos<lua_Number>)},
	{"atan", lux_cast(atan<lua_Number>)},
	{"atan2", lux_cast(atan2<lua_Number>)},
	{"sinh", lux_cast(sinh<lua_Number>)},
	{"cosh", lux_cast(cosh<lua_Number>)},
	{"tanh", lux_cast(tanh<lua_Number>)},
	{"asinh", lux_cast(asinh<lua_Number>)},
	{"acosh", lux_cast(acosh<lua_Number>)},
	{"atanh", lux_cast(atanh<lua_Number>)},
	// lossless linear
	{"line", lux_cast(fma<lua_Number>)},
	// end
	{nullptr}
	};
	luaL_newlib(state, regs);
	return 1;
}

