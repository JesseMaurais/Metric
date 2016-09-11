#ifndef Metric_logic
#define Metric_logic

#include <type_traits>

namespace logic
{
	template <typename type>
	constexpr bool is_unsigned = std::is_unsigned<type>::value;
	#define ASSERT_UNSIGNED(type)\
	 static_assert(logic::is_unsigned<type>, #type " must be unsigned");

	template <typename type>
	constexpr bool is_signed = std::is_signed<type>::value;
	#define ASSERT_SIGNED(type)\
	 static_assert(logic::is_signed<type>, #type " must be signed");

}; // namespace logic

#endif // Metric_logic
