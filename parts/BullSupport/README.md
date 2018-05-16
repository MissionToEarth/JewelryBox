###翻訳用のPLISTのコンフリクト解決の補助
--

Application/Resource/Localized/以下のplistがコンフリクトした場合について、競合の解決を助ける。  

以下のスクリプトを実行する。  

```
resolve_conflict_localized_plist.sh [ROOT_DIR] [バックアップ保存先]
```


- 2017年6月23日


```
1.コンフリクト
<<<<<<< HEAD  
    <key>CANCEL</key>  
    <string>キャンセル</string>
=======
    <key>OK</key>
    <string>OK</string>
>>>>>>> develop

上記は以下の通り解消
    <key>CANCEL</key>  
    <string>キャンセル</string>
    <key>OK</key>
    <string>OK</string>

```

```
2.コンフリクト
    <key>CANCEL</key>  
<<<<<<< HEAD  
    <string>キャンセル</string>
=======
    <string>OK</string>
>>>>>>> develop

上記は以下の通り解消
    <key>CANCEL</key>  
    <string>OK</string>

```

