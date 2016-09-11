#ifndef Metric_logic
#define Metric_logic

#include <type_traits>

namespace logic
{
	template <typename type>
	constexpr bool is_unsigned = std::is_unsigned<type>::value;

}; // namespace logic

#endif // Metric_logic
