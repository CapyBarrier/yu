#ifndef YU_SELECT_SELECT_HPP_
#define YU_SELECT_SELECT_HPP_

#include "concepts/outcome_policy.hpp"
#include "concepts/result_policy.hpp"
#include "detail/selection_performer.hpp"
#include "outcomes/throwing.hpp"
#include "results/common_type.hpp"
#include <utility>

namespace yu::select {

template <                                                                  //
    concepts::result_policy  ResultPolicy  = results::common_type,          //
    concepts::outcome_policy OutcomePolicy = decltype(outcomes::throwing)&, //
    typename Subject                                                        //
    >                                                                       //
auto select(Subject&& subject, OutcomePolicy&& outcome_policy = outcomes::throwing) {
    return detail::selection_performer<ResultPolicy, OutcomePolicy, Subject>{
        std::forward<Subject>(subject),             //
        std::forward<OutcomePolicy>(outcome_policy) //
    };
}

} // namespace yu::select

#endif