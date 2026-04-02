# `yu::tuples::get`

{% include 'unstable.md' %}

```cpp
namespace yu::tuples {
    inline namespace unspecified {
        template <std::size_t Idx>
        inline constexpr unspecified get = unspecified;
    }
}
```

## 概要

Tupleから指定した位置の要素を取得する関数オブジェクト．


## 効果

部分式`expr`の型を`T`，`expr`を評価した値を`t`とする．
このとき，式`yu::tuples::get<Idx>(expr)`の効果は以下の通りとなる．

1. {{ code('yu::tuples::size' | link, '<T>') }}が有効な式でなければ，呼び出しは不適格．
2. {{ code('Idx < ', 'yu::tuples::size' | link, '<T>') }}でなければ，呼び出しは不適格．
3. `std::remove_cvref_t<T>`が要素数の判明している配列型であれば，`t[Idx]`と等しい．
4. `t.template get<Idx>()`が有効な式であれば，`t.template get<Idx>()`と等しい．
5. `get<Idx>(t)`の`get`の意味がADLのみによって決まるコンテキストで，`get<Idx>(t)`が有効な式であれば，`get<Idx>(t)`と等しい．

以上のどれにも当てはまらないとき，呼び出しは不適格となる．


## 戻り値

Tupleオブジェクトの`Idx`番目の要素への参照．
その値カテゴリはTupleオブジェクトの値カテゴリに従う．


## カスタマイゼーションポイント

5か6の条件を満たすようにする．
例えば，ユーザー定義のフリー関数テンプレート`get<Idx>`を定義するか，ユーザー定義のクラスにメンバ関数テンプレート`get<Idx>`を持たせることでカスタマイズできる．


## 例

```cpp
#include <tuple>
#include <string>
#include <yu/tuples/get.hpp>

int main() {
    // std::tuple
    {
    std::tuple<int, char, std::string> tup(1, 'a', "hello");

    std::string& i = yu::tuples::get<2>(tup);
    std::cout << i << std::endl;
    }

    // 組み込み配列
    {
        int arr[3] = {1, 2, 3};

        int& i = yu::tuples::get<1>(arr);
        std::cout << i << std::endl;
    }
}
```

### 出力

```plaintext
hello
2
```