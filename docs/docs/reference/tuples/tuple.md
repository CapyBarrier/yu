# `yu::tuples::tuple`

{{ status_mark('tuples.tuple') }}

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

1. {{ code(ref('tuples.size'), '_v<T>') }}が有効な式であり，`T`のTupleとしての要素数を表す定数式である．
2. `Idx`を，`0`以上{{ code(ref('tuples.size'), '_v<T>') }}未満を動く，`std::size_t`の定数式とする．それぞれの`Idx`に対して，以下の条件が成り立つ．
    1. {{ code(ref_fullname('tuples.get'), '<Idx>(t)') }}は有効な式である．
    2. {{ code(ref_fullname('tuples.get'), '<Idx>(t)') }}は`t`に対して等しさを保持する．
    3. {{ code(ref_fullname('tuples.get'), '<Idx>(t)') }}は`T`のTupleとしての`Idx`番目の要素を返す．
    4. {{ code(ref_fullname('tuples.get'), '<Idx>(t)') }}は`t`の値カテゴリを保存して要素を返す．
    5. {{ code(ref_fullname('tuples.get'), '<Idx>(t)') }}は，他の有効なインデックスでの呼び出し結果に影響しない．

これらの条件のうち，構文的な検証は{{ ref('tuples.tuple_structured') }}で行われる．


## 備考

`std::remove_cvref_t<T>`に対して{{ ref('tuples.known_tuple') }}が特殊化されていて`true`に評価されるとき，`tuple<T>`は{{ code(ref('tuples.tuple_structured'), '<T>') }}の評価をスキップする．
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