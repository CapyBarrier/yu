# `yu::tuples::projected`

{{ status_mark('yu::tuples::projected') }}

```cpp
namespace yu::tuples {
    template <tuple T, elementwise_unary_regular_invocable<T> Proj>
    struct projected {
        template <std::size_t Idx, typename U>
        requires (Idx < size_v<U>)
        std::invoke_result_t<Proj, element_t<Idx, U>> get() const; // 宣言のみ
    };

    template <tuple T, elementwise_unary_regular_invocable<T> Proj>
    inline constexpr bool known_tuple = known_tuple<T>;
}

namespace std {
    template <yu::tuples::tuple T, yu::tuples::elementwise_unary_regular_invocable<T> Proj>
    struct tuple_size<yu::tuples::projected<T, Proj>> : yu::tuples::size<T> {};
}
```

## 概要

Tupleな型`T`に任意の射影`Proj`を適用した結果を表すTupleな型を生成する．

これは射影を受け取るコンセプトやアルゴリズムを制約するために使用するものであり，評価される文脈で使用してはならない．