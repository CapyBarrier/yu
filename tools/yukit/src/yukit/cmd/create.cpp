#include <yukit/cmd/create.hpp>
#include <yukit/util/get_root.hpp>
#include <yukit/util/replace_ns_qualifier.hpp>
#include <yukit/util/sublib_exists.hpp>
#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace yukit::cmd {

int create(std::vector<std::string> args) {
    namespace fs = std::filesystem;

    if (const auto size = args.size(); size != 0 && size != 3) {
        std::cerr << "Invalid number of arguments.\n";
        std::cerr << "For manual: yukit create <sublib> <entity> <category>\n";
        std::cerr << "For interactive: yukit create";

        return 1;
    }

    const fs::path root        = util::get_root();
    const fs::path yukit_root  = root / "yukit";
    const bool     interactive = args.empty();

    const std::vector<std::string> categories{
        "variable",
        "variable-tmpl",
        "function",
        "function-tmpl",
        "class",
        "class-tmpl",
        "alias",
        "alias-tmpl",
        "metafn-type",
        "metafn-value",
        "concept",
        "cpo",
        "function-obj",
    };

    if (interactive) {
        args.resize(3);

        while (true) {
            std::cout << "Sublibrary: ";
            std::cin >> args[0];
            if (util::sublib_exists(yukit_root, args[0])) break;
            std::cout << "Sublibrary \'" << args[0] << "\' does not exist.\n";
        }

        std::cout << "Entity name: ";
        std::cin >> args[1];

        while (true) {
            std::cout << "Category: ";
            std::cin >> args[2];
            if (std::ranges::contains(categories, args[2])) break;
            std::cout << "Invalid category. select one of the following: ";

            const auto size = categories.size();
            for (std::size_t i = 0; i < size; ++i) {
                std::cout << categories[i];
                if (i != size - 1) std::cout << ", ";
            }
            std::cout << '\n';
        }
    } else {
        if (!util::sublib_exists(yukit_root, args[0])) {
            std::cerr << "Sublibrary \'" << args[0] << "\' does not exist.";
            return 1;
        }
        if (!std::ranges::contains(categories, args[2])) {
            std::cerr << "Invalid category.";
            return 1;
        }
    }

    const auto& sublib      = args[0];
    const auto& entity_name = args[1];
    const auto& category    = args[2];

    const std::string entity_fullname_without_yu = sublib + "::" + entity_name;
    const std::string entity_fullname            = "yu::" + sublib + "::" + entity_name;
    const fs::path entity_path = yukit_root / (util::replace_ns_qualifier(entity_fullname_without_yu, "/") + ".yaml");

    if (fs::exists(entity_path)) {
        std::cerr << "File \'" << entity_path.generic_string() << "\' already exists.";
        return 1;
    }

    fs::create_directories(entity_path.parent_path());

    std::ofstream ofs{entity_path};

    ofs << "name: " << entity_fullname << '\n';
    ofs << "sublib: " << sublib << '\n';
    ofs << "category: " << category << '\n';
    ofs << "status: planned\n";

    return 0;
}

} // namespace yukit::cmd