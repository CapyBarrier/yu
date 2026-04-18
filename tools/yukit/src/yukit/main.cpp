#include <yukit/cmd/create.hpp>
#include <yukit/cmd/create_alias.hpp>
#include <yukit/cmd/make_index.hpp>
#include <yukit/cmd/ref.hpp>
#include <yukit/cmd/status.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "No commands provided.";
        return 1;
    }

    std::string cmd = argv[1];

    using fn_cmd = int (*)(std::vector<std::string>);

    std::unordered_map<std::string, fn_cmd> cmds = {
        {      "create",       &yukit::cmd::create},
        {"create-alias", &yukit::cmd::create_alias},
        {  "make-index",   &yukit::cmd::make_index},
        {         "ref",          &yukit::cmd::ref},
        {      "status",       &yukit::cmd::status},
    };

    if (auto it = cmds.find(cmd); it != cmds.end()) {
        return it->second(std::vector<std::string>{argv + 2, argv + argc});
    }

    std::cerr << "Invalid command: " << cmd << '\n';

    std::cerr << "Available commands:\n";
    for (auto& [cmd, fn] : cmds) { std::cout << '\t' << cmd << '\n'; }

    return 1;
}
