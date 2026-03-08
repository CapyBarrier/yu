#ifndef YU_INCLUDE_YU_SELECT_OUTCOMES_DETAIL_OPTIONAL_T_HPP_
#define YU_INCLUDE_YU_SELECT_OUTCOMES_DETAIL_OPTIONAL_T_HPP_

#include <functional> // std::reference_wrapper
#include <optional>
#include <type_traits>
#include <utility>
#include <variant> // std::monostate

namespace yu::select::outcomes::detail {

struct optional_t {
        template <typename Result, typename T>
        auto success(T&& result) const {
            if constexpr (std::is_lvalue_reference_v<Result>) {
                using value_t = std::reference_wrapper<std::remove_reference_t<Result>>;
                return std::optional<value_t>{std::forward<T>(result)};
            } else if constexpr (std::is_rvalue_reference_v<Result>) {
                using value_t = std::remove_reference_t<Result>;
                return std::optional<value_t>{std::forward<T>(result)};
            } else {
                using value_t = Result;
                return std::optional<value_t>{std::forward<T>(result)};
            }
        }

        template <typename Result>
        requires std::is_void_v<Result>
        auto success() const {
            using value_t = std::monostate;
            return std::optional<value_t>{std::monostate{}};
        }

        template <typename Result>
        auto failure() const {
            if constexpr (std::is_lvalue_reference_v<Result>) {
                using value_t = std::reference_wrapper<std::remove_reference_t<Result>>;
                return std::optional<value_t>{std::nullopt};
            } else if constexpr (std::is_rvalue_reference_v<Result>) {
                using value_t = std::remove_reference_t<Result>;
                return std::optional<value_t>{std::nullopt};
            } else {
                using value_t = Result;
                return std::optional<value_t>{std::nullopt};
            }
        }

        template <typename Result>
        requires std::is_void_v<Result>
        auto failure() const {
            using value_t = std::monostate;
            return std::optional<value_t>{std::nullopt};
        }
};

} // namespace yu::select::outcomes::detail

#endif