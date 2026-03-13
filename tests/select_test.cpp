#include <yu/select.hpp>
#include <iostream>
#include <string_view>
#include <cassert>

using namespace std::string_view_literals;

constexpr auto mod2(int x) {
    using namespace yu::select;

    return select(x)(
        where([](int n) { return n % 2 == 0; }) |= actions::value(0),
        otherwise |= actions::value(1)
    );
}

int main() {
    constexpr int x = mod2(1);
    assert(x == 1);
}