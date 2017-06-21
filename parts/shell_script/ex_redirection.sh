echo "Script名" $0
echo "引数の数" $#

# リダイレクションのテスト
# echoによる標準入出力ストリームの利用

#　出力＝＝＝＝＝＝
echo abcdefg > abc
cat abc
#上書きする
echo xyz > abc
cat abc
#追記する
echo 0123 >> abc
echo -n 456 >> abc
echo " 789" >> abc
cat abc

#改行文字を含まない 0byte のファイルを作る。（touchでよいが）
echo -n > empty
cat empty

#入力＝＝＝＝＝
echo 
