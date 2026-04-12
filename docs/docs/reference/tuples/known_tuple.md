# `yu::tuples::known_tuple`

{{ status_mark('tuples.known_tuple') }}

```cpp
namespace yu::tuples {
    template <typename T>
    inline constexpr bool known_tuple = false;                                  // (1)

    template <typename T, std::size_t N>
    inline constexpr bool known_tuple<T [N]> = true;                            // (2)

    template <typename... Ts>
    inline constexpr bool known_tuple<std::tuple<Ts...>> = true;                // (3)

    template <typename T, std::size_t N>
    inline constexpr bool known_tuple<std::array<T, N>> = true;                 // (4)

    template <typename T1, typename T2>
    inline constexpr bool known_tuple<std::pair<T1, T2>> = true;                // (5)

    template <typename I, typename S, std::ranges::subrange_kind K>
    inline constexpr bool known_tuple<std::ranges::subrange<I, S, K>> = true;   //(6)
}
```

## 概要

{{ ref('tuples.tuple') }}コンセプトの評価の動作をカスタマイズする変数テンプレート．
`known_tuple<T>`が`true`となる型`T`に対して，{{ ref('tuples.tuple') }}コンセプトは評価を短絡する．

* (1): `T`に対して`known_tuple<T>`が特殊化されていないとき，デフォルトではカスタマイズされない．
* (2): 要素数の判明している配列型に対してカスタマイズするための部分特殊化．
* (3)-(6): C++23で*tuple-like*だと規定されている型に対してカスタマイズするための部分特殊化

{{ ref('tuples.tuple') }}のモデルでない型に対する特殊化によってカスタマイズしたとき，プログラムの動作は保障されない．