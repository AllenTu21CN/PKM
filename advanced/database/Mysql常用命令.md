
## 安装

* 访问端口 3306
* 初次安装，初始密码：`cat /var/log/mysqld.log |grep password`
* 服务启动
    ```
    systemctl enable mysqld
    systemctl start mysqld
    ```

## MySQL命令

```
# 登录/连接数据库
mysql [-h<address>] 
      [-P<port>]
      -u<username> 
      -p<password>
      -D<database-name>

# 增加密码
mysqladmin -u root -password <new-pw>
# 修改密码
mysqladmin -u root -p <old-pw> password <new-pw>
# 设置当前用户密码
mysql> set password = password('123');

# 查询用户
mysql> SELECT * FROM mysql.user

# 执行SQL文件1
mysql [-h<address>] [-P<port>] -u<username> -p<password> -D<database-name> < xxx.sql

# 执行SQL文件2
mysql [-h<address>] [-P<port>] -u<username> -p
mysql> user <database-name>;
mysql> source xxx.sql;
```

## SQL语句

### 权限管理

```sql
# 开启远程访问(root)
grant all privileges on *.* to 'root'@'%' identified by 'your_password';

# 刷新权限生效
flush privileges;

# 授权用户对服务器的权限
GRANT ALL ON *.* TO 'webapps'@'127.0.0.1';

# 授权用户对数据库的权限
GRANT ALL ON `webapps`.* TO 'webapps'@'127.0.0.1';
```

### 数据库操作

```sql
# 显示数据库
show databases;

# 创建数据库
CREATE DATABASE <name>
CREATE DATABASE `webapps` CHARACTER SET utf8 COLLATE utf8_general_ci

# 删除数据库
drop database <name>;

# 连接数据库
use <name>
```

### 表操作

```sql
# 创建表
CREATE TABLE `user` (
`id`  int(11) UNSIGNED NOT NULL AUTO_INCREMENT ,
`username`  varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '' ,
`password`  varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '' ,
PRIMARY KEY (`id`)
);

# 插入数据
INSERT INTO `user` (`username`, `password`) VALUES ('Tuyj', '123')
INSERT INTO `user` (`username`, `password`) VALUES ('Allen', '123')

# 删除表
drop table <name>;

# 查询行
select * from <name>;
select * from <name> order by id limit 0,2;

# 更新行
UPDATE table_name SET column1=value1,column2=value2,... WHERE some_column=some_value;

# 删除行
DELETE FROM table_name WHERE some_column=some_value;

```

### 用户操作

```sql
# 创建用户
CREATE USER 'webapps'@'127.0.0.1' IDENTIFIED BY '<pwd>';
```

## 常用

### 日期操作

https://www.cnblogs.com/pandaly/p/10268145.html