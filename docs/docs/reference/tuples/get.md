# `yu::tuples::get`

{{ status_mark('tuples.get') }}

```cpp
namespace yu::tuples {
    namespace unspecified {
        template <std::size_t Idx>
        struct unspecified {
            template <typename T>
            requires see_below
            static constexpr decltype(auto) operator()(T&& t) noexcept(see_below);
        };
    }

    inline namespace unspecified {
        template <std::size_t Idx>
        inline constexpr unspecified get{};
    }
}
```

## 概要

Tupleから指定した位置の要素を取得する関数オブジェクト．


## 制約

以下の少なくとも1つを満たすこと．
- `std::remove_cvref_t<T>`が要素数の判明している配列型である．
- `t.template get<Idx>()`が有効な式である．
- `get<Idx>(t)`の`get`の意味がADLのみによって決まる文脈で，有効な式である．

## 効果

部分式`expr`の型を`T`，`expr`を評価した値を`t`とする．
このとき，式`tuples::get<Idx>(expr)`の効果は以下の通りとなる．

1. `std::remove_cvref_t<T>`が要素数の判明している配列型であれば，`t[Idx]`と等価．
2. `t.template get<Idx>()`が有効な式であれば，`t.template get<Idx>()`と等価．
3. `get<Idx>(t)`の`get`の意味がADLのみによって決まる文脈で，`get<Idx>(t)`が有効な式であれば，`get<Idx>(t)`と等価．

以上のどれにも当てはまらないとき，呼び出しは不適格となる．


## 戻り値

Tupleオブジェクトの`Idx`番目の要素への参照．


## 例外

呼び出しが上記の制約を満たすとき，例外の有無は上記の効果で規定された等価な式と一致する．


## カスタマイゼーションポイント

2か3の条件を満たすようにする．
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