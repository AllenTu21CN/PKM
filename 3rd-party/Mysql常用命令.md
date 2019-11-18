
* 访问端口 3306
* 初次安装，初始密码：`cat /var/log/mysqld.log |grep password`
* 常用命令
```
systemctl enable mysqld
systemctl start mysqld

# 登录
mysql [-h <address>] -u root -p 
# 增加密码
mysqladmin -u root -password <new-pw>
# 修改密码
mysqladmin -u root -p <old-pw> password <new-pw>

# 设置当前用户密码
mysql> set password = password('123');

# 开启远程访问
mysql> grant all privileges on *.* to 'root'@'%' identified by 'your_password';
# 刷新权限生效
mysql> flush privileges;

# 创建数据库
mysql> create database <name>

# 显示数据库
mysql> show databases;

# 删除数据库
mysql> drop database <name>;

# 连接数据库
mysql> use <name>

# 删除数据表
mysql> drop table <name>;

# 查询行
mysql> select * from <name>;
mysql> select * from <name> order by id limit 0,2;
```