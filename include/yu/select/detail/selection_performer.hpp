#ifndef YU_SELECT_DETAIL_SELECTION_INVOKER_HPP_
#define YU_SELECT_DETAIL_SELECTION_INVOKER_HPP_

#include "concepts/applicable_outcome_policy.hpp"
#include "concepts/applicable_result_policy.hpp"
#include "concepts/clause_type.hpp"
#include "meta/action_results.hpp"
#include "meta/apply_result_policy.hpp"
#include "meta/capture_type.hpp"
#include "meta/is_all_void.hpp"
#include "meta/is_none_void.hpp"
#include "meta/selectable_clause_count.hpp"
#include "meta/selectable_clauses.hpp"
#include <cstddef>    // std::size_t
#include <functional> // std::reference_wrapper
#include <optional>
#include <type_traits>
#include <utility>

namespace yu::select::detail {

template <typename ResultPolicy, typename OutcomePolicy, typename Subject>
class selection_performer {
    public:
        template <typename T, typename U>
        constexpr explicit selection_performer(T&& subject, U&& outcome_policy) :
            subject_(std::forward<T>(subject)), outcome_policy_(std::forward<U>(outcome_policy)) {}

        template <concepts::clause_type... Clauses>
        constexpr decltype(auto) operator()(Clauses&&... clauses) && {
            using selectable_clauses_t = meta::selectable_clauses_t<Subject, Clauses...>;
            using action_results_t     = meta::action_results_t<Subject, selectable_clauses_t>;

            // Begin Validations

            constexpr std::size_t selectable_clause_count = meta::selectable_clause_count_v<Subject, Clauses...>;
            static_assert(selectable_clause_count != 0, "At least one Clause must be Selectable for given Subject.");

            constexpr bool all_actions_void  = meta::is_all_void_v<action_results_t>;
            constexpr bool none_actions_void = meta::is_none_void_v<action_results_t>;
            static_assert(
                all_actions_void || none_actions_void,
                "All Actions of Selectable Clauses must either all return void, or all return non-void."
            );

            if constexpr (none_actions_void) {
                constexpr bool result_policy_applicable =
                    concepts::applicable_result_policy<ResultPolicy, action_results_t>;
                static_assert(
                    result_policy_applicable,
                    "ResultPolicy must be applicable to the return types of the all Actions of the Selectable Clauses."
                );
            }

            using final_result_t = std::conditional_t<
                none_actions_void,
                meta::apply_result_policy<ResultPolicy, action_results_t>,
                std::type_identity<void>
            >::type;

            constexpr bool outcome_policy_applicable =
                concepts::applicable_outcome_policy<OutcomePolicy, final_result_t>;
            static_assert(
                outcome_policy_applicable,
                "OutcomePolicy must be applicable to the result type determined by ResultPolicy"
            );

            // End Validations

            bool succeeded = false;

            auto selector = [&succeeded, this]<typename Clause>(Clause&& clause, auto& on_selected) {
                if (succeeded) return;

                using decayed_clause = std::decay_t<Clause>;

                if constexpr (decayed_clause::template has_evaluable_action_for<Subject&&>) {
                    if (clause.evaluate_guard(subject_)) {
                        on_selected(std::forward<Clause>(clause));
                        succeeded = true;
                    }
                }
            };

            auto eval_selector = [&selector]<typename... Cs>(auto& on_selected, Cs&&... cs) {
                (selector(std::forward<Cs>(cs), on_selected), ...);
            };

            if constexpr (std::is_void_v<final_result_t>) {
                auto on_selected = [this]<typename Clause>(Clause&& clause) {
                    // discard the result
                    void(std::forward<Clause>(clause).evaluate_action(std::forward<Subject>(subject_)));
                };

                eval_selector(on_selected, std::forward<Clauses>(clauses)...);

                if (succeeded) {
                    return outcome_policy_.template success<final_result_t>();
                } else {
                    return outcome_policy_.template failure<final_result_t>();
                }
            } else if constexpr (std::is_lvalue_reference_v<final_result_t>) {
                using noref_result_t = std::remove_reference_t<final_result_t>;

                std::optional<std::reference_wrapper<noref_result_t>> result;

                auto on_selected = [&result, this]<typename Clause>(Clause&& clause) {
                    result.emplace(std::forward<Clause>(clause).evaluate_action(std::forward<Subject>(subject_)));
                };

                eval_selector(on_selected, std::forward<Clauses>(clauses)...);

                if (succeeded) {
                    // pass as lvalue reference
                    // (std::reference_wrapper<T>::get() returns T&. T& must equals final_result_t)
                    return outcome_policy_.template success<final_result_t>(result->get());
                } else {
                    return outcome_policy_.template failure<final_result_t>();
                }
            } else {
                using noref_result_t = std::remove_reference_t<final_result_t>;

                std::optional<noref_result_t> result;

                auto on_selected = [&result, this]<typename Clause>(Clause&& clause) {
                    result.emplace(std::forward<Clause>(clause).evaluate_action(std::forward<Subject>(subject_)));
                };

                eval_selector(on_selected, std::forward<Clauses>(clauses)...);

                if (succeeded) {
                    // pass as rvalue reference
                    return outcome_policy_.template success<final_result_t>(std::move(*result));
                } else {
                    return outcome_policy_.template failure<final_result_t>();
                }
            }
        }

        template <typename... Clauses>
        decltype(auto) operator()(Clauses&&...) & = delete;

    private:
        using captured_subject_t = meta::capture_type_t<Subject>;
        using outcome_policy_t   = std::decay_t<OutcomePolicy>;

        captured_subject_t subject_;
        outcome_policy_t   outcome_policy_;

        selection_performer(const selection_performer&) = delete;
        selection_performer(selection_performer&&)      = default;

        selection_performer& operator=(const selection_performer&) = delete;
        selection_performer& operator=(selection_performer&&)      = delete;
};

} // namespace yu::select::detail

#endif
