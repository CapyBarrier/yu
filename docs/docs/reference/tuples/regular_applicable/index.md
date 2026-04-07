# `yu::tuples::regular_applicable`

```cpp
namespace yu::tuples {
    template <typename F, typename T>
    concept regular_applicable = applicable<T>;
}
```

## 概要

`regular_applicable`は，任意の関数呼び出し可能な型`F`に対して，型`T`の要素をTupleとして展開して，正則呼び出し可能であることを表すコンセプトである．
ただし，このことは構文的には検証されず，純粋に意味論的な制約として存在する．

`std::regular_invocable`をTupleに拡張したものである．

## 例

```cpp
#include <tuple>
#include <iostream>
#include <yu/tuples/applicable.hpp>

void no_mutate(int& a) {}
auto mutate = [](int& a) { a += 42; }

int main() {
    std::cout << std::boolalpha;

    std::cout << yu::tuples::regular_applicable<decltype(&no_mutate), std::tuple<int>&> << std::endl;
    // decltype(mutate)はregular_applicableのモデルではないが，構文上ではそれを検証できないため，trueと表示される．
    std::cout << yu::tuples::regular_applicable<decltype(mutate), std::tuple<int>&> << std::endl;
}
```

### 出力

```plaintext
true
true
```