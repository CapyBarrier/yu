#ifndef YU_SELECT_DETAIL_CAPTURE_TYPE_HPP_
#define YU_SELECT_DETAIL_CAPTURE_TYPE_HPP_

#include <type_traits>

namespace yu::select::detail {

template <typename T>
using capture_type_t = std::conditional_t< //
    std::is_rvalue_reference_v<T>,         //
    std::decay_t<T>,                       //
    std::type_identity<T>                  //
    >::type;                               //

} // namespace yu::select::detail

#endif