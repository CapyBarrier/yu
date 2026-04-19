# Yu.Tuples

Yu.Tuplesは，タプルとしてアクセス可能な型(Tuple)を統一的に扱う機能群を提供する．
C++標準ライブラリの`<ranges>`と`<algorithm>`が提供する操作を，RangeではなくTupleに対して同様に適用できる．
例えば，`<ranges>`が提供するRangeアダプタやビュー，`<algorithm>`が提供する各アルゴリズムを，Tupleに対して同じ構文で利用できる．

なお，このライブラリでは，"Tuple"という語を{{ ref('yu::tuples::tuple') }}コンセプトで定義している．
用語"Tuple"と{{ ref('yu::tuples::tuple') }}コンセプト，`std::tuple`を混同しないよう注意すること．

## 基本機能

### Tupleコンセプト

{{ entity_row_begin() }}
{{ entity_row('yu::tuples::tuple', 'Tupleを定義するコンセプト') }}
{{ entity_row('yu::tuples::tuple_structured', 'タプルとしてアクセス可能') }}

### アクセス

{{ entity_row_begin() }}
{{ entity_row('yu::tuples::get', 'Tupleの要素にアクセスする') }}
{{ entity_row('yu::tuples::size', 'Tupleの要素数を取得する') }}

### 型へのアクセス

{{ entity_row_begin() }}
{{ entity_row('yu::tuples::element_t', 'Tupleの要素の型を取得する') }}

### カスタマイゼーションポイント

{{ entity_row_begin() }}
{{ entity_row('yu::tuples::known_tuple', '構造検査を省略してTupleとみなす型を明示する') }}

### 関数呼び出し
{{ entity_row_begin() }}
{{ entity_row('yu::tuples::apply', 'Tupleを展開して関数を呼び出す') }}


## 型トレイト

### 特性の観測

{{ entity_row_begin() }}
{{ entity_row('yu::tuples::is_applicable', 'Tupleを展開して関数呼び出し可能かを調べる') }}
{{ entity_row('yu::tuples::is_nothrow_applicable', '例外を投げずにTupleを展開して関数呼び出し可能かを調べる') }}
{{ entity_row('yu::tuples::is_applicable_r', 'Tupleを展開して関数呼び出し可能で，その戻り値型がある型へ変換可能かを調べる') }}
{{ entity_row('yu::tuples::is_nothrow_applicable_r', '例外を投げずにTupleを展開して関数呼び出し可能で，その戻り値型がある型へ変換可能かを調べる') }}


### 型の取得

{{ entity_row_begin() }}
{{ entity_row('yu::tuples::apply_result', 'Tupleを展開して関数を呼び出した際の戻り値型を取得する') }}



### ユーティリティ

{{ entity_row_begin() }}
{{ entity_row('yu::tuples::index_sequence_for', 'Tupleと同じ長さの0から始まる`std::index_sequence`を作る') }}


## コンセプト

### Tupleに対する制約

{{ entity_row_begin() }}
{{ entity_row('yu::tuples::applicable', 'Tupleを展開して呼び出し可能') }}
{{ entity_row('yu::tuples::regular_applicable', 'Tupleを展開して正則に呼び出し可能') }}


### Tupleの各要素に対する制約

{{ entity_row_begin() }}
{{ entity_row('yu::tuples::elementwise_unary_invocable', '各要素に対して呼び出しが可能') }}
{{ entity_row('yu::tuples::elementwise_unary_predicate', '各要素に対する述語') }}



## アルゴリズム

Yu.Tuplesでは，標準ライブラリの`<algorithm>`がRangeに対して提供するものに対して，その対象をTupleへ写したアルゴリズムを提供する．
ただし，TupleとRangeの性質の差異によって，提供されるアルゴリズムの有無やシグネチャの形は，`<algorithm>`のそれと必ずしも一致しない．
例えば，Rangeは実行時にイテレータでアクセスできるが，Tupleへのアクセスではコンパイル時にインデックスが決定している必要があり，この制約によって提供されていないアルゴリズムが存在する．
また，`<algorithm>`では結果を出力イテレータに出力するアルゴリズムが，Yu.Tuplesでは結果を戻り値として返すことがある．

どのアルゴリズムも，意図せずADLで発見されてしまわないよう，関数オブジェクトとして定義される．

これらのアルゴリズムは，型レベルで事前に結果を計算できるときは，実際の処理を省略することがある．

### Tupleを変更しないアルゴリズム

{{ entity_row_begin() }}
{{ entity_row('yu::tuples::all_of', '全ての要素が条件を満たしているか調べる') }}
{{ entity_row('yu::tuples::any_of', '少なくとも1つの要素が条件を満たしているか調べる') }}
{{ entity_row('yu::tuples::none_of', 'どの要素も条件を満たしていないか調べる') }}
{{ entity_row('yu::tuples::contains', '指定された要素を含むことを調べる') }}
{{ entity_row('yu::tuples::contains_slice', '指定されたTupleを含むことを調べる') }}
{{ entity_row('yu::tuples::for_each', '全ての要素に対して処理を行う') }}
{{ entity_row('yu::tuples::for_each_n', '最初のN個の要素に対して処理を行う') }}
{{ entity_row('yu::tuples::count', '指定された値と等しい要素を数える') }}
{{ entity_row('yu::tuples::count_if', '指定された条件を満たす要素を数える') }}
{{ entity_row('yu::tuples::equal', '2つのTupleを等値比較する') }}
{{ entity_row('yu::tuples::starts_with', '先頭が指定されたTupleと一致するか調べる') }}
{{ entity_row('yu::tuples::ends_with', '末尾が指定されたTupleと一致するか調べる') }}

### Tupleの要素を畳み込むアルゴリズム

{{ entity_row_begin() }}
{{ entity_row('yu::tuples::fold_left', '左（先頭）からの畳み込み') }}
{{ entity_row('yu::tuples::fold_right', '右（終端）からの畳み込み') }}
{{ entity_row('yu::tuples::fold_left_first', '左（先頭）からの畳み込み．初期値を省略する') }}
{{ entity_row('yu::tuples::fold_right_last', '右（終端）からの畳み込み．初期値を省略する') }}


## 未分類

{{ entity_row('yu::tuples::projected', 'Tupleに対する射影の結果型を取得する') }}