#ifndef YU_TUPLES_REGULAR_APPLICABLE_HPP_
#define YU_TUPLES_REGULAR_APPLICABLE_HPP_

#include "applicable.hpp"

namespace yu::tuples {

template <typename F, typename T>
concept regular_applicable = applicable<F, T>;

} // namespace yu::tuples

#endif