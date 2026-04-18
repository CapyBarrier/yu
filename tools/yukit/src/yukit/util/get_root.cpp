#include <yukit/util/get_root.hpp>
#include <algorithm>
#include <filesystem>

namespace yukit::util {

std::filesystem::path get_root() {
    namespace fs = std::filesystem;

    static bool     called = false;
    static fs::path root;

    if (called) return root;

    fs::path       current = fs::canonical(fs::current_path());
    const fs::path git_file{".git"};

    fs::directory_iterator iter{current};

    while (std::ranges::contains(iter, git_file)) iter = fs::directory_iterator{current / "../"};

    called = true;

    if (auto result = iter->path(); result.empty()) root = current;
    else root = result;

    return root;
}

} // namespace yukit::util
