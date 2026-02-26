#ifndef YU_SELECT_DETAIL_SELECTION_CONSTRAINTS_HPP_
#define YU_SELECT_DETAIL_SELECTION_CONSTRAINTS_HPP_
#include "selectable_clauses.hpp"
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

namespace yu::select::detail {

template <typename Subject, typename ClauseTuple>
struct is_all_actions_result_void;

template <typename Subject, typename... Clauses>
struct is_all_actions_result_void<Subject, std::tuple<Clauses...>> {
        constexpr static bool value = std::conjunction_v<                       //
            std::is_void<typename Clauses::template action_result_t<Subject&&>> //
            ...                                                                 //
            >;                                                                  //
};

template <typename Subject, typename ClauseTuple>
struct is_none_actions_result_void;

template <typename Subject, typename... Clauses>
struct is_none_actions_result_void<Subject, std::tuple<Clauses...>> {
        constexpr static bool value = !std::disjunction_v<                      //
            std::is_void<typename Clauses::template action_result_t<Subject&&>> //
            ...                                                                 //
            >;                                                                  //
};

template <typename Subject, typename... Clauses>
struct selection_traits {
        using selectable_clauses = selectable_clauses_t<Subject, Clauses...>;

        constexpr static std::size_t selectable_clause_count = std::tuple_size_v<selectable_clauses>;

        constexpr static bool all_result_void  = is_all_actions_result_void<Subject, selectable_clauses>::value;
        constexpr static bool none_result_void = is_none_actions_result_void<Subject, selectable_clauses>::value;
};

} // namespace yu::select::detail

#endif