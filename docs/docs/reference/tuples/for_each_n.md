# `yu::tuples::for_each_n`

{{ status_mark('yu::tuples::for_each_n') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        template <std::size_t N>
        struct unspecified {
            template <tuple Tuple, typename F, typename Proj = std::identity>
            requires elementwise_unary_invocable<F, projected<T, Proj>>
            static constexpr operator()(Tuple&& t, F f, Proj proj = {})
        }
    }

    inline namespace unspecified {
        template <std::size_t N>
        inline constexpr unspecified for_each_n{};
    }
}
```