#ifndef YU_INCLUDE_YU_SELECT_SELECTION_ERROR_HPP_
#define YU_INCLUDE_YU_SELECT_SELECTION_ERROR_HPP_

#include <stdexcept>

namespace yu::select {

struct select_error : std::logic_error {
        using std::logic_error::logic_error;
};

} // namespace yu::select

#endif