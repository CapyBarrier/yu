#ifndef YU_SELECT_DETAIL_PERFORM_SELECTION_HPP_
#define YU_SELECT_DETAIL_PERFORM_SELECTION_HPP_

#include "compute_result_type.hpp"
#include "selection_traits.hpp"
#include <cstddef>
#include <functional>
#include <optional>
#include <type_traits>
#include <utility>
#include <variant> // std::monostate

namespace yu::select::detail {

template <typename ResultPolicy, template <typename> typename OutcomePolicy, typename Subject, typename... Clauses>
auto perform_selection(Subject&& subject, Clauses&&... clauses) {
    using traits = selection_traits<Subject, Clauses...>;

    constexpr std::size_t selectable_clause_count = traits::selectable_clause_count;
    static_assert(selectable_clause_count != 0);

    constexpr bool all_result_void  = traits::all_result_void;
    constexpr bool none_result_void = traits::none_result_void;
    static_assert(all_result_void || none_result_void);

    using selectable_clauses = traits::selectable_clauses;

    using result_t = std::conditional_t<                                  //
        none_result_void,                                                 //
        compute_result_type_t<ResultPolicy, Subject, selectable_clauses>, //
        void                                                              //
        >;                                                                //

    constexpr bool is_result_lvalue = std::is_lvalue_reference_v<result_t>;
    constexpr bool is_result_void   = std::is_void_v<result_t>;

    using captured_result_t = std::conditional_t< //
        is_result_lvalue,                         //
        std::reference_wrapper<result_t>,         //
        std::remove_reference_t<result_t>         //
        >;                                        //

    using result_storage_t = std::conditional_t< //
        is_result_void,                          //
        std::monostate,                          //
        captured_result_t                        //
        >;                                       //

    std::optional<result_storage_t> result;

    bool succeeded = false;

    auto selector = [&succeeded, &subject, &result]<typename Clause>(Clause&& clause) -> void {
        using decayed_clause = std::decay_t<Clause>;

        if (succeeded) return;

        if constexpr (decayed_clause::template has_evaluable_action_for<Subject&&>) {
            if (clause.evaluate_guard(subject)) {
                if constexpr (is_result_void) {
                    std::forward<Clause>(clause).evaluate_action(std::forward<Subject>(subject));
                } else if constexpr (is_result_lvalue) {
                    result.emplace(std::forward<Clause>(clause).evaluate_action(std::forward<Subject>(subject)));
                } else {
                    result = std::forward<Clause>(clause).evaluate_action(std::forward<Subject>(subject));
                }

                succeeded = true;
            }
        }
    };

    (selector(std::forward<Clauses>(clauses)), ...);

    using outcome_policy = OutcomePolicy<result_t>;

    if (succeeded) {
        if constexpr (is_result_void) {
            return outcome_policy::success();
        } else if constexpr (is_result_lvalue) {
            return outcome_policy::success(std::move(*result).get());
        } else {
            return outcome_policy::success(std::move(*result));
        }
    } else {
        return outcome_policy::failure();
    }
}

} // namespace yu::select::detail

#endif