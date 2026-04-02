# `yu::tuples::size`

{% include 'unstable.md' %}

```cpp
namespace yu::tuples {
    template <typename T>
    struct size;

    template <typename T>
    inline constexpr std::size_t size_v = size<T>::value;
}
```

## 概要

`size`は，Tupleの要素数を取得する．


## 効果

1. `std::remove_cvref_t<T>`が要素数の判明している配列型ならば，その配列の要素数を静的メンバ定数`value`として定義する．
2. `std::tuple_size_v<std::remove_cvref_t<T>>`が有効な式であれば，`std::tuple_size_v<std::remove_cvref_t<T>>`を静的メンバ定数`value`として定義する．

以上のどれにも当てはまらないとき，静的メンバ定数`value`は定義されない．


## カスタマイゼーションポイント

2の条件を満たすようにする．`std::tuple_size`を特殊化することでカスタマイズできる．


## 例

```cpp
#include <tuple>
#include <yu/tuples/size.hpp>

int main() {
    // std::tuple
    {
        using T = std::tuple<int, char>;

        static_assert(2 == yu::tuples::size<T>::value);
        // 参照でもよい
        static_assert(2 == yu::tuples::size<T&>::value);
    }

    // 組み込み配列
    {
        using T = int [5];

        static_assert(5 == yu::tuples::size<T>::value);
    }
}
```

### 出力

```plaintext

```