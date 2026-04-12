#include <cstdlib>
#include <format>
#include <iostream>
#include <yukit/cmd/docs/serve_cmd.hpp>
#include <yukit/util/get_root.hpp>
#include <filesystem>

namespace yukit::cmd::docs {

int serve_cmd(int argc, char* argv[]) {
    namespace fs = std::filesystem;

    const fs::path root = yukit::util::get_root();
    const fs::path docs = root / "docs";

    if(!fs::exists(docs)) {
        std::cerr << "Directory not found: " << docs.string() << '\n';
        return 1;
    }

    return std::system(std::format("cd {} & mkdocs serve", docs.string()).c_str());
}

} // namespace yukit::cmd::docs
