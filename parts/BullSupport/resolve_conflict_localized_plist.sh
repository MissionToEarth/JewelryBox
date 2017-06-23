#!/bin/sh

# 引数 $1 に指定されたパスに、バックアップを保存する。

set -eu
trap `echo $(pwd)失敗しちゃった` ERR

WORK_DIR=$(cd $(dirname $0) && pwd)

cp ../../../Resouce/conflict_tmp.plist ../../../Resouce/conflict_tmp.plist-bk
${WORK_DIR}/RsolveLoclizedPlist ../../../Resouce/conflict_tmp.plist 


# コンフリクトした
set +e
CONFLICT_PLISTS=$(git ls-files -u | grep Application/Resources/localized/.*plist)
set -e

echo ${CONFLICT_PLISTS}

for plist in CONFLICT_PLISTS do

	# オリジナルをバックアップ
	# cp ${plist} $1/${plist}.bk
	${WORK_DIR}/../cp.sh ${plist} $GIT_ROOT_DIR $DEST_DIR

	# 修正して上書きしてもらう。
	${WORK_DIR}/BullSupport ${plist} 
done

