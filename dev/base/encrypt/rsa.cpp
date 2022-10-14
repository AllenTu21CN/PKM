#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#define RSAPUBKEY
#define KEYFORMFILE 1
#define KEYFORMMEM 2

#define KEYFORM KEYFORMMEM //内存导入
//#define KEYFORM	KEYFORMFILE	//文件导入

#define PRIVATEKEY "key.pem"
#define PUBLICKEY "key_pub.pem"

int rsa_pub_encrypt(char *str, char *path_key, char **outstr);
int rsa_prv_decrypt(char *str, char *path_key, int inlen, char **outstr);

const char *pubkey = "-----BEGIN PUBLIC KEY-----\n\
MFwwDQYJKoZIhvcNAQEBBQADSwAwSAJBAL9FoRovAH9hlBgV2QvOTFwnMvJko4y/\
t09wl+sglqcWBCChYANssTxVNeE1QmcrJqX+AMtshHpkWn3R2AtZ9W0CAwEAAQ==\
\n-----END PUBLIC KEY-----\n";

const char *prikey = "-----BEGIN RSA PRIVATE KEY-----\n\
MIIBpjBABgkqhkiG9w0BBQ0wMzAbBgkqhkiG9w0BBQwwDgQIzXhYZp+H6EkCAggA\
MBQGCCqGSIb3DQMHBAgSeZA+CubUBASCAWDNHcqFskHOP70Z1W7ju0M6mceR6MPI\
pVB7o1ViLt+5p2iMvvv7t0Jwvaxrf9l7KKgVQViUBm3OFwIpKMdvdqfkLarHTZbh\
3TgAohN8QOfZOa1Lkgo3SIfDjH2uI/B+UDJST2svhYH9ZmMOCFq00YOuSeZ2doRu\
QQGDWOVSGGFVIMqHBFJdLxJzk1PHPOALPTQsUbVQufnUgqgnsNa1JyRuO4GZ3taV\
+m7yStB6DGCNVMOA7s+cnud/QniS/SiwDUVldbttR4ZeJ7zJ5SNtPJMrDkY/Eez9\
fP8Azzygjt64ZcVh5W//mt6i+byKrk1VFeyqFQY8Ck3/DLRznt9mvBuyhymhX5jB\
To53I3qjJjrldWmpHNw7Od+rnJEjm+mBL+5Pr02TLHHz4c/5Rw+KYj/N9DwysrMa\
hnH3mDwPqBa0bu3Wn9iD2L+2JevummYj5h/E3N2bdsuF8f+C7fCJ9kiH\
\n-----END RSA PRIVATE KEY-----\n";

// const char *prikey = "-----BEGIN RSA PRIVATE KEY-----\n\
// MIIBVgIBADANBgkqhkiG9w0BAQEFAASCAUAwggE8AgEAAkEAxaU1UX3sJLfi2XtW\
// 7TKsjhWXyyV7JmQpaB0us4MTBxnD3j+rvdr0WZVBe83XGmzGxYcXYCmOYoXPTHb6\
// 8b5YaQIDAQABAkEAkzixk6c5rEwxNRCzunHhqOCath6QMhOv6Da8n8jF9qXCSSRO\
// HZlf5bbY8WfZ5Vvfbg7FX0ZT9e7dXvc6aFuJFQIhAOeiDtncHL6BPb/G7GMcMK3l\
// JPz/KWIlotb2SbtMa3hvAiEA2m/aK6/lP/c3DDItrexdOaBIqWqCf1AnfNA2tlOd\
// uKcCIQCKw3X8I7YAlnJEmknw0emDs5umCMJk7sEP4DmpgA199wIgOZ/yVT4U41gL\
// XJtMM6q8OTyQjqj7fiyeDi47kMPkQtcCIQCo9ONg3PU70GLt3RscwYNG2J74TGlV\
// 7BYzZGW2SU5WIA==\
// \n-----END RSA PRIVATE KEY-----\n";

static int do_operation(RSA *rsa_ctx, char *instr, char *path_key, int inlen, char **outstr, int type)
{
    if (rsa_ctx == NULL || instr == NULL || path_key == NULL)
    {
        perror("input elems error,please check them!");
        return -1;
    }

    int rsa_len, num;
    rsa_len = RSA_size(rsa_ctx);
    *outstr = (char *)malloc(rsa_len + 1);
    memset(*outstr, 0, rsa_len + 1);
    switch (type)
    {
    case 1: //pub enc
        if (inlen == 0)
        {
            perror("input str len is zero!");
            goto err;
        }

        num = RSA_public_encrypt(inlen, (unsigned char *)instr, (unsigned char *)*outstr, rsa_ctx, RSA_PKCS1_PADDING);

        break;
    case 2: //prv dec
        num = RSA_private_decrypt(inlen, (unsigned char *)instr, (unsigned char *)*outstr, rsa_ctx, RSA_PKCS1_PADDING);
        break;
    default:
        break;
    }

    if (num == -1)
    {
        printf("Got error on enc/dec!\n");
    err:
        free(*outstr);
        *outstr = NULL;
        num = -1;
    }

    return num;
}

int rsa_pub_encrypt(char *str, char *path_key, char **outstr)
{
    RSA *p_rsa;
    BIO *bio = NULL;
    FILE *file;
    int flen, rsa_len, num;
#if KEYFORM == KEYFORMFILE
    if ((file = fopen(path_key, "r")) == NULL)
    {
        perror("open key file error");
        return -1;
    }
#else
    if ((bio = BIO_new_mem_buf(pubkey, -1)) == NULL) //从字符串读取RSA公钥
    {
        perror("BIO_new_mem_buf failed!");
    }
#endif

#ifdef RSAPUBKEY
#if KEYFORM == KEYFORMFILE
    if ((p_rsa = PEM_read_RSA_PUBKEY(file, NULL, NULL, NULL)) == NULL)
    {
#else
    if ((p_rsa = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL)) == NULL)
    {
#endif
#else
    if ((p_rsa = PEM_read_RSAPublicKey(file, NULL, NULL, NULL)) == NULL)
    {
#endif
        ERR_print_errors_fp(stdout);
        return -1;
    }

    num = do_operation(p_rsa, str, path_key, strlen(str), outstr, 1);

    RSA_free(p_rsa);
#if KEYFORM == KEYFORMFILE
    fclose(file);
#else
    BIO_free_all(bio);
#endif

    return num;
}

static int password_cb (char *buf, int size, int rwflag, void *userdata)
{
    strncpy(buf, "dlxx", size);
    return strlen("dlxx");
}

int rsa_prv_decrypt(char *str, char *path_key, int inlen, char **outstr)
{
    RSA *p_rsa;
    BIO *bio = NULL;
    FILE *file;
    int rsa_len, num;

#if KEYFORM == KEYFORMFILE
    if ((file = fopen(path_key, "r")) == NULL)
    {
        perror("open key file error");
        return -1;
    }
#else
    if ((bio = BIO_new_mem_buf(prikey, -1)) == NULL) //从字符串读取RSA公钥
    {
        perror("BIO_new_mem_buf failed!");
    }
#endif

	char pwd[] = "dlxx";
#if KEYFORM == KEYFORMFILE
    if ((p_rsa = PEM_read_RSAPrivateKey(file, NULL, NULL, NULL)) == NULL)
    {
#else
    if ((p_rsa = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, pwd)) == NULL)
    {
#endif
        ERR_print_errors_fp(stdout);
        return -1;
    }

    num = do_operation(p_rsa, str, path_key, inlen, outstr, 2);
    RSA_free(p_rsa);
#if KEYFORM == KEYFORMFILE
    fclose(file);
#else
    BIO_free_all(bio);
#endif

    return num;
}

unsigned char *base64_encode(unsigned char *str, int strlen)
{
    long len;
    long str_len;
    unsigned char *res;
    int i, j;
    //定义base64编码表
    const char *base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    //计算经过base64编码后的字符串长度
    str_len = strlen;
    if (str_len % 3 == 0)
        len = str_len / 3 * 4;
    else
        len = (str_len / 3 + 1) * 4;

    res = (unsigned char *) malloc(sizeof(unsigned char) * len + 1);
    res[len] = '\0';

    //以3个8位字符为一组进行编码
    for (i = 0, j = 0; i < len - 2; j += 3, i += 4)
    {
        res[i] = base64_table[str[j] >> 2];                                     //取出第一个字符的前6位并找出对应的结果字符
        res[i + 1] = base64_table[(str[j] & 0x3) << 4 | (str[j + 1] >> 4)];     //将第一个字符的后位与第二个字符的前4位进行组合并找到对应的结果字符
        res[i + 2] = base64_table[(str[j + 1] & 0xf) << 2 | (str[j + 2] >> 6)]; //将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符
        res[i + 3] = base64_table[str[j + 2] & 0x3f];                           //取出第三个字符的后6位并找出结果字符
    }

    switch (str_len % 3)
    {
    case 1:
        res[i - 2] = '=';
        res[i - 1] = '=';
        break;
    case 2:
        res[i - 1] = '=';
        break;
    }

    return res;
}

unsigned char *base64_decode(const char *code, int *codelen)
{
    //根据base64表，以字符找到对应的十进制数据
    int table[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0,
                   63, 52, 53, 54, 55, 56, 57, 58,
                   59, 60, 61, 0, 0, 0, 0, 0, 0, 0, 0,
                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
                   13, 14, 15, 16, 17, 18, 19, 20, 21,
                   22, 23, 24, 25, 0, 0, 0, 0, 0, 0, 26,
                   27, 28, 29, 30, 31, 32, 33, 34, 35,
                   36, 37, 38, 39, 40, 41, 42, 43, 44,
                   45, 46, 47, 48, 49, 50, 51};
    long len;
    long str_len;
    unsigned char *res;
    int i, j;

    //计算解码后的字符串长度
    len = strlen(code);
    //判断编码后的字符串后是否有=
    if (strstr(code, "=="))
        str_len = len / 4 * 3 - 2;
    else if (strstr(code, "="))
        str_len = len / 4 * 3 - 1;
    else
        str_len = len / 4 * 3;

    res = (unsigned char *) malloc(sizeof(unsigned char) * str_len + 1);
    res[str_len] = '\0';
    *codelen = str_len;
    //以4个字符为一位进行解码
    for (i = 0, j = 0; i < len - 2; j += 3, i += 4)
    {
        res[j] = ((unsigned char)table[code[i]]) << 2 | (((unsigned char)table[code[i + 1]]) >> 4);           //取出第一个字符对应base64表的十进制数的前6位与第二个字符对应base64表的十进制数的后2位进行组合
        res[j + 1] = (((unsigned char)table[code[i + 1]]) << 4) | (((unsigned char)table[code[i + 2]]) >> 2); //取出第二个字符对应base64表的十进制数的后4位与第三个字符对应bas464表的十进制数的后4位进行组合
        res[j + 2] = (((unsigned char)table[code[i + 2]]) << 6) | ((unsigned char)table[code[i + 3]]);        //取出第三个字符对应base64表的十进制数的后2位与第4个字符进行组合
    }

    return res;
}

int main_rsa()
{
    char *ptr_en = NULL, *ptr_de = NULL;
    char *ptr_enbase = NULL, *ptr_debase = NULL;
    int len;
    int decode_len;
    char abyInStr[] = "this is my rsa test";

    printf("Input String[%d]:\n%s\n", strlen(abyInStr), abyInStr);

    //加密
    len = rsa_pub_encrypt(abyInStr, (char *) PUBLICKEY, &ptr_en);
    printf("rsa_pub_encrypt[%d]\n", len);

    //64编码
    ptr_enbase = (char *) base64_encode((unsigned char *) ptr_en, len);
    printf("base64_encode[%d]:\n%s\n", strlen(ptr_enbase), ptr_enbase);

    //64解码
    ptr_debase = (char *) base64_decode((char *) ptr_enbase, &decode_len);
    printf("base64_decode[%d]\n", decode_len);

    //解密
    rsa_prv_decrypt(ptr_debase, ( char *)PRIVATEKEY, len, &ptr_de);
    printf("Output String[%d]:\n%s\n", strlen(ptr_de), ptr_de == NULL ? "NULL" : ptr_de);

    if (ptr_enbase != NULL)
    {
        free(ptr_enbase);
    }
    if (ptr_debase != NULL)
    {
        free(ptr_debase);
    }

    if (ptr_en != NULL)
    {
        free(ptr_en);
    }
    if (ptr_de != NULL)
    {
        free(ptr_de);
    }

    return 0;
}
