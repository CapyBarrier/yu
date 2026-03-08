#ifndef YU_SELECT_SELECT_HPP_
#define YU_SELECT_SELECT_HPP_

#include "detail/selection_performer.hpp"
#include "outcomes/throwing.hpp"
#include "results/common_type.hpp"
#include <utility>

namespace yu::select {

template <                                                  //
    typename ResultPolicy  = results::common_type,          //
    typename OutcomePolicy = decltype(outcomes::throwing)&, //
    typename Subject                                        //
    >                                                       //
auto select(Subject&& subject, OutcomePolicy&& outcome_policy = outcomes::throwing) {
    return detail::selection_performer<ResultPolicy, OutcomePolicy, Subject>{
        std::forward<Subject>(subject),             //
        std::forward<OutcomePolicy>(outcome_policy) //
    };
}

} // namespace yu::select

#endif