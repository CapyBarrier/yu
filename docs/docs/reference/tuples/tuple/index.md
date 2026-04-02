# `yu::tuples::tuple`

{% include 'unstable.md' %}

```cpp
namespace yu::tuples {

template <typename T>
concept tuple = known_tuple<std::remove_cvref_t<T>> || tuple_structured<T>;

}
```

## 概要

`tuple`は，Tupleを定義するコンセプトである．


## モデル

`decltype((t))`が`T&`であるような式`t`があるとする．
`T`が`tuple`のモデルとなるのは，以下の条件をすべて満たす場合である．

1. {{ code('yu::tuples::size' | link, '<T>') }}が有効な式であり，`T`のTupleとしての要素数を表す定数式である．
2. `Idx`を，`0`以上{{ code('yu::tuples::size' | link, '<T>') }}未満を動く，`std::size_t`の定数式とする．
    1. それぞれの`Idx`に対して，{{ code('yu::tuples::get' | link, '<Idx>(t)') }}は有効な式である．
    2. それぞれの`Idx`に対して，{{ code('yu::tuples::get' | link, '<Idx>(t)') }}は，`T`のTupleとしての`Idx`番目の要素を返す．
    3. それぞれの`Idx`に対して，{{ code('yu::tuples::get' | link, '<Idx>(t)') }}は等しさを保持する．

これらの条件のうち，構文的な検証はすべて{{ 'yu::tuples::tuple_structured' | link }}で行われる．


## 備考

`std::remove_cvref_t<T>`に対して{{ 'yu::tuples::known_tuple' | link }}が特殊化されていて`true`に評価されるとき，`tuple<T>`は{{ code('yu::tuples::tuple_structured' | link, '<T>') }}の評価をスキップする．
`tuple`のモデルでない型`T`に対して評価をスキップした場合，プログラムの動作は保障されない．


## 例

```cpp
#include <tuple>
#include <array>
#include <yu/tuples/tuple.hpp>

int main() {
    static_assert(yu::tuples::tuple<std::tuple<int, double, char>>);
    static_assert(yu::tuples::tuple<std::array<double, 3>>);
    // 要素数の判明している組み込み配列型もtupleのモデルである
    static_assert(yu::tuples::tuple<char [2]>);
}
```

### 出力

```plaintext

```