#!bin/sh 
set -eu
trap "echo trap00;  exit 1" SIGINT ERR

work_directory=$(cd $(dirname $0) && pwd)

echo $work_directory

