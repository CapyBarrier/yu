# `yu::tuples::tuple_structured`

```cpp
namespace yu::tuples {
    template <typename T>
    concept tuple_structured = see below;
}
```

## 概要

``tuple_structured``は，{{ entity_link('tuple', '..') }}のモデルとなる型を構文的に厳密に判定するコンセプトである．

## モデル

ある型が``tuple_structured``のモデルであることは，{{ entity_link('tuple', '..') }}のモデルであることと論理的に同値である．
{{ entity_link('tuple', '..') }}を参照すること．