#include <yukit/util/replace_ns_qualifier.hpp>
#include <string>

namespace yukit::util {

std::string replace_ns_qualifier(const std::string& input, const std::string value) {
    std::string            result = input;
    std::string::size_type pos    = 0;

    while ((pos = result.find("::", pos)) != std::string::npos) {
        result.replace(pos, 2, value);
        ++pos;
    }

    return result;
}

} // namespace yukit::util
