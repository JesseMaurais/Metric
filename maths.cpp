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
	{"prim", lux_cast(prim<lua_Integer>)},
	{"perm", lux_cast(perm<lua_Integer>)},
	{"comb", lux_cast(comb<lua_Integer>)},
	// gamma
	{"gamma", lux_cast(tgamma<lua_Number>)},
	{"igamma", lux_cast(igamma<lua_Number>)},
	{"igammac", lux_cast(igammac<lua_Number>)},
	{"lngamma", lux_cast(lgamma<lua_Number>)},
	// beta
	{"beta", lux_cast(beta<lua_Number>)},
	{"ibeta", lux_cast(ibeta<lua_Number>)},
	{"ibetac", lux_cast(ibetac<lua_Number>)},
	// Reimann zeta
	{"zeta", lux_cast(zeta<lua_Number>)},
	// error & complement
	{"erf", lux_cast(erf<lua_Number>)},
	{"erfc", lux_cast(erfc<lua_Number>)},
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
	{"log", lux_cast(logb<lua_Number>)},
	{"log2", lux_cast(log2<lua_Number>)},
	{"log10", lux_cast(log10<lua_Number>)},
	// trigonometric
	{"sin", lux_cast(sin<lua_Number>)},
	{"cos", lux_cast(cos<lua_Number>)},
	{"tan", lux_cast(tan<lua_Number>)},
	{"asin", lux_cast(asin<lua_Number>)},
	{"acos", lux_cast(acos<lua_Number>)},
	{"atan", lux_cast(atan<lua_Number>)},
	{"atan2", lux_cast(atan2<lua_Number>)},
	// hyperbolic
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

	lux_Reg<lua_Number> nums[] =
	{
	{"e", e},
	{"ln2", ln2},
	{"ln10", ln10},
	{"log2e", log2e},
	{"log10e", log10e},
	{"pi", pi},
	{"pi_2", pi_2},
	{"pi_4", pi_4},
	{"pi2_6", pi2_6},
	{"sqrt2pi", sqrt2pi},
	{"sqrt2", sqrt2},
	{"ngamma", ngamma},
	{nullptr}
	};
	lux_settable(state, nums);

	return 1;
}

