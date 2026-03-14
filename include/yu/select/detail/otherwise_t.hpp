#ifndef YU_SELECT_DETAIL_OTHERWISE_T_HPP_
#define YU_SELECT_DETAIL_OTHERWISE_T_HPP_

#include "clause.hpp"
#include "guard.hpp"

namespace yu::select::detail {

class otherwise_t {
    public:
        template <typename Action>
        constexpr auto operator|=(Action&& action) const {
            return clause<guard<>, Action>{guard<>{}, std::forward<Action>(action)};
        }
};

} // namespace yu::select::detail

#endif