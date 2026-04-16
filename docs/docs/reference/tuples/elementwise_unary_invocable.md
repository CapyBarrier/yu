# `yu::tuples::elementwise_unary_invocable`

{{ status_mark('tuples.elementwise_unary_invocable') }}

```cpp
namespace yu::tuples {
    template <typename F, typename T>
    concept elementwise_unary_invocable = see_below;
}
```

## 概要

`elementwise_unary_invocable`は，任意の関数呼び出し可能な型`F`が，型`T`をTupleとして展開した各要素によって呼び出し可能であることを表すコンセプトである．


## 例

```cpp
#include <yu/tuples/elementwise_unary_invocable.hpp>
#include <tuple>
#include <string>
#include <type_traits>

struct printer {
    void operator()(int) const {}
    void operator()(double) const {}
    void operator()(const std::string&) const {}
};

struct int_only {
    void operator()(int) const {}
};

using T = std::tuple<int, double, std::string>;

static_assert(yu::tuples::elementwise_unary_invocable<printer, T>);
static_assert(!yu::tuples::elementwise_unary_invocable<int_only,T>);

using U = std::tuple<int, int, int>;
static_assert(yu::tuples::elementwise_unary_invocable<int_only, U>);
```

### 出力

```plaintext
```
