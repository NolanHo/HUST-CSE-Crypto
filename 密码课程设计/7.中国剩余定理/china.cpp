#include <iostream>
#include <openssl/bn.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    char p_str[4096], q_str[4096], e_str[4096];
    scanf("%s %s %s", p_str, q_str, e_str);

    BIGNUM *p = BN_new(), *q = BN_new(), *e = BN_new(), *phi_n = BN_new();
    BN_dec2bn(&p, p_str);
    BN_dec2bn(&q, q_str);
    BN_dec2bn(&e, e_str);

    BIGNUM *p_minus_1 = BN_new(), *q_minus_1 = BN_new();
    BN_sub(p_minus_1, p, BN_value_one());
    BN_sub(q_minus_1, q, BN_value_one());

    BN_CTX *ctx = BN_CTX_new();
    BN_mul(phi_n, p_minus_1, q_minus_1, ctx);

    BIGNUM *d = BN_mod_inverse(NULL, e, phi_n, ctx);

    // Compute dp, dq, and q_inv for CRT
    BIGNUM *dp = BN_new(), *dq = BN_new(), *q_inv = BN_new();
    BN_mod(dp, d, p_minus_1, ctx);
    BN_mod(dq, d, q_minus_1, ctx);
    BN_mod_inverse(q_inv, q, p, ctx);

    BIGNUM *pq = BN_new();
    BN_mul(pq, p, q, ctx);

    BN_free(p_minus_1);
    BN_free(q_minus_1);

    for (int i = 0; i < n; i++) {
        char c_str[4096];
        BIGNUM* c = BN_new();
        scanf("%s", c_str);
        BN_dec2bn(&c, c_str);

        // Using CRT for decryption
        BIGNUM *m1 = BN_new(), *m2 = BN_new(), *h = BN_new();
        BN_mod_exp(m1, c, dp, p, ctx);
        BN_mod_exp(m2, c, dq, q, ctx);

        BN_sub(h, m1, m2);
        BN_mul(h, h, q_inv, ctx);
        BN_mod(h, h, p, ctx);

        BIGNUM *result = BN_new();
        BN_mul(h, h, q, ctx);
        BN_add(result, m2, h);

        // Make sure the result is within [0, n)
        while(BN_cmp(result, pq) >= 0) {
			BN_sub(result, result, pq);
		}

		BIGNUM *zero = BN_new();
		BN_zero(zero);
		while(BN_cmp(result, zero) < 0) {
			BN_add(result, result, pq);
		}

        char* resultStr = BN_bn2dec(result);
        printf("%s\n", resultStr);

        OPENSSL_free(resultStr);
        BN_free(c);
        BN_free(m1);
        BN_free(m2);
        BN_free(h);
        BN_free(result);
    }

    BN_CTX_free(ctx);
    BN_free(p);
    BN_free(q);
    BN_free(e);
    BN_free(d);
    BN_free(phi_n);
    BN_free(dp);
    BN_free(dq);
    BN_free(q_inv);
    BN_free(pq);

    return 0;
}
