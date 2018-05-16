##Decryptkeyの隠蔽

＜NAME＞  
HideDecryptKeys  

＜概要＞  
複数の複合キーを隠蔽するツール。
csvファイルにあるキーを隠蔽したファイルを作成する。

＜説明＞  
チート問題で、ローカルDBがクラックされている可能性が出てきた。  
原因としては、DBの暗号化に使われているキーが.soファイルから取得できる事が考えられたので、.soから除外する。
また、キーの取得方法も少し複雑にする事になった。

方法について簡単な説明。  

1. ランダムな文字列の中にキーを埋め込む。  
2. キーを取得するときは位置と字数を使って引いてくる。  

クラック対策資料  
<https://drive.google.com/drive/u/0/folders/1ce5PeEQkDWYiXcxOu-JkjhCkprJX5umr>



＜使い方＞

必要なキーを含めた csv形式のファイルを作成してください。  
1. キーのタイプ（使用する対象）  
2. 実際に使用するキー  

	ex)
	STORAGE,nvfu39ufi9r


上のように用意したファイルをプログラムに渡して実行する。

	./csv2key_store _keycsv.txt
	
以下、２つのファイルが ./output/ に出力されるので、BULLプロジェクトの同ファイルへ上書きする。  
KeyStore.h    
KeyStore.cpp    
