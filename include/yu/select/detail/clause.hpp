#ifndef YU_SELECT_DETAIL_CLAUSE_HPP_
#define YU_SELECT_DETAIL_CLAUSE_HPP_

#include "concepts/action_for.hpp"
#include "meta/capture_type.hpp"
#include <concepts>
#include <functional>
#include <type_traits>
#include <utility>

namespace yu::select::detail {

template <typename Guard, typename Action>
class clause {
    public:
        template <typename T, typename U>
        clause(T&& guard, U&& action) :
            guard_(std::forward<T>(guard)), action_(std::forward<U>(action)) {}

        template <typename Subject>
        bool evaluate_guard(Subject& subject) {
            return guard_.evaluate(subject);
        }

        template <typename Subject>
        decltype(auto) evaluate_action(Subject&& subject) {
            if constexpr (std::invocable<Action&&, Subject&&>) {
                return std::invoke(std::forward<Action>(action_), std::forward<Subject>(subject));
            } else if constexpr (std::invocable<Action&&>) {
                return std::invoke(std::forward<Action>(action_));
            }
        }

        template <typename Subject>
        static constexpr bool has_evaluable_action_for = concepts::action_for<Action, Subject>;

        template <typename Subject>
        using action_result_t = std::conditional_t<
            std::invocable<Action&&, Subject>,
            std::invoke_result<Action&&, Subject>,
            std::invoke_result<Action>
        >::type;

    private:
        using guard_t = std::remove_reference_t<Guard>;

        using captured_action_t = meta::capture_type_t<Action>;

        guard_t           guard_;
        captured_action_t action_;
};

} // namespace yu::select::detail

#endif