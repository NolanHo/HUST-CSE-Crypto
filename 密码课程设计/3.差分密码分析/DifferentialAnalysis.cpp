#include<stdio.h>
#include<algorithm>

using namespace std;

#define getc() (_b1==_b2?fread(_b,1,100000,stdin),_b2=_b+100000,*((_b1=_b)++):*(_b1++))
char _b[100000], *_b1, *_b2;

#define S(text) ( \
    (STable_1B[0][((text) & 0xF000) >> 12] << 12) | \
    (STable_1B[0][((text) & 0x0F00) >> 8]  << 8)  | \
    (STable_1B[0][((text) & 0x00F0) >> 4]  << 4)  | \
    (STable_1B[0][(text) & 0x000F]) \
)

#define P(text) ( \
    ((text) & 0x8421)              | \
    (((text) & 0x0840) << 3)       | \
    (((text) & 0x0084) << 6)       | \
    (((text) & 0x0008) << 9)       | \
    (((text) & 0x4210) >> 3)       | \
    (((text) & 0x2100) >> 6)       | \
    (((text) & 0x0002) << 3)       | \
    (((text) & 0x1000) >> 9)         \
)


// 0=正向 1=逆向
short int STable_1B[2][16] = {{14, 4, 13, 1, 2, 15, 11, 8,  3, 10, 6, 12, 5,  9, 0, 7},
                          {14, 3, 4,  8, 1, 12, 10, 15, 7, 13, 9, 6,  11, 2, 0, 5}};
int SPTable[65536]; // S+P 盒代换
int STable_4B[65536]; // S盒代换

unsigned short keys[5];
inline void genKeys(unsigned int key){
    keys[0] = ((key & 0xFFFF0000) >> 16);
    keys[1] = ((key & 0x0FFFF000) >> 12);
    keys[2] = ((key & 0x00FFFF00) >> 8);
    keys[3] = ((key & 0x000FFFF0) >> 4);
    keys[4] = (key & 0x0000FFFF);
}

inline unsigned int SPN(unsigned int key, unsigned short plaintext, unsigned short ciphertext) {
    unsigned short text = plaintext;

    for (int i = 0; i <= 2; ++i) {
        text ^= keys[i];
        text = SPTable[text];
    }
    text ^= keys[3];
    text = STable_4B[text];
    text ^= keys[4];

    return (text == ciphertext);
}


// 预先计算
inline void Preload(){
    // 8倍循环展开
    for(int i=0;i<65536;i+=8){
        int plain=i;
        STable_4B[plain]=S(plain);
        SPTable[i]=P(STable_4B[plain]);
        
        STable_4B[plain+1]=S(plain+1);
        SPTable[i+1]=P(STable_4B[plain+1]);

        STable_4B[plain+2]=S(plain+2);
        SPTable[i+2]=P(STable_4B[plain+2]);

        STable_4B[plain+3]=S(plain+3);
        SPTable[i+3]=P(STable_4B[plain+3]);

        STable_4B[plain+4]=S(plain+4);
        SPTable[i+4]=P(STable_4B[plain+4]);

        STable_4B[plain+5]=S(plain+5);
        SPTable[i+5]=P(STable_4B[plain+5]);

        STable_4B[plain+6]=S(plain+6);
        SPTable[i+6]=P(STable_4B[plain+6]);

        STable_4B[plain+7]=S(plain+7);
        SPTable[i+7]=P(STable_4B[plain+7]);
    }
}
// 快读
inline unsigned short read() {
    unsigned short x = 0;
    char c = getc();
    while (c != ' ' && c != '\n') {
        x = x * 16 + ((c >= 'a') ? (c - 'a' + 10) : (c - '0'));
        c = getc();
    }
    return x;
}




int main() {
    Preload();

    int n, maxNum[2];
    pair<int, int> count1[256], count2[256];
    unsigned int plaintext[65536], ciphertext[65536], temp1[4], temp2[4], k[8], key, times;
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++) {
        fill(count1, count1 + 256, pair<int, int>(0, 0));
        fill(count2, count2 + 256, pair<int, int>(0, 0));
        for (int j = 0; j < 65536; j++) {
            ciphertext[j] = read();
        }
        // 计算第一条链
        for (int j = 0; j < 65536; j += 37) {
            if (((ciphertext[j] ^ ciphertext[j ^ 0xb00]) & 0xf0f0) == 0) {
                for (k[5] = 0; k[5] < 16; k[5]++) {
                    for (k[7] = 0; k[7] < 16; k[7]++) {
                        temp1[1] = ((ciphertext[j] & 0xf00) >> 8) ^ k[5];
                        temp1[3] = ((ciphertext[j] & 0xf) ^ k[7]);
                        temp1[1] = STable_1B[1][temp1[1]];
                        temp1[3] = STable_1B[1][temp1[3]];

                        temp2[1] = ((ciphertext[j ^ 0xb00] & 0xf00) >> 8) ^ k[5];
                        temp2[3] = ((ciphertext[j ^ 0xb00] & 0xf) ^ k[7]);
                        temp2[1] = STable_1B[1][temp2[1]];
                        temp2[3] = STable_1B[1][temp2[3]];

                        temp1[1] ^= temp2[1];
                        temp1[3] ^= temp2[3];
                        
                        if (temp1[1] == 6 && temp1[3] == 6)
                            count1[k[5] * 16 + k[7]].first++;
                    }
                }
            }
            if (((ciphertext[j] ^ ciphertext[j ^ 0x50]) & 0x0f0f) == 0) {
                for (k[4] = 0; k[4] < 16; k[4]++) {
                    for (k[6] = 0; k[6] < 16; k[6]++) {
                        temp1[0] = ((ciphertext[j] & 0xf000) >> 12) ^ k[4];
                        temp1[2] = ((ciphertext[j] & 0xf0) >> 4) ^ k[6];
                        temp1[0] = STable_1B[1][temp1[0]];
                        temp1[2] = STable_1B[1][temp1[2]];

                        temp2[0] = ((ciphertext[j ^ 0x50] & 0xf000) >> 12) ^ k[4];
                        temp2[2] = ((ciphertext[j ^ 0x50] & 0xf0) >> 4) ^ k[6];
                        temp2[0] = STable_1B[1][temp2[0]];
                        temp2[2] = STable_1B[1][temp2[2]];

                        temp1[0] ^= temp2[0];
                        temp1[2] ^= temp2[2];
                        if (temp1[0] == 5 && temp1[2] == 5)
                            count2[k[4] * 16 + k[6]].first++;
                    }
                }
            }
        }
        // 得到部分密钥
        for (int j = 0; j < 256; j++) {
            count1[j].second = j;
            count2[j].second = j;
        }
        sort(count1, count1 + 256);
        sort(count2, count2 + 256);

        k[4] = count2[255].second / 16;
        k[6] = count2[255].second - k[4] * 16;
        
        for (int j = 255; j >= 0; j--) {
            k[5] = count1[j].second / 16;
            k[7] = count1[j].second - k[5] * 16;

            for (k[0] = 0; k[0] < 65536; k[0]++) {
                key = (k[0] << 16) | (k[4] << 12) | (k[5] << 8) | (k[6] << 4) | k[7];
                genKeys(key);
                for (times = 0; times < 10; times++) {
                    if (!SPN(key, times * 1000 + 30000, ciphertext[times * 1000 + 30000]))
                        break;
                }
                if (times == 10) {
                    printf("%08x", key);
                    putchar('\n');
                    break;
                }
            }
            if (times == 10)
                break;
        }
    }
    return 0;
}