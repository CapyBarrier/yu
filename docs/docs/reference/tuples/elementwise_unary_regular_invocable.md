# `yu::tuples::elementwise_unary_regular_invocable`

{{ status_mark('yu::tuples::elementwise_unary_regular_invocable') }}

```cpp
namespace yu::tuples {
    template <typename Fn, typename T>
    concept elementwise_unary_regular_invocable = see_below;
}
```

## 概要

`elementwise_unary_invocable`は，任意の関数呼び出し可能な型`Fn`が，型`T`をTupleとして展開した各要素によって正則に呼び出し可能であることを表すコンセプトである．
