# MySQL 快速手册

## 基础篇

### MySQL的打开

命令行方法：

CMD以管理员方式打开

输入：

```bash
mysql -u root -p
```

输入密码即可登录

### DDL - 定义数据库对象

> 数据库操作

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



> 表单操作

```sql
SHOW TABLES; /*查询当前数据库所有表*/
```

```sql
DESC name; /*查询表结构,即各个key值*/
```

```sql
SHOW CREATE TABLE name; /*查看建表时候的信息*/
```

```sql
/*表的创建*/
CREATE TABLE name(
    字段1 字段1类型 [comment '注释'],
    字段2 字段2类型 [comment '注释']
)[comment "表注释"];

--------------------------
CREATE TABLE name(
    id int comment '注释',
    name varchar(50) comment '注释'
)comment '表注释';
```

```mysql
/*添加字段*/
# ALTER TABLE name ADD 字段名 类型 [comment 注释];
ALTER TABLE name ADD ass int comment "添加字段";
```

```mysql
/*修改字段*/
# 只修改数据类型 ： ALTER TABLE 表名 MODIFY 字段名 新数据类型;
ALTER TABLE name MODIFY ass varchar(10);
# 修改字段名和数据类型 ： ALTER TABLE 表名 CHANGE 旧字段名 新字段名 类型 [comment 注释];
ALTER TABLE name CHANGE ass kkk int comment "注释";
```

```mysql
/*删除字段*/
# ALTER TABLE 表名 DROP 字段名;
ALTER TABLE name DROP kkk;
```

```mysql
/*修改表名*/
# ALTER TABLE 表名 RENAME TO 新表名；
ALTER TABLE name RENAME TO myname;
```

```mysql
/*删除表*/
# 删除表 DROP TABLE [IF EXISTS] 表名;
DROP TABLE [IF EXISTS] name;
# 删除表并重新创建该表 TRUNCATE TABLE 表名;
TRUNCATE TABLE name;
```



> 常见的数据类型

挖个坑  ：)



### DML - 对数据增删改

```mysql
/*添加数据*/
# 给指定字段添加数据 INSERT INTO 表名(字段名1， 字段名2，...) VALUES(值1， 值2...);
INSERT INTO name(id) VALUES(100);
# 给全部字段添加数据(要字段一一对应) INSERT INTO 表名 VALUES(值1， 值2...);
INSERT INTO name VALUES(123, "yyym");
/*批量添加数据*/
# 指定字段 INSERT INTO 表名(字段名1， 字段名2，...) VALUES(值1， 值2...),(值1， 值2...)...;
# 全部字段 INSERT INTO 表名 VALUES(值1， 值2...), (值1， 值2...)...;
INSERT INTO name(id) VALUES(456),(789),(741);
INSERT INTO name VALUES(569, "lr580"), (563, "Hura"), (4743, "cgc");
```

```mysql
/*修改数据*/
# UPDATA 表名 SET 字段名1 = 值1, 字段名2 = 值2... [WHERE 条件];
# 没有条件则说明修改所有值
UPDATE name SET name = "cst7" WHERE id = 789;
```

```mysql
/*删除数据*/
# DELETE FROM 表名 [WHERE 条件];
# 没有条件则删除所有的数据
DELETE FROM name WHERE id = 741;
```



### DQL - 对数据进行查询

```mysql
/* 基本格式如下：
SELECT 字段列表
FROM 表名列表
WHERE 条件列表
GROUP BY 分组字段列表
HAVING 分组后条件列表
ORDER BY 排序字段列表
LIMIT 分页参数 ;
*/
```

> 数据准备（为了更好的演示，我们提供一份数据）

```mysql
CREATE TABLE emp(
    id int comment '编号',
    workno varchar(10) comment '工号',
    name varchar(10) comment '姓名',
    gender char comment '性别',
    age tinyint unsigned comment '年龄',
    idcard char(18) comment '身份证号',
    workaddress varchar(50) comment '工作地址',
    entrydata date comment '入职时间'
) comment '员工表';
```

```mysql
INSERT INTO emp (id, workno, name, gender, age, idcard,workaddress, entrydata)
VALUES  (1, '1','柳岩', '女', 20, '123456789012345678','北京','2000-01-01'),
        (2,'2','张无忌','男',18, '123456789012345670', '北京','2005-09-01'),
        (3,'3','韦一笑','男',38,'123456789712345670','上海','2005-08-01'),
        (4,'4','赵敏','女',18, '123456757123845670','北京', '2009-12-01'),
        (5,'5','小昭','女',16,'123456769012345678' , '上海', '2007-07-01'),
        (6,'6','杨道', '男', 28, '12345678931234567X', '北京', '2006-01-01'),
        (7,'7','范瑶', '男', 40, '123456789212345670', '北京', '2005-05-01'),
        (8,'8','黛绮丝', '女', 38,  '123456157123645670', '天津' , '2015-05-01'),
        (9,'9','范凉凉','女', 45, '123156789012345678' , '北京', '2010-04-01'),
        (10, '10','陈友谅','男', 53,'123456789012345670', '上海' ,'2011-01-01'),
        (11, '11' , '张士诚' , '男', 55 , '123567897123465670', '江苏' , '2015-05-01'),
        (12, '12' , '常遇春', '男', 32, '123446757152345670', '北京', '2004-02-01'),
        (13, '13', '张三丰', '男', 88, '123656789012345678',  '江苏' , '2020-11-01'),
        (14, '14', '灭绝', '女', 65, '123456719012345670', '西安' , '2019-05-01'),
        (15, '15', '胡青牛', '男',70, '12345674971234567X', '西安', '2018-04-01'),
        (16, '16', '周芷若', '女',18,null, '北京', '2012-06-01');
```



> 查询指定字段

```mysql
# 查询指定字段 SELECT 字段1, 字段2 ... FROM 表名;
# 查询全部字段 SELECT * FROM 表名;
# 去除重复记录 SELECT DISTINCT 字段列表 FROM 表名; (即去重数据)
# 可以给字段名起别名 SELECT 字段1 AS 别名 FROM 表名;
SELECT name, workno, age FROM emp;
SELECT * from emp;
SELECT DISTINCT workaddress FROM emp;
SELECT workaddress as '工作地址' FROM emp;
```



> 条件查询

```mysql
# SELECT 字段列表 FROM 表名 WHERE 条件列表
```

|              符号               |                     意义                      |
| :-----------------------------: | :-------------------------------------------: |
|    > , >= , < , <= , = , !=     |                与数学意义一致                 |
| AND , && , OR , \|\| ,  NOT , ! |                  逻辑运算符                   |
|        BETWEEN...AND...         |         在某个范围之内（含最大最小）          |
|            IN(....)             |         在 in 之后列表中的值， 多选一         |
|           LIKE 占位符           | 模糊匹配（_ 匹配单一字符， % 匹配任意个字符） |
|             IS NULL             |                    是NULL                     |

```mysql
# 查询年龄为18，20，40的员工信息
SELECT * FROM emp WHERE age = 18 || age = 20 || age = 40;
SELECT * FROM emp WHERE age in (18, 20, 40);
# 查询姓名为两个字的员工信息
SELECT * FROM emp WHERE name LIKE '__';
# 查询身份证号以X结尾的员工信息
SELECT * FROM emp WHERE idcard LIKE '%X';
```



> 聚合函数

```mysql
# SELECT 聚合函数(字段列表) FROM 表名;
# 所有的NULL值不参与计算
```

| 函数  |   功能   |
| :---: | :------: |
| count | 统计数量 |
|  max  |  最大值  |
|  min  |  最小值  |
|  avg  |  平均值  |
|  sum  |   求和   |

演示

```mysql
SELECT count(id) as '总数' FROM emp;
SELECT avg(age), max(age), min(age) FROM emp;
SELECT count(id) FROM emp WHERE workaddress = '西安';
```



> 分组查询

```mysql
# SELECT 字段列表 FROM 表名 [WHERE 条件] GROUP BY 字段分组名 [HAVING 分组后的过滤条件];
```

WHERE 是分组之前进行过滤， HAVING 是分组之后进行过滤

WHERE 不能对聚合函数进行判断 ， HAVING 可以

```mysql
# 根据性别分组 ，统计男性员工和女性员工的数量
SELECT gender, count(*) from emp GROUP BY gender;
# 根据性别分组 ，统计男性员工和女性员工的平均年龄
SELECT gender, avg(age) FROM emp GROUP BY gender;
# 查询年龄小于45的员工，并根据工作地址分组，获取员工数量大于等于3的工作地址
SELECT workaddress, count(*) FROM emp WHERE age < 45 GROUP BY workaddress HAVING count(*) > 3;
```



> 排序查询

```mysql
#  SELECT 字段列表 FROM 表名 ORDER BY 字段1 排序方法1， 字段2， 排序方法2....;
```

如果第一个字段值一样，才会根据第二个字段排序

> ASC 升序（默认）
>
> DESC 降序

```mysql
SELECT name, age, entrydata FROM emp ORDER BY age , entrydata desc ;
```



> 分页查询

```mysql
SELECT 字段列表 FROM 表名 LIMIT 起始索引, 查询记录数;
```

```mysql
SELECT name, age FROM emp LIMIT 0, 10;
SELECT  name age FROM emp LIMIT 10, 10;
```



### DCL - 用户管理

用户的信息全部存在 mysql数据库的 user表里面

要想查看可以使用

```mysql
USE mysql;
SELECT * FROM user;
```



> 创建用户

```mysql
CREATE USER “用户名”@“主机名” IDENTIFIED  '密码';
```

> 修改用户密码

```mysql
ALTER USER “用户名”@“主机名” IDENTIFIED WITH '原始密码' BY '新密码';
```

> 删除用户

```mysql
DROP USER “用户名”@“主机名”;
```

> 查询权限

```mysql
SHOW GRANTS FOR “用户名”@“主机名”;
```

> 授予权限

```mysql
GRANT 权限列表 ON 数据库名.表名 TO “用户名”@“主机名”; # 可以使用 *
```

> 撤销权限

```mysql
REVOKE 权限列表 ON 数据库名.表名 FROM “用户名”@“主机名”;
```

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230719152144761.png" alt="image-20230719152144761" style="zoom:80%;" />



### 函数

>  字符串函数

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230719152558033.png" alt="image-20230719152558033" style="zoom:80%;" />

> 数值函数

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230719153157616.png" alt="image-20230719153157616" style="zoom:80%;" />

> 时间函数

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230719154120627.png" alt="image-20230719154120627" style="zoom:80%;" />

> 流程函数

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230719154639079.png" alt="image-20230719154639079" style="zoom:80%;" />



### 约束

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230808143252099.png" alt="image-20230808143252099" style="zoom:80%;" />

```mysql
CREATE TABLE user(
    id int primary key auto_increment comment "主键,会自动增长,添加数据的时候不需要传递参数",
    name varchar(10) not null unique comment "不能为空, 且不能重复",
    age int check ( age > 0 && age < 120 ) comment "设置约束条件, 控制年龄的范围",
    static int default 1 comment "设置默认值"
)comment "约束建表";
```



### 多表查询

分类 ： 

* 连接查询
  * 内连接 ： 相当于查询 A， B 交集的部分
  * 外连接
    * 左外连接： 查询左表的全部数据，以及两张表的交集数据
    * 右外连接：查询右表的全部数据，以及两张表的交集数据
  * 自连接



> 内连接

隐式内连接

```mysql
SELECT 字段列表 FROM 表一, 表二 WHERE 条件;
```

显示内连接

```mysql
SELECT 字段列表 FROM 表一 [INNER] JOIN 表二 ON 连接条件
```

 PS ： 可以结合别名， 方便使用



> 外连接

左外连接

```mysql
SELECT 字段列表 FROM 表一 LEFT [OUTER] JOIN 表二 ON 条件;
```

右外连接

```mysql
SELECT 字段列表 FROM 表一 RIGHT [OUTER] JOIN 表二 ON 条件;
```



> 自连接

```mysql
SELECT 字段列表 FROM 表A 别名A JOIN 表二 别名二 ON 条件;
```

可以将自己看成两张表



> 联合查询

吧多次查询的结果联合起来

```mysql
SELECT * from 表A
UNION [ALL]
SELECT * FROM 表B;
```

PS: 联合查询的基本条件为两个表查询出来列数， 内容要一样

PS ： 不加ALL 的话会去重， 加了ALL不会去重



> 子查询

在SQL语句里面嵌套SQL语句

PS： 理解为用SQL语句的返回的表作为临时表进行多表查询

 分类 ：

* 标量子查询（子查询结果为单个值）
* 列子查询 （子查询结果为一列）
* 行子查询（子查询结果为一行）
* 表子查询（子查询结果为多行多列）



__> 标量子查询（子查询结果为单个值）

```mysql
SELECT * from 表一 WHERE 字段 > (SELECT ID FROM 表二 WHERE 条件);
```



__> 列子查询 （子查询结果为一列）

常见操作符

| 操作符 |          描述          |
| :----: | :--------------------: |
|   IN   |     在指定内容里面     |
| NOT IN |    不在指定内容里面    |
|  ANY   |     有一个满足即可     |
|  SOME  |       与ANY一致        |
|  ALL   | 子查询的结果都必须满足 |

```sql
SELECT 字段 FROM 表一 WHERE 字段 > (SELECT ID FROM 表二);
```



__> 行子查询（子查询结果为一行）

```sql
SELECT * FROM 表一 WHERE (字段一, 字段二...) = (SELECT 字段一, 字段二... from 表二 WHERE 条件);
```



__> 表子查询（子查询结果为多行多列）

常用操作符为 IN

```sql
SELECT * FROM 表一 WHERE (字段一, 字段二...) IN (SELECT 字段一, 字段二... from 表二 WHERE 条件);
```



### 事务

....懒了

