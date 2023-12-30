# python基础笔记

## 注释

### 单行注释

以#开头，#右边的所有东西当做说明，而不是真正要执行的程序，起辅助说明作用。

```python
# #开头右边的都是注释，解析器会忽略注释
print('hello world')  #我的作用是在控制台输出hello world
```

### 多行注释

以`'''`开始，并以`'''` 结束，我们称之为多行注释。

```pytho
'''
注释
注释
注释
'''
```



## 变量

### 变量定义

定义变量的语法为: `变量名 = 变量值`。(这里的 = 作用是赋值。)，注：区别于c语言，定义变量时不需要提前声明变量类型。

### 查看数据类型

使用type来查看变量的类型

```python
a = hallo
type(a)
```

## 数据的输出

使用print()

```python
print("hallo world")
```

### 格式化输出

1.

```python
name = "yyym"
age = 16
print("我的名字是%s，年龄是%d"%(name,age))
```

2.

```python
name = "yyym"
age = 16
print("我的名字是{}，年龄是{}".format(name,age))
```

3.

```python
name = "yyym"
age = 16
print(f"我的名字是{name}，年龄是{age}")
```

具体解释

```python
# 省略字段名传递位置参数
print('我叫{}，今年{}岁。'.format('小明', 18))
"""
我叫小明，今年18岁。
"""

# 大括号个数可以少于位置参数的个数
print('我爱吃{}和{}。'.format('香蕉', '苹果', '大鸭梨'))
"""
我爱吃香蕉和苹果。
"""

# 大括号个数多于位置参数的个数则会报错
# print('我还吃{}和{}。'.format('西红柿'))
"""
IndexError: tuple index out of range
"""
```

**可以通过数字形式的简单字段名传递位置参数**。

- 数字必须是大于等于 0 的整数。
- 带数字的替换字段可以重复使用。
- 数字形式的简单字段名相当于把 format 中的所有位置参数整体当作一个元组，通过字段名中的数字进行取值。即 {0} 等价于 tuple[0]，所以大括号内的数字不能越界。

```python
# 通过数字形式的简单字段名传递位置参数
print('身高{0}，家住{1}。'.format(1.8, '铜锣湾'))
"""
身高1.8，家住铜锣湾
"""

# 数字形式的简单字段名可以重复使用。
print('我爱{0}。\n她今年{1}。\n我也爱{0}。'.format('阿香', 17))
"""
我爱阿香。
她今年17。
我也爱阿香。
"""

# 体会把所有位置参数整体当成元组来取值
print('阿香爱吃{1}、{3}和{0}。'.format(
    '榴莲', '臭豆腐', '皮蛋', '鲱鱼罐头', '螺狮粉'))
"""
阿香爱吃臭豆腐、鲱鱼罐头和榴莲。
"""

# 尝试一下越界错误
# print('{1}'.format('错误用法'))
"""
IndexError: tuple index out of range
"""
```

使用**变量名形式**的简单字段名传递**关键字参数**。

- 关键字参数的位置可以随意调换。

```python
# 使用变量名形式的简单字段名传递关键字参数
print('我大哥是{name}，今年{age}岁。'.format(name='阿飞', age=20))
"""
我大哥是阿飞，今年20岁。
"""

# 关键字参数的顺序可以随意调换
print('我大哥是{name}，今年{age}岁。'.format(age=20, name='阿飞'))
"""
我大哥是阿飞，今年20岁。
"""
```

**简单字段名的混合使用**

- 混合使用数字形式和变量名形式的字段名，可以同时传递位置参数和关键字参数。
- 关键字参数必须位于位置参数之后。
- 混合使用时可以省略数字。
- 省略字段名 `{}` 不能和数字形式的字段名 `{非负整数}` 同时使用。

```python
# 混合使用数字形式和变量名形式的字段名
# 可以同时传递位置参数和关键字参数
print('这是一个关于{0}、{1}和{girl}的故事。'.format(
    '小明', '阿飞', girl='阿香'))
"""
这是一个关于小明、阿飞和阿香的故事。
"""

# 但是关键字参数必须位于位置参数之后
# print('这是一个关于{0}、{1}和{girl}的故事。'.format(
    # '小明', girl='阿香' , '阿飞'))
"""
SyntaxError: positional argument follows keyword argument
"""

# 数字也可以省略
print('这是一个关于{}、{}和{girl}的故事。'.format(
    '小明', '阿飞', girl='阿香'))

# 但是省略字段名不能和数字形式的字段名同时出现
# print('这是一个关于{}、{1}和{girl}的故事。'.format(
#     '小明', '阿飞', girl='阿香'))
"""
ValueError: cannot switch from automatic field numbering to manual field specification
"""
```

**使用元组和字典传参**

`str.format()` 方法还可以使用 `*元组` 和 `**字典` 的形式传参，两者可以混合使用。 位置参数、关键字参数、`*元组` 和 `**字典` 也可以同时使用，但是要注意，位置参数要在关键字参数前面，`*元组` 要在 `**字典` 前面。

```python
# 使用元组传参
infos = '钢铁侠', 66, '小辣椒'
print('我是{}，身价{}亿。'.format(*infos))
"""
我是钢铁侠，身家66亿。
"""
print('我是{2}，身价{1}亿。'.format(*infos))
"""
我是小辣椒，身家66亿。
"""

# 使用字典传参
venom = {'name': '毒液', 'weakness': '火'}
print('我是{name}，我怕{weakness}。'.format(**venom))
"""
我是毒液，我怕火。
"""

# 同时使用元组和字典传参
hulk = '绿巨人', '拳头'
captain = {'name': '美国队长', 'weapon': '盾'}
print('我是{}, 我怕{weapon}。'.format(*hulk, **captain))
print('我是{name}, 我怕{1}。'.format(*hulk, **captain))

"""
我是绿巨人, 我怕盾。
我是美国队长, 我怕拳头。
"""

# 同时使用位置参数、元组、关键字参数、字典传参
# 注意：
# 位置参数要在关键字参数前面
# *元组要在**字典前面
tup = '鹰眼',
dic = {'weapon': '箭'}
text = '我是{1}，我怕{weakness}。我是{0}，我用{weapon}。'
text = text.format(
    *tup, '黑寡妇', weakness='男人', **dic)
print(text)
"""
我是黑寡妇，我怕男人。我是鹰眼，我用箭。
"""
```

**使用`.` 点号**

**传递位置参数**

- 替换字段形式：`{数字.属性名}`
- 只有一个替换字段的时候可以省略数字

```python
class Person(object):
  def __init__(self,name,age,gender):
    self.name = name
    self.age = age
    self.gender = gender
p = Person('zhangsan',18,'female')
print('姓名是{0.name},年龄是{0.age},性别是{0.gender}'.format(p))
print('姓名是{.name}'.format(p))  # 只有一个替换字段时，可以省略数字
```

**使用`[]`中括号**

- 用列表传递位置参数
- 用元组传递位置参数
- 用字典传递位置参数

```python
# 中括号用法：用列表传递位置参数
infos = ['阿星', 9527]
food = ['霸王花', '爆米花']
print('我叫{0[0]}，警号{0[1]}，爱吃{1[0]}。'.format(
    infos, food))
"""
我叫阿星，警号9527，爱吃霸王花。
"""

# 中括号用法：用元组传递位置参数
food = ('僵尸', '脑子')
print('我叫{0[0]}，年龄{1}，爱吃{0[1]}。'.format(
    food, 66))
"""
我叫僵尸，年龄66，爱吃脑子。
"""

# 中括号用法：用字典传递位置参数
dic = dict(name='阿星', pid=9527)
print('我是{[name]}！'.format(
    dic))
# 多个替换字段，不能省略数字
print('我是{0[name]}，警号{0[pid]}。'.format(
    dic))
"""
我是阿星！
我是阿星，警号9527。
"""
```

**转换字段**

**转换字段** `conversion field` 的取值有三种，前面要加 `!`：

- `s`：传递参数之前先对参数调用 `str()`
- `r`：传递参数之前先对参数调用 `repr()`
- `a`：传递参数之前先对参数调用 `ascii()`

> `ascii()` 函数类似 `repr()` 函数，返回一个可以表示对象的字符串。 但是对于非 `ASCII` 字符，使用 `\x`，`\u` 或者 `\U` 转义。

```python
# 转换字段
print('I am {!s}!'.format('Bruce Lee 李小龙'))
print('I am {!r}!'.format('Bruce Lee 李小龙'))
print('I am {!a}!'.format('Bruce Lee 李小龙'))
"""
I am Bruce Lee 李小龙!
I am 'Bruce Lee 李小龙'!
I am 'Bruce Lee \u674e\u5c0f\u9f99'!
"""
```

### 常见格式符号

| 格式符号 | 转换                       |
| -------- | -------------------------- |
| **%%**   | **输出 % 号**              |
| **%s**   | **字符串**                 |
| **%d**   | **有符号十进制整数**       |
| **%f**   | **浮点数**                 |
| **%c**   | **字符**                   |
| %u       | 无符号十进制整数           |
| %o       | 八进制整数                 |
| %x       | 十六进制整数（小写字母0x） |
| %X       | 十六进制整数（大写字母0X） |
| %e       | 科学计数法（小写'e'）      |
| %E       | 科学计数法（大写“E”）      |
| %g       | ％f和％e 的简写            |
| %G       | ％f和％E的简写             |

## 数据的输入

输入使用input()函数

```python
name = input("请输入名字")
```

**注意:**

- input()的小括号中放入的是提示信息，用来在获取数据之前给用户的一个简单提示
- input()在从键盘获取了数据以后，会存放到等号右边的变量中
- input()会把用户输入的任何值都作为字符串来对待

## 数据类型转换

| 函数            | 说明                  |
| --------------- | --------------------- |
| int(x, [base ]) | 将x转换为一个整数     |
| float(x)        | 将x转换为一个浮点数   |
| str(x)          | 将对象 x 转换为字符串 |
| bool(x)         | 将对象x转换成为布尔值 |

- 转换成为整数

```python
print(int("123"))  # 123 将字符串转换成为整数

print(int(123.78))  # 123 将浮点数转换成为整数

print(int(True))  # 1 布尔值True转换成为整数是 1
print(int(False)) # 0 布尔值False转换成为整数是 0

# 以下两种情况将会转换失败
'''
123.456 和 12ab 字符串，都包含非法字符，不能被转换成为整数，会报错
print(int("123.456"))
print(int("12ab"))
'''

# 使用int()函数进行类型转换时，还可以传入两个参数，第二个参数用来表示进制。
print(int("21",8))  # 输出的结果 是17.八进制的21,对应的十进制数字是17
print(int("F0",16)) # 输出的结果是240.十六进制的F0,对应的十进制数字是240

"""
以下写法会报错。八进制里允许的最大值是7,所以 29 不是一个合法的八进制数
print(int("29",8))
"""
```

- 转换成为浮点数

```py
f1 = float("12.34")
print(f1)   # 12.34
print(type(f1)) # float 将字符串的 "12.34" 转换成为浮点数 12.34

f2 = float(23)
print(f2)  # 23.0
print(type(f2)) # float 将整数转换成为了浮点数
```

- 转换成为字符串

```python
str1 = str(45)
str2 = str(34.56)
str3 = str(True)
print(type(str1),type(str2),type(str3))# 全部转化为了str
```

- 转换成为布尔值

```python
print(bool(''))
print(bool(""))
print(bool(0))
print(bool({}))
print(bool([]))
print(bool(()))
print(bool(None))
```

**在python中，只有空字符串**`'',""`**，数字0,空字典{},空列表[],空元组(),和空数据None会被转换成为False,其他的都会被转换成为True**

## 算数运算符

| 运算符 | 描述   | 实例                                                         |
| ------ | ------ | ------------------------------------------------------------ |
| +      | 加     | 两个对象相加 a + b 输出结果 30                               |
| -      | 减     | 得到负数或是一个数减去另一个数 a - b 输出结果 -10            |
| *      | 乘     | 两个数相乘或是返回一个被重复若干次的字符串 a * b 输出结果 200 |
| /      | 除     | b / a 输出结果 2                                             |
| //     | 取整除 | 返回商的整数部分 9//2 输出结果 4 , 9.0//2.0 输出结果 4.0     |
| %      | 取余   | 返回除法的余数 b % a 输出结果 0                              |
| **     | 指数   | a**b 为10的20次方， 输出结果 100000000000000000000           |
| ()     | 小括号 | 提高运算优先级，比如: (1+2) * 3                              |

注意：混合运算时，优先级顺序为： `**` 高于 `* / % //` 高于 `+ -` ，为了避免歧义，建议使用 () 来处理运算符优先级。 并且，不同类型的数字在进行混合运算时，整数将会转换成浮点数进行运算。

## 赋值运算符

| 运算符 | 描述       | 实例                                                         |
| ------ | ---------- | ------------------------------------------------------------ |
| =      | 赋值运算符 | 把 = 号右边的结果 赋给 左边的变量，如 num = 1 + 2 * 3，结果num的值为7 |

### 复合赋值运算符

| 运算符 | 描述             | 实例                      |
| ------ | ---------------- | ------------------------- |
| +=     | 加法赋值运算符   | c += a 等效于 c = c + a   |
| -=     | 减法赋值运算符   | c -= a 等效于 c = c - a   |
| *=     | 乘法赋值运算符   | c *= a 等效于 c = c * a   |
| /=     | 除法赋值运算符   | c /= a 等效于 c = c / a   |
| //=    | 取整除赋值运算符 | c //= a 等效于 c = c // a |
| %=     | 取模赋值运算符   | c %= a 等效于 c = c % a   |
| **=    | 幂赋值运算符     | c\**= a 等效于 c = c ** a |

注意：赋值运算符是从右往左运算，将等号右边的值赋值给等号左边，所以，**等号的左边一定不能是常量或者表达式。**

## 比较运算符

以下假设变量a为10，变量b为20：

| 运算符 | 描述                                                         | 实例                                     |
| ------ | ------------------------------------------------------------ | ---------------------------------------- |
| ==     | 等于 - 比较对象是否相等                                      | (a == b) 返回 False.                     |
| !=     | 不等于 - 比较两个对象是否不相等                              | (a != b) 返回 true.                      |
| >      | 大于 - 返回x是否大于y                                        | (a > b) 返回 False。                     |
| <      | 小于 - 返回x是否小于y。所有比较运算符返回1表示真，返回0表示假。这分别与特殊的变量True和False等价。 | (a < b) 返回 true。                      |
| >=     | 大于等于 - 返回x是否大于等于y。                              | (a >= b) 返回 False。                    |
| <=     | 小于等于 - 返回x是否小于等于y。                              | (a <= b) 返回 true。                     |

### 字符串使用比较运算符

- 数字和字符串做`==`运算结果是false,除了 `==` 以外的逻辑运算时，会直接报错。

- 如果是两个字符串进行比较，会将每个字符都转换成对应的编码，然后逐一进行对比。

```python
In [1]: str1='a' 
In [2]: str2='ABC'

# 将字符转换成为对应的编码  a对应的编码是97,A对应的编码是65
In [3]: str1 > str2
Out[3]: True
```

## 逻辑运算符

| 运算符 | 逻辑表达式 | 描述                                                         | 实                                                           |
| ------ | ---------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| and    | x and  y   | 只要有一个运算数是False，结果就是False; 只有所有的运算数都为True时，结果才是True 做取值运算时，取第一个为False的值，如果所有的值都为True,取最后一个值。 | True and True and False-->结果为False True and True and True-->结果为True 1 and 0 and 2-->结果是0;1 and 2 and 3-->结果是3 |
| or     | x or y     | 只要有一个运算数是True，结果就是True; 只有所有的运算数都为False时，结果才是False 做取值运算时，取第一个为True的值，如果所有的值都为False,取最后一个值。 | False or False or True-->结果为True False or False or False-->结果为False 1 or 0 or 2-->结果是1;0 or None or () or '' or {} -->结果是{} |
| not    | not x      | 布尔"非" - 如果 x 为 True，返回 False 。如果 x 为 False，它返回 True。 | not(a and b) 返回 False                                      |

## 条件判断语句

1.

    if 要判断的条件:
        条件成立时，要做的事情

2.

    if 条件:
        满足条件时的操作
    else:
        不满足条件时的操作

3.    

    if xxx1:
        事情1
    elif xxx2:
        事情2
    elif xxx3:
        事情3

说明:

- 当xxx1满足时，执行事情1，然后整个if结束
- 当xxx1不满足时，那么判断xxx2，如果xxx2满足，则执行事情2，然后整个if结束
- 当xxx1不满足时，xxx2也不满足，如果xxx3满足，则执行事情3，然后整个if结束

## 循环判断语句

### while语句

```python
while 判断条件:
    代码块
```

注 ：与c语言不同的是，后面的条件不需要加括号

### for语句

```python
for 临时变量 in 列表或者字符串等可迭代对象:
    循环满足条件时执行的代码
```

使用range()函数可以很好的控制循环次数

```python
for x in range(5)：
    print(x)
```

结果为

```c
0
1
2
3
4
```

其实range的用法非常灵活，下面给出了一个例子：
**range(101)：可以用来产生0到100范围的整数，需要注意的是取不到101。**
**range(1, 101)：可以用来产生1到100范围的整数，相当于前面是闭区间后面是开区间。**
**range(1, 101, 2)：可以用来产生1到100的奇数，其中2是步长，即每次数值递增的值。**
**range(100, 0, -2)：可以用来产生100到1的偶数，其中-2是步长，即每次数字递减的值。**

### break和continue

break是结束整个循环。

continue是结束本次循环，开始下一轮循环。

注：

1. 在Python中，break和continue只能用于循环语句中。
2. break和continue在嵌套循环中使用时，只对最内层循环有效。

### while...else语句

```python
while 判断条件:
  条件成立时，循环体代码
else:
  条件不成立时，执行的代码
```

## 字符串

### 字符串的表示方式

```python
a = "I'm Tom"  # 一对双引号 
b = 'Tom said:"I am Tom"'  # 一对单引号
c = 'Tom said:"I\'m Tom"'  # 转义字符
d = '''Tom said:"I'm Tom"'''  # 三个单引号
e = """Tom said:"I'm Tom" """  # 三个双引号
```

小总结：

- 双引号或者单引号中的数据，就是字符串
- 如果使用一对引号来定义字符串，当出现符号冲突时可以使用转义字符
- 使用三个单引号、双引号定义的字符串可以包裹任意文本

### 转义字符

| 转义字符 |           含义           |
| :------: | :----------------------: |
|    \r    |  将当前位置移到本行开头  |
|    \n    | 将当前位置移到下一行开头 |
|    \t    |    用来表示一个制表符    |
|   `\\`   |  代表一个反斜线字符`\`   |
|   \\'    |    用来显示一个单引号    |
|   \\"    |    用来显示一个双引号    |

### 切片

切片是指对操作的对象截取其中一部分的操作。**字符串、列表、元组**都支持切片操作。

**切片的语法：[起始:结束:步长]，也可以简化使用 [起始:结束]**

**注意：选取的区间从"起始"位开始，到"结束"位的前一位结束（不包含结束位本身)，步长表示选取间隔。**

```python
# 索引是通过下标取某一个元素
# 切片是通过下标去某一段元素
# 结束位不打印
s = 'Hello World!'
print(s)

print(s[4])  # o 字符串里的第5个元素

print(s[3:7])  # lo W 包含下标 3，不含下标 7

print(s[:]) # Hello World! 取出所有元素（没有起始位和结束位之分），默认步长为1

print(s[1:]) # ello World! 从下标为1开始，取出 后面所有的元素（没有结束位）

print(s[:4])  # Hell 从起始位置开始，取到 下标为4的前一个元素（不包括结束位本身）

print(s[:-1]) # Hello World 从起始位置开始，取到 倒数第一个元素（不包括结束位本身）  相当于最后一个字符是-1，依次向前递减

print(s[-4:-1]) # rld 从倒数第4个元素开始，取到 倒数第1个元素（不包括结束位本身）

print(s[1:5:2]) # el 从下标为1开始，取到下标为5的前一个元素，步长为2（不包括结束位本身）

print(s[7:2:-1]) # ow ol 从下标为7的元素开始(包含下标为7的元素)，倒着取到下标为2的元素(不包括下标为2的元素) 

# python 字符串快速逆置
print(s[::-1])  # !dlroW olleH 从后向前，按步长为1进行取值
```

### 字符串常见操作

字符串的常见操作包括：

- **获取长度**:len
- **查找内容**:find,index,rfind,rindex
- **判断**:startswith,endswith,isalpha,isdigit,isalnum,isspace
- **计算出现次数**:count
- **替换内容**:replace
- **切割字符串**:split,rsplit,splitlines,partition,rpartition
- **修改大小写**:capitalize,title,upper,lower
- **空格处理**:ljust,rjust,center,lstrip,rstrip,strip
- **字符串拼接**:join

#### 长度

len函数可以获取字符串的长度。

```python
mystr = '今天天气好晴朗，处处好风光呀好风光'
print(len(mystr))  # 17 获取字符串的长度
```

#### 查找

**1.find**

查找指定内容在字符串中是否存在，如果存在就返回该内容在字符串中第一次出现的开始位置索引值，如果不存在，则返回-1.

语法格式：

```python
S.find(sub[, start[, end]]) -> int
```

示例：

```python
mystr = '今天天气好晴朗，处处好风光呀好风光'
print(mystr.find('好风光'))  # 10 '好风光'第一次出现时，'好'所在的位置
print(mystr.find('你好'))  # -1  '你好'不存在，返回 -1
print(mystr.find('风', 12))  # 15 从下标12开始查找'风',找到风所在的位置是15
print(mystr.find('风光',1,12)) # -1 从下标1开始到12查找"风光",未找到，返回 -1
```

**2.rfind**

类似于 find()函数，不过是从右边开始查找。

```python
mystr = '今天天气好晴朗，处处好风光呀好风光'
print(mystr.rfind('好')) # 14
```

**3.index**

跟find()方法一样，只不过，find方法未找到时，返回-1,而str未找到时，会报一个异常。

语法格式：

```python
S.index(sub[, start[, end]]) -> int
```

**4.rindex**

类似于 index()，不过是从右边开始。

#### 判断

**1. startswith**

判断字符串是否以指定内容开始。 语法格式:

```python
S.startswith(prefix[, start[, end]]) -> bool
```

示例：

```python
mystr = '今天天气好晴朗，处处好风光呀好风光'
print(mystr.startswith('今'))  # True
print(mystr.startswith('今日')) # False
```

**2. endswith**

判断字符串是否以指定内容结束。

```python
mystr = '今天天气好晴朗，处处好风光呀好风光'
print(mystr.endswith('好风光')) #True
print(mystr.endswith('好日子')) #False
```

**3. isalpha**

判断字符串是否是纯字母。

```python
mystr = 'hello'
print(mystr.isalpha())  # True
mystr = 'hello world'
print(mystr.isalpha()) # False 因为中间有空格
```

**4. isdigit**

判断一个字符串是否是纯数字，只要出现非0~9的数字，结果就是False.

```python
mystr = '1234'
print(mystr.isdigit()) # True
mystr = '123.4'
print(mystr.isdigit()) # False
mystr = '-1234'
print(mystr.isdigit()) # False
```

**5. isalnum**

判断是否由数字和字母组成。只要出现了非数字和字母，就返回False.

```python
mystr = 'abcd'
print(mystr.isalnum())  # True
mystr = '1234'
print(mystr.isalnum()) # True
mystr = 'abcd1234'
print(mystr.isalnum()) # True
mystr = 'abcd1234_'
print(mystr.isalnum()) # False
```

**6. isspace**

如果 mystr 中只包含空格，则返回 True，否则返回 False.

```python
mystr = ''
print(mystr.isspace()) # False mystr是一个空字符串
mystr = '  '
print(mystr.isspace()) # True 只有空格
mystr = ' d'
print(mystr.isspace()) # False 除了空格外还有其他内容
```

#### 次数

返回 str在start和end之间 在 mystr里面出现的次数。

语法格式:

```python
S.count(sub[, start[, end]]) -> int
```

示例：

```python
mystr = '今天天气好晴朗，处处好风光呀好风光'
print(mystr.count('好'))  # 3. '好'字出现三次
```

#### 替换

**replace**

必须要用一个新的字符串去接，使用原字符串不行

替换字符串中指定的内容，如果指定次数count，则替换不会超过count次。

```python
mystr = '今天天气好晴朗，处处好风光呀好风光'
newstr = mystr.replace('好', '坏')
print(mystr)  # 今天天气好晴朗，处处好风光呀好风光  原字符串未改变！
print(newstr)  # 今天天气坏晴朗，处处坏风光呀坏风光 得到的新字符串里，'好'被修改成了'坏'

newstr = mystr.replace('好','坏',2)  # 指定了替换的次数
print(newstr) # 今天天气坏晴朗，处处坏风光呀好风光 只有两处的'好'被替换成了'坏'
```





#### 内容分隔

**1.split**

以指定字符串为分隔符切片，如果 maxsplit有指定值，则仅分隔 maxsplit+1 个子字符串。**返回的结果是一个列表。**

```python
mystr = '今天天气好晴朗，处处好风光呀好风光'
result = mystr.split() # 没有指定分隔符，默认使用空格，换行等空白字符进行分隔
print(result) #['今天天气好晴朗，处处好风光呀好风光'] 没有空白字符，所以，字符串未被分隔

result = mystr.split('好')  # 以 '好' 为分隔符
print(result) # ['今天天气', '晴朗，处处','风光呀,'风光']

result = mystr.split("好",2) # 以 '好' 为分隔符，最多切割成3份
print(result) # ['今天天气', '晴朗，处处', '风光呀好风光']
```

**2.rsplit**

用法和split基本一致，只不过是从右往左分隔。

```python
mystr = '今天天气好晴朗，处处好风光呀好风光'
print(mystr.rsplit('好',1))  #['今天天气好晴朗，处处好风光呀', '风光']
```

**3.splitlines**

按照行分隔，返回一个包含各行作为元素的列表。

```python
mystr = 'hello \nworld'
print(mystr.splitlines())
```

**4.partition**

把mystr以str分割成三部分,str前，str和str后，三部分组成一个元组

```python
mystr = '今天天气好晴朗，处处好风光呀好风光'
print(mystr.partition('好'))  # ('今天天气', '好', '晴朗，处处好风光呀好风光')
```

**5.rpartition**

类似于 partition()函数,不过是从右边开始.

```python
mystr = '今天天气好晴朗，处处好风光呀好风光'
print(mystr.rpartition('好'))   # ('今天天气好晴朗，处处好风光呀', '好', '风光')
```

#### 修改大小写

修改大小写的功能只对英文有效，主要包括，首字母大写capitalize,每个单词的首字母大写title,全小写lower,全大写upper.

**1.capitalize**

第一个单词的首字母大写。

```python
mystr = 'hello world'
print(mystr.capitalize()) # Hello world
```

如果第一个不是字母的话，那么就会保持原样

**2.title**

每个单词的首字母大写。

如果第一个不是字母的话，那么就会找到第一个字母让它大写

```python
mystr = 'hello world'
print(mystr.title()) # Hello World
```

**3.lower**

所有都变成小写。

```python
mystr = 'hElLo WorLD'
print(mystr.lower()) # hello world
```

**4.upper**

所有都变成大写。

```python
mystr = 'hello world'
print(mystr.upper())  #HELLO WORLD
```

#### 空格处理

**1. ljust**

返回指定长度的字符串，并在右侧使用空白字符补全(左对齐)。

```python
str = 'hello'
print(str.ljust(10))  # hello     在右边补了五个空格
```

**2. rjust**

返回指定长度的字符串，并在左侧使用空白字符补全(右对齐)。

```python
str = 'hello'
print(str.rjust(10))  #      hello在左边补了五个空格
```

**3. center**

返回指定长度的字符串，并在两端使用空白字符补全(居中对齐)

```python
str = 'hello'
print(str.center(10))  #  hello   两端加空格，让内容居中
```

**4. lstrip**

删除 mystr 左边的空白字符。

```python
mystr = '    he   llo      '
print(str.lstrip())  #he   llo      只去掉了左边的空格，中间和右边的空格被保留
```

**5. rstrip**

删除 mystr 右边的空白字符。

```python
mystr = '    he   llo      '
print(str.rstrip())  #    he   llo右边的空格被删除
```

**6. strip**

删除两边的空白字符。

```python
str = '    he   llo      '
print(str.strip())  #he   llo
```

#### 字符串拼接

**join**

把参数进行遍历，取出参数里的每一项，然后再在后面加上mystr

语法格式:

```python
S.join(iterable)
```

示例:

```python
mystr = 'a'
print(mystr.join('hxmdq'))  #haxamadaq  把hxmd一个个取出，并在后面添加字符a. 最后的 q 保留，没有加 a
print(mystr.join(['hi','hello','good']))  #hiahelloagood
```

作用：可以把列表或者元组快速的转变成为字符串，并且以指定的字符分隔。

```python
txt = '_'
print(txt.join(['hi','hello','good'])) #hi_hello_good
print(txt.join(('good','hi','hello'))) #good_hi_hello
```



```py
s1 = 'abcdefg'
new = ''.join(s1.split(c))
print(new)
#	abdefg
```

可以快速删除字符串中的元素

#### 字符串运算符

1. 字符串和字符串之间能够使用加法运算符，作用是将两个字符串拼接成为一个字符串。例如:`'hello' + 'world'`的结果是 `'helloworld'`
2. 字符串和数字之间可以做乘法运算，结果是将指定的字符串重复多次。例如:`'hello'*2`的结果是`hellohello`
3. 字符串和字符串之间，如果使用比较运算符进行计算，会获取字符对应的编码，然后进行比较。
4. 除上述几种运算符以外，字符串默认不支持其他运算符。

### 字符与编码相互转换

使用chr和ord方法，可以实现字符和编码之间的相互转换。

```python
print(ord('a'))  # 使用ord方法，可以获取一个字符对应的编码
print(chr(100))  # 使用chr方法，可以获取一个编码对应的字符
```

## 成员运算符

成员运算符 (in 和 not in) 可以用来快速的判断元素是否在指定的可迭代对象里，语法格式 `要判断的元素 in 可迭代对象`。

**1.in**

```python
msg = 'hello'
char = input('请输入一个字符:')

# 使用字符串的 find 方法可以判断字符是否存在
if msg.find(char) != -1:
    print('您输入的字符存在')
else:
    print('您输入的字符不存在')

# 使用 in 运算符可以更加方便的查看字符是否存在
if char in msg:
    print('您输入的字符存在')
else:
    print('您输入的字符不存在')
```

**2.not in**

和 in 运算符的使用方式一致，只不过 not in 用来判断元素是否 不在 指定的字符串里。

**注意**

不是所有的数据都能使用身份运算符，身份运算符后面只能是一个可迭代对象。

```python
'h' in 'hello'  
'zhangsan' in ['lisi','henry','merry','jack']

1 in 123 # 报错，数字 123 不是一个可迭代对象
```

## 列表

**1.格式**

定义列的格式：`[元素1, 元素2, 元素3, ..., 元素n]`

变量tmp的类型为列表

```python
tmp = ['xiaoWang',180, 65.0]
```

**2.通过下标访问**

```python
namesList = ['xiaoWang','xiaoZhang','xiaoHua']
print(namesList[0])
print(namesList[1])
print(namesList[2])
```

结果：

```python
xiaoWang
xiaoZhang
xiaoHua
```

### 列表的增删改查

#### 添加元素

添加元素有一下几个方法:

- append 在末尾添加元素
- insert 在指定位置插入元素
- extend 合并两个列表

**1.append**

append会把新元素添加到列表末尾

```python
    #定义变量A，默认有3个元素
    A = ['xiaoWang','xiaoZhang','xiaoHua']

    print("-----添加之前，列表A的数据-----A=%s" % A)

    #提示、并添加元素
    temp = input('请输入要添加的学生姓名:')
    A.append(temp)

    print("-----添加之后，列表A的数据-----A=%s" % A)
```

**2.insert**

insert(index, object) 在指定位置index前插入元素object

```python
strs = ['a','b','m','s']
strs.insert(3,'h')
print(strs)  # ['a', 'b', 'm', 'h', 's']
```

**3.extend**

通过extend可以将另一个集合中的元素逐一添加到列表中

```python
a = ['a','b','c']
b = ['d','e','f']
a.extend(b)
print(a)  # ['a', 'b', 'c', 'd', 'e', 'f'] 将 b 添加到 a 里
print(b) # ['d','e','f'] b的内容不变
```

#### 修改元素

使用下标访问列表的元素再对其重新赋值即可。

#### 查找元素

**1.in/not in**

见成员运算符

**2.index ，count**

见字符串操作

#### 删除元素

列表元素的常用删除方法有：

- del：根据下标进行删除
- pop：删除最后一个元素
- remove：根据元素的值进行删除

**1.del**

```python
movieName = ['加勒比海盗','骇客帝国','第一滴血','指环王','霍比特人','速度与激情']
print('------删除之前------movieName=%s' % movieName)
del movieName[2]
print('------删除之后------movieName=%s' % movieName)
```

**2.pop**

```python
movieName = ['加勒比海盗','骇客帝国','第一滴血','指环王','霍比特人','速度与激情']
print('------删除之前------movieName=%s' % movieName)
movieName.pop()
print('------删除之后------movieName=%s' % movieName)
```

**3.remove**

```python
movieName = ['加勒比海盗','骇客帝国','第一滴血','指环王','霍比特人','速度与激情']
print('------删除之前------movieName=%s' % movieName)
movieName.remove('指环王')
print('------删除之后------movieName=%s' % movieName)
```

#### 列表排序

**sort    reverse**

sort方法是将list按特定顺序重新排列，默认为由小到大，参数reverse=True可改为倒序，由大到小。

reverse方法是将list逆置。

```python
>>> a = [1, 4, 2, 3]
>>> a
[1, 4, 2, 3]
>>> a.reverse()  # 逆置，不排序
>>> a
[3, 2, 4, 1]
>>> a.sort()  # 默认从小到大排序
>>> a
[1, 2, 3, 4]
>>> a.sort(reverse=True)  # 从大到小排序
>>> a
[4, 3, 2, 1]
```

### 遍历列表

```python
namesList = ['xiaoWang','xiaoZhang','xiaoHua']
length = len(namesList)  # 获取列表长度
i = 0
while i<length:
    print(namesList[i])
    i+=1
```

```python
namesList = ['xiaoWang','xiaoZhang','xiaoHua']
for name in namesList:
    print(name)
```

### 列表的复制

**copy**

使用列表的copy方法，可以直接将原来的列表进行复制，变成一个新的列表，这种复制方式是浅复制。

```python
nums1 = [1, 5, 8, 9, 10, 12]
nums2 = nums1.copy()  # 调用列表的copy方法，可以复制出一个新的列表

nums2[0] = 100

# 修改新列表里的数据，不会影响到原有列表里的数据
print(nums2)
print(nums1)
```

**copy的两种模块**

**浅拷贝**（即没有拷贝二维列表的值，而是拷贝了地址）

浅拷贝是对于一个对象的顶层拷贝，通俗的理解是：拷贝了引用，并没有拷贝内容。

```python
import copy

words1 = ['hello', 'good', ['yes', 'ok'], 'bad']

# 浅拷贝只会拷贝最外层的对象，里面的数据不会拷贝，而是直接指向
words2 = copy.copy(words1)

words2[0] = '你好'
words2[2][0] = 'no'

print(words1)  # ['hello', 'good', ['no', 'ok'], 'bad']
# wrods2 里的 yes 被修改成了 no
print(words2)  # ['你好', 'good', ['no', 'ok'], 'bad']
```

**深拷贝**

深拷贝是对于一个对象所有层次的递归拷贝。

```python
import copy

words1 = ['hello', 'good', ['yes', 'ok'], 'bad']

# 深拷贝会将对象里的所有数据都进行拷贝
words2 = copy.deepcopy(words1)

words2[0] = '你好'
words2[2][0] = 'no'

print(words1)  # ['hello', 'good', ['yes', 'ok'], 'bad']
print(words2)  # ['你好', 'good', ['no', 'ok'], 'bad']
```

### 列表的切片

列表和字符串一样，也支持切片，切片其实就是一种浅拷贝。

```python
words1 = ['hello', 'good', ['yes', 'ok'], 'bad']
words2 = words1[:]
words2[0] = '你好'
words2[2][0] = 'no'
print(words1)  # ['hello', 'good', ['no', 'ok'], 'bad']
print(words2) # ['你好', 'good', ['no', 'ok'], 'bad']
```

## 元组

Python的元组与列表类似，不同之处在于**元组的元素不能修改**。元组使用小括号，列表使用方括号。

```py
aTuple = ('et',77,99.9)
```



**访问元组的时候与访问列表的情况一致，用下标索引访问**



**元组中可以使用count和index**



### 定义只有一个元素的元组

**一定要在最后一个元素后加一个逗号**

```py
tutle = (1)
print(tutle)  #  1
print(type(tutle)) # int
right = (1,)
print(right) # (1,)
```

##### 元组内置函数

元组和列表一样，都有一些内置函数方便编程。例如：

- `len(tuple)`：计算元组中元素个数；
- `max(tuple)`：返回元组中元素的最大值；
- `min(tuple)`：返回元组中元素的最小值；
- `tuple(seq)`：将列表转换为元组。



## 字典

相当于C中的结构体

每个键对应一个值

定义字典的格式：**{键1:值1, 键2:值2, 键3:值3, ..., 键n:值n}**

```py
info = {'name':'班长', 'id':100, 'sex':'f', 'address':'地球亚洲中国上海'}
info['name']  # 字典使用键来获取对应的值
```

**如果要想对应多个值可以将值改为列表**

"infor" = [... , ...]

### 查看字典元素

除了使用key查找数据，还可以使用get来获取数据

```py
info = {'name':'班长','age':18}

print(info['age']) # 获取年龄
# print(info['sex']) # 获取不存在的key，会发生异常

print(info.get('sex')) # 获取不存在的key，获取到空的内容，不会出现异常
print(info.get('sex'， '男'))  # 获取不存在的key, 可以提供一个默认值。
```

注意，获取默认值不会修改字典内容

### 修改元素

字典的每个元素中的数据是可以修改的，只要通过key找到，即可修改

```py
info = {'name':'班长', 'id':100}

print('修改之前的字典为 %s:' % info)

info['id'] = 200  # 为已存在的键赋值就是修改

print('修改之后的字典为 %s:' % info)
```

### 添加元素

如果在使用 **变量名['键'] = 数据** 时，这个“键”在字典中，不存在，那么就会新增这个元素

```py
info = {'name':'班长'}

print('添加之前的字典为:%s' % info)

info['id'] = 100  # 为不存在的键赋值就是添加元素

print('添加之后的字典为:%s' % info)
"""
添加之前的字典为:{'name': '班长'}
添加之后的字典为:{'name': '班长', 'id': 100}
"""
```

### 删除元素（del ，clean）

**del删除指定的元素**

```py
info = {'name':'班长', 'id':100}

print('删除前,%s' % info)

del info['name']  # del 可以通过键删除字典里的指定元素

print('删除后,%s' % info)
"""
删除前,{'name': '班长', 'id': 100}
删除后,{'id': 100}
"""
```

**del删除整个字典**

```py
info = {'name':'monitor', 'id':100}

print('删除前,%s'%info)

del info  # del 也可以直接删除变量

print('删除后,%s'%info) #报错
```

**clear清空整个字典**

```py
info = {'name':'monitor', 'id':100}

print('清空前,%s'%info)

info.clear()

print('清空后,%s'%info)
"""
清空前,{'name': 'monitor', 'id': 100}
清空后,{}
"""
```

### 字典的遍历

**遍历字典的key（键）**

```py
dic = {'a': 4, 'b': 5}
for temp in dic.keys():
    print(temp)
```

**遍历字典的value值**

```py
dic = {'a': 4, 'b': 5}
for temp in dic.values():
    print(temp)
```

**遍历字典的项（元素）**

```py
dic = {'a': 4, 'b': 5}
for temp in dic.items():
    print(temp)
"""
('a', 4)
('b', 5)
"""
```

## 集合（set）

集合（set）是一个**无序的不重复元素**序列，可以使用大括号 **{ }** 或者 **set()** 函数创建集合。

**注意：创建一个空集合必须用 set() 而不是 { }，因为 { } 是用来创建一个空字典。**

```py
parame = {value01,value02,...}
或者
set(value)
```

### 集合添加元素

格式

```py
s.add(x)
```

将元素 x 添加到集合 s 中，如果元素已存在，则不进行任何操作

```py
dak = {"adkad", "dakdha"}
print(dak)
dak.add("adha")
print(dak)
"""
{'adkad', 'dakdha'}
{'adha', 'adkad', 'dakdha'}
"""
```

还有一个方法，也可以添加元素，且参数可以是列表，元组，字典等，语法格式如下：

```python
s.update( x )
```

x 可以有多个，用逗号分开。

```python
thisset = set(("Google", "Runoob", "Taobao"))
thisset.update({1,3})
print(thisset)
  # {1, 3, 'Google', 'Taobao', 'Runoob'}
thisset.update([1,4],[5,6])  
print(thisset)
  # {1, 3, 4, 5, 6, 'Google', 'Taobao', 'Runoob'}
```

### 集合移除元素

**1.remove**

语法格式如下：

```python
s.remove( x )
```

将元素 x 从集合 s 中移除，**如果元素不存在，则会发生错误**。

```python
thisset = set(("Google", "Runoob", "Taobao"))
thisset.remove("Taobao")
print(thisset)
  #   {'Google', 'Runoob'}
thisset.remove("Facebook")   # 不存在会发生错误
"""
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
KeyError: 'Facebook'
"""
```

此外还有一个方法也是移除集合中的元素，且**如果元素不存在，不会发生错误**。格式如下所示：

```python
   # s.discard( x )
thisset = set(("Google", "Runoob", "Taobao"))
thisset.discard("Facebook")  # 不存在不会发生错误
print(thisset)
 # {'Taobao', 'Google', 'Runoob'}
```

我们也可以设置随机删除集合中的一个元素，语法格式如下：

```python
# s.pop()
thisset = {"Google", "Runoob", "Taobao", "Facebook"}
x = thisset.pop()

print(x)
print(thisset)
"""
Taobao
{'Runoob', 'Facebook', 'Google'}
"""
```

### 集合常见方法

| 方法                          | 描述                                                         |
| ----------------------------- | ------------------------------------------------------------ |
| add()                         | 为集合添加元素                                               |
| clear()                       | 移除集合中的所有元素                                         |
| copy()                        | 拷贝一个集合                                                 |
| pop()                         | 随机移除元素                                                 |
| remove()                      | 移除指定元素                                                 |
| union                         | 返回两个集合的并集                                           |
| update()                      | 给集合添加元素                                               |
| difference()                  | 返回多个集合的差集                                           |
| difference_update()           | 移除集合中的元素，该元素在指定的集合也存在。                 |
| discard()                     | 删除集合中指定的元素                                         |
| intersection()                | 返回集合的交集                                               |
| intersection_update()         | 删除集合中的元素，该元素在指定的集合中不存在。               |
| isdisjoint()                  | 判断两个集合是否包含相同的元素，如果没有返回 True，否则返回 False。 |
| issubset()                    | 判断指定集合是否为该方法参数集合的子集。                     |
| issuperset()                  | 判断该方法的参数集合是否为指定集合的子集                     |
| symmetric_difference()        | 返回两个集合中不重复的元素集合。                             |
| symmetric_difference_update() | 移除当前集合中在另外一个指定集合相同的元素，并将另外一个指定集合中不同的元素插入到当前集合中。 |

## 执行字符串中的python代码

**使用Python内置的eval函数，可以执行字符串里的Python代码。使用这种方式，可以将字符串转换成为其他类型的数据**。

```python
x = '1+1'
print(eval(x))  # 2
print(type(eval(x)))  # <class 'int'>

y = '{"name":"zhangsan","age":18}'
print(eval(y))
print(type(eval(y)))  # <class 'dict'>

print(eval('1 > 2'))  # False

eval('input("请输入您的姓名:")')
```

## 字典，列表，元组转字符串

**使用json的dumps方法，可以将字典、列表或者元组转换成为字符串**。

```python
import json

person = {'name': 'zhangsan', 'age': 18}
x = json.dumps(person)
print(x)  # {"name": "zhangsan", "age": 18}
print(type(x))  # <class 'str'>

nums = [1, 9, 0, 4, 7]
y = json.dumps(nums)
print(y)  # [1, 9, 0, 4, 7]
print(type(y)) # <class 'str'>

words = ('hello','good','yes')
z = json.dumps(words)
print(z) # ["hello", "good", "yes"]
print(type(z)) # <class 'str'>
Copy
```

**使用json的loads方法，可以将格式正确的字符串转换成为字典、列表**

```python
x = '{"name": "zhangsan", "age": 18}'
person = json.loads(x)
print(person)  # {'name': 'zhangsan', 'age': 18}
print(type(person)) # <class 'dict'>

y = '[1, 9, 0, 4, 7]'
nums = json.loads(y)
print(nums) # [1, 9, 0, 4, 7]
print(type(nums)) # <class 'list'>
```

## 可迭代对象通用方法

**算数运算符**

在Python里，常见的算数运算符，有一些可以使用于可迭代对象，它们执行的结果也稍有区别。

| 运算符 | Python 表达式      | 结果                         | 描述           | 支持的数据类型           |
| :----- | ------------------ | ---------------------------- | -------------- | ------------------------ |
| +      | [1, 2] + [3, 4]    | [1, 2, 3, 4]                 | 合并           | 字符串、列表、元组       |
| -      | {1,2,3,4} - {2,3}  | {1,4}                        | 集合求差集     | 集合                     |
| *      | ['Hi!'] * 4        | ['Hi!', 'Hi!', 'Hi!', 'Hi!'] | 复制           | 字符串、列表、元组       |
| in     | 3 in (1, 2, 3)     | True                         | 元素是否存在   | 字符串、列表、元组、字典 |
| not in | 4 not in (1, 2, 3) | True                         | 元素是否不存在 | 字符串、列表、元组、字典 |

***号运算符**

```python
>>> 'ab' * 4
'ababab'
>>> [1, 2] * 4
[1, 2, 1, 2, 1, 2, 1, 2]
>>> ('a', 'b') * 4
('a', 'b', 'a', 'b', 'a', 'b', 'a', 'b')
```

**in**

in和not in成员运算符可以用于所有的可迭代对象。但是需要注意的是，in 和 not in 在对字典进行判断时，是查看指定的key是否存在，而不是value.

```python
>>> 'llo' in 'hello world'
True
>>> 3 in [1, 2]
False
>>> 4 in (1, 2, 3, 4)
True
>>> "name" in {"name":"chris", "age":18}
True
```

### 带下标的遍历

可迭代对象都可以使用 enumerate 内置类进行包装成一个 enumerate 对象。对enumerate进行遍历，可以同时得到一个可迭代对象的下标和元素。

```python
nums = [12, 9, 8, 5, 4, 7, 3, 6]

# 将列表 nums 包装成 enumerate 对象
for i, num in enumerate(nums): # i表示元素下标，num表示列表里的元素
    print('第%d个元素是%d' % (i, num))
```

## 函数

### 定义

定义函数的格式如下：

```python
def 函数名():
    代码
```

与C同理，可以在函数中增加变量

```python
def add2num(a, b):
    c = a+b
    print c

add2num(11, 22) # 调用带有参数的函数时，需要在小括号中，传递数据
```

### 函数文档注释

```py
def test(a, b):
    """这是一个文档注释"""  # 函数第一行写一个字符串作为函数文档
    return a + b


help(test)

"""
test(a, b)
    这是一个文档注释
"""
```

### 函数内修改全局变量

**使用global**

```py
number = 100


def test():
    global number
    print("first%d" % number)
    number += 10
    print("second%d" % number)


test()
print("third%d" % number)
"""
first100
second110
third110
"""
```

### 函数返回多个值

```python
def divid(a, b):
    shang = a//b
    yushu = a%b 
    return shang, yushu  #默认是元组

result = divid(5, 2)
print(result)  # 输出(2, 1)
```



- return后面可以是元组，列表、字典等，只要是能够存储多个数据的类型，就可以一次性返回多个数据。

  ```python
        def function():
            # return [1, 2, 3]
            # return (1, 2, 3)
            return {"num1": 1, "num2": 2, "num3": 3}
  Copy
  ```

- 如果return后面有多个数据，那么默认是元组。

### 拆包返回数据

```python
def get_my_info():
    high = 178
    weight = 100
    age = 18
    return high, weight, age  # 函数返回三个数据，会自动打包为元组

# result = get_my_info()  # result 接收到一个元组
# print(result)

my_high, my_weight, my_age = get_my_info()  # 直接把元组拆分为三个变量来使用，更加方便
print(my_high)
print(my_weight)
print(my_age)
```

**注意**

- 拆包时要注意，需要拆的数据的个数要与变量的个数相同，否则程序会异常
- 除了对元组拆包之外，还可以对列表、字典等拆包

```python
my_list = ["A", "B", 3]
# 利用拆包，使用三个变量分别保存列表中的每一个数据
value1, value2, value3 = my_list
print(value1, value2, value3)
#A B 3
 
my_dict = {"name": "吕布", "age": 30}
 
# 对字典直接进行拆包，获取的key
data1, data2 = my_dict
print(data1, data2)
#name age
 
data1, data2 = my_dict.values()
print(data1, data2)
#吕布 30
 
def return_value():
    return 1, 3
 
 
# 对函数的返回值进行拆包
value1, value2 = return_value()
print(value1, value2)
#1 3
```

### 函数传入参数说明

**缺省参数**

调用函数时，缺省参数的值如果没有传入，则取默认值。

下例会打印默认的age，如果age没有被传入：

```python
def printinfo(name, age=35):
   # 打印任何传入的字符串
   print("name: %s" % name)
   print("age %d" % age)

# 调用printinfo函数
printinfo(name="miki")  # 在函数执行过程中 age取默认值35
printinfo(age=9 ,name="miki")
"""
name: miki
age: 35
name: miki
age: 9
"""
```



- 在形参中默认有值的参数，称之为缺省参数
- 注意：带有默认值的参数一定要位于参数列表的最后面

**不定长参数**

有时可能需要一个函数能处理比当初声明时更多的参数, 这些参数叫做不定长参数，声明时不会命名。

基本语法如下：

```python
def functionname([formal_args,] *args, **kwargs):
   """函数_文档字符串"""
   function_suite
   return [expression]
Copy
```

**注意：**

- 加了星号（*）的变量args会存放所有未命名的变量参数，args为元组
- 而加**的变量kwargs会存放命名参数，即形如key=value的参数， kwargs为字典.

```python
def test(a, b, *args, **kwargs):
      "函数在声明时，需要两个参数"
    print('a={},b={},args={},kwargs={}'.format(a,b,args,kwargs))

test(2, 3, '你好', 'hi', 'how do you do', name="zhangsan", age=18)
# a=2,b=3,args=('你好', 'hi', 'how do you do'),kwargs={'name': 'zhangsan', 'age': 18}


b = ('hi', '大家好', '今天天气真好')
d = {'name': "zhangsan", "age": 19}

# 注意，在传入参数时的星号问题。
test(10, 20, *b, **d) 
# a=10,b=20,args=('hi', '大家好', '今天天气真好'),kwargs={'name': 'zhangsan', 'age': 19}


# 如果在传值时，不使用星号，会把后面的参数当做 args
test(10,20,b,d)
# a=10,b=20,args=(('hi', '大家好', '今天天气真好'), {'name': 'zhangsan', 'age': 19}),kwargs={}
```



**注意，**

**缺省参数在*args后面**

如果很多个值都是不定长参数，那么这种情况下，可以将缺省参数放到 *args的后面， 但如果有***kwargs的话，**kwargs必须是最后的

```python
def sum_nums_3(a, *args, b=22, c=33, **kwargs):
    print(a)
    print(b)
    print(c)
    print(args)
    print(kwargs)

"""
sum_nums_3(100, 200, 300, 400, 500, 600, 700, b=1, c=2, mm=800, nn=900)
100
1
2
(200, 300, 400, 500, 600, 700)
{'mm': 800, 'nn': 900}
"""
```

## 可变数据类型和不可变数据类型

- 所谓可变类型与不可变类型是指：数据能够直接进行修改，如果能直接修改那么就是可变，否则是不可变
- 可变类型(修改数据，内存地址不会发生变化)有： 列表、字典、集合
- 不可变类型(修改数据，内存地址必定发生变化)有： 数字、字符串、元组



## python自我小tip

**1.print不换行**

```python
print("内容" , end = '')
```

**2.在C语言中的取反！在python 中使用 not **

```python
if(not(number % 100)) ## python
```

```c
if(!(number % 100))  // C
```

**3.同时输入多个数字**

```py
a,b = map(int,input().split()) ##两个数字
a,b,c,d = map(int,input().split()) ##多个数字
```

```py
num = input().split(",")
for i in num:
    .....
"""
num为list，split中为输入的分割符
"""
```



**4.定义空列表**

```py
Arr = []
```

**5.if 和 else 后面都要加:**

```py
if():
    ...
else:
    ...
```

**6.python中的三元运算符**

```py
number = input()
num = int(number) if int(number) > 0 else -int(number)
print(num)
```

**7.python没有++运算符**

**8.while 不用使用括号**

**9.python中使用 / 两个整数会自动转为浮点数**

```py
number = 25
number /= 10          ## number = 2.5
```

```py
number = 25
number = int(number / 10)     ## number = 2
```

**10.input()输入转为int类型**

```python
num = int(input())
```

**11.取整，指数**

类似于c中的 a%b  ，python取整使用 // 

指数使用 **  

```py
a = 4 
b = 6
c = b // a   # c = 1
d = a ** 2   # d = 16
```

**12.    !=     ==     <>    (表示不等于）**

**13.string.find()与string.rfind()**

两个函数后面参数数字刻画了一段距离，find和rfind的区别在于对于这个区间从左边寻找还是从右边寻找

**14.多重赋值**

```py
rat, mouse, day, time = 1, 1, 0, 1
```



**15.控制输出**

```py
a = 1000
print("{:*>5}".format(a))
print("{:*<5}".format(a))
print("{:,}".format(a))
print("{:*<5,}".format(a))
print("{:*^5}".format(a))
print("{:b}".format(a))
print("{:*>5b}".format(a))
"""
*1000
1000*
1,000
1,000
1000*
1111101000
1111101000
"""
```

**16.进制输出**

```py
a = 452
print("{:e}".format(a)) # 科学计数法
print("{:o}".format(a)) # 八进制
print("{:c}".format(a)) # 数字的字符形式
print("{:x}".format(a)) # 十六进制
"""
4.520000e+02
704
Ǆ
1c4
"""
```

**17.保留小数**

```py
a = 3.1415926
print("{:.2f}".format(a))
print("{:*>5.2f}".format(a))
"""
3.14
*3.14
"""
```

**18从列表随机选择一个**

```py
import random
a = ["1", "2", "3"]
name = random.choice(a)
print(name)
```

