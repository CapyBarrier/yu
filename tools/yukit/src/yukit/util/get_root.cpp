#include <yukit/util/get_root.hpp>
#include <algorithm>
#include <filesystem>

namespace yukit::util {
namespace fs = std::filesystem;

fs::path get_root() {
    fs::path       current = fs::current_path();
    const fs::path git_file{".git"};

    fs::directory_iterator iter{current};

    bool found_git_file = false;

    while ((found_git_file = std::ranges::contains(iter, git_file))) { iter = fs::directory_iterator{current / "../"}; }

    return iter->path();
}

} // namespace yukit::util
