#ifndef YU_INCLUDE_YU_SELECT_OUTCOMES_EXPECTED_HPP_
#define YU_INCLUDE_YU_SELECT_OUTCOMES_EXPECTED_HPP_

#include "detail/expected_t.hpp"
#include <utility>

namespace yu::select::outcomes {

template <typename Error>
auto expected(Error&& error) {
    return detail::expected_t<Error>{std::forward<Error>(error)};
}

} // namespace yu::select::outcomes

#endif