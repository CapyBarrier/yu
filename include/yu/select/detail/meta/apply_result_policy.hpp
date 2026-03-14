#ifndef YU_SELECT_DETAIL_META_APPLY_RESULT_POLICY_HPP_
#define YU_SELECT_DETAIL_META_APPLY_RESULT_POLICY_HPP_

#include <tuple>

namespace yu::select::detail::meta {

template <typename ResultPolicy, typename ResultsTuple>
struct apply_result_policy;

template <typename ResultPolicy, typename... Results>
struct apply_result_policy<ResultPolicy, std::tuple<Results...>> {
        using type = ResultPolicy::template result_type<Results...>;
};

template <typename ResultPolicy, typename ResultsTuple>
using apply_result_policy_t = apply_result_policy<ResultPolicy, ResultsTuple>::type;

} // namespace yu::select::detail::meta

#endif