# `yu::tuples::apply`

{{ status_mark('yu::tuples::apply') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        struct unspecified {
            template <typename F, tuple T>
            static constexpr apply_result_t<F, T> operator()(F&& f, T&& t) noexcept(is_nothrow_applicable_v<F, T>);
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
template<typename F, tuple T, std::size_t... Idx>
constexpr decltype(auto) apply_impl(F&& f, T&& t, std::index_sequence<Idx...>) {
  return std::invoke(std::forward<F>(f), tuples::get<Idx>(std::forward<T>(t))...);
}
```
次と等価である．
```cpp
apply_impl(std::forward<F>(f), std::forward<T>(t), index_sequence_for<T>{});
```

### 戻り値

適用した関数呼び出しの戻り値


### 例外

例外指定は{{ ref('yu::tuples::is_nothrow_applicable_v<F, Tuple>') }}による．
