#ifndef YU_SELECT_DETAIL_PERFORM_SELECTION_HPP_
#define YU_SELECT_DETAIL_PERFORM_SELECTION_HPP_

#include "action_results.hpp"
#include "apply_result_policy.hpp"
#include "is_all_void.hpp"
#include "is_none_void.hpp"
#include "selectable_clause_count.hpp"
#include "selectable_clauses.hpp"
#include <cstddef>    // std::size_t
#include <functional> // std::reference_wrapper
#include <optional>
#include <type_traits>
#include <utility>

namespace yu::select::detail {

template <typename ResultPolicy, template <typename> typename OutcomePolicy, typename Subject, typename... Clauses>
auto perform_selection(Subject&& subject, Clauses&&... clauses) {
    using selectable_clauses = selectable_clauses_t<Subject, Clauses...>;
    using results_t          = action_results_t<Subject, selectable_clauses>;

    // Begin Validation

    constexpr std::size_t selectable_clause_count = selectable_clause_count_v<Subject, Clauses...>;
    static_assert(selectable_clause_count != 0, "At least one Clause must be Selectable for given Subject.");

    constexpr bool all_actions_void  = is_all_void_v<results_t>;
    constexpr bool none_actions_void = is_none_void_v<results_t>;
    static_assert(all_actions_void || none_actions_void, "All Actions of Selectable Clauses must either all return void, or all return non-void.");

    // End Validation

    using final_result_t = std::conditional_t<   //
        none_actions_void,                       //
        apply_result_policy<Subject, results_t>, //
        std::type_identity<void>                 //
        >::type;                                 //

    using noref_result_t = std::remove_reference_t<final_result_t>;

    using outcome_policy = OutcomePolicy<final_result_t>;

    if constexpr (std::is_void_v<final_result_t>) {
        bool succeeded = false;

        auto selector = [&succeeded, &subject]<typename Clause>(Clause&& clause) -> void {
            if (succeeded) return;

            using decayed_clause = std::decay_t<Clause>;

            if constexpr (decayed_clause::template has_evaluable_action_for<Subject&&>) {
                if (clause.evaluate_guard(subject)) {
                    std::forward<Clause>(clause).evaluate_action(std::forward<Subject>(subject));
                    succeeded = true;
                }
            }
        };

        (selector(std::forward<Clauses>(clauses)), ...);

        if (succeeded) return outcome_policy::success();
        else return outcome_policy::failure();

    } else if constexpr (std::is_lvalue_reference_v<final_result_t>) {
        bool succeeded = false;

        std::optional<std::reference_wrapper<noref_result_t>> result;

        auto selector = [&succeeded, &subject, &result]<typename Clause>(Clause&& clause) -> void {
            if (succeeded) return;

            using decayed_clause = std::decay_t<Clause>;

            if constexpr (decayed_clause::template has_evaluable_action_for<Subject&&>) {
                if (clause.evaluate_guard(subject)) {
                    result.emplace(std::forward<Clause>(clause).evaluate_action(std::forward<Subject>(subject)));
                    succeeded = true;
                }
            }
        };

        (selector(std::forward<Clauses>(clauses)), ...);

        if (succeeded) {
            // pass as lvalue reference
            // (std::reference_wrapper<T>::get() returns T&)
            return outcome_policy::success((*result).get());
        } else {
            return outcome_policy::failure();
        }

    } else { // when final_result_t is rvalue reference or non-reference
        bool succeeded = false;

        std::optional<noref_result_t> result;

        auto selector = [&succeeded, &subject, &result]<typename Clause>(Clause&& clause) -> void {
            if (succeeded) return;

            using decayed_clause = std::decay_t<Clause>;

            if constexpr (decayed_clause::template has_evaluable_action_for<Subject&&>) {
                if (clause.evaluate_guard(subject)) {
                    result.emplace(std::forward<Clause>(clause).evaluate_action(std::forward<Subject>(subject)));
                    succeeded = true;
                }
            }
        };

        (selector(std::forward<Clauses>(clauses)), ...);

        if (succeeded) {
            // pass as rvalue reference
            return outcome_policy::success(std::move((*result).get()));
        } else {
            return outcome_policy::failure();
        }
    }
}

} // namespace yu::select::detail

#endif