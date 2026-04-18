#ifndef YUKIT_UTIL_ENTITY_PATH_HPP_
#define YUKIT_UTIL_ENTITY_PATH_HPP_

#include <filesystem>
#include <string>

namespace yukit::util {

std::filesystem::path entity_path(const std::filesystem::path yukit_root, const std::string& entity_name);

} // namespace yukit::util

#endif