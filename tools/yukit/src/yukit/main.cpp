#include <yukit/cmd/docs_cmd.hpp>
#include <yukit/cmd/index_cmd.hpp>
#include <yukit/cmd/new_cmd.hpp>
#include <yukit/cmd/status_cmd.hpp>
#include <iostream>
#include <string>
#include <unordered_map>


int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "No commands provided.\n";
        return 1;
    }

    std::string cmd = argv[1];

    using fn_cmd = int (*)(int, char**);

    std::unordered_map<std::string, fn_cmd> cmds = {
        {   "new",    &yukit::cmd::new_cmd},
        { "index",  &yukit::cmd::index_cmd},
        {"status", &yukit::cmd::status_cmd},
        {  "docs",   &yukit::cmd::docs_cmd}
    };

    if (auto it = cmds.find(cmd); it != cmds.end()) { return it->second(argc - 1, argv + 1); }

    std::cerr << "Invalid command: " << cmd << '\n';
    return 1;
}
