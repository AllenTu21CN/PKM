
## 1. 安装

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

## 2. Docker命令

### 2.1 镜像基本操作

```
# 搜索镜像
docker search centos
# 下载/更新
docker pull <img-name>:<tag>
docker pull centos
# 查看已下载镜像
docker images

# 删除镜像
docker image rm [image] 
                        --force    # 强制删除,即便有容器引用该镜像
                        --no-prune # 不要删除未带标签的父镜像
docker rmi [image] # 同上
# 注: 通过tag删除镜像: 1) 一个镜像有多个TAG时,删除某个TAG并不会删除镜像 2) 当一个镜像只有一个TAG时,删除这个TAG会导致镜像被删除

```

### 2.2 镜像修改和制作

* 从容器制作镜像

  1) 从镜像创建容器
  2) 进入容器内,修改配置
  3) 退出容器,并提交改动
  ```
  docker commit -m "Commit message" -a "Author" CONTAINER [REPOSITORY[:TAG]]
  ```

* 通过Dockerfile修改并创建镜像
  * Dockerfile内容参考如下
    ```
    # FROM 指定基础镜像
    FROM centos:8.1.1911

    # 维护者的信息
    MAINTAINER Tuyj <xxx@docker.com>

    # RUN 开头的指令会在创建中运行
    RUN yum -y config-manager --set-enabled PowerTools
    ```
  * 执行命令 
    ```
    docker build -t name[:tag] <Dockerfile-PATH>
    ```
  * Dockfile 中的指令被一条一条的执行。每一步都创建了一个新的容器，在容器中执行指令并提交修改（docker commit）。当所有的指令都执行完毕之后，返回了最终的镜像 id。所有的中间步骤所产生的容器都被删除和清理了。*注意一个镜像不能超过 127 层*

### 2.3 容器管理

* 容器启停

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

## 3. docker-compose命令

### 3.1 基本启停

```
# 根据配置文件后台启动容器
docker-compose up -d        # detach模式/后台模式
# 停止容器
docker-compose down
```

### 链接外部容器

1. 创建共享网络: `docker network create webapps`

2. 查看当前Docker网络: `docker network ls`

3. 各容器`docker-compose.yml`中使用指定网络

```
version: '2'
services:
  app:
    ...

    networks:
    - webapps

networks:
  custom_net:
   external:
      name: webapps
```

4. 各容器中通过service name来访问指定容器中的端口，比如`jdbc:mysql://db:3306/webapps`

## 4. 示例

### 4.1 nextcloud安装和启动

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
      - MYSQL_ROOT_PASSWORD=<pwd>
      - MYSQL_PASSWORD=<pwd>
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