#ifndef YU_INCLUDE_YU_SELECT_DETAIL_APPLICABLE_RESULT_POLICY_HPP_
#define YU_INCLUDE_YU_SELECT_DETAIL_APPLICABLE_RESULT_POLICY_HPP_

#include "apply_result_policy.hpp"
#include <concepts>
#include <functional>
#include <tuple>
#include <type_traits>

namespace yu::select::detail {

template <typename FinalResult, typename ResultsTuple>
struct is_constructible_from_each_results : std::false_type {};

template <typename FinalResult, typename... Results>
struct is_constructible_from_each_results<FinalResult, std::tuple<Results...>> {
        static consteval bool test() {
            if constexpr (std::is_void_v<FinalResult>) {
                return true;
            }
            if constexpr (std::is_lvalue_reference_v<FinalResult>) {
                using noref_result_t = std::remove_reference_t<FinalResult>;
                return (true && ... && std::constructible_from<std::reference_wrapper<noref_result_t>, Results>);
            } else {
                return (true && ... && std::constructible_from<FinalResult, Results>);
            }
        }

        static constexpr bool value = test();
};

template <typename T, typename ResultsTuple>
concept applicable_result_policy = requires {
    typename apply_result_policy_t<T, ResultsTuple>;
    requires is_constructible_from_each_results<apply_result_policy_t<T, ResultsTuple>, ResultsTuple>::value;
};

} // namespace yu::select::detail

#endif