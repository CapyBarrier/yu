#ifndef YU_SELECT_DETAIL_COMPUTE_RESULT_POLICY_HPP_
#define YU_SELECT_DETAIL_COMPUTE_RESULT_POLICY_HPP_

#include "valid_result_policy.hpp"
#include <tuple>

namespace yu::select::detail {

template <typename ResultPolicy, typename Subject, typename ClauseTuple>
struct compute_result_type;

template <typename ResultPolicy, typename Subject, typename... Clauses>
requires valid_result_policy<ResultPolicy, typename Clauses::template action_result_t<Subject&&>...>
struct compute_result_type<ResultPolicy, Subject, std::tuple<Clauses...>> {
        using type = ResultPolicy::template result_type<typename Clauses::template action_result_t<Subject&&>...>;
};

template <typename ResultPolicy, typename Subject, typename ClauseTuple>
using compute_result_type_t = compute_result_type<ResultPolicy, Subject, ClauseTuple>::type;

} // namespace yu::select::detail

#endif