#ifndef YU_SELECT_CONDITIONS_EQUALS_HPP_
#define YU_SELECT_CONDITIONS_EQUALS_HPP_

#include "detail/equals_t.hpp"
#include <utility>

namespace yu::select::conditions {

template <typename Value>
constexpr auto equals(Value&& value) {
    return detail::equals_t<Value>(std::forward<Value>(value));
}

} // namespace yu::select::conditions

#endif