#!/bin/sh

# 引数 
# $1:Gitルートディレクトリ、
# $2:保存先絶対パス　バックアップを保存する。

 if [ $# -lt 2 ]; then
 	echo "Error:　パラメタが足りません。"
 	echo "param1:git root directory, param2:backup directory"
 	exit 1
 fi

set -eu
trap `echo $(pwd)失敗しちゃった` ERR

WORK_DIR=$(cd $(dirname $0) && pwd)
# GIT_ROOT_DIR="/Users/t-harada/develop_wp/BULL"
# DEST_DIR="/Users/t-harada/develop_wp/_EX_"
GIT_ROOT_DIR=$1
DEST_DIR=$2

# コンフリクトした
set +e
CONFLICT_PLISTS=$(git status -s | awk '$1 == "UU" && $2 ~ /^*[.]plist/{ print $2 }')
set -e

echo ${CONFLICT_PLISTS}

for plist in $CONFLICT_PLISTS
do
	echo "るーぷ"
	# オリジナルをバックアップ
	# cp ${plist} $1/${plist}.bk
	${WORK_DIR}/../cp.sh ${WORK_DIR}/${plist} $GIT_ROOT_DIR $DEST_DIR

	# 修正して上書きしてもらう。
	${WORK_DIR}/ResolveLoclizedPlist ${WORK_DIR}/${plist} 

	echo ""$?
done

