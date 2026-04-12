# `yu::tuples::apply_result`

{{ status_mark('tuples.apply_result') }}

```cpp
namespace yu::tuples {
    template <typename F, typename T>
    struct apply_result;

    template <typename F, typename T>
    using apply_result_t = typename apply_result<F, Tuple>::type;
}
```

## 概要

関数呼び出し可能な型`F`に対して、 Tupleである型`T`の要素を展開して関数呼び出しした場合の戻り値型を取得する。
`std::invoke_result`の{{ ref('tuples.apply') }}版である．


## 効果

Tupleを展開して型`F`のオブジェクトを関数呼び出しする式が有効であれば，その式の型をメンバ型エイリアス`type`に定義する．そうでなければ，メンバ型エイリアス`type`は定義されない．


## 例

```cpp
#include <tuple>
#include <type_traits>
#include <string>

int add(int a, int b) { return a + b; }

int main() {
    static_assert(std::is_same_v<std::apply_result_t<decltype(&add), std::tuple<int, int>>, int>);
}
```

## 出力

```plaintext
```