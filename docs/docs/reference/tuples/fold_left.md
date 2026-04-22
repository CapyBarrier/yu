# `yu::tuples::fold_left`

{{ status_mark('yu::tuples::fold_left') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        struct unspecified {
            template <tuple Tuple, typename T, typename F>
            requires see_below
            static constexpr auto operator()(Tuple&& t, T init, F fn);
        };
    }

    inline namespace unspecified {
        inline constexpr unspecified fold_left{};
    }
}
```