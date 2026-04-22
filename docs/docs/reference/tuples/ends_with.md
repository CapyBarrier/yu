# `yu::tuples::ends_with`

{{ status_mark('yu::tuples::ends_with') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        struct unspecified {
            template <
                tuple Tuple1,
                tuple Tuple2,
                typename Pred = std::ranges::equal_to,
                typename Proj1 = std::identity,
                typename Proj2 = std::identity
            >
            requires elementwise_binary_predicate<Pred, projected<Tuple1, Proj1>, projected<Tuple2, Proj2>>
            static constexpr bool operator()(Tuple1&& t1, Tuple2&& t2, Pred pred = {}, Proj1 proj1 = {}, Proj2 proj2= {});
        };
    }

    inline namespace unspecified {
        inline constexpr unspecified ends_with{};
    }
}
```