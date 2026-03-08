#ifndef YU_SELECT_ACTIONS_VALUE_HPP_
#define YU_SELECT_ACTIONS_VALUE_HPP_

#include "detail/value_t.hpp"
#include <utility>

namespace yu::select::actions {

template <typename Value>
auto value(Value&& v) {
    return detail::value_t<Value>(std::forward<Value>(v));
}

} // namespace yu::select::actions

#endif