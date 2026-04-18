#ifndef YUKIT_UTIL_ENTITY_EXISTS_HPP_
#define YUKIT_UTIL_ENTITY_EXISTS_HPP_

#include <filesystem>
#include <string>

namespace yukit::util {

bool entity_exists(const std::filesystem::path& yukit_path, const std::string& entity_name);

} // namespace yukit::util

#endif