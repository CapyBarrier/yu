#include <yukit/util/replace_ns_qualifier.hpp>
#include <yukit/util/entity_path.hpp>
#include <yukit/util/get_root.hpp>
#include <filesystem>
#include <string>

namespace yukit::util {

std::filesystem::path entity_path(const std::filesystem::path yukit_root, const std::string& entity_name) {
    const std::string entity_name_without_yu = entity_name.substr(std::size("yu::") - 1);
    return yukit_root / (util::replace_ns_qualifier(entity_name_without_yu, "/") + ".yaml");
}

} // namespace yukit::util