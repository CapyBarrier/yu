# `yu::tuples::projected`

{{ status_mark('yu::tuples::projected') }}

```cpp
namespace yu::tuples {
    template <tuple Tuple, elementwise_unary_regular_invocable<Tuple> Proj>
    struct projected {
        template <std::size_t Idx>
        requires (Idx < size_v<Tuple>)
        std::invoke_result_t<Proj, element_t<Idx, Tuple>> get() const; // 宣言のみ
    };

    template <tuple Tuple, elementwise_unary_regular_invocable<Tuple> Proj>
    inline constexpr bool known_tuple<projected<Tuple, Proj>> = known_tuple<Tuple>;
}

namespace std {
    template <yu::tuples::tuple Tuple, yu::tuples::elementwise_unary_regular_invocable<Tuple> Proj>
    struct tuple_size<yu::tuples::projected<Tuple, Proj>> : yu::tuples::size<Tuple> {};
}
```

## 概要

Tupleな型`Tuple`に任意の射影`Proj`を適用した結果を表すTupleな型を生成する．

これは射影を受け取るコンセプトやアルゴリズムを制約するために使用するものであり，評価される文脈で使用してはならない．
