
* ���ʶ˿� 3306
* ���ΰ�װ����ʼ���룺`cat /var/log/mysqld.log |grep password`
* ��������
```
systemctl enable mysqld
systemctl start mysqld

# ��¼
mysql [-h <address>] -u root -p 
# ��������
mysqladmin -u root -password <new-pw>
# �޸�����
mysqladmin -u root -p <old-pw> password <new-pw>

# ���õ�ǰ�û�����
mysql> set password = password('123');

# ����Զ�̷���
mysql> grant all privileges on *.* to 'root'@'%' identified by 'your_password';
# ˢ��Ȩ����Ч
mysql> flush privileges;

# �������ݿ�
mysql> create database <name>

# ��ʾ���ݿ�
mysql> show databases;

# ɾ�����ݿ�
mysql> drop database <name>;

# �������ݿ�
mysql> use <name>

# ɾ�����ݱ�
mysql> drop table <name>;

# ��ѯ��
mysql> select * from <name>;
mysql> select * from <name> order by id limit 0,2;
```