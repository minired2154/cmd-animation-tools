# 介紹
簡易的 CMD 動畫工具。

# 使用方法
注意事項：
* 每一個畫面都是以整數的二維陣列儲存
* 陣列中的數字所對應的字元這裡稱為 transfer table，由 unorder_map<int,string> 作為資料結構儲存
	* 因此使用者需要定義自己的 unorder_map

Step 1:
> 宣告，初始化時輸入的兩個整數分別維 row、column。代表的意義為陣列的最大上限，之後的每一幀都不能超過這個上限。

```cpp=
CMD_ANIME_API anime(10,10);
```

Step 2:
> 定義 transfer table，基本上只要照著 unorder_map<int, string> 的形式插入資料後呼叫 TransferNumberToString 函式即可

```cpp=
unorder_map<int, string> transfer
transfer[0] = "oo";
transfer[1] = "xx";
anime.TransferNumberToString(transfer);
```

Step 3:
> 將下一幀輸入給API，同時給定這一幀的大小。注意：每一幀都必須是二維陣列，並且以二星指標作為函數間傳遞的方式。

```cpp=
anime.show(frame, 10, 10);
```
