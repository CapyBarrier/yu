#include "yukit/util/entity_path.hpp"
#include "yukit/util/valid_entity_name.hpp"
#include <yukit/cmd/status.hpp>
#include <yukit/util/entity_exists.hpp>
#include <yukit/util/get_root.hpp>
#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace yukit::cmd {

int status(std::vector<std::string> args) {
    namespace fs = std::filesystem;

    if (const auto size = args.size(); size != 0 && size != 1 && size != 2) {
        std::cerr << "Invalid number of arguments.\n";
        std::cerr << "For manual: yukit status <entity> [new-status-opt]\n";
        std::cerr << "For interactive: yukit status";
        return 1;
    }

    const fs::path root       = util::get_root();
    const fs::path yukit_root = root / "yukit";

    const bool interactive = args.empty();

    if (interactive) {
        args.resize(1);

        while (true) {
            std::cout << "Entity name: ";
            std::cin >> args[0];
            if (!util::valid_entity_name(args[0])) {
                std::cout << "\'" << args[0] << "\' is invalid for entity name.\n";
            } else if (!util::entity_exists(yukit_root, args[0])) {
                std::cout << "Entity \'" << args[0] << "\' does not exist.\n";
            } else {
                break;
            }
        }
    } else {
        if (!util::valid_entity_name(args[0])) {
            std::cerr << "\'" << args[0] << "\' is invalid for entity name.\n";
            return 1;
        } else if (!util::entity_exists(yukit_root, args[0])) {
            std::cerr << "Entity \'" << args[0] << "\' does not exist.\n";
            return 1;
        }
    }

    const std::string& entity = args[0];

    fs::path entity_yaml = util::entity_path(yukit_root, entity);

    std::vector<std::string> yaml_content;

    std::string status, new_status;

    bool change_status = false;

    {
        std::fstream ifs{entity_yaml};

        std::string line;
        while (std::getline(ifs, line)) {
            yaml_content.push_back(line);
            if (line.starts_with("status: ")) status = line.substr(std::size("status: ") - 1);
        }
    }

    if (interactive) {
        std::cout << "Entity \'" << entity << "\' is now \'" << status << "\'.\n";
        std::cout << "Do you want to change the status?";

        std::string input;

        while (true) {
            std::cout << " (y/n): ";
            std::cin >> input;
            if (input == "y" || input == "n") break;
        }

        change_status = (input == "y");
    } else {
        change_status = (args.size() == 2);
    }

    if (!change_status && !interactive) { std::cerr << "Entity \'" << entity << "\' is now \'" << status << "\'."; }

    if (!change_status) return 0;

    const std::array<std::string, 4> valid_statuses{"planned", "unimplemented", "unstable", "stable"};

    if (interactive) {
        while (true) {
            std::cout << "New status: ";
            std::cin >> new_status;

            if (std::ranges::contains(valid_statuses, new_status)) break;

            std::cout << '\'' << new_status << "\' is invalid for status.\n";
            std::cout << "Valid statuses:\n";
            for (const auto& valid_status : valid_statuses) std::cout << '\t' << valid_status << '\n';
        }
    } else {
        new_status = args[1];
        if (!std::ranges::contains(valid_statuses, new_status)) {
            std::cerr << '\'' << status << "\' is invalid for status.";
            return 1;
        }
    }

    {
        std::fstream ofs{entity_yaml};

        for (const auto& line : yaml_content) {
            if (line.starts_with("status: ")) ofs << "status: " << new_status << '\n';
            else ofs << line << '\n';
        }
    }

    return 0;
}

} // namespace yukit::cmd