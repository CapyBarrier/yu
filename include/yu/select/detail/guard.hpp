#ifndef YU_SELECT_DETAIL_GUARD_HPP_
#define YU_SELECT_DETAIL_GUARD_HPP_

#include "clause.hpp"
#include "concepts/condition_for.hpp"
#include "meta/capture_type.hpp"
#include <concepts>
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

namespace yu::select::detail {

template <typename... Conditions>
class guard {
    public:
        template <typename... Ts>
        constexpr explicit guard(Ts&&... conditions) :
            conditions_(std::forward<Ts>(conditions)...) {}

        template <typename Subject>
        constexpr bool evaluate(Subject& subject) {
            if constexpr (sizeof...(Conditions) == 0) {
                return true;
            } else {
                auto evaluator = [&subject]<typename Condition>(Condition& condition) -> bool {
                    static_assert(
                        concepts::condition_for<Condition, Subject>,
                        "Condition must be invocable on a Subject and return a type convertible to bool"
                    );

                    return std::invoke(condition, subject);
                };

                return std::apply(
                    [&evaluator](auto&... conditions) { return (... && evaluator(conditions)); },
                    conditions_
                );
            }
        }

        template <typename Action>
        constexpr auto operator|=(Action&& action) {
            return clause<guard, Action>{std::move(*this), std::forward<Action>(action)};
        }

    private:
        using captured_conditions_t = std::tuple<meta::capture_type_t<Conditions>...>;

        captured_conditions_t conditions_;
};

} // namespace yu::select::detail

#endif