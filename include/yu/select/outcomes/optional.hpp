#ifndef YU_INCLUDE_YU_SELECT_OUTCOMES_OPTIONAL_HPP_
#define YU_INCLUDE_YU_SELECT_OUTCOMES_OPTIONAL_HPP_

#include <optional>

namespace yu::select::outcomes {

template <typename Result>
struct optional {
        template <typename T>
        static std::optional<Result> success(T&& result) {
            return std::optional<Result>{result};
        }

        static std::optional<Result> failure() { return std::nullopt; }
};

template <>
struct optional<void> {
        static void success() {}

        static void failure() {}
};

} // namespace yu::select::outcomes

#endif