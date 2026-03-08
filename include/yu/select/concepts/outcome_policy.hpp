#ifndef YU_INCLUDE_YU_SELECT_CONCEPTS_OUTCOME_POLICY_HPP_
#define YU_INCLUDE_YU_SELECT_CONCEPTS_OUTCOME_POLICY_HPP_

#include <yu/select/policy_tags/outcome_policy_tag.hpp>
#include <concepts>
#include <type_traits>

namespace yu::select::concepts {

template <typename T>
concept outcome_policy = requires {
    typename std::remove_cvref_t<T>::outcome_policy_tag;
    requires std::same_as<
        typename std::remove_cvref_t<T>::outcome_policy_tag,
        policy_tags::outcome_policy_tag
    >;
};

} // namespace yu::select::concepts

#endif