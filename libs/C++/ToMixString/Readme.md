##Decryptkeyの隠蔽

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

csvファイルの内容には必要なキーだけ含めてください。  
1. キーのタイプ（使用する対象）  
2. 実際に使用するキー  

	STORAGE,nvfu39ufi9r


ファイルを用意した後に、以下の通り実行する。

	./csv_to_keyjson key_source.csv.txt
	
	//生成されたjsonファイルを食わせる。	
	./make_cpp mixed_key.json

以下、２つのファイルができるので、プロジェクトに上書きする。  
KeyStore.h    
KeyStore.cpp    
