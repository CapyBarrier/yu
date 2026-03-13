#ifndef YU_SELECT_OTHERWISE_HPP_
#define YU_SELECT_OTHERWISE_HPP_

#include "detail/otherwise_t.hpp"

namespace yu::select {

inline constexpr auto otherwise = detail::otherwise_t{};

} // namespace yu::select

#endif