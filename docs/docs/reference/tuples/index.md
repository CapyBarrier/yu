# Yu.Tuples

Yu.Tuplesは，タプルとしてアクセス可能な型(Tuple)を統一的に扱う機能群を提供する．
C++標準ライブラリの`<ranges>`と`<algorithm>`が提供する操作を，RangeではなくTupleに対して同様に適用できる．
例えば，`<ranges>`が提供するRangeアダプタやビュー，`<algorithm>`が提供する各アルゴリズムを，Tupleに対して同じ構文で利用できる．

なお，このライブラリでは，"Tuple"という語を{{ ref('tuples.tuple') }}コンセプトで定義している．
用語"Tuple"と{{ ref('tuples.tuple') }}コンセプト，`std::tuple`を混同しないよう注意すること．

## 基本機能

### Tupleコンセプト

{{ entity_row_begin() }}
{{ entity_row('tuples.tuple', 'Tupleを定義するコンセプト') }}
{{ entity_row('tuples.tuple_structured', 'タプルとしてアクセス可能') }}

### アクセス

{{ entity_row_begin() }}
{{ entity_row('tuples.get', 'Tupleの要素にアクセスする') }}
{{ entity_row('tuples.size', 'Tupleの要素数を取得する') }}

### 型へのアクセス

{{ entity_row_begin() }}
{{ entity_row('tuples.element_t', 'Tupleの要素の型を取得する') }}

### カスタマイゼーションポイント

{{ entity_row_begin() }}
{{ entity_row('tuples.known_tuple', '構造検査を省略してTupleとみなす型を明示する') }}

### 関数呼び出し
{{ entity_row_begin() }}
{{ entity_row('tuples.apply', 'Tupleを展開して関数を呼び出す') }}


## 型トレイト

### 特性の観測


{{ entity_row_begin() }}
{{ entity_row('tuples.is_applicable', 'Tupleを展開して関数呼び出し可能かを調べる') }}
{{ entity_row('tuples.is_nothrow_applicable', '例外を投げずにTupleを展開して関数呼び出し可能かを調べる') }}
{{ entity_row('tuples.is_applicable_r', 'Tupleを展開して関数呼び出し可能で，その戻り値型がある型へ変換可能かを調べる') }}
{{ entity_row('tuples.is_nothrow_applicable_r', '例外を投げずにTupleを展開して関数呼び出し可能で，その戻り値型がある型へ変換可能かを調べる') }}


### 型の取得

{{ entity_row_begin() }}
{{ entity_row('tuples.apply_result', 'Tupleを展開して関数を呼び出した際の戻り値型を取得する') }}



### ユーティリティ

{{ entity_row_begin() }}
{{ entity_row('tuples.index_sequence_for', 'Tupleと同じ長さの0から始まる`std::index_sequence`を作る') }}


## コンセプト

### Tupleに対する制約

{{ entity_row_begin() }}
{{ entity_row('tuples.applicable', 'Tupleを展開して呼び出し可能') }}
{{ entity_row('tuples.regular_applicable', 'Tupleを展開して正則に呼び出し可能') }}


### Tupleの各要素に対する制約

{{ entity_row_begin() }}
{{ entity_row('tuples.elementwise_invocable', '各要素に対して呼び出しが可能') }}
{{ entity_row('tuples.elementwise_regular_invocable', '各要素に対して正則に呼び出しが可能') }}
{{ entity_row('tuples.elementwise_predicate', '各要素に対する述語') }}



