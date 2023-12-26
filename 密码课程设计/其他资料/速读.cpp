#define MAX_BUFSIZE (1 << 22)
char _b[MAX_BUFSIZE],*_b1,*_b2;
//读一个字符
#define getch() (_b1==_b2?_b2=_b+fread(_b,1,MAX_BUFSIZE,stdin),_b1=_b,*(_b1++):*(_b1++))
//读一个整数（本题不需要）
//若读无符号整数可以忽略f,getchar可以用getch替换
int read() {
    char ch = getchar(); int x = 0, f = 1;
    while(ch < '0' || ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    } return x * f;
}


char output_buf[MAX_BUFSIZE];          
char *p = output_buf;
u32 num2char[0x10000];  
//u16到字符串的映射，num2char保存的是索引值的ascii码，
//Little endian的情况，例如num2chr[0x012a]==0x61323130
#define output(x) (*(u32 *)p = num2char[x], p += 4)
#define putch(c) (*p++ = c)
#define flush() (fwrite(output_buf, 1, p - output_buf, stdout), p = output_buf)
//MAX_BUFSIZE是读写函数的最大缓冲，比实际读写的数据小，所以到一定的时候就要清空，否则就会溢出。
if ((p - output_buf) > (MAX_BUFSIZE >> 1))
    flush();//清空缓冲区