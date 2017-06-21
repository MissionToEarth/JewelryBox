#!/bin/bash -eu

if [ $# -lt 2 ] ; then
echo 'BULL専用 インポートツール のためのヘルパー。'
echo '次の引数を指定してください。'
echo 'param1：保存先のプロジェクトディレクトリ　param2：コピー元のディレクトリ'
exit -1
fi
if [ -e $1 -a -e $2  ] ; then
echo 'あるよ'
else
echo 'ないよ'
fi

dest_dir=$1
echo dest_dir$original$origina$original
2先のフecho ${original/$1/}
    ァイル一覧取得　


original_files=[]
for original in `find $1` ; do
    echo "------保存先ファイルｰｰｰｰｰｰ"$original
    echo ${original/$1/}
    original_files+=(${original/$2/})
done
echo ${original_files[@]}

exit 0


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