#include "arith.hpp"
#include <lux/lux.hpp>

template <size_t size> struct lux_Integer
{
	typedef arithmetic::integer<size> User;
	typedef lux_Store<User> Type;

	static int __tostring(lua_State *state)
	{
		return lux_push<std::string>(state, Type::to(state));
	}

	static int __call(lua_State *state)
	{
		return lux_push<lua_Integer>(state, Type::to(state));
	}

	static int __new(lua_State *state)
	{
		switch (lua_type(state, 1))
		{
		case LUA_TSTRING: {
			std::string string = lua_tostring(state, 1);
			User value = string;
			return Type::push(state, value);
		}
		case LUA_TNUMBER: {
			lua_Integer integer = lua_tointeger(state, 1);
			User value = integer;
			return Type::push(state, value);
		}
		default:
			return luaL_argerror(state, 1, "string, integer");
		}
	}

	static int __add(lua_State *state)
	{
		const User &A = Type::to(state, 1);
		const User &B = Type::to(state, 2);
		return lux_push(state, A + B);
	}

	static int __sub(lua_State *state)
	{
		const User &A = Type::to(state, 1);
		const User &B = Type::to(state, 2);
		return lux_push(state, A - B);
	}

	static int __mul(lua_State *state)
	{
		const User &A = Type::to(state, 1);
		const User &B = Type::to(state, 2);
		return lux_push(state, A * B);
	}

	static int __div(lua_State *state)
	{
		const User &A = Type::to(state, 1);
		const User &B = Type::to(state, 2);
		return lux_push(state, A / B);
	}

	static int __mod(lua_State *state)
	{
		const User &A = Type::to(state, 1);
		const User &B = Type::to(state, 2);
		return lux_push(state, A % B);
	}
	/*
	static int __shl(lua_State *state)
	{
		const User &A = Type::to(state, 1);
		const auto B = lua_tointeger(state, 2);
		return lux_push(state, A << B);
	}

	static int __shr(lua_State *state)
	{
		const User &A = Type::to(state, 1);
		const auto B = lua_tointeger(state, 2);
		return lux_push(state, A >> B);
	}
	*/
	static int __eq(lua_State *state)
	{
		const User &A = Type::to(state, 1);
		const User &B = Type::to(state, 2);
		return lux_push(state, A == B);
	}

	static int __le(lua_State *state)
	{
		const User &A = Type::to(state, 1);
		const User &B = Type::to(state, 2);
		return lux_push(state, A <= B);
	}

	static int __lt(lua_State *state)
	{
		const User &A = Type::to(state, 1);
		const User &B = Type::to(state, 2);
		return lux_push(state, A < B);
	}

	static int open(lua_State *state)
	{
		luaL_newmetatable(state, Type::name);
		luaL_Reg regs[] = 
		{
		{"__tostring", __tostring},
		{"__call", __call},
		{"__add", __add},
		{"__sub", __sub},
		{"__mul", __mul},
		{"__div", __div},
		{"__mod", __mod},
//		{"__shl", __shl},
//		{"__shr", __shr},
		{"__eq", __eq},
		{"__le", __le},
		{"__lt", __lt},
		{"new", __new},
		{nullptr}
		};
		luaL_setfuncs(state, regs, 0);
		return 1;
	}
};


extern "C" int luaopen_arith(lua_State *state)
{
	return lux_Integer<8>::open(state);
}

