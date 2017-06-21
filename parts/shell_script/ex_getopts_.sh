#!/bin/sh

cat ${0##*/}
cat $0

# getopts 最小サンプル
function sample()
{
  echo 引数=$1
  getopts "adh" opts
  echo getopts結果=$opts
}

# 一般的なサンプル
function getopts_sample()
{
	local OPTIND OPTARG OPT ## [@重要]:グローバル変数を汚さないようにする。（関数内で使い場合特に。）

	while getopts "a:b:" OPT; do
		case $OPT in
			a )
				echo $OPT
				echo $OPTARG
				;;
			b )
				echo $OPT
				echo $OPTARG
				;;
		    \? )
				echo $OPT
        		echo nothing matched
        		;;
		esac
	done
}

getopts_sample -a wawawa -b amb bang -d -e -f -e