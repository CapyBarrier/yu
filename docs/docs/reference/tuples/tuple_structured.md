# `yu::tuples::tuple_structured`

{{ status_mark('tuples.tuple_structured') }}

```cpp
namespace yu::tuples {
    template <typename T>
    concept tuple_structured = see_below;
}
```

## 概要

``tuple_structured``は，{{ ref('tuples.tuple') }}のモデルとなる型を構文的に厳密に判定するコンセプトである．

## モデル

ある型が``tuple_structured``のモデルであることは，{{ ref('tuples.tuple') }}のモデルであることと論理的に同値である．
{{ ref('tuples.tuple') }}を参照すること．