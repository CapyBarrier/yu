#include <yu/tuples/tuple.hpp>
#include <array>
#include <tuple>

int main() {
    static_assert(yu::tuples::tuple<std::tuple<int, double, char>>);
    static_assert(yu::tuples::tuple<std::array<double, 3>>);
    // 要素数の判明している組み込み配列型もtupleのモデルである
    static_assert(yu::tuples::tuple<char[2]>);
}