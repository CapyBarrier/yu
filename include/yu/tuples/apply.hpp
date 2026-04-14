#ifndef YU_TUPLES_APPLY_HPP_
#define YU_TUPLES_APPLY_HPP_

#include "apply_result.hpp"
#include "is_nothrow_applicable.hpp"
#include "tuple.hpp"
#include "yu/tuples/get.hpp"
#include "yu/tuples/index_sequence_for.hpp"
#include <cstddef>
#include <functional>
#include <utility>

namespace yu::tuples {

namespace _detail::apply {

template <typename F, typename T, std::size_t... Idx>
constexpr decltype(auto) impl(F&& fn, T&& t, std::index_sequence<Idx...>) {
    return std::invoke(std::forward<F>(fn), tuples::get<Idx>(std::forward<T>(t))...);
}

} // namespace _detail::apply

namespace _unspecified::apply {

struct fn {
    public:
        template <typename F, tuple T>
        static constexpr apply_result_t<F, T> operator()(F&& fn, T&& t) noexcept(is_nothrow_applicable_v<F, T>) {
            return _detail::apply::impl(std::forward<F>(fn), std::forward<T>(t), tuples::index_sequence_for<T>{});
        }
};

} // namespace _unspecified::apply

inline namespace _fn {

inline constexpr _unspecified::apply::fn apply{};

}

} // namespace yu::tuples

#endif