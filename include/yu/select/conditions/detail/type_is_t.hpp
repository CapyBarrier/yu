#ifndef YU_SELECT_CONDITIONS_DETAIL_TYPE_IS_T_HPP_
#define YU_SELECT_CONDITIONS_DETAIL_TYPE_IS_T_HPP_

#include <type_traits>

namespace yu::select::conditions::detail {

template <typename T>
class type_is_t {
    public:
        template <typename Subject>
        decltype(auto) operator()(Subject&) {
            return std::is_same_v<std::remove_cvref_t<T>, std::remove_cvref_t<Subject>>;
        }
};

} // namespace yu::select::conditions::detail

#endif