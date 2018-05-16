# Python3.x
# コマンドライン引数を取り扱う。
#オプション引数と位置引数

# GUI
import tkinter as tk

# 引数処理
import sys 
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('path_src') #No.1 位置引数追加
parser.add_argument('path_dest') #No.2 位置引数追加
args = parser.parse_args()
print(args.path_src)
print(args.path_dest)
print(sys.argv[0])

def pushed():
 print("clicked")


root = tk.Tk()
root.title(args.path_src);

#メインウィンドウを640x480にする
root.geometry("640x480")

#ラベルを追加
label = tk.Label(root, text="Hello,World")
#表示
label.grid()

button = tk.Button(root, text="クリックしてね", command=pushed)
button.grid()

root.mainloop()# 最後に追加した部品から"mainloop()"を呼び出す約束がある。