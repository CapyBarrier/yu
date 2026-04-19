#include <yukit/cmd/ref.hpp>
#include <yukit/cmd/reference/make_template.hpp>
#include <yukit/cmd/reference/pages.hpp>
#include <yukit/cmd/reference/serve.hpp>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

namespace yukit::cmd {

int ref(std::vector<std::string> args) {
    if (args.empty()) {
        std::cerr << "No reference commands provided.";
        return 1;
    }

    std::string cmd = args[0];

    using fn_cmd = int (*)(std::vector<std::string>);

    std::unordered_map<std::string, fn_cmd> cmds = {
        {"make-template", &reference::make_template},
        {        "serve",         &reference::serve},
        {        "pages",         &reference::pages}
    };

    if (auto it = cmds.find(cmd); it != cmds.end()) {
        return it->second(std::vector<std::string>{std::ranges::begin(args) + 1, std::ranges::end(args)});
    }

    std::cerr << "Invalid reference command: " << cmd << '\n';

    std::cerr << "Available reference commands:\n";
    for (auto& [cmd, fn] : cmds) { std::cout << '\t' << cmd << '\n'; }

    return 1;
}

} // namespace yukit::cmd