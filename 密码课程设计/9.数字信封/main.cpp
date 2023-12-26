#include <iostream>
#include <cstring>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/sm2.h>
#include <openssl/rand.h>
#include <openssl/objects.h>
#include <openssl/x509v3.h>

using namespace std;
#include <openssl/pkcs7.h>
#include <openssl/x509.h>


const char cacert[] = "\
-----BEGIN CERTIFICATE----- \n\
MIIB/zCCAaagAwIBAgIJAKKa0PAt9M1FMAoGCCqBHM9VAYN1MFsxCzAJBgNVBAYT \n\
AkNOMQ4wDAYDVQQIDAVIdUJlaTEOMAwGA1UEBwwFV3VIYW4xDTALBgNVBAoMBEhV \n\
U1QxDDAKBgNVBAsMA0NTRTEPMA0GA1UEAwwGY2Fyb290MB4XDTIwMDkyMDIwNTkx \n\
OVoXDTMwMDkxODIwNTkxOVowWzELMAkGA1UEBhMCQ04xDjAMBgNVBAgMBUh1QmVp \n\
MQ4wDAYDVQQHDAVXdUhhbjENMAsGA1UECgwESFVTVDEMMAoGA1UECwwDQ1NFMQ8w \n\
DQYDVQQDDAZjYXJvb3QwWTATBgcqhkjOPQIBBggqgRzPVQGCLQNCAASJ8mm28JJR \n\
bZKLr6DCo1+KWimpKEsiTfZM19Zi5ao7Au6YLosyN71256MWmjwkwXxJeLa0lCfm \n\
kF/YWCX6qGQ0o1MwUTAdBgNVHQ4EFgQUAL5hW3RUzqvsiTzIc1gUHeK5uzQwHwYD \n\
VR0jBBgwFoAUAL5hW3RUzqvsiTzIc1gUHeK5uzQwDwYDVR0TAQH/BAUwAwEB/zAK \n\
BggqgRzPVQGDdQNHADBEAiAaZMmvE5zzXHx/TBgdUhjtpRH3Jpd6OZ+SOAfMtKxD \n\
LAIgdKq/v2Jkmn37Y9U8FHYDfFqk5I0qlQOAmuvbVUi3yvM= \n\
-----END CERTIFICATE----- \n\
";

const char certB[] = "\
-----BEGIN CERTIFICATE----- \n\
MIICHDCCAcKgAwIBAgIBAzAKBggqgRzPVQGDdTBbMQswCQYDVQQGEwJDTjEOMAwG \n\
A1UECAwFSHVCZWkxDjAMBgNVBAcMBVd1SGFuMQ0wCwYDVQQKDARIVVNUMQwwCgYD \n\
VQQLDANDU0UxDzANBgNVBAMMBmNhcm9vdDAeFw0yMDA5MjAyMTIxMDNaFw0zMDA5 \n\
MTgyMTIxMDNaMEoxCzAJBgNVBAYTAkNOMQ4wDAYDVQQIDAVIdUJlaTENMAsGA1UE \n\
CgwESFVTVDEMMAoGA1UECwwDQ1NFMQ4wDAYDVQQDDAVVc2VyQjBZMBMGByqGSM49 \n\
AgEGCCqBHM9VAYItA0IABB+6yy4hQEnt0lkrBm8RVLXz2P/6V6i74DOkTsomIS5D \n\
8RLpcK03vJL+UfPzQO5Ekr3LBiEPRD1oa+h5wlC6ZJejgYcwgYQwCQYDVR0TBAIw \n\
ADALBgNVHQ8EBAMCBSAwKgYJYIZIAYb4QgENBB0WG0dtU1NMIEdlbmVyYXRlZCBD \n\
ZXJ0aWZpY2F0ZTAdBgNVHQ4EFgQUAhr5rk22vn/vEACBoMYN1FMPmGAwHwYDVR0j \n\
BBgwFoAUAL5hW3RUzqvsiTzIc1gUHeK5uzQwCgYIKoEcz1UBg3UDSAAwRQIhANkY \n\
3oWdgG8jriJXuRhX5le4QjE19EnKB4rWCQcKvORfAiAR4hnLYT+dXgFCxVgPkjGO \n\
PDXj9mXJk6crvhRRxZfWNg== \n\
-----END CERTIFICATE----- \n\
";

const char certC[] = "\
-----BEGIN CERTIFICATE----- \n\
MIICPjCCAeWgAwIBAgIBBDAKBggqgRzPVQGDdTBbMQswCQYDVQQGEwJDTjEOMAwG \n\
A1UECAwFSHVCZWkxDjAMBgNVBAcMBVd1SGFuMQ0wCwYDVQQKDARIVVNUMQwwCgYD \n\
VQQLDANDU0UxDzANBgNVBAMMBmNhcm9vdDAeFw0yMDA5MjcxNDIwMjFaFw0zMDA5 \n\
MjUxNDIwMjFaMG0xCzAJBgNVBAYTAkNOMQ4wDAYDVQQIDAVIdUJlaTENMAsGA1UE \n\
CgwESFVTVDEMMAoGA1UECwwDQ1NFMQ4wDAYDVQQDDAVVc2VyQzEhMB8GCSqGSIb3 \n\
DQEJARYSeG10YW5nQGh1c3QuZWR1LmNuMFkwEwYHKoZIzj0CAQYIKoEcz1UBgi0D \n\
QgAEHSrf7RNs2+Rf1TrPeJREGSy+6YTC9t4rtp1vY7Akuct504We3iAiALcIarFt \n\
QxQOr5Zf4l7Ybt3NocM8fLxkNqOBhzCBhDAJBgNVHRMEAjAAMAsGA1UdDwQEAwIF \n\
4DAqBglghkgBhvhCAQ0EHRYbR21TU0wgR2VuZXJhdGVkIENlcnRpZmljYXRlMB0G \n\
A1UdDgQWBBQvMLtMYb/dD9cNF0+s/cZNxHUBGjAfBgNVHSMEGDAWgBQAvmFbdFTO \n\
q+yJPMhzWBQd4rm7NDAKBggqgRzPVQGDdQNHADBEAiBrTVuYbSUlOX4TYV4q094S \n\
XgfnobZWYPeRjGmBNAEIMwIgfHrQR9RfLd62bg0iZBpfgwvtGuaCE3DX24xapZ6U \n\
fIc= \n\
-----END CERTIFICATE----- \n\
";

const char pkeyB[] = "\
-----BEGIN EC PARAMETERS----- \n\
BggqgRzPVQGCLQ== \n\
-----END EC PARAMETERS----- \n\
-----BEGIN EC PRIVATE KEY----- \n\
MHcCAQEEINQhCKslrI3tKt6cK4Kxkor/LBvM8PSv699Xea7kTXTToAoGCCqBHM9V \n\
AYItoUQDQgAEH7rLLiFASe3SWSsGbxFUtfPY//pXqLvgM6ROyiYhLkPxEulwrTe8 \n\
kv5R8/NA7kSSvcsGIQ9EPWhr6HnCULpklw== \n\
-----END EC PRIVATE KEY----- \n\
";

X509* getX509(const char* cert)
{
	BIO* bio;
	bio = BIO_new(BIO_s_mem());
	BIO_puts(bio, cert);
	return  PEM_read_bio_X509(bio, NULL, NULL, NULL);
}

EVP_PKEY* getpkey(const char* private_key)
{
	BIO* bio_pkey = BIO_new_mem_buf((char*)private_key, strlen(private_key));
	if (bio_pkey == NULL)
		return NULL;
	return  PEM_read_bio_PrivateKey(bio_pkey, NULL, NULL, NULL);
}


int main(int argc, char** argv)
{
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();

	char src[256] = { 0 };
	bool flag = false;
	int ret;

	// read the pkcs7 data
	BIO* in = BIO_new_fd(fileno(stdin), BIO_NOCLOSE);
	PKCS7* p7 = PEM_read_bio_PKCS7(in, NULL, NULL, NULL);

	// decode to get the initial data
	BIO* p7bio = PKCS7_dataDecode(p7, getpkey(pkeyB), NULL, getX509(certB));
	if (!p7bio) {
		printf("ERROR\n");
		BIO_free(in);
		BIO_free(p7bio);
		PKCS7_free(p7);
		return 0;
	}
	else {
		int srcLen = BIO_read(p7bio, src, 4096);
		src[srcLen] = '\0';
	}

	// get the stack of singer's info
	STACK_OF(PKCS7_SIGNER_INFO)* sk = PKCS7_get_signer_info(p7);

	// get the number of signers
	int signCount = sk_PKCS7_SIGNER_INFO_num(sk);

	for (int i = 0; i < signCount; i++)
	{
		// 获取签名者信息
		PKCS7_SIGNER_INFO* signInfo = sk_PKCS7_SIGNER_INFO_value(sk, i);

		// 获取签名者证书
		X509* x509 = X509_find_by_issuer_and_serial(p7->d.signed_and_enveloped->cert, signInfo->issuer_and_serial->issuer, signInfo->issuer_and_serial->serial);
		
		X509_STORE* store = X509_STORE_new();
		//X509_STORE_set_verify_cb(store, verify_cb);
		X509_STORE_add_cert(store, getX509(cacert));

		X509_STORE_CTX* ctx = X509_STORE_CTX_new();
		X509_STORE_CTX_init(ctx, store, x509, NULL);

		// 验证签名
		ret = PKCS7_dataVerify(store, ctx, p7bio, p7, signInfo);

		X509_STORE_CTX_cleanup(ctx);
		X509_STORE_CTX_free(ctx);
		X509_STORE_free(store);
		X509_free(x509);
		
		if (ret!= 1)
		{
			continue;
		}
		else {
			flag = true;
			break;
		}
	}

	if (flag) {
		printf("%s\n", src);
	}
	else {
		printf("ERROR\n");
	}

	BIO_free(in);
	BIO_free(p7bio);
	PKCS7_free(p7);

	return 0;
}