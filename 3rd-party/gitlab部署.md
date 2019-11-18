
## 安装

```
# docker安装gitlab
docker search gitlab
docker pull docker.io/gitlab/gitlab-ce

# docker-compose.yml
version: '2'

services:
  app:
    image: gitlab/gitlab-ce
    ports:
      - 40001:80
      - 40002:443
    volumes:
      - /opt/gitlab/config:/etc/gitlab
      - /opt/gitlab/log:/var/log/gitlab
      - /mnt/work/gitlab/data:/var/opt/gitlab
    restart: always
    hostname: git.mmx2.ml
```

## 配置

```
# 配置外部访问url: 修改`/etc/gitlab/gitlab.rb`
external_url 'http://git.mmx2.ml'

# 邮箱配置,参考[文档](https://docs.gitlab.com/omnibus/settings/smtp.html)
gitlab_rails['smtp_enable'] = true
gitlab_rails['smtp_address'] = "smtp.163.com"
gitlab_rails['smtp_port'] = 465
gitlab_rails['smtp_user_name'] = "tuyajie21cn@163.com"
gitlab_rails['smtp_password'] = "tuyajie31CN"
gitlab_rails['smtp_domain'] = "163.com"
gitlab_rails['smtp_authentication'] = "login"
gitlab_rails['smtp_enable_starttls_auto'] = true
gitlab_rails['smtp_tls'] = true

gitlab_rails['gitlab_email_from'] = "tuyajie21cn@163.com"
user["git_user_email"] = "tuyajie21cn@163.com"

# 发送测试邮件
gitlab-rails console 
Notify.test_email('415929165@qq.com', 'test main', 'test').deliver_now
```

## 常用命令

```
# 重新应用gitlab的配置
gitlab-ctl reconfigure
 
# 重启gitlab服务
gitlab-ctl restart
 
# 查看gitlab运行状态
gitlab-ctl status
 
#停止gitlab服务
gitlab-ctl stop
 
# 查看gitlab运行日志
gitlab-ctl tail
 
# 停止相关数据连接服务
gitlab-ctl stop unicorn
gitlab-ctl stop sideki
```