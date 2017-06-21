# コマンドの実行結果を変数に保存
# バッククォートを使用する。　または、丸カッコ()でも可能
echo 開始
VAR=`python3 --version`
echo 変数代入終了
echo 結果＝${VAR}

echo 開始
#これも同様の意味。
VAR_2=(python3 --version)
echo 変数代入終了
echo 結果＝${VAR_2}
