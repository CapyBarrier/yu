#ifndef YU_SELECT_CONDITIONS_DETAIL_EQUALS_T_HPP_
#define YU_SELECT_CONDITIONS_DETAIL_EQUALS_T_HPP_

#include <concepts>
#include <utility>
#include <yu/select/detail/capture_type.hpp>

namespace yu::select::conditions::detail {

template <typename Value>
class equals_t {
    public:
        template <typename T>
         explicit equals_t(T&& value) : value_(std::forward<T>(value)) {}

        template <typename Subject>
        requires std::equality_comparable_with<Value&&, Subject&>
        decltype(auto) operator()(Subject& subject) {
            return std::forward<Value>(value_) == subject;
        }

    private:
        using captured_value_t = yu::select::detail::capture_type_t<Value>;

        captured_value_t value_;
};

} // namespace yu::select::actions::detail

#endif