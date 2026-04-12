# `yu::tuples::is_applicable_r`

{{ status_mark('tuples.is_applicable_r') }}

```cpp
namespace yu::tuples {
    template <typename R, typename F, typename T>
    struct is_applicable_r;

    template <typename R, typename F, typename T>
    inline constexpr bool is_applicable_r_v = is_applicable_r<F, T>::value;
}
```

## 概要

関数呼び出し可能な型`F`に対して、 Tupleである型`T`の要素を展開して関数呼び出しが可能で，その戻り値型が`R`に変換可能かどうかを調べる．
`std::is_invocable_r`の{{ ref('tuples.apply') }}版である．


## 効果

Tupleを展開して型`F`のオブジェクトを関数呼び出しする式が有効で，その戻り値型が`R`に変換可能であれば，`std::true_type`から派生する．
そうでなければ，`std::false_type`から派生する．
