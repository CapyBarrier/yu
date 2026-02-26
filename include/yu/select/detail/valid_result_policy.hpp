#ifndef YU_SELECT_DETAIL_VALID_RESULT_POLICY_HPP_
#define YU_SELECT_DETAIL_VALID_RESULT_POLICY_HPP_

namespace yu::select::detail {

template <typename T, typename... Results>
concept valid_result_policy = requires { typename T::template result_type<Results...>; };

} // namespace yu::select::detail

#endif