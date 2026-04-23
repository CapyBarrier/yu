# `yu::tuples::fold_left_first`

{{ status_mark('yu::tuples::fold_left_first') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        struct unspecified {
            template <tuple Tuple, typename Fn>
            requires see_below
            static constexpr auto operator()(Tuple&& tuple, Fn fn);
        };
    }

    inline namespace unspecified {
        inline constexpr unspecified fold_left_first{};
    }
}
```