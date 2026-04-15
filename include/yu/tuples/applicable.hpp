#ifndef YU_TUPLES_APPLICABLE_HPP_
#define YU_TUPLES_APPLICABLE_HPP_

#include "apply.hpp"
#include <utility>

namespace yu::tuples {

template <typename F, typename T>
concept applicable = requires(F&& fn, T&& t) { tuples::apply(std::forward<F>(fn), std::forward<T>(t)); };

} // namespace yu::tuples

#endif