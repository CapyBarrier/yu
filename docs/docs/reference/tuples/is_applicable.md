# `yu::tuples::is_applicable`

{{ status_mark('yu::tuples::is_applicable') }}

```cpp
namespace yu::tuples {
    template <typename Fn, typename T>
    struct is_applicable;

    template <typename Fn, typename T>
    inline constexpr bool is_applicable_v = is_applicable<Fn, T>::value;
}
```

## 概要

関数呼び出し可能な型`Fn`に対して、 Tupleである型`T`の要素を展開して関数呼び出しが可能であるか調べる。
`std::is_invocable`の{{ ref('yu::tuples::apply') }}版である．


## 効果

型`T`がTupleであり，`T`を展開して型`Fn`のオブジェクトを関数呼び出しする式が有効であれば，`std::true_type`から派生する．
そうでなければ，`std::false_type`から派生する．