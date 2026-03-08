#ifndef YU_SELECT_DETAIL_GUARD_HPP_
#define YU_SELECT_DETAIL_GUARD_HPP_

#include "capture_type.hpp"
#include "clause.hpp"
#include "condition_for.hpp"
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
        explicit guard(Ts&&... conditions) :
            conditions_(std::forward<Ts>(conditions)...) {}

        template <typename Subject>
        bool evaluate(Subject& subject) {
            if constexpr (sizeof...(Conditions) == 0) {
                return true;
            } else {
                auto evaluator = [&]<typename Condition>(Condition& condition) -> bool {
                    static_assert(
                        condition_for<Condition, Subject>,
                        "Condition must be a predicate or equality comparable with Subject"
                    );

                    if constexpr (std::predicate<Condition&, Subject&>) {
                        return std::invoke(condition, subject);
                    } else if constexpr (std::equality_comparable_with<Condition&, Subject&>) {
                        return subject == condition;
                    }
                };

                return std::apply(
                    [&evaluator](auto&... conditions) {
                        return (true && ... && evaluator(conditions));
                    },
                    conditions_
                );
            }
        }

        template <typename Action>
        auto operator|=(Action&& action) {
            return clause<guard, Action>{std::move(*this), std::forward<Action>(action)};
        }

    private:
        using captured_conditions_t = std::tuple<capture_type_t<Conditions>...>;

        captured_conditions_t conditions_;
};

} // namespace yu::select::detail

#endif