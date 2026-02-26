#ifndef YU_INCLUDE_YU_SELECT_OUTCOMES_THROWING_HPP_
#define YU_INCLUDE_YU_SELECT_OUTCOMES_THROWING_HPP_

#include <yu/select/select_error.hpp>

namespace yu::select::outcomes {

template <typename Result>
struct throwing {
        template <typename T>
        static Result success(T&& result) {
            return std::forward<T>(result);
        }

        static void success() {}

        [[noreturn]] static void failure() { throw select_error{"no clause was selected."}; }
};

} // namespace yu::select::outcomes

#endif