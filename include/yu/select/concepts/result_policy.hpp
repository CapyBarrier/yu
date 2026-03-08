#ifndef YU_INCLUDE_YU_SELECT_CONCEPTS_RESULT_POLICY_HPP_
#define YU_INCLUDE_YU_SELECT_CONCEPTS_RESULT_POLICY_HPP_

#include <yu/select/policy_tags/result_policy_tag.hpp>
#include <concepts>

namespace yu::select::concepts {

template <typename T>
concept result_policy = requires {
    typename std::remove_cvref_t<T>::result_policy_tag;
    requires std::same_as<
        typename std::remove_cvref_t<T>::result_policy_tag,
        policy_tags::result_policy_tag
    >;
};

} // namespace yu::select::concepts

#endif