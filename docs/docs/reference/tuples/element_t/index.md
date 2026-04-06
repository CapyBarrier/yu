# `yu::tuples::element_t`

```cpp
namespace yu::tuples {
    template <std::size_t Idx, typename T>
    using element_t = decltype(yu::tuples::get<Idx>(std::declval<T>()));
}
```

## 概要

Tupleから、指定した位置の要素の型を取得する。


## 例

```cpp
#include <yu/tuples/element_t.hpp>
#include <tuple>
#include <type_traits>

int main() {
    // std::tuple
    {
        using T = std::tuple<int, char, double>;

        static_assert(std::is_same_v<yu::tuples::element_t<0, T>, int&&>);
    }

    // 組み込み配列
    {
        using T = double[1];

        static_assert(std::is_same_v<yu::tuples::element_t<0, T>, double&&>);
    }
}
```

### 出力

```plaintext

```
