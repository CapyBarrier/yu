#ifndef YUKIT_UTIL_GET_ROOT_HPP_
#define YUKIT_UTIL_GET_ROOT_HPP_

#include <filesystem>

namespace yukit::util {

namespace fs = std::filesystem;

fs::path get_root();

} // namespace yukit::util

#endif