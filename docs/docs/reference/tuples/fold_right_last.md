# `yu::tuples::fold_right_last`

{{ status_mark('yu::tuples::fold_right_last') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        struct unspecified {
            template <tuple Tuple, typename Fn>
            requires see_below
            static constexpr auto operator()(Tuple&& t, Fn fn);
        };
    }

    inline namespace unspecified {
        inline constexpr unspecified fold_right_last{};
    }
}
```