
## ��װ

```
# docker��װgitlab
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

## ����

```
# �����ⲿ����url: �޸�`/etc/gitlab/gitlab.rb`
external_url 'http://git.mmx2.ml'

# ��������,�ο�[�ĵ�](https://docs.gitlab.com/omnibus/settings/smtp.html)
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

# ���Ͳ����ʼ�
gitlab-rails console 
Notify.test_email('415929165@qq.com', 'test main', 'test').deliver_now
```

## ��������

```
# ����Ӧ��gitlab������
gitlab-ctl reconfigure
 
# ����gitlab����
gitlab-ctl restart
 
# �鿴gitlab����״̬
gitlab-ctl status
 
#ֹͣgitlab����
gitlab-ctl stop
 
# �鿴gitlab������־
gitlab-ctl tail
 
# ֹͣ����������ӷ���
gitlab-ctl stop unicorn
gitlab-ctl stop sideki
```