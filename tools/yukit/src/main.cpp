#include "index_cmd.hpp"
#include "new_cmd.hpp"
#include "status_cmd.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

// int help_cmd(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "No commands provided.\n";
        return 1;
    }

    std::string cmd = argv[1];

    using fn_cmd = int (*)(int, char**);

    std::unordered_map<std::string, fn_cmd> cmds = {
        {   "new",    &new_cmd},
        { "index",  &index_cmd},
        {"status", &status_cmd}
    };

    if (auto it = cmds.find(cmd); it != cmds.end()) { return it->second(argc - 1, argv + 1); }

    std::cerr << "Invalid command: " << cmd << '\n';
    return 1;
}
