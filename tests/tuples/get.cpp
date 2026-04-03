#include <yu/tuples/get.hpp>
#include <cassert>
#include <cstddef>
#include <tuple>
#include <type_traits>


struct foo {
        template <std::size_t>
        int get() {
            return 42;
        }
};

namespace std {

template <>
struct tuple_size<foo> : std::integral_constant<std::size_t, 3> {};

} // namespace std

int main() {
    {
        int arr[3] = {1, 2, 3};
        assert(yu::tuples::get<1>(arr) == arr[1]);

        yu::tuples::get<2>(arr) = 4;
        assert(arr[2] == 4);
    }
    {
        foo x{};
        assert(yu::tuples::get<0>(x) == x.template get<0>());

        assert(yu::tuples::get<0>(x) == 42);
    }
    {
        std::tuple<int, char, double> tup(1, 'a', 3.14);

        assert(yu::tuples::get<1>(tup) == std::get<1>(tup));

        yu::tuples::get<2>(tup) = 2.78;
        assert(std::get<2>(tup) == 2.78);
    }

    return 0;
}