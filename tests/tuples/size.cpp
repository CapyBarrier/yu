#include <yu/tuples/size.hpp>
#include <cassert>
#include <tuple>
#include <utility>

int main() {
    using arr_t = int[10];
    using tup_t = std::tuple<int, float, bool, short[10]>;
    using pair_t = std::pair<int, long>;

    static_assert(yu::tuples::size_v<arr_t> == 10);
    static_assert(yu::tuples::size_v<tup_t> == 4);
    static_assert(yu::tuples::size_v<pair_t> == 2);

    return 0;
}