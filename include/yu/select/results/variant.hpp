#ifndef YU_SELECT_RESULTS_VARIANT_HPP_
#define YU_SELECT_RESULTS_VARIANT_HPP_

#include <variant>
#include <yu/select/policy_tags/result_policy_tag.hpp>

namespace yu::select::results {

struct variant {
        using result_policy_tag = policy_tags::result_policy_tag;

        template <typename... ActionResults>
        using result_type = std::variant<ActionResults...>;
};

} // namespace yu::select::results

#endif