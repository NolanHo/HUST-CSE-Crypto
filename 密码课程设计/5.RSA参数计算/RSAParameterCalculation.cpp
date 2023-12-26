#include <iostream>
#include <openssl/bn.h>
using namespace std;

int gcdExtended(BIGNUM *a, BIGNUM *b, BIGNUM *g, BIGNUM *x, BIGNUM *y, BN_CTX *ctx);
void modInverse(BIGNUM *inv, BIGNUM *a, BIGNUM *m, BN_CTX *ctx);
int my_gcd(BIGNUM *g, BIGNUM *a, BIGNUM *b,  BN_CTX *ctx);

// 使用扩展欧几里得算法求模逆
// inv = a^-1 mod m
void modInverse(BIGNUM *inv, BIGNUM *a, BIGNUM *m, BN_CTX *ctx) {
    BIGNUM *g = BN_new();
    BIGNUM *x = BN_new();
    BIGNUM *y = BN_new();
    BIGNUM *temp = BN_new();

    if (gcdExtended(a, m, g, x, y, ctx) != 1) {
        goto cleanup;
    }

    if (BN_is_negative(x)) {
        BN_add(temp, x, m);
        BN_copy(x, temp);
    }

    BN_copy(inv, x);

cleanup:
    BN_free(g);
    BN_free(x);
    BN_free(y);
    BN_free(temp);
}

// g = (a,b)
int my_gcd(BIGNUM *g, BIGNUM *a, BIGNUM *b,  BN_CTX *ctx) {
    BIGNUM *tempA = BN_new();
    BIGNUM *tempB = BN_new();
    BIGNUM *remainder = BN_new();
    int ret = 1; 

    BN_copy(tempA, a);
	BN_copy(tempB, b);

    // Perform the Euclidean algorithm
    while (!BN_is_zero(tempB)) {
        if (BN_mod(remainder, tempA, tempB, ctx) == NULL) {
            ret = 0;  // Modulo operation failed
            goto cleanup;
        }
        BN_copy(tempA, tempB);
		BN_copy(tempB, remainder);
    }

    BN_copy(g, tempA);

cleanup:
    // Free dynamically allocated BIGNUM objects
    BN_free(tempA);
    BN_free(tempB);
    BN_free(remainder);

    return ret;
}

// 计算GCD（最大公约数）
// g = (a,b) = a * x + b * y
int gcdExtended(BIGNUM *a, BIGNUM *b, BIGNUM *g, BIGNUM *x, BIGNUM *y, BN_CTX *ctx) {
    BIGNUM *x1 = BN_new();
    BIGNUM *y1 = BN_new();  // To store results of recursive call
    BIGNUM *a1 = BN_new();
    BIGNUM *b1 = BN_new();
    BIGNUM *quotient = BN_new();
    BIGNUM *temp = BN_new();
    int ret = 1;

    if (BN_is_zero(b)) {
        BN_copy(x, BN_value_one());
        BN_zero(y);
        BN_copy(g, a);
        goto cleanup;
    }

    BN_copy(a1, a);
    BN_copy(b1, b);

    BN_mod(temp, a1, b1, ctx);
    if (gcdExtended(b1, temp, g, x1, y1, ctx) != 1) {
        ret = 0; // Something went wrong
        goto cleanup;
    }

    BN_copy(x, y1);
    BN_div(quotient, NULL, a1, b1, ctx);
    BN_mul(temp, quotient, y1, ctx);
    BN_sub(y, x1, temp);

cleanup:
    BN_free(x1);
    BN_free(y1);
    BN_free(a1);
    BN_free(b1);
    BN_free(quotient);
    BN_free(temp);

    return ret;
}

int main(){
	int n;
	cin >> n;
	for (int cnt = 0; cnt < n; cnt++){
		BIGNUM *e = BN_new();
		BIGNUM *p = BN_new();
		BIGNUM *q = BN_new();
		BIGNUM *phi_n = BN_new();
		BIGNUM *d = BN_new();
		BN_CTX *ctx = BN_CTX_new();
		char e_str[23333];
		char p_str[23333];
		char q_str[23333];
		cin >> e_str;
		cin >> p_str;
		cin >> q_str;
		BN_dec2bn(&e, e_str);
		BN_dec2bn(&p, p_str);
		BN_dec2bn(&q, q_str);

		// 计算p,q的差值, 如果太小则ERROR
		BIGNUM *p_minus_q = BN_new();
		BIGNUM *x = BN_new();
		BN_dec2bn(&x, "65536");
		BN_sub(p_minus_q, p, q);
		if (BN_cmp(p_minus_q, x) < 0){
			cout << "ERROR" << endl;
			continue;
		}

		// e 太小则ERROR, < 65537
		if (BN_cmp(x, e) > 0){
			cout << "ERROR" << endl;
			continue;
		}

		// p - 1, q - 1
		BIGNUM *p_minus_1 = BN_new();
		BN_sub(p_minus_1, p, BN_value_one());
		BIGNUM *q_minus_1 = BN_new();
		BN_sub(q_minus_1, q, BN_value_one());

		// phi_n = (p - 1) * (q - 1)
		BN_mul(phi_n, p_minus_1, q_minus_1, ctx);

		// e 和 phi_n的最大公约数不为1, 不满足(e, phi_n) = 1
		BIGNUM *judge = BN_new();
		my_gcd(judge, e, phi_n, ctx);
		if (!BN_is_one(judge)){
			cout << "ERROR" << endl;
			continue;
		}

		// (p-1, q-1) < 20 
		BIGNUM *maxgcd = BN_new();
		BN_dec2bn(&x, "20");
		my_gcd(maxgcd, p_minus_1, q_minus_1, ctx);
		if (BN_cmp(maxgcd, x) > 0){
			cout << "ERROR" << endl;
			continue;
		}

		// d = e^-1 mod phi_n
		BIGNUM *mod_inverse = BN_new();
		modInverse(mod_inverse, e, phi_n, ctx);
		if (mod_inverse != NULL){
			cout << BN_bn2dec(mod_inverse) << endl;
			BN_free(mod_inverse);
		} else{
			cout << "ERROR" << endl;
		}

		BN_free(e);
		BN_free(p);
		BN_free(q);
		BN_free(phi_n);
		BN_free(d);
		BN_free(p_minus_1);
		BN_free(q_minus_1);
		BN_CTX_free(ctx);
	}
	return 0;
}