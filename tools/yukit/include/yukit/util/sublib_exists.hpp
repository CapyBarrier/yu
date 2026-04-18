#ifndef YUKIT_UTIL_SUBLIB_EXISTS_HPP_
#define YUKIT_UTIL_SUBLIB_EXISTS_HPP_

#include <filesystem>
#include <string>

namespace yukit::util {

bool sublib_exists(const std::filesystem::path& yukit_root, const std::string& sublib);

} // namespace yukit::util

#endif