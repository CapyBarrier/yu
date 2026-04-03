#ifndef YU_TUPLES_GET_HPP_
#define YU_TUPLES_GET_HPP_

#include "_detail/bounded_array.hpp"
#include "_detail/sized.hpp"
#include <cstddef>
#include <utility>

namespace yu::tuples {

namespace _unspecified::get {

// Poison Pill
template <std::size_t>
void get() = delete;

} // namespace _unspecified::get

namespace _detail::get {

template <typename T, std::size_t Idx>
concept within_size_range = sized<T> && (Idx < size_v<T>);

template <typename T, std::size_t Idx>
concept array_gettable_at = within_size_range<T, Idx> && bounded_array<T>;

template <typename T, std::size_t Idx>
concept member_gettable_at
    = within_size_range<T, Idx> && !bounded_array<T> && requires(T&& t) { std::forward<T>(t).template get<Idx>(); };

using _unspecified::get::get;

template <typename T, std::size_t Idx>
concept unqualified_gettable_at
    = within_size_range<T, Idx> && !member_gettable_at<T, Idx> && requires(T&& t) { get<Idx>(std::forward<T>(t)); };

} // namespace _detail::get

namespace _unspecified::get {

template <std::size_t Idx>
struct fn {
        template <typename T>
        requires _detail::get::array_gettable_at<T, Idx>
        [[nodiscard]]
        static constexpr decltype(auto) operator()(T&& array) noexcept {
            return std::forward<T>(array)[Idx];
        }

        template <typename T>
        requires _detail::get::member_gettable_at<T, Idx>
        [[nodiscard]]
        static constexpr decltype(auto) operator()(T&& t) noexcept(noexcept(std::forward<T>(t).template get<Idx>())) {
            return std::forward<T>(t).template get<Idx>();
        }

        template <typename T>
        requires _detail::get::unqualified_gettable_at<T, Idx>
        [[nodiscard]]
        static constexpr decltype(auto) operator()(T&& t) noexcept(noexcept(get<Idx>(std::forward<T>(t)))) {
            return get<Idx>(std::forward<T>(t));
        }
};

} // namespace _unspecified::get

inline namespace _cpo {

template <std::size_t Idx>
inline constexpr _unspecified::get::fn<Idx> get{};

}

} // namespace yu::tuples

#endif