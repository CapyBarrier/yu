# `yu::tuples::element_type`

{% include 'unstable.md' %}

```cpp
namespace yu::tuples {
    template <std::size_t Idx, typename T>
    struct element_type;

    template <std::size_t Idx, typename T>
    using element_type_t = element_type<Idx, T>::type;
}
```

## 概要

``element_type``は，Tupleから`Idx`番目の要素の型を取得する．


## 効果

1. {{ code('yu::tuples::size' | link, '<T>') }}が有効な式でなければ，メンバ型エイリアス`type`は定義されない．
2. {{ code('yu::tuples::size' | link, '<T>') }}でなければ，メンバ型エイリアス`type`は定義されない．
3. `std::remove_cvref_t<T>`が要素数の判明している配列型ならば，その配列の型をメンバ型エイリアス`type`として定義する．
4. `std::tuple_element_t<Idx, std::remove_cvref_t<T>>`が有効な型であれば，`std::tuple_element_t<Idx, std::remove_cvref_t<T>>`をメンバ型エイリアス`type`として定義する．

以上のどれにも当てはまらないとき，メンバ型エイリアス`type`は定義されない．


## カスタマイゼーションポイント

4の条件を満たすようにする．`std::tuple_element`を特殊化することでカスタマイズできる．


## 例

```cpp
#include <tuple>
#include <type_traits>
#include <yu/tuples/element_type.hpp>

int main() {
    // std::tuple
    {
        using T = std::tuple<int, char, double>;

        static_assert(std::is_same_v<yu::tuples::element_type_t<0, T> , int>);
        // 参照でもよい
        static_assert(std::is_same_v<yu::tuples::element_type_t<0, T&> , int>);
    }

    // 組み込み配列
    {
        using T = double [1];

        static_assert(std::is_same_v<yu::tuples::element_type_t<0, T> , double>);
    }
}
```

### 出力

```plaintext

```