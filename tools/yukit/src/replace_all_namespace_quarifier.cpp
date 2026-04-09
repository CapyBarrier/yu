#include "replace_all_namespace_quarifier.hpp"
#include <string>


std::string replace_all_namespace_quarifier(const std::string& input, const std::string value) {
    std::string            result = input;
    std::string::size_type pos    = 0;

    while ((pos = result.find("::", pos)) != std::string::npos) {
        result.replace(pos, 2, value);
        ++pos;
    }

    return result;
}