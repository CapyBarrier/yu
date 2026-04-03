# `yu::tuples::tuple_structured`

{% include 'unstable.md' %}

```cpp
namespace yu::tuples {
    template <typename T>
    concept tuple_structured = see_below;
}
```

## 概要

``tuple_structured``は，{{ 'yu::tuples::tuple' | link }}のモデルとなる型を構文的に厳密に判定するコンセプトである．

## モデル

ある型が``tuple_structured``のモデルであることは，{{ 'yu::tuples::tuple' | link }}のモデルであることと論理的に同値である．
{{ 'yu::tuples::tuple' | link }}を参照すること．