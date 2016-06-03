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
	// end
	{nullptr}
	};
	luaL_newlib(state, regs);
	return 1;
}

