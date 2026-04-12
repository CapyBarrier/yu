#include <yukit/cmd/docs/pages_cmd.hpp>
#include <yukit/cmd/docs/serve_cmd.hpp>
#include <yukit/cmd/docs_cmd.hpp>
#include <iostream>
#include <string>
#include <unordered_map>


namespace yukit::cmd {

int docs_cmd(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "No docs commands provided.\n";
        return 1;
    }

    std::string cmd = argv[1];

    using fn_cmd = int (*)(int, char**);

    std::unordered_map<std::string, fn_cmd> cmds = {
        {"pages", &yukit::cmd::docs::pages_cmd},
        {"serve", &yukit::cmd::docs::serve_cmd}
    };

    if (auto it = cmds.find(cmd); it != cmds.end()) { return it->second(argc - 1, argv + 1); }

    std::cerr << "Invalid command: " << cmd << '\n';
    return 1;
}

} // namespace yukit::cmd
