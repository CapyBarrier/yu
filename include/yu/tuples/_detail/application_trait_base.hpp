#ifndef YU_TUPLES_DETAIL_APPLICATION_TRAIT_BASE_HPP_
#define YU_TUPLES_DETAIL_APPLICATION_TRAIT_BASE_HPP_

#include <yu/tuples/element_t.hpp>
#include <yu/tuples/index_sequence_for.hpp>
#include <cstddef>
#include <utility>

namespace yu::tuples::_detail {

template <template <typename...> typename InvocationTrait, typename Tuple, typename IndexSequence, typename... Args>
struct application_trait_base_impl;

template <template <typename...> typename InvocationTrait, typename Tuple, std::size_t... Idx, typename... Args>
struct application_trait_base_impl<InvocationTrait, Tuple, std::index_sequence<Idx...>, Args...> :
    InvocationTrait<Args..., tuples::element_t<Idx, Tuple>...> {};

template <template <typename...> typename InvocationTrait, typename Tuple, typename... Args>
struct application_trait_base :
    application_trait_base_impl<InvocationTrait, Tuple, tuples::index_sequence_for<Tuple>, Args...> {};

} // namespace yu::tuples::_detail

#endif