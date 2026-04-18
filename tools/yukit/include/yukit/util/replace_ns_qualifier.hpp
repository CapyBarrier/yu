#ifndef YUKIT_UTIL_REPLACE_NS_QUALIFIER_HPP_
#define YUKIT_UTIL_REPLACE_NS_QUALIFIER_HPP_

#include <string>

namespace yukit::util {

std::string replace_ns_qualifier(const std::string& ns_qualified_name, const std::string value);

} // namespace yukit::util

#endif