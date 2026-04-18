#include <yukit/util/valid_entity_name.hpp>
#include <algorithm>
#include <string>

namespace yukit::util {

bool valid_entity_name(const std::string& entity_name) {
    if ((std::ranges::count(entity_name, ':') / 2) < 2) return false;
    if (!entity_name.starts_with("yu::")) return false;

    return true;
}

} // namespace yukit::util