# Yu.Meta

Yu.Metaは，メタプログラミングのための基本的な機能と，組み合わせて使うための型リストを提供する．
このライブラリは，他のYuサブライブラリにインクルードされることを前提とする．

## メタ関数操作

| 名前                                           | 説明                                                         | バージョン | 状態   |
| ---------------------------------------------- | ------------------------------------------------------------ | ---------- | ------ |
| {{linkof('yu::meta::wrap_fn')}}                | メタ関数をラップする                                         | -          | 未実装 |
| {{linkof('yu::meta::invoke')}}                 | メタ関数に指定した型を適用する                               | -          | 未実装 |
| {{linkof('yu::meta::unwrap_invoke')}}          | ラップされたメタ関数に指定した型を適用する                   | -          | 未実装 |
| {{linkof('yu::meta::apply_type_list')}}        | メタ関数に指定した型リストの要素を展開し適用する             | -          | 未実装 |
| {{linkof('yu::meta::unwrap_apply_type_list')}} | ラップされたメタ関数に指定した型リストの要素を展開し適用する | -          | 未実装 |
| {{linkof('yu::meta::bind_front')}}             | メタ関数の引数を先頭から順に部分適用する                     | -          | 未実装 |
| {{linkof('yu::meta::bind_back')}}              | メタ関数の引数を末尾から順に部分適用する                     | -          | 未実装 |

## 型リスト

| 名前                              | 説明                     | バージョン | 状態   |
| --------------------------------- | ------------------------ | ---------- | ------ |
| {{linkof('yu::meta::type_list')}} | 複数の型を格納するリスト | -          | 未実装 |

### 観測

| 名前                                           | 説明                                       | バージョン | 状態   |
| ---------------------------------------------- | ------------------------------------------ | ---------- | ------ |
| {{linkof('yu::meta::type_list::size')}}        | 要素数を取得する                           | -          | 未実装 |
| {{linkof('yu::meta::type_list::empty')}}       | 空かどうか調べる                           | -          | 未実装 |
| {{linkof('yu::meta::type_list::at')}}          | 指定位置の要素を取得する                   | -          | 未実装 |
| {{linkof('yu::meta::type_list::front')}}       | 先頭の要素を取得する                       | -          | 未実装 |
| {{linkof('yu::meta::type_list::back')}}        | 末尾の要素を取得する                       | -          | 未実装 |
| {{linkof('yu::meta::type_list::all_of')}}      | 全ての要素が条件を満たしているかを調べる   | -          | 未実装 |
| {{linkof('yu::meta::type_list::any_of')}}      | どれかの要素が条件を満たしているかを調べる | -          | 未実装 |
| {{linkof('yu::meta::type_list::none_of')}}     | 全ての要素が条件を満たしていないかを調べる | -          | 未実装 |
| {{linkof('yu::meta::type_list::find')}}        | 指定された値を検索する                     | -          | 未実装 |
| {{linkof('yu::meta::type_list::find_if')}}     | 条件を満たす最初の要素を検索する           | -          | 未実装 |
| {{linkof('yu::meta::type_list::find_if_not')}} | 条件を満たしていない最初の要素を検索する   | -          | 未実装 |
| {{linkof('yu::meta::type_list::count')}}       | 指定された値である要素の数を数える         | -          | 未実装 |
| {{linkof('yu::meta::type_list::count_if')}}    | 条件を満たしている要素の数を数える         | -          | 未実装 |
| {{linkof('yu::meta::type_list::equal')}}       | 2つのリストを等値比較する                  | -          | 未実装 |


### 変更

| 名前                                          | 説明                                                 | バージョン | 状態   |
| --------------------------------------------- | ---------------------------------------------------- | ---------- | ------ |
| {{linkof('yu::meta::type_list::append')}}     | 末尾に要素を追加する                                 | -          | 未実装 |
| {{linkof('yu::meta::type_list::prepend')}}    | 先頭に要素を追加する                                 | -          | 未実装 |
| {{linkof('yu::meta::type_list::insert')}}     | 指定位置へ要素を挿入する                             | -          | 未実装 |
| {{linkof('yu::meta::type_list::erace')}}      | 指定位置の要素を削除する                             | -          | 未実装 |
| {{linkof('yu::meta::type_list::transform')}}  | 全ての要素に関数を適用する                           | -          | 未実装 |
| {{linkof('yu::meta::type_list::replace')}}    | 指定された型と一致する要素を指定された型に置き換える | -          | 未実装 |
| {{linkof('yu::meta::type_list::replace_if')}} | 条件を満たす要素を指定された型に置き換える           | -          | 未実装 |
| {{linkof('yu::meta::type_list::remove')}}     | 指定された要素を除ける                               | -          | 未実装 |
| {{linkof('yu::meta::type_list::remove_if')}}  | 条件を満たす要素を除ける                             | -          | 未実装 |
| {{linkof('yu::meta::type_list::unique')}}     | 重複した要素を除ける                                 | -          | 未実装 |
| {{linkof('yu::meta::type_list::reverse')}}    | 要素の並びを逆にする                                 | -          | 未実装 |
