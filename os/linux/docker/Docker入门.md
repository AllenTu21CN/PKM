
## ��װ

* docker��װ

```
yum install docker
systemctl enable docker
systemctl start docker 
```

* docker-compose��װ
    * ��[Github](https://github.com/docker/compose/releases/)��ȡ���µ�release�汾
    * ���غ����`/user/bin`��

* GUI����Portainer��װ
    * [https://portainer.io/install.html](https://portainer.io/install.html)
    * ��������
    
    ```
    docker volume create portainer_data
    docker run -d -p 9000:9000 -v /var/run/docker.sock:/var/run/docker.sock -v portainer_data:/data portainer/portainer
    ```

## Docker����

* �������

```
docker search centos
docker pull <img-name>:<tag>    # ����/����
docker pull centos
docker images       # �鿴�����ؾ���
```

* ������ͣ/����

```
# ��������: ��������
docker run <img-name>[:<tag>] <cmd>
# ��������: ����ʽ(��������)
docker run -it <img-name>[:<tag>] <shell-name> # 'i':���ֱ�׼����� 't': ����α�ն��Ұ󶨱�׼����
# ��������: ��̨�ػ�
docker run -d/--detach <img-name>[:<tag>] <cmd>
# ������������
    -p/--publish [<ip>:]<host-port>:<container-port> # portӳ��
    -v/--volume <host-dir>:<container-dir>           # ����ӳ��
    --name                                           # ������������
    -e                                               # ���û�������,�����ж��
    --link                                           # ������������
    --hostname                                       # ָ�������а󶨵����������ڴ�������ֿ��ʱ��ʹ�õ�

# ��������: ��ֹͣ��
docker start <name/id>

# ɾ��/ֹͣ/ɱ��
docker rm/stop/kill <name/id>

# �鿴�����ڲ����
docker logs <name/id> -f # ����ģʽ
                      -t # ��ʾʱ���

# �鿴�Ѵ���������
docker ps       # (Ĭ��)������
          -a    # ����״̬
          -n    # �����n��(����״̬)
          -l    # �����1��(����״̬)
          -q    # quietģʽ�Ĵ�ӡ,ֻ��ʾid

# �鿴�����ײ���Ϣ
docker inspect <name/id>
                         -f {{.State.Pid}} # ��ʽ�����,��: �鿴��һ�����̵�ID
```

* ��������

```
# attach��������
docker attach <name/id>     # ����ն�attachͬһ������ʱ,�������ʱͬ��/������

# ����������SSHServer,Զ�̵�¼,�������������

# nsenterͨ�������ĵ�һ������ID����������namespace
nsenter --target 3326 --mount --uts --ipc --net --pid

# exec��������
docker exec -it <name/id> /bin/bash 
```

## docker-compose����

```
# ���������ļ���̨��������
docker-compose up -d        # detachģʽ/��̨ģʽ
# ֹͣ����
docker-compose down
```

## ʾ��: nextcloud��װ������

```
docker search nextcloud
docker pull docker.io/nextcloud

# �ֶ���������(���Ƽ�)
docker run -d --restart=always --name nextcloud -p 80:80 -v /root/nextcloud:/data docker.io/nextcloud

# docker-compose.yml
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
      - 18081:80
      - 18443:443
    links:
      - db
    volumes:
      - ./nextcloud:/var/www/html
      - /mnt/house/nextcloud/data:/var/www/html/data
    restart: always


docker-compose up -d
```