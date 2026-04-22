# `yu::tuples::for_each`

{{ status_mark('yu::tuples::for_each') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        struct unspecified {
            template <tuple Tuple, typename F, typename Proj = std::identity>
            requires elementwise_unary_invocable<F, projected<T, Proj>>
            static constexpr operator()(Tuple&& t, F f, Proj proj = {})
        }
    }

    inline namespace unspecified {
        inline constexpr unspecified for_each{};
    }
}
```