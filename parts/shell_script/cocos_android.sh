#!/bin/bash -eu

# cocos2dx android
#　WP:BULLのAndroidビルド　実行まで。

#中断した場合のトラップ （Ctrl+Cなどの場合）
trap "echo trap00;  exit 1" SIGINT

cmd_param=""
if [[ ${1} = "release" ]]; then
	#statements
	echo release build
	cmd_param="-b release"
elif [[ ${1} = "debug" ]]; then
	#statements
	echo debug build
elif [[ ${1} = "gradle" ]]; then
	# source ~/.bash_profile
	wonderplanet_crashfeaver_bull_
	cd ./Application
	./gradlew clean check assembleRelease
	echo $!
	echo $?
	adb install -r ./proj.android/build/outputs/apk/proj.android-release.apk
	echo $!
	echo $?
	echo -e '\a'
	exit 0	
elif [[ ${1} = "install" ]]; then
	# source ~/.bash_profile
	wonderplanet_crashfeaver_bull_
	cd ./Application
	adb install -r ./proj.android/build/outputs/apk/proj.android-release.apk
	echo $!
	echo $?
	echo -e '\a'
	exit 0
fi

echo "Script名" $0
echo "引数の数:" $#
echo "option" ${cmd_param}

# source ~/.bash_profile

wonderplanet_crashfeaver_bull_

# gradlewについて、スクリプトがあるディレクトリに移動してから実行しないといけないらしいため移動させた
cd ./Application

./proj.android/build_native.py ${cmd_param}

echo $!
echo $?
echo -e '\a'

# 問題　ビルドに失敗した場合　も　継続してしまう　ひどい


./gradlew clean check assembleRelease

echo $!
echo $?
echo -e '\a'


adb install -r ./proj.android/build/outputs/apk/proj.android-release.apk
echo $!
echo $?
echo -e '\a'
echo -e '\a'
echo -e '\a'
