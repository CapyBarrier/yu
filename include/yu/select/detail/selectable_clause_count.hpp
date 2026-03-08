#ifndef YU_INCLUDE_YU_SELECT_DETAIL_SELECTABLE_CLAUSE_COUNT_HPP_
#define YU_INCLUDE_YU_SELECT_DETAIL_SELECTABLE_CLAUSE_COUNT_HPP_

#include <cstddef> // std::size_t
#include <type_traits>

namespace yu::select::detail {

template <typename Subject, typename... Clauses>
struct selectable_clause_count :
    std::integral_constant<
        std::size_t,
        (0uz + ... + std::size_t{Clauses::template has_evaluable_action_for<Subject>})
    > {};

template <typename Subject, typename... Clauses>
inline constexpr std::size_t selectable_clause_count_v =
    selectable_clause_count<Subject, Clauses...>::value;

} // namespace yu::select::detail

#endif