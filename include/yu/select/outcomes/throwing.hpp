#ifndef YU_INCLUDE_YU_SELECT_OUTCOMES_THROWING_HPP_
#define YU_INCLUDE_YU_SELECT_OUTCOMES_THROWING_HPP_

#include <yu/select/policy_tags/outcome_policy_tag.hpp>
#include <yu/select/select_error.hpp>
#include <utility>

namespace yu::select::outcomes {

struct throwing {
        using outcome_policy_tag = policy_tags::outcome_policy_tag;

        template <typename Result, typename T>
        Result success(T&& result) const {
            return std::forward<T>(result);
        }

        template <typename Result>
        requires std::is_void_v<Result>
        Result success() const {}

        template <typename Result>
        [[noreturn]]
        Result failure() const {
            throw select_error{"No clause was selected"};
        }
};

} // namespace yu::select::outcomes

#endif