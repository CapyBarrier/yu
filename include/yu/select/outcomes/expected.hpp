#ifndef YU_INCLUDE_YU_SELECT_OUTCOMES_EXPECTED_HPP_
#define YU_INCLUDE_YU_SELECT_OUTCOMES_EXPECTED_HPP_

#include <yu/select/detail/meta/capture_type.hpp>
#include <yu/select/policy_tags/outcome_policy_tag.hpp>
#include <functional> // std::reference_wrapper
#include <type_traits>
#include <utility>
#include <expected>

namespace yu::select::outcomes {

template <typename Error>
struct expected {
    public:
        using outcome_policy_tag = policy_tags::outcome_policy_tag;

        template <typename T>
        explicit expected(T&& error) :
            error_(std::forward<T>(error)) {}

        template <typename Result, typename T>
        auto success(T&& result) const {
            if constexpr (std::is_lvalue_reference_v<Result>) {
                using value_t = std::reference_wrapper<std::remove_reference_t<Result>>;
                return std::expected<value_t, Error>{std::forward<T>(result)};
            } else if constexpr (std::is_rvalue_reference_v<Result>) {
                using value_t = std::remove_reference_t<Result>;
                return std::expected<value_t, Error>{std::forward<T>(result)};
            } else {
                using value_t = Result;
                return std::expected<value_t, Error>{std::forward<T>(result)};
            }
        }

        template <typename Result>
        requires std::is_void_v<Result>
        auto success() const {
            using value_t = Result;
            return std::expected<value_t, Error>{};
        }

        template <typename Result>
        auto failure() const {
            if constexpr (std::is_lvalue_reference_v<Result>) {
                using value_t = std::reference_wrapper<std::remove_reference_t<Result>>;
                return std::expected<value_t, Error>{std::unexpected{std::forward<Error>(error_)}};
            } else if constexpr (std::is_rvalue_reference_v<Result>) {
                using value_t = std::remove_reference_t<Result>;
                return std::expected<value_t, Error>{std::unexpected{std::forward<Error>(error_)}};
            } else {
                using value_t = Result;
                return std::expected<value_t, Error>{std::unexpected{std::forward<Error>(error_)}};
            }
        }

        template <typename Result>
        requires std::is_void_v<Result>
        auto failure() const {
            using value_t = Result;
            return std::expected<value_t, Error>{std::unexpected{std::forward<Error>(error_)}};
        }

    private:
        using captured_error_t = yu::select::detail::meta::capture_type_t<Error>;

        captured_error_t error_;
};

} // namespace yu::select::outcomes

#endif