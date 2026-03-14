#ifndef YU_SELECT_DETAIL_CONCEPTS_CLAUSE_TYPE_HPP_
#define YU_SELECT_DETAIL_CONCEPTS_CLAUSE_TYPE_HPP_

#include <yu/select/detail/clause.hpp>
#include <type_traits>

namespace yu::select::detail::concepts {

template <typename T>
struct is_clause_type_impl : std::false_type {};

template <typename Guard, typename Action>
struct is_clause_type_impl<clause<Guard, Action>> : std::true_type {};

template <typename T>
struct is_clause_type : is_clause_type_impl<std::remove_cvref_t<T>> {};

template <typename T>
concept clause_type = is_clause_type<T>::value;

} // namespace yu::select::detail::concepts

#endif