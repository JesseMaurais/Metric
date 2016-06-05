#include "stats.hpp"
#include <lux/lux.hpp>

extern "C" int luaopen_stats(lua_State *state)
{
	using namespace stats;
	luaL_Reg regs[] =
	{
	// normal
	{"dnorm", lux_cast(dnorm<lua_Number>)},
	{"pnorm", lux_cast(pnorm<lua_Number>)},
	// gamma
	{"dgamma", lux_cast(dgamma<lua_Number>)},
	{"pgamma", lux_cast(pgamma<lua_Number>)},
	// exponential
	{"dexp", lux_cast(dexp<lua_Number>)},
	{"pexp", lux_cast(pexp<lua_Number>)},
	// chi-squared
	{"dchisq", lux_cast(dchisq<lua_Number>)},
	{"pchisq", lux_cast(pchisq<lua_Number>)},
	// beta
	{"dbeta", lux_cast(dbeta<lua_Number>)},
	{"pbeta", lux_cast(pbeta<lua_Number>)},
	// fisher
	{"pf", lux_cast(pf<lua_Number>)},
	// end
	{nullptr}
	};
	luaL_newlib(state, regs);
	return 1;
}

