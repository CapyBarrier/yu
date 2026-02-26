#ifndef YU_SELECT_OTHERWISE_HPP_
#define YU_SELECT_OTHERWISE_HPP_

#include "detail/guard.hpp"

namespace yu::select {

inline auto otherwise = detail::guard<>{};

} // namespace yu::select

#endif