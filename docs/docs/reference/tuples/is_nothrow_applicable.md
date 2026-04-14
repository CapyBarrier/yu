# `yu::tuples::is_nothrow_applicable`

{{ status_mark('tuples.is_applicable') }}

```cpp
namespace yu::tuples {
    template <typename F, typename T>
    struct is_nothrow_applicable;

    template <typename F, typename T>
    inline constexpr bool is_nothrow_applicable_v = is_nothrow_applicable<F, T>::value;
}
```

## 概要

関数呼び出し可能な型`F`に対して、 Tupleである型`T`の要素を展開して関数呼び出しが可能で，その際に例外を送出しないことを調べる。
`std::is_nothrow_invocable`の{{ ref('tuples.apply') }}版である．


## 効果

型`T`がTupleであり，`T`を展開して型`F`のオブジェクトを関数呼び出しする式が有効であれば，`std::true_type`から派生する．
そうでなければ，`std::false_type`から派生する．