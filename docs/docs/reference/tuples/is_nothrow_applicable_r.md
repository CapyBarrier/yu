# `yu::tuples::is_nothrow_applicable_r`

{{ status_mark('tuples.is_nothrow_applicable_r') }}

```cpp
namespace yu::tuples {
    template <typename F, typename T>
    struct is_nothrow_applicable_r;

    template <typename F, typename T>
    inline constexpr bool is_nothrow_applicable_r_v = is_nothrow_applicable_r<F, T>::value;
}
```

## 概要

関数呼び出し可能な型`F`に対して、 Tupleである型`T`の要素を展開して関数呼び出しが可能で，その戻り値型が`R`に変換可能であり，さらにその際に例外を送出しないことを調べる。
`std::is_nothrow_invocable_r`の{{ ref('tuples.apply') }}版である．


## 効果

型`T`がTupleであり，`T`を展開して型`F`のオブジェクトを関数呼び出しする式が有効で，その戻り値型が`R`に変換可能であり，さらにその際に例外を送出しないのならば，`std::true_type`から派生する．
そうでなければ，`std::false_type`から派生する．