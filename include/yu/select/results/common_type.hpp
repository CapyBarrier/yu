#ifndef YU_SELECT_RESULTS_COMMON_TYPE_HPP_
#define YU_SELECT_RESULTS_COMMON_TYPE_HPP_

#include <type_traits>

namespace yu::select::results {

struct common_type {
        template <typename... ActionResults>
        using result_type = std::common_type_t<ActionResults...>;
};

} // namespace yu::select::results

#endif