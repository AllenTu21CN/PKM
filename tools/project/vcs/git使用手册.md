# Git常用命令

```
git status              #当前改动(含删除、改动、增加)
git diff --name-status  #当前修改的文件
git remote -v           #所有的remote地址
```

# 基础

## 原理

* 本地仓库存储结构

![](git存储结构.png)

## 创建

```
# 本地库
git clone /path/to/repository
# 远程库
git clone git@xxxx/xxxx.git
# 添加第二个远程
git remote add username-xx git@xxxx/xxxx.git
# 克隆指定分支的最近一次提交
git clone --depth 1 /path/to/repository -b <branch-or-tag> 
# 重新拉取完整项目,解决depth不完整的问题
git pull --unshallow
```

## 文件添加/删除

```
git add *
git add <filename>
        -A          #递归的添加目录下所有文件
        -i          #互动模式
git rm <filename>   #文件删除
       --cached     #只删除文件跟踪 但不删除文件本身
       -r           #循环删除当前目录下所有文件
```

## 忽略

* 忽略文件权限校验: `git config --add core.filemode false`
* 忽略文件追踪,在`.git/info/exclude`添加如下

```
.o
.svn
*.pyc

```

## 提交改动

```
# 改动->HEAD
git commit -m "代码提交信息"
           -a #全部提交

#HEAD->仓库
git push origin master
git remote add origin <server>
```

## 放弃改动

```
#HEAD->文件
git checkout -- <filename>     #已添加到缓存区的改动，以及新文件，都不受影响

#远程仓库->文件(丢弃所有本地改动与提交)
git fetch origin
git reset --hard origin/master #撤销到HEAD状态
git revert <commit版本>        #恢复到历史版本
```

## 分支操作

```
#创建分支并切换
git checkout -b fname

#切换分支
git checkout fname

#删除分支
git branch -d fname

#再删除远程分支
git push origin :fname

#推送分支到仓库
git push origin fname

#重命名分支
git branch (-m | -M) [<oldbranch>] <newbranch>

#查看分支关系
git show-branch       #分支递交状况
git log --graph       #当前分支commit图
git log --graph --all #所有分支commit图
git log --graph --decorate --pretty=oneline --abbrev-commit --all #同上
```

## 分支合并

```
#合并其他分支到当前分支(自动模式)
git merge <branch>

#将B分支上的f.txt以补丁形式附加到A分支上
git checkout A_branch
git checkout --patch B_branch path/to/f.txt

#将A分支的f.txt文件覆盖B分支对应文件
git checkout B_branch
git checkout A_bracn path/to/f.txt
```

## 更新

```
#自动merge
git pull <remote> <branch>
# 自动合并失败会导致冲突（conflicts）。必须：人肉修改冲突,然后执行git add <filename>
# 在合并改动之前，也可以使用如下命令查看：git diff <source_branch> <target_branch>

#手动merge
git fetch origin master
git log -p master..origin/master
git merge origin/master
```

## 标签

```
git tag <tag> logID #commitID的前N位,保证唯一即可
```

## 日志

```
git log -p              #按补丁格式显示每次提交的内容差异
        -[n]            #则仅显示最近的n次更新
        --stat          #显示简要的增改行数统计 
        --shortstat     #只显示最后的行数修改添加移除统计
        --name-only     #显示已修改的文件清单
        --name-status   #显示带[新增/修改/删除]状态的文件清单。
        --relative-date #相对时间显示
        --abbrev-commit #显示短的(保证唯一的)commitID(SHA-1值)
        --graph         #显示 ASCII 图形表示的分支合并历史。
        --pretty        #使用其他格式显示历史提交信息. oneline,short,full,fuller,format(后跟指定格式),如:
                        #  --pretty=format:"%h - %an, %ar : %s"
                        #   选项     说明
                        #   %H      提交对象（commit）的完整哈希字串
                        #   %h      提交对象的简短哈希字串
                        #   %T      树对象（tree）的完整哈希字串
                        #   %t      树对象的简短哈希字串
                        #   %P      父对象（parent）的完整哈希字串
                        #   %p      父对象的简短哈希字串
                        #   %an     作者（author）的名字
                        #   %ae     作者的电子邮件地址
                        #   %ad     作者修订日期（可以用 -date= 选项定制格式）
                        #   %ar     作者修订日期，按多久以前的方式显示
                        #   %cn     提交者(committer)的名字
                        #   %ce     提交者的电子邮件地址
                        #   %cd     提交日期
                        #   %cr     提交日期，按多久以前的方式显示
                        #   %s      提交说明
```

## 修改注释

```
#修改最近一个还没有push提交
git commit --amend

#修改最近N个还没有push提交
git rebase -i head~3 #修改当前版本的倒数第三次状态，这个命令后会出来：
                     #  pick f9173fc Fix wrong name 'path_filename'
                     #  pick 3fddde0 Change versiton to 0.2:   Add share option
                     #  pick 5962845 Change platform section name from [arch-platform-name] to [name:platform]
                     #  ...
                     #  如果你要修改哪个，就把那行的pick改成edit，然后保存退出，这时候会提示
                     #  Stopped at 4c85552... Change versiton to 0.2:   Add share option
                     #  You can amend the commit now, with
                     #          git commit --amend
                     #  Once you are satisfied with your changes, run
                     #          git rebase --continue
                     #  按照提示进行修改即可。

#修改push之后的提交
git push -f origin master   #按照上面修改本地提交,然后-f强制提交到远程
```

## 其他不常用

* 重命名常用关键词: 在`.git/config`添加

```
[alias]
 co = checkout
 ci = commit
 b = branch

```

* 远程仓库允许提交: 在远程仓库的`.git/config`添加如下

```
[receive]
    denyCurrentBranch = ignore
```

