#include <stdio.h>
#include <openssl/bn.h>
void expmod(BIGNUM *res, BIGNUM *m, BIGNUM *e, const BIGNUM *mod, BN_CTX *ctx);

void expmod(BIGNUM *res, BIGNUM *m, BIGNUM *e, const BIGNUM *mod, BN_CTX *ctx) {
    BN_MONT_CTX *mont_ctx = BN_MONT_CTX_new();
    BIGNUM *temp = BN_new();
    BIGNUM *exp = BN_new();

    // 初始化 Montgomery 上下文
    BN_MONT_CTX_set(mont_ctx, mod, ctx);

    // 初始化结果为 1，并转换为 Montgomery 形式
    BN_one(res);
    BN_to_montgomery(res, res, mont_ctx, ctx);

    // 转换 base 到 Montgomery 形式
    BN_to_montgomery(temp, m, mont_ctx, ctx);

    // e = exponent
    BN_copy(exp, e);

    while (!BN_is_zero(exp)) {
        // 如果 e 是奇数，则 result = result * temp mod mod
        if (BN_is_odd(exp)) {
            BN_mod_mul_montgomery(res, res, temp, mont_ctx, ctx);
        }

        // temp = temp * temp mod mod
        BN_mod_mul_montgomery(temp, temp, temp, mont_ctx, ctx);

        // e = e / 2
        BN_rshift1(exp, exp);
    }

    // 将结果从 Montgomery 形式转换回标准形式
    BN_from_montgomery(res, res, mont_ctx, ctx);

    BN_MONT_CTX_free(mont_ctx);
    BN_free(temp);
    BN_free(exp);
}


int main() {
    BN_CTX *ctx = BN_CTX_new();
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char e_str[23333], m_str[23333], p_str[23333], q_str[23333];
        BIGNUM *e = BN_new(), *m = BN_new(), 
               *p = BN_new(), *q = BN_new(), 
               *N = BN_new(), *result = BN_new();

        scanf("%s %s %s %s", e_str, m_str, p_str, q_str);
        BN_dec2bn(&e, e_str);
        BN_dec2bn(&m, m_str);
        BN_dec2bn(&p, p_str);
        BN_dec2bn(&q, q_str);

        BN_mul(N, p, q, ctx);

        expmod(result, m, e, N, ctx);

        // Print
        char *result_str = BN_bn2dec(result);
        printf("%s\n", result_str);

        // Free
        OPENSSL_free(result_str);
        BN_free(e);
        BN_free(m);
        BN_free(p);
        BN_free(q);
        BN_free(N);
        BN_free(result);
    }

    BN_CTX_free(ctx);

    return 0;
}