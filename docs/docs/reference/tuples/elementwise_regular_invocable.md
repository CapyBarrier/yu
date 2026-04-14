# `yu::tuples::elementwise_regular_invocable`

{{ status_mark('tuples.elementwise_regular_invocable') }}

```cpp
namespace yu::tuples {
    template <typename F, typename T>
    concept elementwise_regular_invocable = elementwise_invocable<F, T>;
}
```

## 概要

`elementwise_regular_invocable`は，`elementwise_invocable`は，任意の関数呼び出し可能な型`F`が，型`T`をTupleとして展開した各要素によって，正則呼び出し可能であることを表すコンセプトである．
呼び出しが正則であることは構文的に検証できないため，この制約は純粋に意味論的に存在する．

## 例

```cpp
#include <yu/tuples/elementwise_regular_invocable.hpp>
#include <tuple>
#include <iostream>

int add(int a) {
    return a + 1;
}

int main() {
    std::cout << std::boolalpha;

    using F1 = decltype(&add);
    using T1 = std::tuple<int, int>;

    // 各要素は関数addの引数として呼び出し可能
    std::cout << yu::tuples::elementwise_regular_invocable<F1, T1> << std::endl;

    auto capture = [x = 42](int a) { return x + a; };
    using F2 = decltype(capture);
    using T2 = std::tuple<int>;

    // F2はelementwise_regular_invocableのモデルではないが，構文上ではそれを検証できないため，trueと表示される．
    std::cout << yu::tuples::elementwise_regular_invocable<F2, T2> << std::endl;
}
```

### 出力

```plaintext
true
true
```


