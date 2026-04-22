# `yu::tuples::fold_right_last`

{{ status_mark('yu::tuples::fold_right_last') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        struct unspecified {
            template <tuple Tuple, typename F>
            requires see_below
            static constexpr auto operator()(Tuple&& t, F fn);
        };
    }

    inline namespace unspecified {
        inline constexpr unspecified fold_right_last{};
    }
}
```