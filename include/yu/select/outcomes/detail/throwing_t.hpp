#ifndef YU_INCLUDE_YU_SELECT_OUTCOMES_DETAIL_THROWING_T_HPP_
#define YU_INCLUDE_YU_SELECT_OUTCOMES_DETAIL_THROWING_T_HPP_

#include <utility>
#include <yu/select/select_error.hpp>

namespace yu::select::outcomes::detail {

struct throwing_t {
        template <typename Result, typename T>
        Result success(T&& result) const {
            return std::forward<T>(result);
        }

        template <typename Result>
        requires std::is_void_v<Result>
        Result success() const {}

        template <typename Result>
        [[noreturn]] Result failure() const {
            throw select_error{"No clause was selected"};
        }
};

} // namespace yu::select::outcomes::detail

#endif