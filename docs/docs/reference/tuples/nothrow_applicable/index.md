# `yu::tuples::nothrow_applicable`

```cpp
namespace yu::tuples {
    template <typename F, typename T>
    concept nothrow_applicable = see_below
}
```

## 概要

`nothrow_applicable`は，任意の関数呼び出し可能な型`F`に対して，型`T`の要素をTupleとして展開して呼び出し可能であり，かつその際に例外を送出しないことを表すコンセプトである．

## 例

```cpp
#include <tuple>
#include <iostream>
#include <yu/tuples/nothrow_applicable.hpp>

int add(int a, int b) { return a + b; }
int add_noexcept(int a, int b) noexcept { return a + b; }

int main() {
    std::cout << std::boolalpha;

    std::cout << yu::tuples::nothrow_applicable<decltype(&add_noexcept), std::tuple<int, int>> << std::endl;
    std::cout << yu::tuples::nothrow_applicable<decltype(&add), std::tuple<int, int>> << std::endl;
}
```

### 出力

```plaintext
true
false
```