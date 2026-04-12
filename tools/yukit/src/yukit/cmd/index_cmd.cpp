#include <yukit/cmd/index_cmd.hpp>
#include <yukit/util/get_root.hpp>
#include <yukit/util/replace_ns_qualifier.hpp>
#include <cstddef>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace yukit::cmd {

std::string get_json_text(std::filesystem::path path);

int index_cmd(int argc, [[maybe_unused]] char* argv[]) {
    namespace fs = std::filesystem;

    if (1 < argc) {
        std::cerr << "Too much options provided.\n";
        return 1;
    }

    const fs::path root  = yukit::util::get_root();
    const fs::path spec  = root / "spec";
    const fs::path index = root / ".cache" / "yukit" / "index.json";

    if (fs::exists(index)) fs::remove(index);

    std::vector<std::string> entries;

    for (const auto& p : fs::recursive_directory_iterator(spec)) {
        if (p.path().extension() == ".yaml") { entries.push_back(get_json_text(p.path())); }
    }

    std::ofstream ofs{index};
    ofs << "{\n";

    for (std::size_t i = 0, size = entries.size(); i < size; ++i) {
        ofs << entries[i];
        if (i + 1 != size) ofs << ",\n";
        else ofs << "\n";
    }

    ofs << "}";

    ofs.close();

    return 0;
}

std::string get_json_text(std::filesystem::path path) {
    std::ifstream ifs{path};

    constexpr std::string_view fmt{
        "    \"{}\": {{ \n"                // id
        "        \"lib\": \"{}\",\n"      // lib name
        "        \"name\": \"{}\",\n"     // entity name
        "        \"fullname\": \"{}\",\n" // entity fullname
        "        \"category\": \"{}\",\n" // category
        "        \"status\": \"{}\",\n"   // status
        "        \"url\": \"{}\"\n"       // url
        "    }}"
    };

    std::string yaml_line;

    std::getline(ifs, yaml_line);
    const std::string id = yaml_line.substr(std::size("id: ") - 1);

    const std::string lib = [&] {
        if (auto pos = id.find('.'); pos != std::string::npos) return id.substr(0, pos);
        else return id;
    }();

    std::getline(ifs, yaml_line);
    const std::string name = yaml_line.substr(std::size("name: ") - 1);

    const std::string fullname = std::format("yu::{}::{}", lib, name);

    std::getline(ifs, yaml_line);
    const std::string category = yaml_line.substr(std::size("category: ") - 1);

    std::getline(ifs, yaml_line);
    const std::string status = yaml_line.substr(std::size("status: ") - 1);

    const std::string url
        = std::format("/yu/reference/{}/{}/index.html", lib, yukit::util::replace_ns_qualifier(name, "/"));

    ifs.close();

    return std::format(fmt, id, lib, name, fullname, category, status, url);
}

} // namespace yukit::cmd
