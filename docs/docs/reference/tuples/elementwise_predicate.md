# `yu::tuples::elementwise_predicate`

{{ status_mark('tuples.elementwise_predicate') }}

```cpp
namespace yu::tuples {
    template <typename F, typename T>
    concept elementwise_predicate = see_below;
}
```

## 概要

`elementwise_predicate`は，任意の関数呼び出し可能な型`F`が，型`T`をTupleとして展開した各要素によって，述語として呼び出し可能であることを表すコンセプトである．
これは，`F`が`T`をTupleとして展開した各要素で正則呼び出し可能であり，かつそれらすべての呼び出しの戻り値が`bool`に変換可能であることと同値である．


## 例

```cpp
#include <yu/tuples/elementwise_predicate.hpp>
#include <tuple>
#include <string>

struct predicate {
    bool operator()(int) const { return true; }
    bool operator()(double) const { return false; }
    bool operator()(const std::string&) const { return true; }
};

struct incomplete_predicate {
    bool operator()(int) const { return true; }
    bool operator()(double) const { return false; }
};

struct non_predicate {
    void operator()(auto) const {}
};

int main() {
    using T = std::tuple<int, double, std::string>;

    static_assert(yu::tuples::elementwise_predicate<predicate, T>);
    static_assert(!yu::tuples::elementwise_predicate<incomplete_predicate, T>);

    using U = std::tuple<int, int, int>;
    static_assert(yu::tuples::elementwise_predicate<non_predicate, U>);

    return 0;
}
```

### 出力

```plaintext
```
