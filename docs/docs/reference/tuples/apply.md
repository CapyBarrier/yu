# `yu::tuples::apply`

{{ status_mark('yu::tuples::apply') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        struct unspecified {
            template <typename Fn, tuple Tuple>
            static constexpr apply_result_t<Fn, Tuple> operator()(Fn&& fn, Tuple&& tuple) noexcept(is_nothrow_applicable_v<Fn, Tuple>);
        };
    }

    inline namespace unspecified {
        inline constexpr unspecified apply{};
    }
}
```

### 概要

Tupleを展開し，関数の引数に適用してその関数を実行する．


### 制約

適用先の関数はCallableであること．

### 効果

次のような関数があるとき，
```cpp
template<typename Fn, tuple Tuple, std::size_t... Idx>
constexpr decltype(auto) apply_impl(Fn&& fn, Tuple&& tuple, std::index_sequence<Idx...>) {
  return std::invoke(std::forward<Fn>(fn), tuples::get<Idx>(std::forward<Tuple>(tuple))...);
}
```
次と等価である．
```cpp
apply_impl(std::forward<Fn>(fn), std::forward<Tuple>(tuple), index_sequence_for<Tuple>{});
```

### 戻り値

適用した関数呼び出しの戻り値


### 例外

例外指定は{{ ref('yu::tuples::is_nothrow_applicable_v<Fn, Tuple>') }}による．
