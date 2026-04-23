# `yu::tuples::applicable`

{{ status_mark('yu::tuples::applicable') }}

```cpp
namespace yu::tuples {
    template <typename Fn, typename T>
    concept applicable = requires(Fn&& fn, T&& t){
        tuples::apply(std::forward<Fn>(fn), std::forward<T>(t));
    };
}
```

## 概要

`applicable`は，任意の関数呼び出し可能な型`Fn`に対して，型`T`の要素をTupleとして展開して呼び出し可能であることを表すコンセプトである．

`std::invocable`の{{ ref('yu::tuples::apply') }}版である．

## 例

```cpp
#include <tuple>
#include <iostream>
#include <yu/tuples/applicable.hpp>

int add(int a, int b) { return a + b; }

int main() {
    std::cout << std::boolalpha;

    std::cout << yu::tuples::applicable<decltype(&add), std::tuple<int, int>> << std::endl;
    std::cout << yu::tuples::applicable<decltype(&add), std::tuple<int>> << std::endl;

    std::cout << yu::tuples::applicable<decltype(&add), int [2]> << std::endl;
    std::cout << yu::tuples::applicable<decltype(&add), int [1]> << std::endl;

    std::cout << yu::tuples::applicable<decltype(&add), int> << std::endl;
}
```

### 出力

```plaintext
true
false
true
false
false
```