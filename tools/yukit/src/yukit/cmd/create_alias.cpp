#include "yukit/util/entity_exists.hpp"
#include "yukit/util/entity_path.hpp"
#include "yukit/util/get_root.hpp"
#include <yukit/cmd/create_alias.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace yukit::cmd {

int create_alias(std::vector<std::string> args) {
    namespace fs = std::filesystem;

    if (const auto size = args.size(); size != 0 && size != 2) {
        std::cerr << "Invalid number of arguments.\n";
        std::cerr << "For manual: yukit create-alias <alias> <target-fullname>\n";
        std::cerr << "For interactive: yukit create-alias";

        return 1;
    }

    const fs::path root        = util::get_root();
    const fs::path yukit_root  = root / "yukit";
    const bool     interactive = args.empty();

    if (interactive) {
        args.resize(2);

        std::cout << "Alias name: ";
        std::cin >> args[0];

        while (true) {
            std::cout << "Entity name: ";
            std::cin >> args[1];
            if (util::entity_exists(yukit_root, args[1])) break;
            std::cout << "Entity \'" << args[1] << "\' does not exist.\n";
        }
    } else {
        if (!util::entity_exists(yukit_root, args[1])) {
            std::cerr << "Entity \'" << args[1] << "\' does not exist.";
            return 1;
        }
    }

    const auto& alias         = args[0];
    const auto& target_entity = args[1];

    const fs::path entity_path = util::entity_path(yukit_root, target_entity);
    const fs::path alias_path  = entity_path.parent_path() / (alias + ".yaml");

    std::string target_sublib;
    std::string target_category;

    {
        std::ifstream ifs{entity_path};

        std::string line;
        while (std::getline(ifs, line)) {
            if (line.starts_with("sublib: ")) target_sublib = line.substr(std::size("sublib: ") - 1);
            if (line.starts_with("category: ")) target_category = line.substr(std::size("category: ") - 1);
        }
    }

    if (!target_category.starts_with("metafn")) {
        std::cerr << "Error: only meta-function can be aliased.";
        return 1;
    }

    std::string alias_category;

    if (target_category == "metafn-type") alias_category = "alias-tmpl";
    if (target_category == "metafn-value") alias_category = "variable-tmpl";

    const std::string alias_fullname = "yu::" + target_sublib + "::" + alias;

    std::ofstream ofs{alias_path};

    ofs << "name: " << alias_fullname << '\n';
    ofs << "sublib: " << target_sublib << '\n';
    ofs << "alias: " << target_entity << '\n';
    ofs << "category: " << target_category << '\n';
    ofs << "status: planned\n";

    return 0;
}

} // namespace yukit::cmd