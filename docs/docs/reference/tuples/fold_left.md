# `yu::tuples::fold_left`

{{ status_mark('yu::tuples::fold_left') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        struct unspecified {
            template <tuple Tuple, typename T, typename Fn>
            requires see_below
            static constexpr auto operator()(Tuple&& t, T init, Fn fn);
        };
    }

    inline namespace unspecified {
        inline constexpr unspecified fold_left{};
    }
}
```