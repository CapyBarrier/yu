#ifndef YU_SELECT_RESULTS_AS_HPP_
#define YU_SELECT_RESULTS_AS_HPP_

namespace yu::select::results {

template <typename T>
struct as {
        template <typename... ActionResults>
        using result_type = T;
};

} // namespace yu::select::results

#endif