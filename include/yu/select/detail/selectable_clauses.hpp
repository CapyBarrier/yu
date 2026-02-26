#ifndef YU_SELECT_DETAIL_SELECTABLE_CLAUSES_HPP_
#define YU_SELECT_DETAIL_SELECTABLE_CLAUSES_HPP_

#include <tuple>
#include <type_traits>

namespace yu::select::detail {

template <typename T, typename Tuple>
struct prepend_tuple;

template <typename T, typename... Elems>
struct prepend_tuple<T, std::tuple<Elems...>> {
        using type = std::tuple<T, Elems...>;
};

template <typename T, typename Tuple>
using prepend_tuple_t = prepend_tuple<T, Tuple>::type;

template <typename Subject, typename... Clauses>
struct selectable_clauses;

template <typename Subject, typename Clause>
struct selectable_clauses<Subject, Clause> {
        using type = std::conditional_t< //
            Clause::template has_evaluable_action_for<Subject>,
            std::tuple<Clause>, //
            std::tuple<>        //
            >;                  //
};

template <typename Subject, typename HeadClause, typename... RestClauses>
struct selectable_clauses<Subject, HeadClause, RestClauses...> {
    private:
        using rest = selectable_clauses<Subject, RestClauses...>::type;

    public:
        using type = std::conditional_t<                            //
            HeadClause::template has_evaluable_action_for<Subject>, //
            prepend_tuple_t<HeadClause, rest>,                      //
            rest                                                    //
            >;                                                      //
};

template <typename Subject, typename... Clauses>
using selectable_clauses_t = selectable_clauses<Subject, Clauses...>::type;

} // namespace yu::select::detail

#endif