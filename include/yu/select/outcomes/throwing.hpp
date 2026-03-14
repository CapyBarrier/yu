#ifndef YU_SELECT_OUTCOMES_THROWING_HPP_
#define YU_SELECT_OUTCOMES_THROWING_HPP_

#include <yu/select/policy_tags/outcome_policy_tag.hpp>
#include <yu/select/select_error.hpp>
#include <utility>

namespace yu::select::outcomes {

struct throwing {
        using outcome_policy_tag = policy_tags::outcome_policy_tag;

        template <typename Result, typename T>
        constexpr Result success(T&& result) const {
            return std::forward<T>(result);
        }

        template <typename Result>
        requires std::is_void_v<Result>
        constexpr Result success() const {}

        template <typename Result>
        [[noreturn]]
        constexpr Result failure() const {
            throw select_error{"No clause was selected"};
        }
};

} // namespace yu::select::outcomes

#endif