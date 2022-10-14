## AES(对称)

* 通常使用方法
    * 定义密钥(密码)，加解密双方带外交换密钥
    * plaintext + 密钥 --encrypt--> ciphertext （输入、密钥、输出数据长度一致）
    * ciphertext + 密钥 --decrypt--> plaintext （输入、密钥、输出数据长度一致）

* 算法重要参数
    * 密钥长度：128/192/256位，影响数据的处理和对齐长度；如128位密钥，即最多16个字符的"密码"
    * 加密模式：ECB/CBC/CFB/OFB
        * 除了ECB，其他模式都需要额外参数：IV偏移值，具体含义未了解
    * 填充模式：zero/pkcs5/pkcs7/iso10126/ansix923，即密钥、加解密数据不满处理长度（比如128位）时，填充方式
    * 输出方式：AES算法输出为二进制流，一般附加使用base64编码，可以获得可见字符串


* 一个可用的AES加解密实现 tiny-AES
    * https://github.com/kokke/tiny-AES-c
    * 每次加解密只处理“一个处理长度”的数据，比如128位（16字节），大于这个长度的数据加解密，需要自己分次理
    * 可参考使用代码：tiny-AES-c/test.c testtest_encrypt_ecb_verbose

## RSA（非对称）

* "个人发送加密数据给发布者"流程
    * 发布者生成密钥对，公开传输公钥
    * 个人: plaintext + 公钥 --encrypt--> ciphertext
    * 发布者: ciphertext + 私钥 --decrypt--> plaintext
    * 原理：只有唯一的私钥才能解密公钥编码的数据

* "发布者签名向个人证明身份"流程
    * 发布者生成密钥对，公开传输公钥
    * 发布者: plaintext + 私钥 --encrypt--> ciphertext
    * 个人: ciphertext + 公钥 --decrypt--> plaintext
    * 原理: 公钥只能解密唯一的私钥编码的数据

* 密钥对生成参数
    * 密钥长度：512/1024/2048/4096位
    * 密钥存储格式：PKCS#1/PKCS#8
        * 理解："密钥"加上一些信息base64编码成"PKCS"格式，在加上格式封装存成"PEM"文件
        * PEM可以存储PKCS#1/PKCS#8/CRT等数据格式
        * 不管那种格式，密钥本身的数据是一样的，只是存储格式的差别
        * PKCS#8是1的优化，存储了更多的密钥本身的信息
        ![](https://i0.hdslb.com/bfs/article/cc24148a74b58651d3c9cb264fe0e6a2bfa23024.png@710w_686h_progressive.webp)
    * 私钥密码：用于二次保护（加密）私钥的密码，可以为空

* 加解密参数
    * 填充模式：pkcs1/pkcs1_oaep/sslv23
        * pkcs1填充大小为11字节

* 使用OpenSSL for Win：http://slproweb.com/
* OpenSSL 命令行/库 与 RSA https://www.jianshu.com/p/9da812e0b8d0
* rsa.cpp: 使用OpenSSL做RSA的加解密，但是带密码的私钥情况下解码失败
* OpenSSL命令加解密RSA：
    * 加密：
    `echo 12345678 12345678 1234 | openssl pkeyutl -encrypt -pubin -inkey plt_rsa_pub_pkcs8.pem  -pkeyopt rsa_padding_mode:pkcs1 | openssl enc -A -base64`
    * 解密：
    `echo U7sV0lGRtL/wWr9AjmR6fyDmUoN15dutvO9S9YudXVVdP+eml5vgRIRRBlRpZ9F/JD/fuQUmQeyeIZChWikXlw== | openssl base64 -d | openssl pkeyutl -decrypt -inkey plt_rsa_pri_pkcs8.pem -pkeyopt rsa_padding_mode:pkcs1 -passin pass:dlxx`