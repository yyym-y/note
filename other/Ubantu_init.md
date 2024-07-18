### 初始化 root 密码

```
sudo passwd root
```

### 安装 ssh

```
apt install openssh-server
```

### 取消ssh 登录密码

```
vim /etc/ssh/sshd_config
```

添加一行:

```
PermitRootLogin yes
```

重启ssh