# `yu::tuples::applicable`

{{ status_mark('tuples.applicable') }}

```cpp
namespace yu::tuples {
    template <typename F, typename T>
    concept applicable = requires(F&& f, T&& t){
        tuples::apply(std::forward<F>(f), std::forward<T>(t));
    };
}
```

## 概要

`applicable`は，任意の関数呼び出し可能な型`F`に対して，型`T`の要素をTupleとして展開して呼び出し可能であることを表すコンセプトである．

`std::invocable`の{{ ref('tuples.apply') }}版である．

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