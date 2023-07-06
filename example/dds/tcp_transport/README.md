# TCP_TRANSPORT

## 说明

在 tcp 模式下，publisher 会作为 server 端启动，subscriber 作为 client 端启动

#### 自签名证书

```bash
# 生成根证书的私钥
openssl genrsa -out ca.key 4096

# 利用私钥生成一个根证书的申请
openssl req -new -key ca.key -out ca.csr

# 自签名的方式签发之前的申请的证书
openssl x509 -req -days 3650  -in ca.csr -signkey ca.key -out ca.crt

# 生成服务器验证证书的私钥
openssl genrsa -out server.key 4096

# 生成证书的申请文件
openssl req -new -key server.key -out server.csr

# 利用根证书签发服务器身份验证证书，(PEM格式)
openssl x509 -req -days 3650 -in server.csr -sha256 -CA ca.crt -CAkey ca.key -CAcreateserial -CAserial server.srl -out server.crt
```

```bash
# 生成秘钥交换文件
openssl dhparam -out dh2048.pem 2048
```
