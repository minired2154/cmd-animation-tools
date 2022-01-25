#include <cstring>
#include <unordered_map>

using namespace std;

class CMD_ANIME_API {
    /*
    CMD 動畫的簡易 API，使用者利用整數陣列作為輸入，
    並且給定每個整數對應的輸出字串。例如：0 輸出 "XX"、1 輸出 "OO"。
    給定的方式使用 unorder_map<int, string> 作為資料結構。

    範例：
    -step 1:
        CMD_ANIME_API anime(5,5); //固定陣列最大限制。
    -step 2:
        unorder_map<int, string> transfer;
        transfer[0] = "XX";
        transfer[1] = "OO";
        anime.TransferNumberToString(transfer); //將定應的整數對應字串map傳到class裡面
    -step 3:
        anime.show(/*arr, 5, 5) //裡面放入下一幀的陣列。
    */
   protected:
    int col, row;
    int **cur_screen, **next_screen;           //存著目前的整數型態陣列
    unordered_map<int, string> TransferTable;  //使用者決定陣列中的數字要輸出什麼字串
    bool isSame(int);
    void replace(int);
    void framecpy(int **&, int **, int, int);
    void showcur();
    void print();

   public:
    CMD_ANIME_API(int, int);                                  //初始化時，決定最大陣列大小
    void TransferNumberToString(unordered_map<int, string>);  // 傳入陣列中的整數要對應的字串，例如：0輸出O，1輸出x。
    void show(int **&, int, int);                             // 將下一幀的陣列輸入，同時給定陣列大小。給定的大小不能超過初始化時的大小
    ~CMD_ANIME_API();
};