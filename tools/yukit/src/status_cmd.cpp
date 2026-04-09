#include "status_cmd.hpp"
#include "get_root.hpp"
#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int status_cmd(int argc, char* argv[]) {
    namespace fs = std::filesystem;

    constexpr char separator = fs::path::preferred_separator;

    if (argc < 2) {
        std::cerr << "usage: yukit status <id> [status-opt]\n";
        return 1;
    }

    const fs::path root = get_root();

    const std::string id      = argv[1];
    std::string       id_path = id;
    std::ranges::replace(id_path, '.', separator);

    const fs::path yaml = root / "spec" / (id_path + ".yaml");

    if (!fs::exists(yaml)) {
        std::cerr << "Markdown not found: " << yaml.string();
        return 1;
    }

    std::ifstream fin(yaml);

    std::vector<std::string> lines;
    std::string              line;

    while (std::getline(fin, line)) { lines.push_back(line); }
    fin.close();

    if (argc == 3) { // change status
        const std::string status = argv[2];

        constexpr std::string_view valid_statuses[] = {"planned", "unimplemented", "unstable", "stable"};

        if (!std::ranges::contains(valid_statuses, status)) {
            std::cerr << "Invalid status: " << status;
            return 1;
        }

        lines[3] = std::format("status: {}", status);

        std::ofstream fout(yaml);
        for (size_t i = 0; i < lines.size(); ++i) {
            fout << lines[i];
            if (i + 1 < lines.size()) fout << '\n';
        }

        fout.close();

        std::cout << "changed status to " << status << "\n";

    } else { // show status
        std::cout << lines[3] << '\n';
    }

    return 0;
}