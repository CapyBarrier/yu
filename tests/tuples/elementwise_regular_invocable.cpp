#include <yu/tuples/elementwise_regular_invocable.hpp>
#include <tuple>

int add(int a) {
    return a + 1;
}

int main() {
    using F1 = decltype(&add);
    using T1 = std::tuple<int, int>;

    static_assert(yu::tuples::elementwise_regular_invocable<F1, T1>);

    auto capture = [x = 42](int a) { return x + a; };
    using F2 = decltype(capture);
    using T2 = std::tuple<int>;

    static_assert(yu::tuples::elementwise_regular_invocable<F2, T2>);

    return 0;
}
