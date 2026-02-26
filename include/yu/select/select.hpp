#ifndef YU_SELECT_SELECT_HPP_
#define YU_SELECT_SELECT_HPP_

#include "detail/selection_invoker.hpp"
#include "outcomes/throwing.hpp"
#include "results/common_type.hpp"
#include <utility>

namespace yu::select {

template <                                                             //
    typename ResultPolicy                      = results::common_type, //
    template <typename> typename OutcomePolicy = outcomes::throwing,   //
    typename Subject                                                   //
    >                                                                  //
auto select(Subject&& subject) {
    return detail::selection_invoker<ResultPolicy, OutcomePolicy, Subject>{std::forward<Subject>(subject)};
}

} // namespace yu::select

#endif