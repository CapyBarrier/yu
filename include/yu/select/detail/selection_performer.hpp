#ifndef YU_SELECT_DETAIL_SELECTION_INVOKER_HPP_
#define YU_SELECT_DETAIL_SELECTION_INVOKER_HPP_

#include "action_results.hpp"
#include "apply_result_policy.hpp"
#include "capture_type.hpp"
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

template <typename ResultPolicy, template <typename> typename OutcomePolicy, typename Subject>
class selection_performer {
    public:
        template <typename T>
        explicit selection_performer(T&& subject) : subject_(std::forward<T>(subject)) {}

        template <typename... Clauses>
        auto operator()(Clauses&&... clauses) && {
            using selectable_clauses_t = selectable_clauses_t<Subject, Clauses...>;
            using action_results_t     = action_results_t<Subject, selectable_clauses_t>;

            // Begin Validations

            constexpr std::size_t selectable_clause_count = selectable_clause_count_v<Subject, Clauses...>;
            static_assert(selectable_clause_count != 0, "At least one Clause must be Selectable for given Subject.");

            constexpr bool all_actions_void  = is_all_void_v<action_results_t>;
            constexpr bool none_actions_void = is_none_void_v<action_results_t>;
            static_assert(all_actions_void || none_actions_void,
                          "All Actions of Selectable Clauses must either all return void, or all return non-void.");

            // End Validations

            using final_result_t = std::conditional_t<          //
                none_actions_void,                              //
                apply_result_policy<Subject, action_results_t>, //
                std::type_identity<void>                        //
                >::type;

            using noref_result_t = std::remove_reference_t<final_result_t>;

            using outcome_policy = OutcomePolicy<final_result_t>;

            if constexpr (std::is_void_v<final_result_t>) {
                bool succeeded = false;

                auto selector = [&succeeded, this]<typename Clause>(Clause&& clause) -> void {
                    if (succeeded) return;

                    using decayed_clause = std::decay_t<Clause>;

                    if constexpr (decayed_clause::template has_evaluable_action_for<Subject&&>) {
                        if (clause.evaluate_guard(subject_)) {
                            std::forward<Clause>(clause).evaluate_action(std::forward<Subject>(subject_));
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

                auto selector = [&succeeded, this, &result]<typename Clause>(Clause&& clause) -> void {
                    if (succeeded) return;

                    using decayed_clause = std::decay_t<Clause>;

                    if constexpr (decayed_clause::template has_evaluable_action_for<Subject&&>) {
                        if (clause.evaluate_guard(subject_)) {
                            result.emplace(std::forward<Clause>(clause).evaluate_action(std::forward<Subject>(subject_)));
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

                auto selector = [&succeeded, this, &result]<typename Clause>(Clause&& clause) -> void {
                    if (succeeded) return;

                    using decayed_clause = std::decay_t<Clause>;

                    if constexpr (decayed_clause::template has_evaluable_action_for<Subject&&>) {
                        if (clause.evaluate_guard(subject_)) {
                            result.emplace(std::forward<Clause>(clause).evaluate_action(std::forward<Subject>(subject_)));
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

        template <typename... Clauses>
        auto operator()(Clauses&&...) & = delete;

    private:
        using captured_subject_t = capture_type_t<Subject>;

        captured_subject_t subject_;

        selection_performer(const selection_performer&) = delete;
        selection_performer(selection_performer&&)      = default;

        selection_performer& operator=(const selection_performer&) = delete;
        selection_performer& operator=(selection_performer&&)      = delete;
};

} // namespace yu::select::detail

#endif
