#!/bin/bash

# "."コマンドで shellスクリプトを読み込む事ができる。

# 渡された引数をチェック
func_print_params()
{
  echo "\$0=$0"
  echo "\$#=$#"
  echo "\$@=$@"
  echo "\$*=$*"
  echo "\$1=$1"
  echo "\$2=$2"
  echo "\$3=$3"
}

local_value()
{
	local num=0
	return num
}
