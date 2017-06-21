#!/bin/bash -eu
# $1保存先ディレクトリ
# $2コピー元ディレクトリ

if [ $# -lt 2 ] ; then
echo 'BULL専用 インポートツール のためのヘルパー。'
echo '次の引数を指定してください。'
echo 'param1：保存先のプロジェクトディレクトリ　param2：コピー元のディレクトリ'
exit -1
fi

if [ -d $1 -a -d $2 ];then
:
else
echo "parameter is not directory!"
exit -1
fi

if [ -e $1 -a -e $2  ] ; then
echo 'あるよ'
else
echo 'ないよ'
fi

dest_dir=$1
echo dest_dir

# 保存先のファイル一覧取得　
original_files=[]
for original in `find $1` ; do
    echo "------保存先ファイルｰｰｰｰｰｰ"
    echo `basename $original`
    original_files+=($original)
done
echo ${original_files[@]}

# コピー元ファイル一覧
import_files=()
for tgt in `find $2`; do

    echo ${tgt/$2/}

    echo $1${tgt/$2/}
    if [ -e $1${tgt/$2/} ] ; then
        echo "ある"
    else
        echo "ない"
    fi

    n=`basename $1${tgt/$2/}`
    echo $n
    import_files+=($tgt)    

    value='Mm'

    if [ $(echo $tgt | grep -e $value) ]; then
        echo "HIT!" $value
    else
        echo "doesn't include"
    fi

done

echo "はいす"${import_files[@]}


# 文字列の比較
if [ ${foo} = ${var} ]; then
    echo "equal"
fi