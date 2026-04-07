# `yu::tuples::is_applicable`

{% include 'unimplemented.md' %}

```cpp
namespace yu::tuples {
    template <typename F, typename T>
    struct is_applicable;

    template <typename F, typename T>
    inline constexpr bool is_applicable_v = is_applicable<F, T>::value;
}
```

## 概要

関数呼び出し可能な型`F`に対して、 Tupleである型`T`の要素を展開して関数呼び出しが可能であるか調べる。
`std::is_invocable`の{{linkof('yu::tuples::apply')}}版である．


## 効果

Tupleを展開して型`F`のオブジェクトを関数呼び出しする式が有効であれば，`std::true_type`から派生する．
そうでなければ，`std::false_type`から派生する．