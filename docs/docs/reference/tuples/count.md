# `yu::tuples::count`

{{ status_mark('yu::tuples::count') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        struct unspecified {
            template <tuple Tuple, typename T, typename Proj = std::identity>
            requires elementwise_binary_predicate_with<std::ranges::equal_to, projected<Tuple, Proj>, T>
            static constexpr bool operator()(Tuple&& t, const T& value, Proj proj = {});
        };
    }

    inline namespace unspecified {
        inline constexpr unspecified count{};
    }
}
```