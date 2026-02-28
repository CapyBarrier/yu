#ifndef YU_INCLUDE_YU_SELECT_DETAIL_ACTION_RESULTS_HPP_
#define YU_INCLUDE_YU_SELECT_DETAIL_ACTION_RESULTS_HPP_

#include <tuple>

namespace yu::select::detail {

template <typename Subject, typename ClausesTuple>
struct action_results;

template <typename Subject, typename... Clauses>
struct action_results<Subject, std::tuple<Clauses...>> {
        using type = std::tuple<typename Clauses::template action_result_t<Subject&&>...>;
};

template <typename Subject, typename ClausesTuple>
using action_results_t = action_results<Subject, ClausesTuple>::type;

} // namespace yu::select::detail

#endif