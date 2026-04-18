#include <yukit/cmd/reference/serve.hpp>
#include <yukit/util/get_root.hpp>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <iostream>
#include <string>
#include <vector>

namespace yukit::cmd::reference {

int serve(std::vector<std::string> args) {
    if (!args.empty()) {
        std::cerr << "Too many options provided (expected 0 option).";
        return 1;
    }

    namespace fs = std::filesystem;

    const fs::path root = util::get_root();
    const fs::path docs = root / "docs";

    if (!fs::exists(docs)) {
        std::cerr << "Directory not found: " << docs.string() << '\n';
        return 1;
    }

    return std::system(std::format("cd {} & mkdocs serve", docs.string()).c_str());
    return 0;
}

} // namespace yukit::cmd::reference