#include "yukit/util/sublib_exists.hpp"
#include <yukit/cmd/reference/pages.hpp>
#include <yukit/util/get_root.hpp>
#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


namespace yukit::cmd::reference {

int pages(std::vector<std::string> args) {
    namespace fs = std::filesystem;

    if (const auto size = args.size(); size != 0 && size != 1) {
        std::cerr << "Invalid number of arguments.\n";
        std::cerr << "For manual: yukit make-index <sublib>\n";
        std::cerr << "For interactive: yukit make-index";
        return 1;
    }

    const fs::path root        = util::get_root();
    const fs::path yukit_root  = root / "yukit";
    const bool     interactive = args.empty();

    if (interactive) {
        args.resize(1);

        while (true) {
            std::cout << "Sublibrary name: ";
            std::cin >> args[0];
            if (util::sublib_exists(yukit_root, args[0])) break;
            std::cout << "Sublibrary \'" << args[0] << "\' does not exist.\n";
        }
    } else {
        if (!util::sublib_exists(yukit_root, args[0])) {
            std::cerr << "Sublibrary \'" << args[0] << "\' does not exist.";
            return 1;
        }
    }

    const auto& sublib = args[0];

    const fs::path mkdocs_root = root / "docs";
    const fs::path mkdocs_docs = mkdocs_root / "docs";
    const fs::path reference   = mkdocs_docs / "reference";
    const fs::path sublib_dir  = reference / sublib;

    if (!fs::exists(sublib_dir)) {
        std::cerr << "Sublibrary directory '" << sublib_dir.generic_string() << "' does not exist.";
        return 1;
    }

    const fs::path pages = sublib_dir / ".pages";

    if (fs::exists(pages)) fs::remove(pages);

    std::ofstream ofs{pages};
    {
        std::string title = sublib;
        title[0]          = std::toupper(title[0]);
        title             = "Yu." + title;

        ofs << "title: " << title;
    }

    ofs << "\n\n";

    {
        ofs << "nav:\n";
        ofs << "  - index.md\n";

        std::vector<fs::path> mds;

        for (const auto& md : fs::recursive_directory_iterator(sublib_dir)) {
            if (md.path().extension() == ".md") { mds.push_back(md.path()); }
        }

        auto comp = [&sublib_dir](const fs::path& a, const fs::path& b) {
            fs::path rel_a = fs::relative(a, sublib_dir);
            fs::path rel_b = fs::relative(b, sublib_dir);

            auto depth_a = std::distance(rel_a.begin(), rel_a.end());
            auto depth_b = std::distance(rel_b.begin(), rel_b.end());

            if (depth_a != depth_b) { return depth_a < depth_b; }
            return rel_a.string() < rel_b.string();
        };

        auto path_to_ns = [](const std::string& path) {
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
        };

        std::sort(mds.begin(), mds.end(), comp);

        for (const auto& md : mds) {
            std::string md_relative = fs::relative(md, sublib_dir).replace_extension().generic_string();

            std::string link = fs::relative(md, mkdocs_docs).replace_extension().generic_string();

            ofs << std::format("  - {}: {}/index.html\n", path_to_ns(md_relative), link);
        }
    }

    return 0;
}

} // namespace yukit::cmd::reference