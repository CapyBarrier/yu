#include <iostream>
#include <yu/select.hpp>

constexpr auto multiplication_of(int n) {
    return [=](int x) { return x % n == 0; };
}

int main() {
    using namespace yu::select;

    for (int n = 1; n <= 20; n++) {
        select(n)(                                                           //
            where(multiplication_of(15)) |= [] { std::cout << "fizzbuzz"; }, //
            where(multiplication_of(5)) |= [] { std::cout << "buzz"; },      //
            where(multiplication_of(3)) |= [] { std::cout << "fizz"; },      //
            otherwise |= [](int x) { std::cout << x; }                       //
        );                                                                   //

        std::cout << " ";
    }
}