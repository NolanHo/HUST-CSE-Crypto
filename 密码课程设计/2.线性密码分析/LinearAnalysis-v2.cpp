#include<stdio.h>
#include<algorithm>

using namespace std;

// 0加密 1解密, 16位输入输出
short int STable_1B[2][16] = {{14, 4, 13, 1, 2, 15, 11, 8,
                            3, 10, 6, 12, 5, 9, 0, 7},
                           {14, 3, 4, 8, 1, 12, 10, 15,
                            7, 13, 9, 6, 11, 2, 0, 5}};

int SPTable[65536]; // S+P 盒代换
int STable_4B[65536]; // S盒代换
unsigned short Hex[128]; // 16进制转换

//s盒代换 0加密 1解密
inline unsigned short S(int mode, unsigned short text) {
    unsigned short res = 0;
    res |= STable_1B[mode][(text & 0xF000) >> 12] << 12;
    res |= STable_1B[mode][(text & 0x0F00) >> 8] << 8;
    res |= STable_1B[mode][(text & 0x00F0) >> 4] << 4;
    res |= STable_1B[mode][(text & 0x000F)];
    return res;
};

//p盒代换
inline unsigned short P(unsigned short text) {
    return  (text & 0x8000) |
           ((text & 0x0800) << 3) |
           ((text & 0x0080) << 6) |
           ((text & 0x0008) << 9) |

           ((text & 0x4000) >> 3) |
           ((text & 0x0400)) |
           ((text & 0x0040) << 3) |
           ((text & 0x0004) << 6) |

           ((text & 0x2000) >> 6) |
           ((text & 0x0200) >> 3) |
           ((text & 0x0020)) |
           ((text & 0x0002) << 3) |

           ((text & 0x1000) >> 9) |
           ((text & 0x0100) >> 6) |
           ((text & 0x0010) >> 3) |
            (text & 0x0001);
}

// 预先计算和初始化
inline void Preload(){
    // 16进制转换
    Hex['0'] = 0;
    Hex['1'] = 1;
    Hex['2'] = 2;
    Hex['3'] = 3;
    Hex['4'] = 4;
    Hex['5'] = 5;
    Hex['6'] = 6;
    Hex['7'] = 7;
    Hex['8'] = 8;
    Hex['9'] = 9;
    Hex['a'] = 10;
    Hex['b'] = 11;
    Hex['c'] = 12;
    Hex['d'] = 13;
    Hex['e'] = 14;
    Hex['f'] = 15;
    
    // 8倍循环展开
    for(int i=0;i<65536;i+=8){
        int plain=i;
        STable_4B[plain]=S(0,plain);
        SPTable[i]=P(STable_4B[plain]);
        
        STable_4B[plain+1]=S(0,plain+1);
        SPTable[i+1]=P(STable_4B[plain+1]);

        STable_4B[plain+2]=S(0,plain+2);
        SPTable[i+2]=P(STable_4B[plain+2]);

        STable_4B[plain+3]=S(0,plain+3);
        SPTable[i+3]=P(STable_4B[plain+3]);

        STable_4B[plain+4]=S(0,plain+4);
        SPTable[i+4]=P(STable_4B[plain+4]);

        STable_4B[plain+5]=S(0,plain+5);
        SPTable[i+5]=P(STable_4B[plain+5]);

        STable_4B[plain+6]=S(0,plain+6);
        SPTable[i+6]=P(STable_4B[plain+6]);

        STable_4B[plain+7]=S(0,plain+7);
        SPTable[i+7]=P(STable_4B[plain+7]);
    }
}

// 判断是否为密钥
inline unsigned int SPN(unsigned int key, unsigned short plaintext, unsigned short ciphertext) {
    unsigned short keys[5];

    keys[0] = ((key & 0xFFFF0000) >> 16);
    keys[1] = ((key & 0x0FFFF000) >> 12);
    keys[2] = ((key & 0x00FFFF00) >> 8);
    keys[3] = ((key & 0x000FFFF0) >> 4);
    keys[4] = (key & 0x0000FFFF);

    unsigned short text = plaintext;

    text = SPTable[text ^ keys[0]];
    text = SPTable[text ^ keys[1]];
    text = SPTable[text ^ keys[2]];
    text = STable_4B[text ^ keys[3]];
    text ^= keys[4];
    
    return (text == ciphertext);
}

// 快速读入16进制数
inline unsigned short read() {
    unsigned short x = 0;
    char c1 = getchar();
    if (c1 == ' ' || c1 == '\n')
        c1 = getchar();
    char c2 = getchar();
    char c3 = getchar();
    char c4 = getchar();
    return (Hex[c1] << 12) | (Hex[c2] << 8) | (Hex[c3] << 4) | (Hex[c4]);
}


int main() {
    Preload();
    int n, times, maxNum[2];
    pair<int, int> count1[256], count2[256];
    unsigned plaintext[8000], ciphertext[8000], temp[4], k[8], lastKey2, key;
    scanf("%d", &n);

    getchar(); // 去掉换行符

    for (int i = 0; i < n; i++) {
        lastKey2 = -1;
        fill(count1, count1 + 256, pair<int, int>(-4000, 0));

        // 读入8000组明密文对
        for (int j = 0; j < 8000; j++) {
            plaintext[j] = read();
            ciphertext[j] = read();
        }

        // 计算第一条链
        for (int j = 0; j < 8000; j++) {
            for (k[5] = 0; k[5] < 16; k[5]++) {
                for (k[7] = 0; k[7] < 16; k[7]++) {
                    temp[1] = ((ciphertext[j] & 0xf00) >> 8) ^ k[5];
                    temp[3] = ((ciphertext[j] & 0xf) ^ k[7]);
                    temp[1] = STable_1B[1][temp[1]];
                    temp[3] = STable_1B[1][temp[3]];
                    if ((
                         ((plaintext[j] & 0x800) >> 11) ^ 
                         ((plaintext[j] & 0x200) >> 9) ^
                         ((plaintext[j] & 0x100) >> 8) ^

                         (temp[1] & 0x1) ^ 
                         ((temp[1] & 0x4) >> 2) ^ 
                         (temp[3] & 0x1) ^ 
                         ((temp[3] & 0x4) >> 2
                         )) == 0)
                        count1[k[5] * 16 + k[7]].first++;
                }
            }
        }

        // 得到部分密钥
        for (int j = 0; j < 256; j++) {
            count1[j].second = j;
            count1[j].first = abs(count1[j].first);
        }
        sort(count1, count1 + 256);

        // 枚举密钥
        for (int j = 255; j >= 0; j--) {
            lastKey2 = k[5];
            k[5] = count1[j].second / 16;
            k[7] = count1[j].second - k[5] * 16; // optimize: k[7] = count1[j].second % 16;

            // 计算第二条链
            if (j == 255 || lastKey2 != k[5]) {
                fill(count2, count2 + 256, pair<int, int>(-4000, 0));
                for (int j = 0; j < 8000; j++) {
                    for (k[4] = 0; k[4] < 16; k[4]++) {
                        for (k[6] = 0; k[6] < 16; k[6]++) {
                            temp[0] = ((ciphertext[j] & 0xF000) >> 12) ^ k[4];
                            temp[1] = ((ciphertext[j] & 0xF00) >> 8) ^ k[5];
                            temp[2] = ((ciphertext[j] & 0xF0) >> 4) ^ k[6];

                            temp[0] = STable_1B[1][temp[0]];
                            temp[1] = STable_1B[1][temp[1]];
                            temp[2] = STable_1B[1][temp[2]];
                            if ((
                                ((plaintext[j] & 0x800) >> 11) ^ 
                                ((plaintext[j] & 0x400) >> 10) ^
                                ((temp[0] & 0x4) >> 2) ^ 
                                (temp[0] & 0x1) ^ 
                                ((temp[1] & 0x4) >> 2) ^ 
                                (temp[1] & 0x1) ^
                                ((temp[2] & 0x4) >> 2) ^ 
                                (temp[2] & 0x1)) == 0)
                                count2[k[4] * 16 + k[6]].first++;
                        }
                    }
                }
                for (int j = 0; j < 256; j++) {
                    count2[j].second = j;
                    count2[j].first = abs(count2[j].first);
                }
                maxNum[0] = max_element(count2, count2 + 256) - count2;
                count2[maxNum[0]].first = 0;
                maxNum[1] = (*max_element(count2, count2 + 256)).second;
            }

            for (int h = 0; h < 1; h++) {
                k[4] = maxNum[h] / 16;
                k[6] = maxNum[h] - k[4] * 16;

                for (k[0] = 0; k[0] < 65535; k[0]++) {
                    key = (k[0] << 16) | (k[4] << 12) | (k[5] << 8) | (k[6] << 4) | k[7];
                    for (times = 0; times < 2; times++) {
                        if (!SPN(key, plaintext[times], ciphertext[times])){
                            break;
                        }
                    }
                    // 如果两个明密文对都满足，则输出密钥
                    if (times == 2) {
                        printf("%08x", key);
                        putchar('\n');
                        break;
                    }
                }
                // 如果两个明密文对都满足，则退出循环
                if (times == 2)
                    break;
            }
            // 如果两个明密文对都满足，则退出循环
            if (times == 2)
                break;
        }
    }
    return 0;
}

