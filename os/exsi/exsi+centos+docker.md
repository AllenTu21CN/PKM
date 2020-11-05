# ���˷��������¼

## 1. ��װ&����ESXi

* [VMWare����](https://www.vmware.com/products/esxi-and-esx.html)����ISO(VMware-VMvisor-Installer-6.7.0.update03-14320388.x86_64.iso)
* UltraISO��ISOд�뵽U��A�У���Ϊ��װ��
* ��U�����������ݰ�װ�򵼽�ESXiϵͳ��װ��U��B�У���Ϊϵͳ��
* ���ΰ�װ��ͨ��ֱ�ӿ���̨(TVUI)�������硢����SSH
* �޸�ESXi Web��vSphere Web client���˿� @Deprecated
    * ��������·������֧�ֶ˿�ӳ�䣬�����������ESXi��Ҫ����80/443�˿ڣ����ڰ�ȫ���ǣ���Ҫ�޸Ķ˿ںţ�
    * �ο�[�ٷ��ĵ�](https://kb.vmware.com/s/article/1021199?lang=zh_CN)����[�˿�ʹ�ñ�](https://kb.vmware.com/s/article/1012382)����[�����ο�](https://www.cnblogs.com/hitaoge/p/11158225.html)
        * �޸� /etc/vmware/rhttpproxy/config.xml ��httpPort��httpsPort
        * �����޸ķ���ǽ���ԣ�/etc/vmware/firewall/service.xml �޸�80/443�˿�
    * ���������޸ģ�ȴӰ����esxcli��vSphere client��ʹ�ã��������Ӿܾ�����û�м����о����ͬ���޸�esxcliʹ�ö˿ڣ����չٷ��ĵ����޸�vSphere client�˿ڵ�˼·Ӧ�ÿ�����ͨ��
* SSH�˿��޸ģ�ԭ��ͬ�� @Deprecated
    * �ο�[�ٷ��ĵ�](https://kb.vmware.com/s/article/2011818?lang=zh_CN)
    * ���ڰ�ȫ���ǣ����շ���������¶SSH����
* �رշ���ǽ��[�ο�](https://www.kkpan.com/article/2475.html)�����ڰ�ȫ���ǣ���û�в��� @Deprecated
* ESXiĬ�������Ѿ��㹻�ȶ���С���޸ķ������Ӳ��ɿ����أ����Եȸ���·��������WEB��SSH�˿ڻ�ԭ
* �½��洢�豸
    * ESXi Web -> �洢 -> �½����ݴ洢 -> VMFS��ʽ -> ѡ��SSD���̣���SATA����ֱͨ��������У���Ҫ�����ʽ��ΪESXi�Ĵ���
* **����Ӳ��ֱͨ**
    * ����ֱͨ: ESXi Web -> ���� -> ���� -> Ӳ�� -> PCI�豸 -> �л�ֱͨ
    * ���������ʱ�������PCI�豸,�������װ�ú�,ϵͳ�о���ֱ�ӿ�����PCI�豸
    * ESXi 6.7U3Ĭ�ϲ�֧��ֱͨSATA����������Ҫ��̨�޸����ò������ã�6.7.0�ƺ���֧����˲�����
        ``` ESXi-Shell
        [root ~]$ lspci -v | grep AHCI
        0000:00:1f.2 SATAcontroller Mass storage controller: Intel Corporation Lynx Point AHCIController [vmhba0]
         Class 0106: 8086:8c02
        [root ~]$ echo "#Intel Corporation Lynx Point AHCI Controller" >> /etc/vmware/passthru.map
        # ����8086 8c02Ϊlspci�����Ʒ�ơ��ͺţ�d3d0Ϊ�̶����豸���ͣ�
        [root ~]$ echo "8086 8c02 d3d0 false" >> /etc/vmware/passthru.map
        [root ~]$ reboot
        ```
    * Ч������
    ![ʾ��](passthru.png)
    ![ʾ��](add_passthru_dev.png)
    ![ʾ��](sata_on_client.png)
    ![ʾ��](disk_on_client.png)
* ���������
    * ��������μ�
    ![ʾ��](create_vos.png)
    * ע�⣬���PCIֱͨ�豸����������ڴ�Ԥ�����ֵ����趨������ڴ�
    * �������ϵͳ��ͼ�ν���,���ֶ�ָ���Կ�������<Ĭ������>���ܵ���ϵͳ�޷�������

## 2. ��װ&����CentOS7

* ��������
    * ����ͨ��ͼ�ν����޸�IP/DNS/Route
    * Ҳ�����޸������ļ� `/etc/resolv.conf` �� `/etc/sysconfig/network-scripts/ifcfg-enXXX`
* �رշ���ǽ��SELinux
    * `firewall-cmd --state` �� `systemctl status firewalld` �鿴״̬
    * ͨ��`systemctl start/stop/disable firewalld`���Ʒ���ǽ״̬
    * `getenforce`��ȡSELinux״̬��ͨ��`setenforce 0`��ʱ�ر�, �޸�`/etc/selinux/config`���ùر�
    * CentOS 7Ĭ��û�а�װiptables
* sudoers����
    * �����޸�`/etc/sudoers`�������Ƽ�ͨ������`visudo`���޸�����
    * ͨ��`sudo -l`��ȡ��ǰ�û���sudoȨ��
    * ����ֱ����sudoers�ļ������Ȩ�ޣ�Ҳ���Ե���д��`/etc/sudoers.d/`�£���sudoers��`#includedir /etc/sudoers.d`,һ��'#'��ʾ�򿪣�
    * ���Բο�root�û��ſ�����Ȩ�ޣ�Ҳ���Բο���������ʹ�û���ȡָ��Ȩ�����������룺
    ```shell
    # allen�û������Ի���%group_name
    allen   ALL=(ALL)NOPASSWD: /usr/bin/yum, \
            /bin/vim /var/log/secure
    ```
* ����yumԴ
    * ʹ�ð���Դ���Ĭ��yumԴ
    ```shell
    cd /etc/yum.repos.d/
    wget http://mirrors.aliyun.com/repo/Centos-7.repo
    mv CentOS-Base.repo CentOS-Base.repo.ori
    mv Centos-7.repo Centos-7-aliyun.repo
    ln -s Centos-7-aliyun.repo CentOS-Base.repo
    yum clean all
    yum makecache
    yum update
    ```
    * ���yumԴ: *������*
* SSH�˿��޸�
    * rootȨ���޸�`/etc/ssh/sshd_config`��`Port 22`
    * ��������`Port 22`֮���һ���¶˿�,����ͨ����ɾ��Ĭ�϶˿�
    * ����sshd����Ч: `systemctl restart sshd`
* ����ϵͳ��־
    * `/var/log/cron` ��ʱ������־
    * `/var/log/secure` ��ȫ��ص���־(��SSH��¼��)
* ������Ӻ͹���
    * `smartctl --all /dev/sdb`���Բ鿴����S.M.A.R.T��Ϣ��smartctlΪcentos�Դ����ߣ�Ҳ����ͨ��`yum install smartmontools`��װ
    * ��������ʽ���������ļ�ϵͳ������
    ```shell
    # ��������
    fdisk /dev/sdb  # ��sdb����
        -> p        # �鿴������Ϣ
        -> n        # �½�����
        -> 1        # �������(��Ӧsdb1)
        ->          # ��������̷�1��������ʼ�����ͽ�����������Ĭ��ֵ
        -> w        # ����ִ�з���
    
    # ��ʽ���ʹ����ļ�ϵͳ
    # xfsΪ���µ��ļ�ϵͳ����,Ч�ʸ���; ʹ��mkfs.xfs�����ļ�ϵͳδ��Ч
    mkfs -t xfs /dev/sdb1
    
    # �ֶ����Թ���
    mkdir /mnt/hhd_Hitachi
    mount /dev/sdb1 /mnt/hhd_Hitachi
    
    # ���������Զ�����
    # /etc/fstab���������
    /dev/sdb1 /mnt/hhd_Hitachi xfs defaults 0 0
    # �����й��ز�������������ֵ
    #   defaults: rw, suid, dev, exec, auto, nouser, and async.
    #   auto/noauto �Զ�����
    #   nouser ֻ�г����û����Թ���
    #   ro ��ֻ��Ȩ�޹���
    #   rw ���ɶ���дȨ�޹���
    #   user �κ��û������Թ���
    ```
* ����NFS
    ����μ�<NFS����>�ĵ�

## 3. ������������

### ����IP��������
* �绰�����ſͷ���Ҫ����IP
* freenomע����Ѷ�������
* freenom��������IP,����DNSЧ��

### DDNS
* ���ؿ�ԴDDNS��������[godns](https://github.com/TimothyYe/godns)������һЩ��Ŀ�����ѡ����[NewFuture/DDNS](https://github.com/NewFuture/DDNS)��
    * pythonʵ�֣�֧��dnspod,����DNS,CloudFlare,DNSCOM...
    * python3.5δ���Գɹ���python2.7����
    * ���������޸���run.py
    * `config.json`����
    
    ```
    {
      "$schema": "https://ddns.newfuture.cc/schema/v2.json", 
      "debug": false, 
      "dns": "cloudflare", 
      "id": "415929165@qq.com", 
      "index4": "url:http://ip.sb", 
      "index6": false, 
      "ipv4": [
        "mmx2.ml", 
        "www.mmx2.ml",
        "git.mmx2.ml",
        "disk.mmx2.ml"
      ], 
      "ipv6": [
      ], 
      "proxy": null, 
      "token": "xxxxxxxxxx"
    }
    ```
* ѡ��DNS���̣�����[aliyun](http://www.alidns.com/)��[dnspod](https://www.dnspod.cn/)�����ѡ��[cloudflare](https://www.cloudflare.com/)
    * cloudflare��������������ٶȿ죬��������£�֧�ֹ����⣻����ɫ�շѷ�����CDN
    * cloudflare��ע���˺ţ�����api token
* ������ע�᳧�̴���DNSת����DNS����
    * cloudflare�����site,��ȡDNSת�Ƶ�ַ
    * freenom��дcloudflare dns�����ַ
* ����crontab���񣬶�ʱ��鹫��IP�䶯��ͬ����cloudflare
    * `start_task.sh`

    ```
    #!/usr/bin/env bash
    RUN_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )";
    
    INTERVAL=$1
    [ -z "$INTERVAL" ] && INTERVAL=5
    
    crontab -l > _tmp_crontab.txt
    
    grep "ddns_timer_task.sh" _tmp_crontab.txt > /dev/null
    
    if [ $? -eq 0 ]; then
        echo "Had added this task, ignore current action"
    else
        echo "Try to add task to crontab with interval $INTERVAL mins"
        echo "*/$INTERVAL * * * * sh $RUN_DIR/ddns_timer_task.sh $RUN_DIR >> $RUN_DIR/record.log 2>&1" >> _tmp_crontab.txt
        echo "1 1 1 * * touch $RUN_DIR/config.json" >> _tmp_crontab.txt
        crontab _tmp_crontab.txt
    fi
    
    rm _tmp_crontab.txt
    ```
    * `ddns_timer_task.sh`: 
    
    ```python2.7 \"$1/run.py\" -c "$1/config.json"```

## 4.��������

### �˿������
* mmx2.ml:28443 -> 10.1.83.102:28443 -> ESXi Http
* mmx2.ml:22103 -> 10.1.83.103:22103 -> SSH
* mmx2.ml:28081 -> 10.1.83.103:28081 -> NextCloud Http:80
* mmx2.ml:40001 -> 10.1.83.103:40001 -> Gitlab Http:80
* mmx2.ml:40002 -> 10.1.83.103:40002 -> Gitlab Https:443
* mmx2.ml:40003 -> 10.1.83.103:40003 -> SSH@11.5@3bu
* mmx2.ml:40004 -> 10.1.83.103:40004 -> ProxyHttp@ss.3bu.cn
* mmx2.ml:40005 -> 10.1.83.103:40005 -> ProxySocks5@ss.3bu.cn

### SSH�˿�ת��
* ����ʹ�ù�˾����: `sshpass -p $REMOTE_SSH_PASSWD ssh -o StrictHostKeyChecking=no -p $REMOTE_SSH_PORT $REMOTE_SSH_SVR -NfR $REMOTE_PROXY_PORT:$LOCAL_PROXY_SVR:$LOCAL_PROXY_PORT`
* ����SSH��˾������: `sshpass -p $REMOTE_SSH_PASSWD ssh -o StrictHostKeyChecking=no -p $REMOTE_SSH_PORT $REMOTE_SSH_SVR -NfR $REMOTE_PROXY_PORT:localhost:$LOCAL_SSH_PORT`