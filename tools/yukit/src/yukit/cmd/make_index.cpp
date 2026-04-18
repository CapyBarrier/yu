#include <yukit/cmd/make_index.hpp>
#include <yukit/util/get_root.hpp>
#include <yukit/util/replace_ns_qualifier.hpp>
#include <yukit/util/sublib_exists.hpp>
#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

namespace yukit::cmd {

int make_index(std::vector<std::string> args) {
    namespace fs = std::filesystem;

    if (const auto size = args.size(); size != 0) {
        std::cerr << "Too many options provided (expected 0 option).";
        return 1;
    }

    const fs::path root       = util::get_root();
    const fs::path yukit_root = root / "yukit";

    const fs::path yamls_path = yukit_root;
    const fs::path index      = yukit_root / "index.json";

    std::vector<fs::path> yamls;
    for (const auto& entry : fs::recursive_directory_iterator{yamls_path}) {
        if (const auto& path = entry.path(); path.extension() == ".yaml") yamls.push_back(path);
    }

    const std::size_t yamls_size = yamls.size();

    struct json_entry {
            std::string fullname, qualified_name, identifier, ns, alias, category, status, url;
    };

    std::vector<json_entry> json_entries;

    for (const auto& yaml : yamls) {
        std::string fullname;
        std::string sublib;
        std::string category;
        std::string status;
        std::string alias;

        {
            std::ifstream ifs{yaml};

            std::string line;
            while (std::getline(ifs, line)) {
                if (line.starts_with("name: ")) fullname = line.substr(std::size("name: ") - 1);
                if (line.starts_with("alias: ")) alias = line.substr(std::size("alias: ") - 1);
                if (line.starts_with("sublib: ")) sublib = line.substr(std::size("sublib: ") - 1);
                if (line.starts_with("category: ")) category = line.substr(std::size("category: ") - 1);
                if (line.starts_with("status: ")) status = line.substr(std::size("status: ") - 1);
            }
        }

        const std::string qualified_name = fullname.substr(std::size("yu::") - 1);
        const std::string identifier     = fullname.substr(fullname.find_last_of("::") + 1);
        const std::string ns             = fullname.substr(0, fullname.find_last_of("::") - 1);
        const std::string url
            = std::format("/yu/reference/{}/index.html", util::replace_ns_qualifier(qualified_name, "/"));

        json_entries.push_back({fullname, qualified_name, identifier, ns, alias, category, status, url});
    }

    if (fs::exists(index)) fs::remove(index);

    std::ofstream ofs{index};

    ofs << "{\n";

    for (std::size_t idx = 0; idx < yamls_size; ++idx) {
        auto& [fullname, qualified_name, identifier, ns, alias, category, status, url] = json_entries[idx];

        if (!alias.empty()) url = std::ranges::find(json_entries, alias, &json_entry::fullname)->url;

        ofs << "    \"" << fullname << "\": {\n";

        ofs << std::format("        \"fullname\": \"{}\",\n", fullname)
            << std::format("        \"qualified_name\": \"{}\",\n", qualified_name)
            << std::format("        \"identifier\": \"{}\",\n", identifier)
            << std::format("        \"namespace\": \"{}\",\n", ns) //
            << std::format("        \"alias\": \"{}\",\n", alias)
            << std::format("        \"category\": \"{}\",\n", category)
            << std::format("        \"status\": \"{}\",\n", status) //
            << std::format("        \"url\": \"{}\"\n", url);

        ofs << "    }";

        if (idx + 1 != yamls_size) ofs << ",\n";
        else ofs << "\n";
    }

    ofs << "}";

    return 0;
}

} // namespace yukit::cmd