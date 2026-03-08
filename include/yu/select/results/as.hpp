#ifndef YU_SELECT_RESULTS_AS_HPP_
#define YU_SELECT_RESULTS_AS_HPP_

#include <yu/select/policy_tags/result_policy_tag.hpp>

namespace yu::select::results {

template <typename T>
struct as {
        using result_policy_tag = policy_tags::result_policy_tag;

        template <typename... ActionResults>
        using result_type = T;
};

} // namespace yu::select::results

#endif