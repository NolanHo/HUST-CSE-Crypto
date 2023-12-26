#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <cstring>
#include <map>
#define outt(x) printf("%s = %u  ",#x,x);
#define hh puts("")
const int maxM = 1000;
using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned char uchar;

uint SHA1_tmp;
#define SHA1_ROTL(a,b) (SHA1_tmp=(a),((SHA1_tmp>>(32-b))&(0x7fffffff>>(31-b)))|(SHA1_tmp<<b))
#define SHA1_F(B,C,D,t) ((t<40)?((t<20)?((B&C)|((~B)&D)):(B^C^D)):((t<60)?((B&C)|(B&D)|(C&D)):(B^C^D)))
int UnitSHA1(const char* str, int length, unsigned sha1[5]);
void getstr(unsigned n, char str[8]);
void R(unsigned sha1[5], char str[8], int i);


int lenth;
string nowstr1, nowstr2;
map<string, string>RainbowTable;
unsigned nowsha1[5], OriginSha1[5], inchain[5];
char ChainHead[maxM], ChainTail[maxM], targetSha1[maxM];

// 比较头链
bool WorkWithHead(string HeadofChain, string TailofChain) {
	int len = HeadofChain.length();
	char ch[255] = {};
	for ( int i = 0; i < len; i++) ch[i] = HeadofChain[i];
	ch[len] = '\0';
	for (int turnn = 1; turnn <= 100; ++turnn) {
		for (int i = 1; i <= 100; ++i) {
			UnitSHA1(ch, strlen(ch), nowsha1);
			for (int j = 0; j <= 5; ++j) {
				if (j == 5) {
					printf("%s", ch);
					return 1;
				}
				if (OriginSha1[j] != nowsha1[j]) break;
			}
			R(nowsha1, ch, i);
		}
	}
	return 0;
}

int main() {
	int m;
	scanf("%d", &m);
	// 读入彩虹表
	for (int i = 1; i <= m; ++i) {
		scanf("%s%s", ChainHead, ChainTail);
		nowstr1 = ChainHead;
		nowstr2 = ChainTail;
		RainbowTable[nowstr2] = nowstr1;
	}

	// 读入目标哈希值
	scanf("%s", targetSha1);
	for (int i = 0; i < 5; ++i) {
		OriginSha1[i] = 0;
		for (uint j = 7ll, val = 1ll; j <= 7; --j, val <<= 4) {
			OriginSha1[i] += val * (isdigit(targetSha1[i * 8 + j]) ? (targetSha1[i * 8 + j] - '0') : (targetSha1[i * 8 + j] - 'a' + 10ll));
		}
	}

	memset(targetSha1, 0, sizeof(targetSha1));

	for (int nowpls = 1; nowpls <= 100; nowpls++) {
		for (int i = 0; i < 5; ++i) {
            inchain[i] = OriginSha1[i];
        }
		targetSha1[0] = 0;
		for (int i = nowpls; i < 100; ++i) {
			R(inchain, targetSha1, i);
			UnitSHA1(targetSha1, strlen(targetSha1), inchain);
		}
		R(inchain, targetSha1, 100);
		for (int turnn = 1; turnn <= 100; ++turnn) {
			nowstr1 = targetSha1;
			if (RainbowTable.find(nowstr1) != RainbowTable.end()) {
				if (WorkWithHead(RainbowTable[nowstr1], nowstr1)) {
					// 找到了
					return 0;
				}
			}
			for (int i = 1; i <= 100; ++i) {
				UnitSHA1(targetSha1, strlen(targetSha1), inchain);
				R(inchain, targetSha1, i);
			}
		}
	}
	puts("None");
	return 0;
}

int UnitSHA1(const char* str, int length, unsigned sha1[5]) {
	uchar *pp, *ppend;
	uint l, i, K[80], W[80], TEMP, A, B, C, D, E, H0, H1, H2, H3, H4;
	H0 = 0x67452301, H1 = 0xEFCDAB89, H2 = 0x98BADCFE, H3 = 0x10325476, H4 = 0xC3D2E1F0;
	for (i = 0; i < 20; K[i++] = 0x5A827999);
	for (i = 20; i < 40; K[i++] = 0x6ED9EBA1);
	for (i = 40; i < 60; K[i++] = 0x8F1BBCDC);
	for (i = 60; i < 80; K[i++] = 0xCA62C1D6);
	l = length + ((length % 64 > 56) ? (128 - length % 64) : (64 - length % 64));
	if (!(pp = (unsigned char*)malloc((unsigned int)l))) return -1;
	for (i = 0; i < length; pp[i + 3 - 2 * (i % 4)] = str[i], i++);
	for (pp[i + 3 - 2 * (i % 4)] = 128, i++; i < l; pp[i + 3 - 2 * (i % 4)] = 0, i++);
	*((unsigned int*)(pp + l - 4)) = length << 3;
	*((unsigned int*)(pp + l - 8)) = length >> 29;
	for (ppend = pp + l; pp < ppend; pp += 64) {
		for (i = 0; i < 16; W[i] = ((unsigned int*)pp)[i], i++);
		for (i = 16; i < 80; W[i] = SHA1_ROTL((W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]), 1), i++);
		A = H0, B = H1, C = H2, D = H3, E = H4;
		for (i = 0; i < 80; i++) {
			TEMP = SHA1_ROTL(A, 5) + SHA1_F(B, C, D, i) + E + W[i] + K[i];
			E = D, D = C, C = SHA1_ROTL(B, 30), B = A, A = TEMP;
		}
		H0 += A, H1 += B, H2 += C, H3 += D, H4 += E;
	}
	free(pp - l);
	sha1[0] = H0, sha1[1] = H1, sha1[2] = H2, sha1[3] = H3, sha1[4] = H4;
	return 0;
}
void getstr(unsigned n, char str[8]) {
	str[0] = 'a';
	str[1] = '0';
	str[2] = '0';
	str[3] = '0';
	str[4] = '0';
	str[5] = '0';
	str[6] = '0';
	str[7] = '0';
	int i = 2;
	unsigned tmp;
	while (n) {
		tmp = n % 36;
		if (tmp < 10) str[i++] = tmp + '0';
		else str[i++] = tmp - 10 + 'a';
		n = n / 36;
	}
}

void R(unsigned sha1[5], char str[8], int i) {
	getstr((sha1[0] + sha1[1]*i) % 2176782336, str);
}