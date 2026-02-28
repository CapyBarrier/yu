#ifndef YU_SELECT_ACTIONS_DETAIL_VALUE_T_HPP_
#define YU_SELECT_ACTIONS_DETAIL_VALUE_T_HPP_

#include <utility>
#include <yu/select/detail/capture_type.hpp>

namespace yu::select::actions::detail {

template <typename Value>
class value_t {
    public:
        template <typename T>
        explicit value_t(T&& value) : value_(std::forward<T>(value)) {}

        decltype(auto) operator()() { return std::forward<Value>(value_); }

    private:
        using captured_value_t = yu::select::detail::capture_type_t<Value>;

        captured_value_t value_;
};

} // namespace yu::select::actions::detail

#endif