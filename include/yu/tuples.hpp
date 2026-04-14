#ifndef YU_TUPLES_HPP_
#define YU_TUPLES_HPP_

// Basics

// Tuple concept
#include <yu/tuples/tuple.hpp>
#include <yu/tuples/tuple_structured.hpp>

// Access
#include <yu/tuples/get.hpp>
#include <yu/tuples/size.hpp>

// Access to types
#include <yu/tuples/element_t.hpp>

// Customization point
#include <yu/tuples/known_tuple.hpp>

// Type traits

// Observation traits
#include <yu/tuples/is_applicable.hpp>
#include <yu/tuples/is_applicable_r.hpp>
#include <yu/tuples/is_nothrow_applicable.hpp>
#include <yu/tuples/is_nothrow_applicable_r.hpp>

// Transformation traits
#include <yu/tuples/apply_result.hpp>

// Utility
#include <yu/tuples/index_sequence_for.hpp>

#endif