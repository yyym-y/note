# MySQL.....讲解

## 数据库概念：

|      名称      |                 全称                 |                简称                |
| :------------: | :----------------------------------: | :--------------------------------: |
|     数据库     | 存储数据的仓库，数据有组织的进行存储 |           DateBase（DB）           |
| 数据库管理系统 |         操纵和管理数据的软件         | DataBase Management System（DBMS） |
|      SQL       |      操纵关系型数据库的编程语言      |                SQL                 |



登录方式：

cmd以**管理员**打开：

```bash
net start mysql80
```

```bash
net stop mysql80
```

接着进行等录操作：

```bat
mysql -u root -p
```



## 关系型数据库（RDMBMS）

由二维表构成，由横轴和竖轴确定位置，类比excel表格

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512150602508.png" alt="image-20230512150602508" style="zoom:80%;" />

通过表来存储的数据库就叫做关系型数据库，否则就叫做非关系型数据库

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511190711501.png" alt="image-20230511190711501" style="zoom: 50%;" />

安装好sql后，电脑就成为了一个简单的服务器，然后客户端连接上软件，然后软件可以创建多个数据库，每一个数据库可以创建多个表，每个表可以存储不同的信息



## SQL

SQL分类：

| 分类 |                    说明                    |
| :--: | :----------------------------------------: |
| DDL  |          定义语言：定义数据库对象          |
| DML  | 操作语言：对数据库表中的数据进行增删改操作 |
| DQL  |       查询语言：查询数据库中表的记录       |
| DCL  |  控制语言：创建数据库用户，控制数据库权限  |

* SQL通用语法：

> **以分号结尾**
>
> 不区分大小写
>
> 单行注释：`#` 	, 	`--`
>
> 多行注释: `/**/`



### DDL



```sql
SHOW DATABASES; # 显示所有的数据库
```

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512151542648.png" alt="image-20230512151542648" style="zoom:80%;" />

```sql
SELECT DATABASE(); # 查询当前数据库
```

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512151715284.png" alt="image-20230512151715284" style="zoom:80%;" />

```sql
CREATE DATABASE name;
/*创建数据库，如果已经创建会报错，可以加上前置语句*/
CREATE DATABASE IF NOT EXISTS name;
/*也可以指定字符集*/
CREATE DATABASE IF NOT EXISTS name default charset utf8mb4;
/*不推荐使用utf8，因为utf8是三个字节，但有些字符需要四个字节，所以推荐使用utf8mb4*/
```

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512151751755.png" alt="image-20230512151751755" style="zoom:80%;" />

```sql
DROP DATABASE name;
/*存在就会删除，不存在报错*/
DROP DATABASE IF EXISTS name;
```

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512151926870.png" alt="image-20230512151926870" style="zoom:80%;" />

```sql
USE name; # 使用直接加就好了
```

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512151616182.png" alt="image-20230512151616182" style="zoom:80%;" />

### 