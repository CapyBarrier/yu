# `yu::tuples::count_if`

{{ status_mark('yu::tuples::count_if') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        struct unspecified {
            template <tuple T, typename Pred, typename Proj = std::identity>
            requires elementwise_unary_predicate<Pred, projected<T, Pred>>
            static constexpr operator()(T&& t, Pred pred, Proj proj = {});
        };
    }

    inline namespace unspecified {
        inline constexpr unspecified count_if{};
    }
}
```