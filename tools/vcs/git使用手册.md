# Git��������

```
git status              #��ǰ�Ķ�(��ɾ�����Ķ�������)
git diff --name-status  #��ǰ�޸ĵ��ļ�
git remote -v           #���е�remote��ַ
```

# ����

## ԭ��

* ���زֿ�洢�ṹ
    ![](git�洢�ṹ.png)

## ����

```
# ���ؿ�
git clone /path/to/repository
# Զ�̿�
git clone git@xxxx/xxxx.git
# ��ӵڶ���Զ��
git remote add username-xx git@xxxx/xxxx.git
```

## �ļ����/ɾ��

```
git add *
git add <filename>
        -A          #�ݹ�����Ŀ¼�������ļ�
        -i          #����ģʽ
git rm <filename>   #�ļ�ɾ��
       --cached     #ֻɾ���ļ����� ����ɾ���ļ�����
       -r           #ѭ��ɾ����ǰĿ¼�������ļ�
```

## ����

* �����ļ�Ȩ��У��: `git config --add core.filemode false`
* �����ļ�׷��,��`.git/info/exclude`�������

```
.o
.svn
*.pyc

```

## �ύ�Ķ�

```
# �Ķ�->HEAD
git commit -m "�����ύ��Ϣ"
           -a #ȫ���ύ

#HEAD->�ֿ�
git push origin master
git remote add origin <server>
```

## �����Ķ�

```
#HEAD->�ļ�
git checkout -- <filename>     #����ӵ��������ĸĶ����Լ����ļ���������Ӱ��

#Զ�ֿ̲�->�ļ�(�������б��ظĶ����ύ)
git fetch origin
git reset --hard origin/master #������HEAD״̬
git revert <commit�汾>        #�ָ�����ʷ�汾
```

## ��֧����

```
#������֧���л�
git checkout -b fname

#�л���֧
git checkout fname

#ɾ����֧
git branch -d fname

#��ɾ��Զ�̷�֧
git push origin :fname

#���ͷ�֧���ֿ�
git push origin fname

#��������֧
git branch (-m | -M) [<oldbranch>] <newbranch>

#�鿴��֧��ϵ
git show-branch       #��֧�ݽ�״��
git log --graph       #��ǰ��֧commitͼ
git log --graph --all #���з�֧commitͼ
git log --graph --decorate --pretty=oneline --abbrev-commit --all #ͬ��
```

## ��֧�ϲ�

```
#�ϲ�������֧����ǰ��֧(�Զ�ģʽ)
git merge <branch>

#��B��֧�ϵ�f.txt�Բ�����ʽ���ӵ�A��֧��
git checkout A_branch
git checkout --patch B_branch path/to/f.txt

#��A��֧��f.txt�ļ�����B��֧��Ӧ�ļ�
git checkout B_branch
git checkout A_bracn path/to/f.txt
```

## ����

```
#�Զ�merge
git pull <remote> <branch>
# �Զ��ϲ�ʧ�ܻᵼ�³�ͻ��conflicts�������룺�����޸ĳ�ͻ,Ȼ��ִ��git add <filename>
# �ںϲ��Ķ�֮ǰ��Ҳ����ʹ����������鿴��git diff <source_branch> <target_branch>

#�ֶ�merge
git fetch origin master
git log -p master..origin/master
git merge origin/master
```

## ��ǩ

```
git tag <tag> logID #commitID��ǰNλ,��֤Ψһ����
```

## ��־

```
git log -p              #��������ʽ��ʾÿ���ύ�����ݲ���
        -[n]            #�����ʾ�����n�θ���
        --stat          #��ʾ��Ҫ����������ͳ�� 
        --shortstat     #ֻ��ʾ���������޸�����Ƴ�ͳ��
        --name-only     #��ʾ���޸ĵ��ļ��嵥
        --name-status   #��ʾ��[����/�޸�/ɾ��]״̬���ļ��嵥��
        --relative-date #���ʱ����ʾ
        --abbrev-commit #��ʾ�̵�(��֤Ψһ��)commitID(SHA-1ֵ)
        --graph         #��ʾ ASCII ͼ�α�ʾ�ķ�֧�ϲ���ʷ��
        --pretty        #ʹ��������ʽ��ʾ��ʷ�ύ��Ϣ. oneline,short,full,fuller,format(���ָ����ʽ),��:
                        #  --pretty=format:"%h - %an, %ar : %s"
                        #   ѡ��     ˵��
                        #   %H      �ύ����commit����������ϣ�ִ�
                        #   %h      �ύ����ļ�̹�ϣ�ִ�
                        #   %T      ������tree����������ϣ�ִ�
                        #   %t      ������ļ�̹�ϣ�ִ�
                        #   %P      ������parent����������ϣ�ִ�
                        #   %p      ������ļ�̹�ϣ�ִ�
                        #   %an     ���ߣ�author��������
                        #   %ae     ���ߵĵ����ʼ���ַ
                        #   %ad     �����޶����ڣ������� -date= ѡ��Ƹ�ʽ��
                        #   %ar     �����޶����ڣ��������ǰ�ķ�ʽ��ʾ
                        #   %cn     �ύ��(committer)������
                        #   %ce     �ύ�ߵĵ����ʼ���ַ
                        #   %cd     �ύ����
                        #   %cr     �ύ���ڣ��������ǰ�ķ�ʽ��ʾ
                        #   %s      �ύ˵��
```

## �޸�ע��

```
#�޸����һ����û��push�ύ
git commit --amend

#�޸����N����û��push�ύ
git rebase -i head~3 #�޸ĵ�ǰ�汾�ĵ���������״̬����������������
                     #  pick f9173fc Fix wrong name 'path_filename'
                     #  pick 3fddde0 Change versiton to 0.2:   Add share option
                     #  pick 5962845 Change platform section name from [arch-platform-name] to [name:platform]
                     #  ...
                     #  �����Ҫ�޸��ĸ����Ͱ����е�pick�ĳ�edit��Ȼ�󱣴��˳�����ʱ�����ʾ
                     #  Stopped at 4c85552... Change versiton to 0.2:   Add share option
                     #  You can amend the commit now, with
                     #          git commit --amend
                     #  Once you are satisfied with your changes, run
                     #          git rebase --continue
                     #  ������ʾ�����޸ļ��ɡ�

#�޸�push֮����ύ
git push -f origin master   #���������޸ı����ύ,Ȼ��-fǿ���ύ��Զ��
```

## ����������

* ���������ùؼ���: ��`.git/config`���

```
[alias]
 co = checkout
 ci = commit
 b = branch

```

* Զ�ֿ̲������ύ: ��Զ�ֿ̲��`.git/config`�������

```
[receive]
    denyCurrentBranch = ignore
```

