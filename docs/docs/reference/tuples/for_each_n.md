# `yu::tuples::for_each_n`

{{ status_mark('yu::tuples::for_each_n') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        template <std::size_t N>
        struct unspecified {
            template <tuple Tuple, typename Fn, typename Proj = std::identity>
            requires elementwise_unary_invocable<Fn, projected<Tuple, Proj>>
            static constexpr operator()(Tuple&& tuple, Fn fn, Proj proj = {})
        }
    }

    inline namespace unspecified {
        template <std::size_t N>
        inline constexpr unspecified for_each_n{};
    }
}
```