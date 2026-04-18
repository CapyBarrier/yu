#include <yukit/util/sublib_exists.hpp>
#include <filesystem>

namespace yukit::util {

bool sublib_exists(const std::filesystem::path& yukit_root, const std::string& sublib) {
    namespace fs = std::filesystem;

    const fs::path sublib_path = yukit_root / sublib;

    return fs::exists(sublib_path);
}

} // namespace yukit::util