#ifndef YU_INCLUDE_YU_SELECT_RESULTS_DETAIL_DEDUCE_COMMON_TYPE_HPP_
#define YU_INCLUDE_YU_SELECT_RESULTS_DETAIL_DEDUCE_COMMON_TYPE_HPP_

#include <type_traits>

namespace yu::select::results::detail {

template <typename... Ts>
struct deduce_common_type;

template <typename T>
struct deduce_common_type<T> {
        using type = T;
};

template <typename T, typename U>
struct deduce_common_type<T, U> {
        using type = decltype(true ? std::declval<T>() : std::declval<U>());
};

template <typename Head, typename Next, typename... Rest>
struct deduce_common_type<Head, Next, Rest...> {
        using type = deduce_common_type<typename deduce_common_type<Head, Next>::type, Rest...>;
};

template <typename... Ts>
using deduce_common_type_t = deduce_common_type<Ts...>::type;

} // namespace yu::select::results::detail

#endif