## 安装

* docker安装参考[官方文档](https://hub.docker.com/_/nextcloud/)

* `docker-compose.yml`如下

```
version: '2'

services:
  db:
    image: mariadb
    command: --transaction-isolation=READ-COMMITTED --binlog-format=ROW # --log-bin to enable log to bin
    restart: always
    volumes:
      - ./mariadb:/var/lib/mysql
    environment:
      - MYSQL_ROOT_PASSWORD=tuyajieno1
      - MYSQL_PASSWORD=tuyajieno1
      - MYSQL_DATABASE=nextcloud
      - MYSQL_USER=nextcloud

  app:
    image: nextcloud
    ports:
      - 28081:80
    links:
      - db
    volumes:
      - ./nextcloud:/var/www/html
      - /mnt/house/nextcloud/data:/var/www/html/data
    restart: always
```

* 官方docker镜像
    * 应用目录在`/var/www/html`
    * 配置文件`/var/www/html/config/config.php`
    * 数据目录`/var/www/html/data`

## 常用命令
```
# 查看用户列表
php occ user:list

# 扫描指定用户下面的文件(更新web中的文件列表)
php occ files:scan mm [--all] [-p=...]

# 全量生成图片缩略图
php occ preview:generate-all -vvv

# 增量生成图片缩略图
php occ preview:pre-generate 
```