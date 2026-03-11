#ifndef YU_INCLUDE_YU_SELECT_RESULTS_DEDUCED_HPP_
#define YU_INCLUDE_YU_SELECT_RESULTS_DEDUCED_HPP_

#include "detail/deduce_common_type.hpp"
#include <yu/select/policy_tags/result_policy_tag.hpp>

namespace yu::select::results {

struct deduced {
        using result_policy_tag = policy_tags::result_policy_tag;

        template <typename... Ts>
        using result_type = detail::deduce_common_type_t<Ts...>;
};

} // namespace yu::select::results

#endif