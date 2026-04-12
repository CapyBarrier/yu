#include "yukit/util/get_root.hpp"
#include <yukit/cmd/docs/pages_cmd.hpp>
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace yukit::cmd::docs {

std::string path_to_ns(std::string& path);

int pages_cmd(int argc, char* argv[]) {
    namespace fs = std::filesystem;

    if (2 != argc) {
        std::cerr << "usage: yu docs pages <sublib>\n";
        return 1;
    }

    const std::string sublib_name = argv[1];

    const fs::path root        = yukit::util::get_root();
    const fs::path mkdocs_root = root / "docs";
    const fs::path mkdocs_docs        = mkdocs_root / "docs";
    const fs::path reference   = mkdocs_docs / "reference";
    const fs::path sublib      = reference / sublib_name;

    if (!fs::exists(sublib)) {
        std::cerr << "Sublibrary '" << sublib_name << "' does't exists.";
        return 1;
    }

    const fs::path pages = sublib / ".pages";

    if (fs::exists(pages)) fs::remove(pages);

    std::ofstream ofs{pages};

    // Write title
    {
        std::string title = sublib_name;
        title[0]          = std::toupper(title[0]);
        title             = "Yu." + title;

        ofs << "title: " << title;
    }

    ofs << "\n\n";

    // Write nav
    {
        ofs << "nav:\n";
        ofs << "  - index.md\n";

        std::vector<fs::path> mds;

        for (const auto& md : fs::recursive_directory_iterator(sublib)) {
            if (md.path().extension() == ".md") { mds.push_back(md.path()); }
        }

        auto comp = [&sublib](const fs::path& a, const fs::path& b) {
            fs::path rel_a = fs::relative(a, sublib);
            fs::path rel_b = fs::relative(b, sublib);

            auto depth_a = std::distance(rel_a.begin(), rel_a.end());
            auto depth_b = std::distance(rel_b.begin(), rel_b.end());

            if (depth_a != depth_b) { return depth_a < depth_b; }
            return rel_a.string() < rel_b.string();
        };

        std::sort(mds.begin(), mds.end(), comp);

        for (const auto& md : mds) {
            std::string md_relative = fs::relative(md, sublib).replace_extension().generic_string();

            std::string link = fs::relative(md, mkdocs_docs).replace_extension().generic_string();

            ofs << std::format("  - {}: {}/index.html\n", path_to_ns(md_relative), link);
        }
    }

    ofs.close();

    return 0;
}

std::string path_to_ns(std::string& path) {
    std::string result;
    result.reserve(path.size());

    for (char c : path) {
        if (c == '/') {
            result += "::";
        } else {
            result += c;
        }
    }

    return result;
}

} // namespace yukit::cmd::docs
