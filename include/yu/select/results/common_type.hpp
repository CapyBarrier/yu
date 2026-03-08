#ifndef YU_SELECT_RESULTS_COMMON_TYPE_HPP_
#define YU_SELECT_RESULTS_COMMON_TYPE_HPP_

#include <yu/select/policy_tags/result_policy_tag.hpp>
#include <type_traits>

namespace yu::select::results {

struct common_type {
        using result_policy_tag = policy_tags::result_policy_tag;

        template <typename... ActionResults>
        using result_type = std::common_type_t<ActionResults...>;
};

} // namespace yu::select::results

#endif