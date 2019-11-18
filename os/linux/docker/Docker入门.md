
## 安装

* docker安装

```
yum install docker
systemctl enable docker
systemctl start docker 
```

* docker-compose安装
    * 从[Github](https://github.com/docker/compose/releases/)获取最新的release版本
    * 下载后放入`/user/bin`下

* GUI管理Portainer安装
    * [https://portainer.io/install.html](https://portainer.io/install.html)
    * 启动服务
    
    ```
    docker volume create portainer_data
    docker run -d -p 9000:9000 -v /var/run/docker.sock:/var/run/docker.sock -v portainer_data:/data portainer/portainer
    ```

## Docker命令

* 镜像操作

```
docker search centos
docker pull <img-name>:<tag>    # 下载/更新
docker pull centos
docker images       # 查看已下载镜像
```

* 容器启停/管理

```
# 运行容器: 短暂运行
docker run <img-name>[:<tag>] <cmd>
# 运行容器: 交互式(进入容器)
docker run -it <img-name>[:<tag>] <shell-name> # 'i':保持标准输入打开 't': 分配伪终端且绑定标准输入
# 运行容器: 后台守护
docker run -d/--detach <img-name>[:<tag>] <cmd>
# 运行其他参数
    -p/--publish [<ip>:]<host-port>:<container-port> # port映射
    -v/--volume <host-dir>:<container-dir>           # 磁盘映射
    --name                                           # 定义容器名字
    -e                                               # 设置环境变量,可以有多个
    --link                                           # 关联其他容器
    --hostname                                       # 指定容器中绑定的域名，会在创建镜像仓库的时候使用到

# 运行容器: 已停止的
docker start <name/id>

# 删除/停止/杀死
docker rm/stop/kill <name/id>

# 查看容器内部输出
docker logs <name/id> -f # 跟踪模式
                      -t # 显示时间戳

# 查看已创建的容器
docker ps       # (默认)运行中
          -a    # 所有状态
          -n    # 最近的n个(所有状态)
          -l    # 最近的1个(所有状态)
          -q    # quiet模式的打印,只显示id

# 查看容器底层信息
docker inspect <name/id>
                         -f {{.State.Pid}} # 格式化输出,例: 查看第一个进程的ID
```

* 容器进入

```
# attach进入容器
docker attach <name/id>     # 多个终端attach同一个容器时,输入输出时同步/阻塞的

# 容器内运行SSHServer,远程登录,但不建议如此做

# nsenter通过容器的第一个进程ID进入容器的namespace
nsenter --target 3326 --mount --uts --ipc --net --pid

# exec进入容器
docker exec -it <name/id> /bin/bash 
```

## docker-compose命令

```
# 根据配置文件后台启动容器
docker-compose up -d        # detach模式/后台模式
# 停止容器
docker-compose down
```

## 示例: nextcloud安装和启动

```
docker search nextcloud
docker pull docker.io/nextcloud

# 手动启动容器(不推荐)
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