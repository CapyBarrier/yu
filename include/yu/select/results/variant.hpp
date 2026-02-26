#ifndef YU_SELECT_RESULTS_VARIANT_HPP_
#define YU_SELECT_RESULTS_VARIANT_HPP_

#include <variant>

namespace yu::select::results {

struct variant {
        template <typename... ActionResults>
        using result_type = std::variant<ActionResults...>;
};

} // namespace yu::select::results

#endif