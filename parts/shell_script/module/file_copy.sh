#ファイルをコピーします。
# パラメータ：元のファイルパス　送り先のディレクトリ　＜＜これだけではcpするだけなので無意味。


trap "echo trap00;  exit 1" SIGINT

echo $0

# check paramater
# require $1 is file path 
# 未実装

# 単純なコピー
cp $1 $2

# error check
# 失敗していたら処理を止める。


echo $!
echo $?
echo -e '\a'

echo $0
echo "Complete file copy."