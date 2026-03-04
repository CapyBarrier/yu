#ifndef YU_SELECT_DETAIL_WHERE_T_HPP_
#define YU_SELECT_DETAIL_WHERE_T_HPP_

#include "guard.hpp"

namespace yu::select::detail {

struct where_t {
        template <typename... Conditions>
        auto operator()(Conditions&&... conditions) const {
            return guard<Conditions...>{std::forward<Conditions>(conditions)...};
        }
};

} // namespace yu::select::detail

#endif