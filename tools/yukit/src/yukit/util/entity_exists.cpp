#include <yukit/util/entity_exists.hpp>
#include <yukit/util/replace_ns_qualifier.hpp>
#include <filesystem>
#include <string>

namespace yukit::util {

bool entity_exists(const std::filesystem::path& yukit_root, const std::string& entity_name) {
    namespace fs = std::filesystem;

    const std::string entity_name_without_yu = entity_name.substr(std::size("yu::") - 1);
    fs::path          entity_path            = replace_ns_qualifier(entity_name_without_yu, "/") + ".yaml";

    return fs::exists(yukit_root / entity_path);
}

} // namespace yukit::util