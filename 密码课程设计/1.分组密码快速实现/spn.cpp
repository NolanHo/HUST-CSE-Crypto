#include<cstdio>
#include<cstring>
using namespace std;

// 快速读取
static char buf[100000],*pa=buf,*pd=buf;
#define gc pa==pd&&(pd=(pa=buf)+fread(buf,1,100000,stdin),pa==pd)?EOF:*pa++



int x[4],key[8]; // x为明文，key为密钥, 4位16进制数, 共32位, 即8个字节
int chan[4]; // 临时变量

// 读取明文
inline void readText(){
    int yy=0;
	char c=(gc);
	
	while(1){
		if(c>='0'&&c<='9'){
			x[yy++]=c^48;c=(gc);
		}else if(c>='a'&&c<='f'){
			x[yy++]=c-'a'+10;c=(gc);
		}
		else break;
	}
}

// 读取key
inline void readkey(){
	int yy=0;
	char c=(gc);
	while(1){
		if(c>='0'&&c<='9'){
			key[yy++]=c^48;c=(gc);
		}else if(c>='a'&&c<='f'){
			key[yy++]=c-87;c=(gc);
		}
		else break;
	}
}


// S盒
int STable[16]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7};

// 逆S盒
int rSTable[16]={14,3,4,8,1,12,10,15,7,13,9,6,11,2,0,5};

// 十六进制输出表
char hex[16]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};


int main(){
	int n = 0;
	scanf("%d\n",&n);

    int j,k;

	for(int line=0;line<n;line++){
		// 读取key和明文
		readkey();
		readText();

		//加密
		for(j=0;j<3;j++){
			memset(chan,0,sizeof(chan));
			for(k=0;k<=3;k++){
				x[k]^=key[k+j];
				x[k]=STable[x[k]];

				chan[3]+=(x[k]&1)<<(3-k);
				x[k]>>=1;
				chan[2]+=(x[k]&1)<<(3-k);
				x[k]>>=1;
				chan[1]+=(x[k]&1)<<(3-k);
				x[k]>>=1;
				chan[0]+=(x[k]&1)<<(3-k);
				x[k]>>=1;
			}
			x[0]=chan[0];
			x[1]=chan[1];
			x[2]=chan[2];
			x[3]=chan[3];
		}

		// 异或最后一轮轮密钥并输出
		for(k=0;k<4;k++) {
			x[k]^=key[k+3];
			x[k]=STable[x[k]];
			x[k]^=key[k+4];
			putchar(hex[x[k]]);
		}
		putchar(' ');

		//解密
		x[3]^=1; 
			
		for(k=0;k<4;k++) {
			x[k]^=key[k+4];
			x[k]=rSTable[x[k]];
			x[k]^=key[k+3];
		}
		for(j=2;j>=0;j--){
			memset(chan,0,sizeof(chan));
			for(k=0;k<=3;k++){
				chan[3]+=(x[k]&1)<<(3-k);
				x[k]>>=1;
				chan[2]+=(x[k]&1)<<(3-k);
				x[k]>>=1;
				chan[1]+=(x[k]&1)<<(3-k);
				x[k]>>=1;
				chan[0]+=(x[k]&1)<<(3-k);
				x[k]>>=1;		
			}
			for(k=0;k<4;k++){
				x[k]=rSTable[chan[k]];
				x[k]^=key[k+j];
			}
		}

		// 输出第二段
		putchar(hex[x[0]]);
		putchar(hex[x[1]]);
		putchar(hex[x[2]]);
		putchar(hex[x[3]]);
		putchar('\n');
	}
}
