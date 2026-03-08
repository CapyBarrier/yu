#ifndef YU_INCLUDE_YU_SELECT_DETAIL_APPLICABLE_OUTCOME_POLICY_HPP_
#define YU_INCLUDE_YU_SELECT_DETAIL_APPLICABLE_OUTCOME_POLICY_HPP_

#include <type_traits>
#include <utility>

namespace yu::select::detail {

template <typename T, typename FinalResult>
consteval bool is_applicable_outcome_policy() {
    if constexpr (std::is_void_v<FinalResult>) {
        bool result = requires(T& outcome_policy) {
            outcome_policy.template success<FinalResult>();
            outcome_policy.template failure<FinalResult>();
        };
        return result;
    } else {
        bool result = requires(T& outcome_policy, FinalResult&& result) {
            outcome_policy.template success<FinalResult>(std::forward<FinalResult>(result));
            outcome_policy.template failure<FinalResult>();
        };
        return result;
    }
}

template <typename T, typename FinalResult>
concept applicable_outcome_policy = is_applicable_outcome_policy<T, FinalResult>();

} // namespace yu::select::detail

#endif