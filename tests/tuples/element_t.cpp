#include <yu/tuples/element_t.hpp>
#include <tuple>
#include <type_traits>

int main() {
    // std::tuple
    {
        using T = std::tuple<int, char, double>;

        static_assert(std::is_same_v<yu::tuples::element_t<0, T>, int&&>);
    }

    // 組み込み配列
    {
        using T = double[1];

        static_assert(std::is_same_v<yu::tuples::element_t<0, T>, double&&>);
    }
}