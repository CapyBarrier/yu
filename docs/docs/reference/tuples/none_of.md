# `yu::tuples::none_of`

{{ status_mark('yu::tuples::none_of') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        struct unspecified {
            template <tuple Tuple, typename Pred, typename Proj = std::identity>
            requires elementwise_unary_predicate<Pred, projected<Tuple, Proj>>
            static constexpr bool operator()(Tuple&& tuple, Pred pred, Proj proj = {});
        };
    }

    inline namespace unspecified {
        inline constexpr unspecified all_of{};
    }
}
```