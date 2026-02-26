#ifndef YU_SELECT_DETAIL_CAPTURE_T_HPP_
#define YU_SELECT_DETAIL_CAPTURE_T_HPP_

#include <type_traits>

namespace yu::select::detail {

template <typename T>
using capture_t = std::conditional_t< //
    std::is_rvalue_reference_v<T>,    //
    std::remove_reference_t<T>,       //
    T                                 //
    >;                                //

} // namespace yu::select::detail

#endif