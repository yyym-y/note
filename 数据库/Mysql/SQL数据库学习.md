![image-20230511185525642](../AppData/Roaming/Typora/typora-user-images/image-20230511185525642.png)

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511185602810.png" alt="image-20230511185602810" style="zoom:80%;" />

下载操作：

[MySQL](https://www.mysql.com/cn/)

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511185859030.png" alt="image-20230511185859030" style="zoom:80%;" />



<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511194154612.png" alt="image-20230511185940618" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511194227617.png" alt="image-20230511194227617" style="zoom:80%;" />

登录方法：

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511194448111.png" alt="image-20230511194448111" style="zoom:80%;" />

2.

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511194615831.png" alt="image-20230511194615831" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511194659854.png" alt="image-20230511194659854" style="zoom:80%;" />在这

里开启或关闭

3.

cmd以管理员打开：

```bash
net start mysql80
```

```bash
net stop mysql80
```

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511194922601.png" alt="image-20230511194922601" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511195201100.png" alt="image-20230511195201100" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511190546492.png" alt="image-20230511190546492" style="zoom:80%;" />



通过表来存储的数据库就叫做关系型数据库，否则就叫做非关系型数据库

![image-20230511190711501](../AppData/Roaming/Typora/typora-user-images/image-20230511190711501.png)

安装好sql后，电脑就成为了一个简单的服务器，然后客户端连接上软件，然后软件可以创建多个数据库，每一个数据库可以创建多个表，每个表可以存储不同的信息

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511191137251.png" alt="image-20230511191137251" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511192446709.png" alt="image-20230511192446709" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511191707322.png" alt="image-20230511191707322" style="zoom:80%;" />

```sql
SHOW DATABASES; # 显示所有的数据库
```

```sql
SELECT DATABASE(); # 查询当前数据库
```

```sql
CREATE DATABASE name;
/*创建数据库，如果已经创建会报错，可以加上前置语句*/
CREATE DATABASE IF NOT EXISTS name;
/*也可以指定字符集*/
CREATE DATABASE IF NOT EXISTS name default charset utf8mb4;
/*不推荐使用utf8，因为utf8是三个字节，但有些字符需要四个字节，所以推荐使用utf8mb4*/
```

```sql
DROP DATABASES name;
/*存在就会删除，不存在报错*/
DROP DATABASES IF EXISTS name;
```

```sql
USE name; # 使用直接加就好了
```

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511195851733.png" alt="image-20230511195851733" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511195923825.png" alt="image-20230511195923825" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511200006904.png" alt="image-20230511200006904" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511200036591.png" alt="image-20230511200036591" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511200052995.png" alt="image-20230511200052995" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511200130070.png" alt="image-20230511200130070" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511200235484.png" alt="image-20230511200235484" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511200249102.png" alt="image-20230511200249102" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511200507878.png" alt="image-20230511200507878" style="zoom:80%;" />

![image-20230511200701779](../AppData/Roaming/Typora/typora-user-images/image-20230511200701779.png)

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511202158808.png" alt="image-20230511202158808" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511202505030.png" alt="image-20230511202505030" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511202625687.png" alt="image-20230511202625687" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511202720888.png" alt="image-20230511202720888" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511202832158.png" alt="image-20230511202832158" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511211412298.png" alt="image-20230511211412298" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511211641601.png" alt="image-20230511211641601" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511212047290.png" alt="image-20230511212047290" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230511212149989.png" alt="image-20230511212149989" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512152340817.png" alt="image-20230512152340817" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512153059187.png" alt="image-20230512153059187" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512153323968.png" alt="image-20230512153323968" style="zoom:80%;" />

所有null值不参与聚合运算

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512153748951.png" alt="image-20230512153748951" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512153906065.png" alt="image-20230512153906065" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512154454868.png" alt="image-20230512154454868" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512155127972.png" alt="image-20230512155127972" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512155528348.png" alt="image-20230512155528348" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512160107862.png" alt="image-20230512160107862" style="zoom:80%;" />

 <img src="../AppData/Roaming/Typora/typora-user-images/image-20230512160257625.png" alt="image-20230512160257625" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512160342592.png" alt="image-20230512160342592" style="zoom:80%;" />

1、char_length(str)
（1）计算单位：字符
（2）不管汉字还是数字或者是字母都算是一个字符
2、length(str)
（1）计算单位：字节
（2）utf8编码：一个汉字三个字节，一个数字或字母一个字节。
（3）gbk编码：一个汉字两个字节，一个数字或字母一个字节。

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512200030361.png" alt="image-20230512200030361" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512200201054.png" alt="image-20230512200201054" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512200715450.png" alt="image-20230512200715450" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512201016854.png" alt="image-20230512201016854" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512201659562.png" alt="image-20230512201659562" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512202424736.png" alt="image-20230512202424736" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512202458866.png" alt="image-20230512202458866" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512203108935.png" alt="image-20230512203108935" style="zoom:80%;" />

如果是自动增长，申请失败后也会增加导致增加的数据混乱

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512203222220.png" alt="image-20230512203222220" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512203613605.png" alt="image-20230512203613605" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512203635694.png" alt="image-20230512203635694" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512204039432.png" alt="image-20230512204039432" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512204446899.png" alt="image-20230512204446899" style="zoom:80%;" />

<img src="../AppData/Roaming/Typora/typora-user-images/image-20230512204535957.png" alt="image-20230512204535957" style="zoom:80%;" />

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230512205343962.png" alt="image-20230512205343962" style="zoom:80%;" />