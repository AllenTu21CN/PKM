## ��װ

* docker��װ�ο�[�ٷ��ĵ�](https://hub.docker.com/_/nextcloud/)

* `docker-compose.yml`����

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

* �ٷ�docker����
    * Ӧ��Ŀ¼��`/var/www/html`
    * �����ļ�`/var/www/html/config/config.php`
    * ����Ŀ¼`/var/www/html/data`

## ��������
```
# �鿴�û��б�
php occ user:list

# ɨ��ָ���û�������ļ�(����web�е��ļ��б�)
php occ files:scan mm [--all] [-p=...]

# ȫ������ͼƬ����ͼ
php occ preview:generate-all -vvv

# ��������ͼƬ����ͼ
php occ preview:pre-generate 
```