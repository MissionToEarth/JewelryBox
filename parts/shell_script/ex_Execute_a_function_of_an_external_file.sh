#!/bin/bash
path=$(dirname $0)
external_file=$path/ex_function.sh

# read external file.
. $external_file

#実行
func 1 2 3 4
