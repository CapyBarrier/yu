# `yu::tuples::index_sequence_for`

{{ status_mark('yu::tuples::index_sequence_for') }}

```cpp
namespace yu::tuples {
    template <tuple T>
    using index_sequence_for = std::make_index_sequence<size_v<T>>;
}
```

## 概要

`index_sequence_for`は，{{ ref('yu::tuples::tuple') }}をインデックス展開するための`std::index_sequence`を生成する型エイリアステンプレートである．

## 例

```cpp
#include <iostream>
#include <utility>
#include <tuple>
#include <yu/tuples/index_sequence_for.hpp>

template <typename T, std::size_t... Idx>
void f(T&& tuple, std::index_sequence<Idx...>) {
    ((std::cout << yu::tuples::get<Idx>(tuple) << "\n"), ...);
}

template <typename T>
requires yu::tuples::tuple<T>
void g(T&& tup) {
  f(std::forward<T>(tup), yu::tuples::index_sequence_for<T>{});
}


int main() {
  g(std::make_tuple(1, 'a', "Hello"));
}
```

### 出力

```plaintext
1
a
Hello
```