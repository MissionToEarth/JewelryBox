#!/bin/sh
 
# ■ パーミッションを自動で元に戻すスクリプト
#
# ■ 概要
#
# 環境によって git clone したファイルのパーミッションが変わってしまうことがある。
# その時 git diff した時に下記のようなパーミッション変更だけの情報が表示される。
#
# diff --git a/Smarty/templates/admin/order/mail.txt b/Smarty/templates/admin/order/mail.txt
# old mode 100644          
# new mode 100755
#
# これを手作業で chmod 644 Smarty/templates/admin/order/mail.txt とやると
# 大変なので自動化する。
#
 
GIT_PAGER=cat git diff | awk '{
    LINE[FNR] = $0 # FNR は現在の行番号
}
END {
    for(i = 1; i <= FNR; i++){
        split(LINE&#91;i&#93;, arr);
        if ( arr&#91;1&#93; == "diff" ){
            filepath = arr&#91;3&#93;; # a/xxxx/yyy/zzz.php のようになっている("a/" が邪魔)
 
            i++;
            split(LINE&#91;i&#93;, arr);
            old_mode = arr&#91;3&#93;;
 
 
            i++;
            split(LINE&#91;i&#93;, arr);
            new_mode = arr&#91;3&#93;;
 
            sub("a/", "", filepath);
            sub("100", "", old_mode);
 
            print "chmod " old_mode " " filepath;
        }
    }
}' > chmod.sh


## 念のため変更するか確認する
cat chmod.sh
echo -n "パーミッションの変更を続けますか？ [y/n] "
 
read ans
if [ "$ans" != "y" -a "$ans" != "Y" ]; then
    echo "---> 処理を中断します"
    rm -f chmod.sh
    exit 1;
fi
 
/bin/sh ./chmod.sh
rm -f chmod.sh
echo "done."