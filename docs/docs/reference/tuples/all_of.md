# `yu::tuples::all_of`

{{ status_mark('yu::tuples::all_of') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        struct unspecified {
            template <
                tuple T
                elementwise_unary_invocable<T> Proj = std::identity
                elementwise_unary_predicate<projected<T>> Pred
            >
            static constexpr bool operator()(T&& t, Pred pred, Proj proj = {});
        };
    }

    inline namespace unspecified {
        inline constexpr unspecified all_of{};
    }
}
```

## 概要