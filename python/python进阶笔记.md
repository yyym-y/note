# python进阶笔记

## 函数进阶

### lambda 匿名函数

用lambda关键词能创建小型匿名函数。这种函数得名于省略了用def声明函数的标准步骤。

lambda函数的语法**只包含一个语句**，如下：

```python
lambda 参数列表: 运算表达式
```

如下实例：

```python
sum = lambda arg1, arg2: arg1 + arg2

# 调用sum函数
print("Value of total : %d" % sum( 10, 20 ))
print("Value of total : %d" % sum( 20, 20 ))
"""
30
40
"""
```



Lambda函数能接收任何数量的参数但只能返回一个表达式的值

匿名函数可以执行任意表达式(甚至print函数)，但是一般认为表达式应该有一个计算结果供返回使用。



Python中使用函数作为参数的内置函数和类:

| 函数名或类名 | 功能                                                         | 参数描述                                       |
| ------------ | ------------------------------------------------------------ | ---------------------------------------------- |
| sorted函数   | 用来将一个无序列表进行排序                                   | 函数参数的返回值规定按照元素的哪个属性进行排序 |
| filter类     | 用来过滤一个列表里符合规定的所有元素，得到的结果是一个迭代器 | 函数参数的返回值指定元素满足的过滤条件         |
| map类        | 将列表里的每一项数据都执行相同的操作，得到的结果是一个迭代器 | 函数参数用来指定列表里元素所执行的操作         |
| reduce函数   | 对一个序列进行压缩运算，得到一个值。python3以后，这个方法被移到了functools模块 | 函数参数用来指定元素按照哪种方式合并           |



### 高阶函数

在Python中，函数其实也是一种数据类型。

函数对应的数据类型是 `function`,可以把它当做是一种复杂的数据类型。

既然同样都是一种数据类型，我们就可以把它当做数字或者字符串来处理。

**定义一个变量来给函数取别名**

```python
def test():
    return 'hello wrold'

fun = test   # 定义了一个变量fun,让它指向了 test 这个函数
print(fun())   # 使用fun()可以直接调用test这个函数

print(id(fun))  # 1819677672040
print(id(test))  # 1819677672040
```

> 注意：在定义一个变量表示一个函数时，函数后面不能加括号！加括号表示的是调用这个函数。

```python
def test():
    return 'hello world'

result = test()   # 这种写法是调用test函数，并把函数的返回值赋值给result变量
print(result())   # 这里会报错  TypeError: 'str' object is not callable

fun = test   # 这种写法是给test函数起了一个别名，注意，这里的test后面不能加()
fun()        # 可以使用别名调用这个函数
```



既然变量可以指向函数，函数的参数能接收变量，那么一个函数就可以接收另一个函数作为参数，同样，我们还可以把一个函数当做另一个函数的返回值。这种函数的使用方式我们称之为高阶函数。

**函数做为另一个函数的参数**

```python
def test(age,action):
    if age < 18:
        print('您还没满十八岁，请退出')
    action()   # 把参数action直接当做一个函数来调用

def smoke():
    print('我已经年满十八岁了，我想抽烟')

my_action = smoke  # 定义一个变量my_action，让它指向smoke函数
test(21, my_action)  # 将my_action传给 test 函数作为它的参数

test(21,smoke)  # 还可以不再定义一个新的变量，直接传入函数名
```

**函数作为另一个函数的返回值**

```python
def test():
    print('我是test函数里输入的内容')

def demo():
    print('我是demo里输入的内容')
    return test  # test 函数作为demo函数的返回值

result = demo()  # 我是demo里输入的内容  调用 demo 函数，把demo函数的返回值赋值给 result
print(type(result)) # <class 'function'>  result 的类型是一个函数

result() # 我是demo里输入的内容    我是test函数里输入的内容   既然result是一个函数，那么就可以直接使用() 调用这个函数

demo()()  # 我是demo里输入的内容    我是test函数里输入的内容
```

### 闭包

函数只是一段可执行代码，编译后就“固化”了，每个函数在内存中只有一份实例，得到函数的入口点便可以执行函数了。函数还可以嵌套定义，即在一个函数内部可以定义另一个函数，有了嵌套函数这种结构，便会产生闭包问题。

**函数嵌套**

在函数里面还可以定义函数，可以嵌套多层，执行需要被调用。

```python
def outer():
    print('outer----hello')
    def inner():  # inner这个函数是在outer函数内部定义的
        print('inner----hello')
    inner()  # inner函数只在outer函数内部可见

outer()
# inner()  这里会报错，在outer函数外部无法访问到inner函数
```

**什么是闭包**

闭包是由函数及其相关的引用环境组合而成的实体(即：**闭包=函数块+引用环境**)。

```python
def outer(n):
    num = n
    def inner():
        return num+1
    return inner

print(outer(3)())  # 4
print(outer(5)())  # 5
```

在这段程序中，函数 inner 是函数 outer 的内嵌函数，并且 inner 函数是outer函数的返回值。当我们调用分别由不同的参数调用 outer 函数得到的函数时，得到的结果是隔离的(相互不影响)，也就是说每次调用outer函数后都将生成并保存一个新的局部变量num,这里outer函数返回的就是闭包。 **如果在一个内部函数里，对在外部作用域（但不是在全局作用域）的变量进行引用，那么内部函数就被认为是闭包(closure).**



**闭包里默认不能修改外部变量。**

```python
def outer(n):
    num = n
    def inner():
        num = num + 1
        return num
    return inner

print(outer(1)())
```

上述代码运行时会报错！

在python里，只要看到了赋值语句，就会认为赋值语句的左边是一个局部变量。`num = num + 1` 这段代码里，`num` 在`=`的左边，python解析器会认为我们要修改`inner`函数里`num`这个局部变量，而这个变量使用之前是未声明的，所以会报错。



报错的原因在于当我们在闭包内修改外部变量时，会被python解析器误会为内部函数的局部变量。所以，解决方案就在于，我们需要想办法，让解析器知道我们不是要修改局部变量，而是要修改外部变量。

- 解决方法：使用 nonlocal 关键字

```python
def outer(n):
    num = n
    def inner():
        nonlocal num  # 修改前使用nonlocal关键字对 num 变量进行说明
        num = num + 1
        return num
    return inner

print(outer(2)())
```



## 模块

模块就好比是工具包，要想使用这个工具包中的工具(就好比函数)，就需要导入这个模块

### 导入模块

- import 模块名
- from 模块名 import 功能名
- from 模块名 import *
- import 模块名 as 别名
- from 模块名 import 功能名 as 别名



#### **import**

在Python中用关键字`import`来引入某个模块，比如要引入系统模块 math，就可以在文件最开始的地方用`import math`来引入。

语法:

```python
import 模块1,模块2,...  # 导入方式

模块名.函数名()  # 使用模块里的函数
```



#### **from…import**

有时候我们只需要用到模块中的某个函数，只需要引入该函数即可，此时可以用下面方法实现：

```python
from 模块名 import 函数名1,函数名2....
```

不仅可以引入函数，还可以引入一些全局变量、类等

- 注意:

  > 通过这种方式引入的时候，调用函数时只能给出函数名，不能给出模块名，但是当两个模块中含有相同名称函数的时候，后面一次引入会覆盖前一次引入。也就是说假如模块A中有函数function( )，在模块B中也有函数function( )，如果引入A中的function在先、B中的function在后，那么当调用function函数的时候，是去执行模块B中的function函数。

例如，要导入模块fib的fibonacci函数，使用如下语句：

```python
from fib import fibonacci
```

**注意**

- 不会把整个fib模块导入到当前的命名空间中，它只会将fib里的fibonacci单个函数引入

  



#### **from … import***

把一个模块的所有内容全都导入到当前的命名空间也是可行的，只需使用如下声明：

```python
from modname import *
```

**注意**

- 这提供了一个简单的方法来导入一个模块中的所有项目。然而这种声明不该被过多地使用。





#### **as 别名**

```python
In [1]: import time as tt  # 导入模块时设置别名为 tt

In [2]: time.sleep(1)
---------------------------------------------------------------------------
NameError                                 Traceback (most recent call last)
<ipython-input-2-07a34f5b1e42> in <module>()
----> 1 time.sleep(1)

NameError: name 'time' is not defined

In [3]: 

In [3]: tt.sleep(1)  # 使用别名才能调用方法

In [4]: 

In [4]: from time import sleep as sp  # 导入方法时设置别名

In [5]: sleep(1)
---------------------------------------------------------------------------
NameError                                 Traceback (most recent call last)
<ipython-input-5-82e5c2913b44> in <module>()
----> 1 sleep(1)

NameError: name 'sleep' is not defined

In [6]: 

In [6]: sp(1)  # 使用别名才能调用方法

In [7]:
```



### 系统常见模块

#### OS模块

OS全称OperationSystem,即操作系统模块，这个模块可以用来操作系统的功能，并且实现跨平台操作。

```python
import os
os.getcwd()  # 获取当前的工作目录，即当前python脚本工作的目录
os.chdir('test') # 改变当前脚本工作目录，相当于shell下的cd命令
os.rename('毕业论文.txt','毕业论文-最终版.txt') # 文件重命名
os.remove('毕业论文.txt') # 删除文件
os.rmdir('demo')  # 删除空文件夹
os.removedirs('demo') # 删除空文件夹
os.mkdir('demo')  # 创建一个文件夹
os.chdir('C:\\') # 切换工作目录
os.listdir('C:\\') # 列出指定目录里的所有文件和文件夹
os.name # nt->widonws posix->Linux/Unix或者MacOS
os.environ # 获取到环境配置
os.environ.get('PATH') # 获取指定的环境配置

os.path.abspath(path) # 获取Path规范会的绝对路径
os.path.exists(path)  # 如果Path存在，则返回True
os.path.isdir(path)  # 如果path是一个存在的目录，返回True。否则返回False
os.path.isfile(path) # 如果path是一个存在的文件，返回True。否则返回False
os.path.splitext(path)  # 用来将指定路径进行分隔，可以获取到文件的后缀名
os.walk #遍历文件夹
```



#### sys模块

该模块提供对解释器使用或维护的一些变量的访问，以及与解释器强烈交互的函数。

```python
import sys
sys.path # 模块的查找路径
sys.argv # 传递给Python脚本的命令行参数列表
sys.exit(code) # 让程序以指定的退出码结束

sys.stdin # 标准输入。可以通过它来获取用户的输入
sys.stdout # 标准输出。可以通过修改它来百变默认输出
sys.stderr # 错误输出。可以通过修改它来改变错误删除
```



#### math模块

math模块保存了数学计算相关的方法，可以很方便的实现数学运算。

```python
import math
print(math.fabs(-100)) # 取绝对值
print(math.ceil(34.01))  #向上取整
print(math.factorial(5)) # 计算阶乘
print(math.floor(34.98))  # 向下取整
print(math.pi)   # π的值，约等于 3.141592653589793
print(math.pow(2, 10)) # 2的10次方
print(math.sin(math.pi / 6))  # 正弦值
print(math.cos(math.pi / 3))  # 余弦值
print(math.tan(math.pi / 2))  # 正切值
```



#### random模块

random 模块主要用于生成随机数或者从一个列表里随机获取数据。

```python
print(random.random())  # 生成 [0,1)的随机浮点数
print(random.uniform(20, 30))  # 生成[20,30]的随机浮点数
print(random.randint(10, 30))  # 生成[10,30]的随机整数
print(random.randrange(20, 30))  # 生成[20,30)的随机整数
print(random.choice('abcdefg'))  # 从列表里随机取出一个元素
print(random.sample('abcdefghij', 3)) # 从列表里随机取出指定个数的元素
```



#### datetime模块

datetime模块主要用来显示日期时间，这里主要涉及 `date`类，用来显示日期；`time`类，用来显示时间；`dateteime`类，用来显示日期时间;`timedelta`类用来计算时间。

```python
import datetime
print(datetime.date(2020, 1, 1))  # 创建一个日期
print(datetime.time(18, 23, 45)) # 创建一个时间
print(datetime.datetime.now())  # 获取当前的日期时间
print(datetime.datetime.now() + datetime.timedelta(3))  # 计算三天以后的日期时间
```



#### time模块

除了使用datetime模块里的time类以外，Python还单独提供了另一个time模块，用来操作时间。time模块不仅可以用来显示时间，还可以控制程序，让程序暂停(使用sleep函数)

```python
print(time.time())  # 获取从1970-01-01 00:00:00 UTC 到现在时间的秒数
print(time.strftime("%Y-%m-%d %H:%M:%S")) # 按照指定格式输出时间
print(time.asctime()) #Mon Apr 15 20:03:23 2019
print(time.ctime()) # Mon Apr 15 20:03:23 2019

print('hello')
print(time.sleep(10)) # 让线程暂停10秒钟
print('world')
```



```py
import time
print(time.time()) # 返回时间戳
print(time.ctime())
print(time.localtime())
print(list(time.localtime())) # year, month, day, hour, minte, second,
time.sleep(3) //3s后执行下一条
print("-----------")
"""
1669801629.8112
Wed Nov 30 17:47:09 2022
time.struct_time(tm_year=2022, tm_mon=11, tm_mday=30, tm_hour=17, tm_min=47, tm_sec=9, tm_wday=2, tm_yday=334, tm_isdst=0)
[2022, 11, 30, 17, 47, 9, 2, 334, 0]
-----------
"""
```







#### calendar模块

calendar模块用来显示一个日历，使用的不多，了解即可。

```python
calendar.setfirstweekday(calendar.SUNDAY) # 设置每周起始日期码。周一到周日分别对应 0 ~ 6
calendar.firstweekday()# 返回当前每周起始日期的设置。默认情况下，首次载入calendar模块时返回0，即星期一。
c = calendar.calendar(2019)  # 生成2019年的日历，并且以周日为其实日期码
print(c)  #打印2019年日历
print(calendar.isleap(2000)) # True.闰年返回True,否则返回False
count = calendar.leapdays(1996,2010) # 获取1996年到2010年一共有多少个闰年
print(calendar.month(2019, 3))  # 打印2019年3月的日历
```





#### hashlib模块

hashlib是一个提供字符加密功能的模块，包含MD5和SHA的加密算法，具体支持md5,sha1, sha224, sha256, sha384, sha512等算法。 该模块在用户登录认证方面应用广泛，对文本加密也很常见。

```python
import hashlib

# 待加密信息
str = '这是一个测试'

# 创建md5对象
hl = hashlib.md5('hello'.encode(encoding='utf8'))
print('MD5加密后为 ：' + hl.hexdigest())

h1 = hashlib.sha1('123456'.encode())
print(h1.hexdigest())
h2 = hashlib.sha224('123456'.encode())
print(h2.hexdigest())
h3 = hashlib.sha256('123456'.encode())
print(h3.hexdigest())
h4 = hashlib.sha384('123456'.encode())
print(h4.hexdigest())
```





#### hmac模块

HMAC算法也是一种一种单项加密算法，并且它是基于上面各种哈希算法/散列算法的，只是它可以在运算过程中使用一个密钥来增增强安全性。hmac模块实现了HAMC算法，提供了相应的函数和方法，且与hashlib提供的api基本一致。

```python
h = hmac.new('h'.encode(),'你好'.encode())
result = h.hexdigest()
print(result)  # 获取加密后的结果
```





#### copy模块

copy模块里有copy和deepcopy两个函数，分别用来对数据进行深复制和浅复制。

```python
import copy

nums = [1, 5, 3, 8, [100, 200, 300, 400], 6, 7]
nums1 = copy.copy(nums)  # 对nums列表进行浅复制
nums2 = copy.deepcopy(nums)  # 对nums列表进行深复制
```



#### uuid模块

UUID是128位的全局唯一标识符，通常由32字节的字母串表示，它可以保证时间和空间的唯一性，也称为GUID。通过MAC地址、时间戳、命名空间、随机数、伪随机数来保证生产的ID的唯一性。随机生成字符串，可以当成token使用，当成用户账号使用，当成订单号使用。

| 方法                       | 作用                                                         |
| -------------------------- | ------------------------------------------------------------ |
| uuid.uuid1()               | 基于MAC地址，时间戳，随机数来生成唯一的uuid，可以保证全球范围内的唯一性。 |
| uuid.uuid2()               | 算法与uuid1相同，不同的是把时间戳的前4位置换为POSIX的UID。不过需要注意的是python中没有基于DCE的算法，所以python的uuid模块中没有uuid2这个方法。 |
| uuid.uuid3(namespace,name) | 通过计算一个命名空间和名字的md5散列值来给出一个uuid，所以可以保证命名空间中的不同名字具有不同的uuid，但是相同的名字就是相同的uuid了。namespace并不是一个自己手动指定的字符串或其他量，而是在uuid模块中本身给出的一些值。比如uuid.NAMESPACE_DNS，uuid.NAMESPACE_OID，uuid.NAMESPACE_OID这些值。这些值本身也是UUID对象，根据一定的规则计算得出。 |
| uuid.uuid4()               | 通过伪随机数得到uuid，是有一定概率重复的                     |
| uuid.uuid5(namespace,name) | 和uuid3基本相同，只不过采用的散列算法是sha1                  |

一般而言，在对uuid的需求不是很复杂的时候，uuid1或者uuid4方法就已经够用了，使用方法如下：

```python
import uuid

print(uuid.uuid1())  # 根据时间戳和机器码生成uuid,可以保证全球唯一
print(uuid.uuid4())  # 随机生成uuid,可能会有重复

# 使用命名空间和字符串生成uuid.
# 注意一下两点:
# 1. 命名空间不是随意输入的字符串，它也是一个uuid类型的数据
# 2. 相同的命名空间和想到的字符串，生成的uuid是一样的
print(uuid.uuid3(uuid.NAMESPACE_DNS, 'hello'))
print(uuid.uuid5(uuid.NAMESPACE_OID, 'hello'))
```



### PIP模块和包

在安装Python时，同时还会安装pip软件，它是Python的包管理工具，可以用来查找、下载、安装和卸载Python的第三方资源包。

对第三方包的管理主要包含查找、安装和卸载三个部分的操作。

**安装**

使用 `pip install <包名>`命令可以安装指定的第三方资源包。

```shell
pip install ipython # 安装ipython包
```

使用 install 命令下载第三方资源包时，默认是从 pythonhosted下载，由于各种原因，在国内下载速度相对来说比较慢，在某些时候甚至会出现连接超时的情况，我们可以使用国内镜像来提高下载速度。

**临时修改**

如果只是想临时修改某个第三方资源包的下载地址，在第三方包名后面添加 -i 参数，再指定下载路径即可，格式为`pip install <包名> -i <国内镜像路径>`

```shell
pip install ipython -i https://pypi.douban.com/simple
```

**永久修改**

除了临时修改pip的下载源以外，我们还能永久改变pip的默认下载路径。

在当前用户目录下创建一个pip的文件夹，然后再在文件夹里创建pip.ini文件并输入一下内容:

```shell
[global]
index-url=https://pypi.douban.com/simple
[install]
trusted-host=pypi.douban.com
```

**常见国内镜像**

- 阿里云 https://mirrors.aliyun.com/pypi/simple/
- 中国科技大学 https://pypi.mirrors.ustc.edu.cn/simple/
- 豆瓣(douban) https://pypi.douban.com/simple/
- 清华大学 https://pypi.tuna.tsinghua.edu.cn/simple/
- 中国科学技术大学 https://pypi.mirrors.ustc.edu.cn/simple/

**卸载**

使用 `pip uninstall <包名>`命令可以用来卸载指定的第三方资源包。

```shell
pip uninstall ipython # 卸载ipython包
```

**查找**

使用`pip list` 或者 `pip freeze`命令可以来管理第三方资源包。这两个命令的功能一致，都是用来显示当前环境里已经安装的包，区别在于`pip list`会列出所有的包，包括一些无法uninstall的包；而`pip freeze`只会列出我们安装的第三方包。

**总结**

开发中，我们通常会使用很多第三方的资源包，我们在将程序部署到服务器的时候，不仅要把代码上传到服务器，同时还需要把代码里用到的第三方资源包告诉服务器。那么这里就有两个问题:

1. 当我们电脑上运行很多个项目，每个项目使用的第三方资源包又不一致时，怎样将代码和它使用到的第三方资源包放在一起呢？答:虚拟环境

2. 怎样将自己代码使用到的第三方资源包告诉给服务器？

   > 1. 使用 pip freeze > requires.txt 命令，将代码里使用到的第三方资源包以及版本号写入到 requirements.txt 文件，在部署时，同时将 requirements.txt 文件上传到服务器。
   > 2. 服务器在拿到代码以后，首先运行 pip install -r requirements.txt 命令，将文件里列出的所有第三方框架先安装到服务器，然后才能运行代码。

### 自定义模块

除了使用系统提供的内置模块以外，我们还能自己写一个模块供自己的程序使用。一个py文件就是一个模块，所以，自定义模块很简单，基本上相当于创建一个py文件。但是，需要注意的是，如果一个py文件要作为一个模块被别的代码使用，这个py文件的名字一定要遵守标识符的命名规则。

#### 模块放置位置

创建一个模块非常简单，安装标识符的命名规则创建一个py文件就是一个模块。但是问题是，我们需要把创建好的这个py文件放在哪个位置，在代码中使用 `import`语句才能找到这个模块呢?

Python内置sys模块的path属性，列出了程序运行时查找模块的目录，只需要把我们创建好的模块放到这些任意的一个目录里即可。

```python
import sys
print(sys.path)
[
 'C:\\Users\\chris\\Desktop\\Test',
 'C:\\Users\\chris\\AppData\\Local\\Programs\\Python\\Python37\\python37.zip',
 'C:\\Users\\chris\\AppData\\Local\\Programs\\Python\\Python37\\DLLs',
 'C:\\Users\\chris\\AppData\\Local\\Programs\\Python\\Python37\\lib',
 'C:\\Users\\chris\\AppData\\Local\\Programs\\Python\\Python37',
 'C:\\Users\\chris\\AppData\\Roaming\\Python\\Python37\\site-packages',
 'C:\\Users\\chris\\AppData\\Local\\Programs\\Python\\Python37\\lib\\site-packages'
]
```

#### `__all__`的使用

使用`from <模块名> import *`导入一个模块里所有的内容时，本质上是去查找这个模块的`__all__`属性，将`__all__`属性里声明的所有内容导入。如果这个模块里没有设置`__all__`属性，此时才会导入这个模块里的所有内容。 

**模块里的私有成员**

模块里以一个下划线`_`开始的变量和函数，是模块里的私有成员，当模块被导入时，以`_`开头的变量默认不会被导入。但是它不具有强制性，如果一个代码强行使用以`_`开头的变量，有时也可以。但是强烈不建议这样使用，因为有可能会出问题。

#### 总结

test1.py:模块里没有`__all__`属性

```python
a = 'hello'
def fn():
    print('我是test1模块里的fn函数')
```

test2.py:模块里有`__all__`属性

```python
x = '你好'
y = 'good'
def foo():
    print('我是test2模块里的foo函数')
__all__ = ('x','foo')
```

test3.py:模块里有以`_`开头的属性

```python
m = '早上好'
_n = '下午好'
def _bar():
    print('我是test3里的bar函数')
```

demo.py

```python
from test1 import *
from test2 import *
from test3 import *

print(a)
fn()

print(x)
# print(y) 会报错，test2的__all__里没有变量 y
foo()


print(m)
# print(_n)  会报错，导入test3时， _n 不会被导入

import test3
print(test3._n)  # 也可以强行使用，但是强烈不建议
```



#### `__name__`的使用

在实际开中，当一个开发人员编写完一个模块后，为了让模块能够在项目中达到想要的效果，这个开发人员会自行在py文件中添加一些测试信息，例如：

test1.py

```python
def add(a,b):
    return a+b

# 这段代码应该只有直接运行这个文件进行测试时才要执行
# 如果别的代码导入本模块，这段代码不应该被执行
ret = add(12,22)
print('测试的结果是',ret)
```

demo.py

```python
import test1.py   # 只要导入了tets1.py,就会立刻执行 test1.py 代码，打印测试内容
```

为了解决这个问题，python在执行一个文件时有个变量`__name__`.在Python中，当直接运行一个py文件时，这个py文件里的`__name__`值是`__main__`,据此可以判断一个一个py文件是被直接执行还是以模块的形式被导入。

```python
def add(a,b):
    return a+b

if __name__ == '__main__':  # 只有直接执行这个py文件时,__name__的值才是 __main__
    # 以下代码只有直接运行这个文件才会执行，如果是文件被别的代码导入，下面的代码不会执行
    ret = add(12,22)
    print('测试的结果是',ret)
```

#### 注意事项

在自定义模块时，需要注意一点，自定义模块名不要和系统的模块名重名，否则会出现问题！



### 面向对象基础

- 面向过程：根据业务逻辑从上到下写代码。
- 面向对象：将变量与函数绑定到一起，分类进行封装，每个程序只要负责分配给自己的分类，这样能够更快速的开发程序，减少了重复代码。



面向对象编程（Object Oriented Programming，OOP，面向对象程序设计）和面相过程编程，是两种不同的编程方式。

面向对象编程的关注点在于**谁来做**

> 相比较函数，面向对象是更大的封装，根据职责在 一个对象中封装多个方法

- 在完成某一个需求前，首先确定职责 —— 要做的事情（方法）
- 根据 职责 确定不同的 对象，在对象内部封装不同的方法（多个）
- 最后完成的代码，就是顺序地调用不同对象的相应方法。

特点:

- 注重 对象和职责，不同的对象承担不同的职责。
- 更加适合应对复杂的需求变化，是专门应对复杂项目开发，提供的固定套路。
- 需要在面向过程基础上，再学习一些面向对象的语法。



#### 类

类是对一群具有相同特征或者行为 的事物的一个统称，是抽象的，不能直接使用

- 特征其实就是一个变量，在类里我们称之为属性。
- 行为其实就是一个函数，在类里我们称之为方法。
- 类其实就是由 **属性** 和 **方法** 组成的一个抽象概念。

类就相当于制造飞机时的图纸，是一个模板。这个模板只规定了飞机的某些特征(例如大小，颜色，型号等等)和行为(例如起飞，降落，飞行等等)，它并不是一个具体的飞机，而是对飞机的一个抽象概念。它出现的目的，是为了让我们的创建飞机对象。



#### 对象

对象是由类创建出来的一个具体存在，可以直接使用。由哪一个类创建出来的 对象，就拥有在哪一个类中定义的属性和方法。 **对象** 就相当于用图纸制造的飞机。在开发中，应该先有类，在类里定义好属性和行为，再根据类来创建对象



#### 类和对象的关系

- 类是模板，对象是根据类这个模板创建出来的，应该先有类，再有对象。
- 使用同一个类，能够创建出很多对象。
- 类中定义了什么属性和方法，对象中就有什么属性和方法。
- 不同对象对应的属性值也会不同。

例如：定义了一个狗类，这个狗类有以下属性：

- 品种
- 颜色
- 性别
- 名字

现在根据这个类创建出了两条狗，这两条狗分别是 `哈士奇、灰色、母、二哈` 和 `中华田园犬、黄色、公、旺财`。我们发现，这两条狗都具有 品种、颜色、性别和名字这些属性，但是每条狗对应的属性值却不一样。

#### 类的设计

在使用面相对象开发前，应该首先分析需求，确定一下，程序中需要包含哪些类！

在程序开发中，要设计一个类，通常需要满足一下三个要素：

1. **类名** 这类事物的名字，安照大驼峰命名法(每个单词的首字母大写)起名。
2. **属性** 这类事物具有什么样的特征。
3. **方法** 这类事物具有什么样的行为。

**定义类名**

名词提炼法:分析整个业务流程，出现的名词，通常就是找到的类。

**属性和方法的确定**

- 对对象的特征描述，可以定义成属性
- 对象具有的行为（动词）可以定义成方法

#### 面向对象基本语法

在Python中，对象几乎是无处不在的，我们可以使用`dir`内置函数来查看这个对象里的方法。

##### 定义简单的类1

> 面向对象是更大的封装，在一个类中封装多个方法，这样通过这个类创建出来的对象，就可以直接调用这些方法了！

在Python中要定义一个只包含方法的类，语法格式如下：

```python
class 类名:
    def 方法1(self,参数列表):
        pass
    def 方法2(self,参数列表):
        pass
```

> 1. 方法的定义格式和之前学习过的函数一样
> 2. 方法里的**第一个参数必须是self**，大家暂时先记住，稍后介绍 self.
> 3. 类名要遵守大驼峰命名法。

**创建实例对象**

当一个类定义完成之后，要使用这个类来创建对象，语法格式如下：

```python
对象变量名 = 类名()
```

**第一个面向对象代码**

需求

- 小猫 爱 吃 鱼，小猫 要 喝 水

分析

- 定义一个猫类 Cat
- 定义两个方法 eat 和 drink
- 按照需求 —— 不需要定义属性

```python
class Cat:
    """这是个猫类"""

    def eat(self):
        print("小猫在吃东西")

    def drink(self):
        print("小猫在喝水")

tom = Cat()  # 创建了一个Cat对象
tom.eat()
tom.drink()

hello_kitty = Cat()  # 又创建了一个新的Cat对象
hello_kitty.eat()
hello_kitty.drink()
```

##### self的使用

**给对象添加属性**

python支持动态属性，当一个对象创建好了以后，直接使用 `对象.属性名 = 属性值` 就可以很方便的给对象添加一个属性。

```python
tom = Cat()
tom.name = 'Tom'  # 可以直接给 tom 对象添加一个 name 属性
```

这种方法很方便，但是，不建议使用这种方式给对象添加属性。

**self的概念**

哪个对象调用了方法，方法里的`self`指的就是谁。 通过 `self.属性名` 可以访问到这个对象的属性；通过 `self.方法名()` 可以调用这个对象的方法。

```python
class Cat:
    def eat(self):
        print("%s爱吃鱼" %self.name)

tom = Cat()
tom.name = 'Tom'  # 给 tom 对象添加了一个name属性
tom.eat()  # Tom爱吃鱼

lazy_cat = Cat()
lazy_cat.name = "大懒猫"
lazy_cat.eat() # 大懒猫爱吃鱼
```

**直接给对象添加属性的缺点**

上述代码中，我们是先创建对象，然后再给对象添加 `name` 属性，但是这样做会有问题。

```python
tom = Cat()
tom.eat()
tom.anme = "Tom"
```

程序运行时会报错：

```python
AttributeError: 'Cat' object has no attribute 'name'
错误提示：'Cat'对象没有 'name' 属性
```

在日常开发中，不推荐在类的外部直接给对象添加属性这种方式。对象应该具有哪些属性，我们应该封装在类的内部。



### 魔法方法1

Python 里有一种方法，叫做魔法方法。Python 的类里提供的，两个下划线开始，两个下划线结束的方法，就是魔法方法，魔法方法在恰当的时候就会被激活，自动执行。 魔法方法的两个特点：

- 两侧各有两个下划线；
- "咒语"名字已经由 Python 官方定义好，我们不能乱写。

#### 1.`__init__`方法

`__init__()`方法，在创建一个对象时默认被调用，不需要手动调用。在开发中，如果希望在创建对象的同时，就设置对象的属性，可以对 `__init__` 方法进行改造。

```python
class Cat:
    """这是一个猫类"""
    def __init__(self,name):  # 重写了 __init__ 魔法方法
        self.name = name

    def eat(self):
        return "%s爱吃鱼"%self.name
    def drink(self):
        return '%s爱喝水'%self.name

    """
        tom = Cat()
        TypeError: __init__() missing 1 required positional argument: 'name'
        这种写法在运行时会直接报错！因为 __init__ 方法里要求在创建对象时，必须要传递 name 属性，如果不传入会直接报错！
    """

tom = Cat("Tom")  # 创建对象时，必须要指定name属性的值
tom.eat()   # tom爱吃鱼
```

注意：

1. `__init__()`方法在创建对象时，会默认被调用，不需要手动的调用这个方法。
2. `__init__()`方法里的self参数，在创建对象时不需要传递参数，python解释器会把创建好的对象引用直接赋值给self
3. 在类的内部，可以使用self来使用属性和调用方法；在类的外部，需要使用对象名来使用属性和调用方法。
4. 如果有多个对象，每个对象的属性是各自保存的，都有各自独立的地址。
5. 方法是所有对象共享的，只占用一份内存空间，方法被调用时会通过self来判断是哪个对象调用了实例方法。



#### 2.`__del__`方法

创建对象后，python解释器默认调用`__init__()`方法；

而当删除对象时，python解释器也会默认调用一个方法，这个方法为`__del__()`方法。

```python
class Student:
    def __init__(self,name,score):
        print('__init__方法被调用了')
        self.name = name
        self.score = score

    def __del__(self):
        print('__del__方法被调用了')
s = Student('lisi',95)
del s
input('请输入内容')
"""
__init__方法被调用了
__del__方法被调用了
请输入内容
"""
```



#### 3.`__str__`方法

`__str__`方法返回对象的描述信息，使用`print()`函数打印对象时，其实调用的就是这个对象的`__str__`方法。

```python
class Cat:
    def __init__(self,name,color):
        self.name = name
        self.color = color

tom = Cat('Tom','white')

# 使用 print 方法打印对象时，会调用对象的 __str__ 方法，默认会打印类名和对象的地址名
print(tom)   # <__main__.Cat object at 0x0000021BE3B9C940>
```

如果想要修改对象的输出的结果，可以重写 `__str__` 方法。

```python
class Person:
    def __init__(self,name,age):
        self.name = name
        self.age = age

    def __str__(self):
        return '哈哈'

p  = Person('张三',18)
print(p)   # 哈哈  打印对象时，会自动调用对象的 __str__ 方法
```

一般情况下，我们在打印一个对象时，可能需要列出这个对象的所有属性。

```python
class Student:
    def __init__(self,name,score):
        self.name = name
        self.score = score
    def __str__(self):
        return '姓名是:{},成绩是{}分'.format(self.name,self.score)

s = Student('lisi',95)
print(s)   # 姓名是:lisi,成绩是95分
```



#### 4.`__repr__`方法

`__repr__`方法和`__str__`方法功能类似，都是用来修改一个对象的默认打印内容。在打印一个对象时，如果没有重写`__str__`方法，它会自动来查找`__repr__`方法。如果这两个方法都没有，会直接打印这个对象的内存地址。

```python
class Student:
    def __init__(self, name, score):
        self.name = name
        self.score = score

    def __repr__(self):
        return 'helllo'


class Person:
    def __repr__(self):
        return 'hi'

    def __str__(self):
        return 'good'


s = Student('lisi', 95)
print(s)  # hello

p = Person()
print(p)  # good
```



#### 5.`__call__`方法

对象后面加括号，触发执行。

```python
class Foo:
    def __init__(self):
        pass

    def __call__(self, *args, **kwargs):
        print('__call__')


obj = Foo()  # 执行 __init__
obj()  # 执行 __call__   #__call__
```



#### 总结

1. 当创建一个对象时，会自动调用`__init__`方法，当删除一个对象时，会自动调用`__del__`方法。
2. 使用`__str__`和`__repr__`方法，都会修改一个对象转换成为字符串的结果。一般来说，`__str__`方法的结果更加在意可读性，而`__repr__`方法的结果更加在意正确性(例如:datetime模块里的datetime类)



### 魔法方法2

### 对象内置属性

使用内置函数`dir`可以查看一个对象支持的所有属性和方法，Python中存在着很多的内置属性。

#### `__slots__`

Python中支持动态属性，可以直接通过点语法直接给一个对象添加属性，代码更加的灵活。但是在某些情况下，我们可能需要对属性进行控制，此时，就使用`__slots__`实现。(控制属性的个数，不允许再添加)

```python
class Person(object):
    __slots__ = ('name', 'age')
    def __init__(self, name, age):
        self.name = name
        self.age = age
p = Person('张三', 18)
p.name = '李四'

# 对象p只能设置name和age属性，不能再动态添加属性
# p.height = 180 # 报错
```



#### `__doc__`

表示类的描述信息。

```python
class Foo:
    """ 描述类信息，这是用于看片的神奇 """
    def func(self):
        pass

print(Foo.__doc__)
#输出：类的描述信息
```



#### `__module__` 和 `__class__`

`__module__` 表示当前操作的对象在那个模块；`__class__` 表示当前操作的对象的类是什么。

```python
test.py
class Person(object):
    def __init__(self):
        self.name = 'laowang'
main.py
from test import Person

obj = Person()
print(obj.__module__)  # 输出 test 即：输出模块
print(obj.__class__)  # 输出 test.Person 即：输出类
```



#### `__dict__`

以字典的形式，显示对象所有的属性和方法。

```python
class Province(object):
    country = 'China'

    def __init__(self, name, count):
        self.name = name
        self.count = count

    def func(self, *args, **kwargs):
        print('func')

# 获取类的属性，即：类属性、方法、
print(Province.__dict__)
# 输出：{'__dict__': <attribute '__dict__' of 'Province' objects>, '__module__': '__main__', 'country': 'China', '__doc__': None, '__weakref__': <attribute '__weakref__' of 'Province' objects>, 'func': <function Province.func at 0x101897950>, '__init__': <function Province.__init__ at 0x1018978c8>}

obj1 = Province('山东', 10000)
print(obj1.__dict__)
# 获取 对象obj1 的属性
# 输出：{'count': 10000, 'name': '山东'}

obj2 = Province('山西', 20000)
print(obj2.__dict__)
# 获取 对象obj1 的属性
# 输出：{'count': 20000, 'name': '山西'}
```



#### `__getitem__`、`__setitem__`和`__delitem__`方法

这三个方法，是将对象当做字典一样进行操作。

```python
class Foo(object):

    def __getitem__(self, key):
        print('__getitem__', key)

    def __setitem__(self, key, value):
        print('__setitem__', key, value)

    def __delitem__(self, key):
        print('__delitem__', key)

obj = Foo()

result = obj['k1']      # 自动触发执行 __getitem__
obj['k2'] = 'laowang'   # 自动触发执行 __setitem__
del obj['k1']           # 自动触发执行 __delitem__
```



### 实例属性、类属性

在面向对象开发中，使用类创建出来的实例是一个对象，那么，类是否是一个对象呢？

#### 实例属性

通过类创建的对象被称为 **实例对象**，对象属性又称为实例属性，记录对象各自的数据，不同对象的同名实例属性，记录的数据各自独立，互不干扰。

```python
class Person(object):
    def __init__(self,name,age):
        # 这里的name和age都属于是实例属性，每个实例在创建时，都有自己的属性
        self.name = name
        self.age = age

# 每创建一个对象，这个对象就有自己的name和age属性
p1 = Person('张三',18)
p2 = Person("李四",20)
```

#### 类属性

类属性就是类对象所拥有的属性，它被该类的所有实例对象所共有，类属性可以通过类对象或者实例对象访问。

```python
class Dog:
    type = "狗"  # 类属性

dog1 = Dog()
dog2 = Dog()

# 不管是dog1、dog2还是Dog类，都可以访问到type属性
print(Dog.type)  # 结果：狗
print(dog1.type)  # 结果：狗
print(dog2.type)  # 结果：狗
Copy
```

**使用场景：**

1. 类的实例记录的某项数据始终保持一致时，则定义类属性。
2. /实例属性要求每个对象为其单独开辟一份内存空间来记录数据，而类属性为全类所共有 ，仅占用一份内存，更加节省内存空间。

**注意点：**

1> **尽量避免类属性和实例属性同名**。如果有同名实例属性，**实例对象会优先访问实例属性**。

```python
class Dog(object):
    type = "狗"  # 类属性

    def __init__(self):
        self.type = "dog"  # 对象属性

# 创建对象
dog1 = Dog()

print(dog1.type)     # 结果为 “dog”   类属性和实例属性同名，使用 实例对象 访问的是 实例属性
Copy
```

2> **类属性只能通过类对象修改，不能通过实例对象修改**

```python
lass Dog(object):
    type = "狗"  # 类属性

# 创建对象
dog1 = Dog()
dog1.type = "dog"   # 使用 实例对象 创建了对象属性type

print(dog1.type)     # 结果为 “dog”   类属性和实例属性同名，访问的是实例属性
print(Dog.type)      # 结果为 "狗"   访问类属性

# 只有使用类名才能修改类属性
Dog.type = "土狗"
print(Dog.type)  # 土狗
dog2 = Dog()
print(dog2.type)  # 土狗
Copy
```

3> **类属性也可以设置为私有**，前边添加两个下划线。 如:

```python
class Dog(object):
    count = 0  # 公有的类属性
    __type = "狗"  # 私有的类属性

print(Dog.count)       # 正确
print(Dog.__type)      # 错误,私有属性，外部无法访问。
```



### 私有属性和方法

在实际开发中，对象的某些属性或者方法可能只希望在对象的内部别使用，而不希望在外部被访问到，这时就可以定义私有属性和私有方法。

#### 定义方法

在定义属性或方法时，在属性名或者方法名前增加两个下划线`__`，定义的就是私有属性或方法。

```python
class Person:
    def __init__(self,name,age):
        self.name = name
        self.age = age
        self.__money = 2000  # 使用 __ 修饰的属性，是私有属性

    def __shopping(self, cost):
        self.__money -= cost  # __money 只能在对象内部使用
        print('还剩下%d元'%self.__money)

    def test(self):
        self.__shopping(200)  # __shopping 方法也只能在对象内部使用

p = Person('张三',18)
# print(p.__money)   这里会报错，不能直接访问对象内部的私有属性
p.test()
# p.__shopping()  这里会报错，__shopping 只能在对象内部使用，外部无法访问
```

#### 访问私有属性和方法

私有属性不能直接使用，私有方法不能直接调用。但是，通过一些代码，我们也可以在外部访问一个对象的私有属性和方法。

**直接访问**

使用方式:在私有属性名或方法名前添加 `_类名`

```python
class Person:
    def __init__(self,name,age):
        self.name = name
        self.age = age
        self.__money = 2000

    def __shopping(self, cost):
        self.__money -= cost


p = Person('李四',20)
print(p._Person__money)  # 使用对象名._类名__私有属性名 可以直接访问对象的私有属性
p._Person__shopping(100)  # 使用对象名._类名__函数名 可以直接调用对象的私有方法
print(p._Person__money)
```

注意：在开发中，我们强烈不建议使用 `对象名._类名__私有属性名` 的方式来访问对象的私有属性！

#### 定义方法访问私有变量

在实际开发中，如果对象的变量使用了`__` 来修饰，就说明它是一个私有变量，不建议外部直接使用和修改。如果硬要修改这个属性，可以使用定义`get`和`set`方法这种方式来实现。

```python
class Person:
    def __init__(self,name,age):
        self.name = name
        self.age = age
        self.__money = 2000  # __money 是私有变量，外部无法访问

    def get_money(self):  # 定义了get_money 方法，在这个方法里获取到 __money
        return self.__money  # 内部可以访问 __money 变量

    def set_money(self,money): # 定义了set_money 方法，在这个方法里，可以修改 __money
        self.__money = money

p = Person('王五',21)

# 外部通过调用 get_money 和 set_money 这两个公开方法获取和修改私有变量
print(p.get_money())
p.set_money(8000)
print(p.get_money())
```



### 面向对象进阶

#### 类方法

- **第一个形参是类对象的方法**
- 需要用装饰器`@classmethod`来标识其为类方法，对于类方法，**第一个参数必须是类对象**，一般以`cls`作为第一个参数。

```python
class Dog(object):
    __type = "狗"

    # 类方法，用classmethod来进行修饰
    @classmethod
    def get_type(cls):
        return cls.__type
print(Dog.get_type()) 
```

> 使用场景：
>
> - 当方法中 **需要使用类对象** (如访问私有类属性等)时，定义类方法
> - 类方法一般和类属性配合使用

#### 静态方法

- 需要通过装饰器`@staticmethod`来进行修饰，**静态方法既不需要传递类对象也不需要传递实例对象（形参没有self/cls）**。
- 静态方法 也能够通过 **实例对象** 和 **类对象** 去访问。

```python
class Dog(object):
    type = "狗"

    def __init__(self):
        name = None

    # 静态方法    
    @staticmethod
    def introduce():  # 静态方法不会自动传递实例对象和类对象
        print("犬科哺乳动物,属于食肉目..")

dog1 = Dog()
Dog.introduce()    # 可以用 实例对象 来调用 静态方法
dog1.introduce()    # 可以用 类对象 来调用 静态方法
```

> 使用场景：
>
> - 当方法中 **既不需要使用实例对象**(如实例对象，实例属性)，**也不需要使用类对象** (如类属性、类方法、创建实例等)时，定义静态方法
> - **取消不需要的参数传递**，有利于 **减少不必要的内存占用和性能消耗**

**注意**

- 类中定义了同名的方法时，调用方法会执行最后定义的方法

```python
class Dog:

    def demo_method(self):
        print("对象方法")

    @classmethod
    def demo_method(cls):
        print("类方法")

    @staticmethod
    def demo_method():  # 被最后定义
        print("静态方法")

dog1 = Dog()
Dog.demo_method()  # 结果: 静态方法
dog1.demo_method()  # 结果: 静态方法
```

### 单例设计

#### `__new__`和`__init__`方法

```python
class A(object):
    def __init__(self):
        print("这是 init 方法")

    def __new__(cls):
        print("这是 new 方法")
        return object.__new__(cls)

A()
```

**总结**

- `__new__`至少要有一个参数cls，代表要实例化的类，此参数在实例化时由Python解释器自动提供
- `__new__`必须要有返回值，返回实例化出来的实例，这点在自己实现`__new__`时要特别注意，可以return父类`__new__`出来的实例，或者直接是object的`__new__`出来的实例
- `__init__`有一个参数self，就是这个`__new__`返回的实例，`__init__`在`__new__`的基础上可以完成一些其它初始化的动作，`__init__`不需要返回值



#### 单例设计模式

举个常见的单例模式例子，我们日常使用的电脑上都有一个回收站，在整个操作系统中，回收站只能有一个实例，整个系统都使用这个唯一的实例，而且回收站自行提供自己的实例。因此回收站是单例模式的应用。

确保某一个类只有一个实例，而且自行实例化并向整个系统提供这个实例，这个类称为单例类，单例模式是一种对象创建型模式。

```python
# 实例化一个单例
class Singleton(object):
    __instance = None
    __is_first = True

    def __new__(cls, age, name):
        if not cls.__instance:
            cls.__instance = object.__new__(cls)
        return cls.__instance

    def __init__(self, age, name):
        if self. __is_first: # 不会再创建第二个对象
            self.age = age
            self.name = name
            Singleton. __is_first = False


a = Singleton(18, "张三")
b = Singleton(28, "张三")

print(id(a))
print(id(b))

print(a.age) # 18
print(b.age) # 18

a.age = 19
print(b.age)
```



### 继承

继承是面向对象软件设计中的一个概念，与多态、封装共为面向对象的三个基本特征。继承可以使得子类具有父类的属性和方法或者重新定义、追加属性和方法等。



- 在程序中，继承描述的是多个类之间的所属关系。
- 如果一个类A里面的属性和方法可以复用，则可以通过继承的方式，传递到类B里。
- 那么类A就是基类，也叫做父类；类B就是派生类，也叫做子类。

```python
class Animal:
    def __int__(self):
        pass
    """动物类"""
    def sleep(self):
        print('正在睡觉')


class Dog(Animal):
    """Dog类继承自Animal类"""
    def __init__(self):
        pass

class Cat(Animal):  # 定义类时，在括号后面传入父类的类名，表示子类继承父类
    """Cat类继承自Animal类"""
    def __int__(self):
        pass

# Dog 和 Cat 都继承自Animal类，可以直接使用Animal类里的sleep方法
dog = Dog()
dog.sleep()

cat = Cat()
cat.sleep()
```



### 对象内置函数

Python中的身份运算符用来判断两个对象是否相等；isinstance用来判断对象和类之间的关系；issublcass用啊里判断类与类之间的关系。

#### 身份运算符

身份运算符用来比较两个对象的内存地址，看这两个对象是否是同一个对象。

```python
class Person(object):
    def __init__(self, name, age):
        self.name = name
        self.age = age


p1 = Person('张三', 18)
p2 = Person('张三', 18)
p3 = p1

print(p1 is p2)  # False
print(p1 is p3)  # True
```

#### isinstance

instance内置函数，用来判断一个实例对象是否是由某一个类(或者它的子类)实例化创建出来的。

```python
class Person(object):
    def __init__(self, name, age):
        self.name = name
        self.age = age


class Student(Person):
    def __init__(self, name, age, score):
        super(Student, self).__init__(name, age)
        self.score = score


class Dog(object):
    def __init__(self, name, color):
        self.name = name
        self.color = color


p = Person('tony', 18)
s = Student('jack', 20, 90)
d = Dog('旺财', '白色')

print(isinstance(p, Person))  # True.对象p是由Person类创建出来的
print(isinstance(s, Person))  # True.对象s是有Person类的子类创建出来的
print(isinstance(d, Person))  # False.对象d和Person类没有关系
```

#### issubclass

issubclass 用来判断两个类之间的继承关系。

```python
class Person(object):
    def __init__(self, name, age):
        self.name = name
        self.age = age


class Student(Person):
    def __init__(self, name, age, score):
        super(Student, self).__init__(name, age)
        self.score = score


class Dog(object):
    def __init__(self, name, color):
        self.name = name
        self.color = color


print(issubclass(Student, Person))  # True
print(issubclass(Dog, Person))  # False
```



### 多态

面向对象的三大特性：

- 封装：这是定义类的准则，根据对象的特点，将行为和属性抽象出来，封装到一个类中。
- 继承：这是设计类的技巧。父类与子类，主要体现在代码的重用，不需要大量的编写重复代码。
- 多态：不同的子类调用相同的父类方法，产生不同的执行结果，可以增加代码的外部灵活度。多态是以继承和重写父类方法为前提的，它是一种调用方法的技巧，不会影响到类的内部设计。

**场景**

- 提供三个类：缉毒犬、军犬、人
- 缉毒犬-->追查毒品，军犬-->攻击假人，人-->让小狗干活
- 设计类来完成功能。

![img](file:///C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/Desktop/python%E5%88%9D%E5%85%A5%E9%97%A8%EF%BC%88b%E7%AB%99%EF%BC%89/Day12-%E9%9D%A2%E5%90%91%E5%AF%B9%E8%B1%A1%E8%BF%9B%E9%98%B6/03-%E7%AC%94%E8%AE%B0/imgs/%E6%B2%A1%E6%9C%89%E4%BD%BF%E7%94%A8%E5%A4%9A%E6%80%81.png)

代码实现:

```python
class ArmyDog(object):

    def bite_enemy(self):
        print('追击敌人')

class DrugDog(object):

    def track_drug(self):
        print('追查毒品')

class Person(object):

    def work_with_army(self, dog):
        dog.bite_enemy()

    def work_with_drug(self, dog):
        dog.track_drug()

ad = ArmyDog()
dd = DrugDog()

p = Person()
p.work_with_army(ad)
p.work_with_drug(dd)
```

思考：这段代码设是否有问题？

新增需求：此时，又多了一个犬种，就又需要在Person类里新建一个方法，让这个方法操作新的狗。

```python
class XiaoTianDog(object):

    def eat_moon(self):
        print('哮天犬把月亮吃了')

class Person(object):

    def work_with_xiaotian(self, dog):  # 添加方法
        dog.eat_moon()
```

Person 类总是不断的添加新的功能，每次都需要改动Person类的源码，程序的扩展性太差了！

- 最好是提供一个父类 Dog，具备 work 的功能，其他小狗继承它，这样只要是小狗类，则行为被统一起来了，我们人类完全可以保证，只要是小狗的子类，找它干活肯定不会有问题。
- 这样人只要一个方法就能逗任意种类的狗玩，哪怕是添加新的狗，人的类都不需要修改。
- 图示如下：

代码实现:

```python
class Dog(object):

    def work(self):  # 父类提供统一的方法，哪怕是空方法
        pass

class ArmyDog(Dog):   # 继承 Dog

    def work(self):  # 子类重写方法，并且处理自己的行为
        print('追击敌人')

class DrugDog(Dog):

    def work(self):
        print('追查毒品')

class Person(object):

    def work_with_dog(self, dog):
        dog.work()    # 使用小狗可以根据对象的不同而产生不同的运行效果, 保障了代码的稳定性

# 子类对象可以当作父类来使用
dog = Dog()
ad = ArmyDog()
dd = DrugDog()


p = Person()
p.work_with_dog(dog)
p.work_with_dog(ad)  # 同一个方法，只要是 Dog 的子类就可以传递，提供了代码的灵活性
p.work_with_dog(dd)  # 并且传递不同对象，最终 work_with_dog 产生了不同的执行效果
```

- 最终效果
  - Person 类中只需要调用 Dog 对象 work() 方法，而不关心具体是 什么狗
  - work() 方法是在 Dog 父类中定义的，子类重写并处理不同方式的实现
  - 在程序执行时，传入不同的 Dog 对象作为实参，就会产生不同的执行效果

**多态总结**

- 定义：多态是一种使用对象的方式，子类重写父类方法，调用不同子类对象的相同父类方法，可以产生不同的执行结果
- 好处：调用灵活，有了多态，更容易编写出通用的代码，做出通用的编程，以适应需求的不断变化！
- 实现步骤：
  - 定义父类，并提供公共方法
  - 定义子类，并重写父类方法
  - 传递子类对象给调用者，可以看到不同子类执行效果不同



### 文件操作

#### <1>打开文件

在python，使用open函数，可以打开一个已经存在的文件，或者创建一个新文件

open(文件路径，访问模式)

示例如下：

```python
f = open('test.txt', 'w')
```

说明:

**文件路径**

文件的路径分为相对路径和绝对路径两种。

- 绝对路径：指的是绝对位置，完整地描述了目标的所在地，所有目录层级关系是一目了然的。
  - 例如：`C:/Users/chris/AppData/Local/Programs/Python/Python37/python.exe`，从电脑的盘符开始，表示的就是一个绝对路径。
- 相对路径：是从当前文件所在的文件夹开始的路径。
  - `test.txt`，是在当前文件夹查找 `test.txt` 文件
  - `./test.txt`，也是在当前文件夹里查找`test.txt`文件， `./` 表示的是当前文件夹。
  - `../test.txt`，从当前文件夹的上一级文件夹里查找 `test.txt` 文件。 `../` 表示的是上一级文件夹
  - `demo/test.txt`，在当前文件夹里查找 `demo`这个文件夹，并在这个文件夹里查找 `test.txt`文件。

**访问模式：**

| 访问模式 | 说明                                                         |
| :------: | :----------------------------------------------------------- |
|    r     | 以只读方式打开文件。文件的指针将会放在文件的开头。如果文件不存在，则报错。**这是默认模式。** |
|    w     | 打开一个文件只用于写入。如果该文件已存在则将其覆盖。如果该文件不存在，创建新文件。 |
|    a     | 打开一个文件用于追加。如果该文件已存在，文件指针将会放在文件的结尾。也就是说，新的内容将会被写入到已有内容之后。如果该文件不存在，创建新文件进行写入。 |
|    r+    | 打开一个文件用于读写。文件指针将会放在文件的开头。           |
|    w+    | 打开一个文件用于读写。如果该文件已存在则将其覆盖。如果该文件不存在，创建新文件。 |
|    a+    | 打开一个文件用于读写。如果该文件已存在，文件指针将会放在文件的结尾。文件打开时会是追加模式。如果该文件不存在，创建新文件用于读写。 |
|    rb    | 以二进制格式打开一个文件用于只读。文件指针将会放在文件的开头。 |
|    wb    | 以二进制格式打开一个文件只用于写入。如果该文件已存在则将其覆盖。如果该文件不存在，创建新文件。 |
|    ab    | 以二进制格式打开一个文件用于追加。如果该文件已存在，文件指针将会放在文件的结尾。也就是说，新的内容将会被写入到已有内容之后。如果该文件不存在，创建新文件进行写入。 |
|   rb+    | 以二进制格式打开一个文件用于读写。文件指针将会放在文件的开头。 |
|   wb+    | 以二进制格式打开一个文件用于读写。如果该文件已存在则将其覆盖。如果该文件不存在，创建新文件。 |
|   ab+    | 以二进制格式打开一个文件用于读写。如果该文件已存在，文件指针将会放在文件的结尾。如果该文件不存在，创建新文件用于读写。 |

#### <2>关闭文件

close( )

示例如下：

```python
# 新建一个文件，文件名为:test.txt
f = open('test.txt', 'w')

# 关闭这个文件
f.close()
```

#### <3>写数据(write)

使用write()可以完成向文件写入数据

demo: 新建一个文件 `file_write_test.py`,向其中写入如下代码:

```python
f = open('test.txt', 'w')
f.write('hello world, i am here!\n' * 5)
f.close()
```

运行之后会在`file_write_test.py`文件所在的路径中创建一个文件`test.txt`,并写入内容，运行效果显示如下: ![img](imgs/文件写入.png)

注意：

- 如果文件不存在，那么创建；如果存在那么就先清空，然后写入数据

#### <4>读数据(read)

使用read(num)可以从文件中读取数据，num表示要从文件中读取的数据的长度（单位是字节），如果没有传入num，那么就表示读取文件中所有的数据

demo: 新建一个文件`file_read_test.py`，向其中写入如下代码:

```python
f = open('test.txt', 'r')
content = f.read(5)  # 最多读取5个数据
print(content)

print("-"*30)  # 分割线，用来测试

content = f.read()  # 从上次读取的位置继续读取剩下的所有的数据
print(content)

f.close()  # 关闭文件，这个可是个好习惯哦
```

运行现象：

```
hello
------------------------------
 world, i am here!
```

注意：

- 如果用open打开文件时，如果使用的"r"，那么可以省略 `open('test.txt')`

#### <5>读数据（readline）

readline只用来读取一行数据。

```python
f = open('test.txt', 'r')

content = f.readline()
print("1:%s" % content)

content = f.readline()
print("2:%s" % content)


f.close()
```

#### <6>读数据（readlines）

readlines可以按照行的方式把整个文件中的内容进行一次性读取，并且返回的是一个列表，其中每一行为列表的一个元素。

```python
f = open('test.txt', 'r')
content = f.readlines()
print(type(content))

for temp in content:
    print(temp)

f.close()
```

### 指针定位

- tell() 方法用来显示当前指针的位置

  ```python
  f = open('test.txt')
  print(f.read(10))  # read 指定读取的字节数
  print(f.tell())    # tell()方法显示当前文件指针所在的文字
  f.close()
  ```

- seek(offset,whence) 方法用来重新设定指针的位置。

  - offset:表示偏移量
  - whence:只能传入012中的一个数字。
    - 0表示从文件头开始
    - 1表示从当前位置开始
    - 2 表示从文件的末尾开始

  ```python
  f = open('test.txt','rb')  # 需要指定打开模式为rb,只读二进制模式
  
  print(f.read(3))
  print(f.tell())
  
  f.seek(2,0)   # 从文件的开头开始，跳过两个字节
  print(f.read())
  
  f.seek(1,1) # 从当前位置开始，跳过一个字节
  print(f.read())
  
  f.seek(-4,2) # 从文件末尾开始，往前跳过四个字节
  print(f.read())
  
  f.close()
  ```



### CSV文件操作

#### CSV文件读入

CSV文件：Comma-Separated Values，中文叫逗号分隔值或者字符分割值，其文件**以纯文本的形式存储表格数据。**可以把它理解为一个表格，只不过这个表格是以纯文本的形式显示的，单元格与单元格之间，默认使用逗号进行分隔；每行数据之间，使用换行进行分隔。

```
name,age,score
zhangsan,18,98
lisi,20,99
wangwu,17,90
jerry,19,95
```

Python中的csv模块，提供了相应的函数，可以让我们很方便的读写csv文件。

#### CSV文件的写入

```python
import csv

# 以写入方式打开一个csv文件
file = open('test.csv','w')

# 调用writer方法，传入csv文件对象，得到的结果是一个CSVWriter对象
writer = csv.writer(file)

# 调用CSVWriter对象的writerow方法，一行行的写入数据
writer.writerow(['name', 'age', 'score'])

# 还可以调用writerows方法，一次性写入多行数据
writer.writerows([['zhangsan', '18', '98'],['lisi', '20', '99'], ['wangwu', '17', '90'], ['jerry', '19', '95']])
file.close()
```

#### CSV文件的读取

```python
import csv

# 以读取方式打开一个csv文件
file = open('test.csv', 'r')

# 调用csv模块的reader方法，得到的结果是一个可迭代对象
reader = csv.reader(file)

# 对结果进行遍历，获取到结果里的每一行数据
for row in reader:
    print(row)

file.close()
```

### 将数据写入内存

除了将数据写入到一个文件以外，我们还可以使用代码，将数据暂时写入到内存里，可以理解为数据缓冲区。Python中提供了StringIO和BytesIO这两个类将字符串数据和二进制数据写入到内存里。

#### StringIO

StringIO可以将字符串写入到内存中，像操作文件一下操作字符串。

```python
from io import StringIO

# 创建一个StringIO对象
f = StringIO()
# 可以像操作文件一下，将字符串写入到内存中
f.write('hello\r\n')
f.write('good')

# 使用文件的 readline和readlines方法，无法读取到数据
# print(f.readline())
# print(f.readlines())

# 需要调用getvalue()方法才能获取到写入到内存中的数据
print(f.getvalue())

f.close()
Copy
```

#### BytesIO

如果想要以二进制的形式写入数据，可以使用BytesIO类，它的用法和StringIO相似，只不过在调用write方法写入时，需要传入二进制数据。

```python
from io import BytesIO

f = BytesIO()
f.write('你好\r\n'.encode('utf-8'))
f.write('中国'.encode('utf-8'))

print(f.getvalue())
f.close()
```



### 序列化和反序列化

通过文件操作，我们可以将字符串写入到一个本地文件。但是，如果是一个对象(例如列表、字典、元组等)，就无法直接写入到一个文件里，需要对这个对象进行序列化，然后才能写入到文件里。

设计一套协议，按照某种规则，把内存中的数据转换为字节序列，保存到文件，这就是序列化，反之，从文件的字节序列恢复到内存中，就是反序列化。

Python中提供了JSON和pickle两个模块用来实现数据的序列化和反序列化。

#### JSON模块

JSON(JavaScriptObjectNotation, JS对象简谱)是一种轻量级的数据交换格式，它基于 ECMAScript 的一个子集，采用完全独立于编程语言的**文本格式**来存储和表示数据。JSON的本质是字符串！

#### 使用JSON实现序列化

JSON提供了dump和dumps方法，将一个对象进行序列化。

dumps方法的作用是把对象转换成为字符串，它本身不具备将数据写入到文件的功能。

```python
import json
file = open('names.txt', 'w')
names = ['zhangsan', 'lisi', 'wangwu', 'jerry', 'henry', 'merry', 'chris']
# file.write(names)  出错，不能直接将列表写入到文件里

# 可以调用 json的dumps方法，传入一个对象参数
result = json.dumps(names)

# dumps 方法得到的结果是一个字符串
print(type(result))  # <class 'str'>

# 可以将字符串写入到文件里
file.write(result)

file.close()
```

dump方法可以在将对象转换成为字符串的同时，指定一个文件对象，把转换后的字符串写入到这个文件里。

```python
import json

file = open('names.txt', 'w')
names = ['zhangsan', 'lisi', 'wangwu', 'jerry', 'henry', 'merry', 'chris']

# dump方法可以接收一个文件参数，在将对象转换成为字符串的同时写入到文件里
json.dump(names, file)
file.close()
```

注意：如果是一个空对象，调用dumps方法转换成为一个JSON对象，得到的结果是null(JS里的空对象)

```python
json.dumps(None)  # null
```

#### 使用JSON实现反序列化

使用loads和load方法，可以将一个JSON字符串反序列化成为一个Python对象。

loads方法需要一个字符串参数，用来将一个字符串加载成为Python对象。

```python
import json

# 调用loads方法，传入一个字符串，可以将这个字符串加载成为Python对象
result = json.loads('["zhangsan", "lisi", "wangwu", "jerry", "henry", "merry", "chris"]')
print(type(result))  # <class 'list'>
```

load方法可以传入一个文件对象，用来将一个文件对象里的数据加载成为Python对象。

```python
import json

# 以可读方式打开一个文件
file = open('names.txt', 'r')

# 调用load方法，将文件里的内容加载成为一个Python对象
result = json.load(file)

print(result)
file.close()
```

#### pickle模块

和json模块类似，pickle模块也有dump和dumps方法可以对数据进行序列化，同时也有load和loads方法进行反序列化。区别在于，json模块是将对象转换成为字符串，而pickle模块是将对象转换成为二进制。

pickle模块里方法的使用和json里方法的使用大致相同，需要注意的是，**pickle是将对象转换成为二进制，所以，如果想要把内容写入到文件里，这个文件必须要以二进制的形式打开。**

**区别(了解)**

> 思考: json和pickle两个模块都可以将对象进行序列化和反序列化，那它们有哪些区别，在使用场景上又该如何选择？

- json模块:
  - 将对象转换成为字符串，不管是在哪种操作系统，哪种编程语言里，字符串都是可识别的。
  - json就是用来在不同平台间传递数据的。
  - 并不是所有的对象都可以直接转换成为一个字符串，下标列出了Python对象与json字符串的对应关系。

| Python     | JSON   |
| ---------- | ------ |
| dict       | object |
| list,tuple | array  |
| str        | string |
| int,float  | number |
| True       | true   |
| False      | false  |
| None       | null   |

- 如果是一个自定义对象，默认无法装换成为json字符串，需要手动指定JSONEncoder.

- 如果是将一个json串重新转换成为对象，这个对象里的方法就无法使用了。

  ```python
  import json
  class MyEncode(json.JSONEncoder):
      def default(self, o):
          # return {"name":o.name,"age":o.age}
          return o.__dict__
  
  class Person(object):
      def __init__(self, name, age):
          self.name = name
          self.age = age
  
        def eat(self):
            print(self.name+'正在吃东西')
  
  p1 = Person('zhangsan', 18)
  
  # 自定义对象想要转换成为json字符串，需要给这个自定义对象指定JSONEncoder
  result = json.dumps(p1, cls=MyEncode)
  print(result)  # {"name": "zhangsan", "age": 18}
  
  # 调用loads方法将对象加载成为一个对象以后，得到的结果是一个字典
  p = json.loads(result)
  print(type(p))
  Copy
  ```

- pickle模块：
  - pickle序列化是将对象按照一定的规则转换成为二进制保存，它不能跨平台传递数据。
  - pickle的序列化会将对象的所有数据都保存。



### 异常处理

程序在运行过程中，由于我们的编码不规范，或者其他原因一些客观原因，导致我们的程序无法继续运行，此时，程序就会出现异常。如果我们不对异常进行处理，程序可能会由于异常直接中断掉。为了保证程序的健壮性，我们在程序设计里提出了异常处理这个概念。

#### try...except语句

try...except语句可以对代码运行过程中可能出现的异常进行处理。 语法结构:

```python
try:
    可能会出现异常的代码块
except 异常的类型:
    出现异常以后的处理语句

```

示例：

```python
try:
    f = open('test.txt', 'r')
    print(f.read())
except FileNotFoundError:
    print('文件没有找到,请检查文件名称是否正确')
```



#### try...else语句

咱们应该对else并不陌生，在if中，它的作用是当条件不满足时执行的实行；同样在try...except...中也是如此，即如果没有捕获到异常，那么就执行else中的事情

```py
try: 
    num = 100 
    print(num) 
except NameError as errorMsg: 
    print('产生错误了:%s'%errorMsg) 
else: 
    print('没有捕获到异常，真高兴') 
    
'''
100
没有捕获到异常，真高兴
'''
```



#### try..finally语句

try...finally...语句用来表达这样的情况:

> 在程序中，如果一个段代码必须要执行，即无论异常是否产生都要执行，那么此时就需要使用finally。 比如文件关闭，释放锁，把数据库连接返还给连接池等。

```python
try:
    f = open('test.txt')
    try:
        while True:
            content = f.readline()
            if len(content) == 0:
                break
            print(content)
    except:
        #如果在读取文件的过程中，产生了异常，那么就会捕获到
        #比如 按下了 ctrl+c
        pass
    finally:
        f.close()
        print('关闭文件')
except:
    print("没有这个文件")
```

说明：

> 我们可以观察到KeyboardInterrupt异常被触发，程序退出。但是在程序退出之前，finally从句仍然被执行，把文件关闭。



### with关键字

对于系统资源如文件、数据库连接、socket 而言，应用程序打开这些资源并执行完业务逻辑之后，必须做的一件事就是要关闭（断开）该资源。

比如 Python 程序打开一个文件，往文件中写内容，写完之后，就要关闭该文件，否则会出现什么情况呢？极端情况下会出现 "Too many open files" 的错误，因为系统允许你打开的最大文件数量是有限的。

同样，对于数据库，如果连接数过多而没有及时关闭的话，就可能会出现 "Can not connect to MySQL server Too many connections"，因为数据库连接是一种非常昂贵的资源，不可能无限制的被创建。

来看看如何正确关闭一个文件。

- 普通版:

```python
def m1():
    f = open("output.txt", "w")
    f.write("python之禅")
    f.close()
```

这样写有一个潜在的问题，如果在调用 write 的过程中，出现了异常进而导致后续代码无法继续执行，close 方法无法被正常调用，因此资源就会一直被该程序占用者释放。那么该如何改进代码呢？

- 进阶版:

```python
def m2():
    f = open("output.txt", "w")
    try:
        f.write("python之禅")
    except IOError:
        print("oops error")
    finally:
        f.close()
```

改良版本的程序是对可能发生异常的代码处进行 try 捕获，使用 try/finally 语句，该语句表示如果在 try 代码块中程序出现了异常，后续代码就不再执行，而直接跳转到 except 代码块。而无论如何，finally 块的代码最终都会被执行。因此，只要把 close 放在 finally 代码中，文件就一定会关闭。

- 高级版:

```python
def m3():
    with open("output.txt", "r") as f:
        f.write("Python之禅")
```

一种更加简洁、优雅的方式就是用 with 关键字。open 方法的返回值赋值给变量 f，当离开 with 代码块的时候，系统会自动调用 f.close() 方法， with 的作用和使用 try/finally 语句是一样的。



### 上下文管理器

with语句实质上是一个上下文管理器，with语句后的对象都会有`__enter__()`和`__exit__()`方法。在进入到上下文时，会自动调用`__enter__()`方法，程序正常执行完成，或者出现异常中断的时候，都会调用`__exit__()`方法。

```python
class MyContext(object):
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def __enter__(self):
        print('调用了enter方法')
        return self

    def test(self):
        1 / 0
        print(self.name + '调用了test方法')

    def __exit__(self, exc_type, exc_val, exc_tb):
        print('调用了exit方法')
        print(exc_type, exc_val, exc_tb)

with MyContext('zhangsan', 18) as context:
    context.test()
```



### 自定义异常

你可以用raise语句来引发一个异常。异常/错误对象必须有一个名字，且它们应是Error或Exception类的子类

下面是一个引发异常的例子:

```python
class ShortInputException(Exception):
    '''自定义的异常类'''
    def __init__(self, length, atleast):
        #super().__init__()
        self.length = length
        self.atleast = atleast

    def __str__(self):
        return '输入的长度是 %d,长度至少应是 %d'% (self.length, self.atleast))

def main():
    try:
        s = input('请输入 --> ')
        if len(s) < 3:
            # raise 引发一个自定义的异常
            raise ShortInputException(len(s), 3)
    except ShortInputException as result:  # x这个变量被绑定到了错误的实例
        print('ShortInputException:' % result)
    else:
        print('没有异常发生.')

main()
```

运行结果如下:

![img](file:///C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/Desktop/python%E5%88%9D%E5%85%A5%E9%97%A8%EF%BC%88b%E7%AB%99%EF%BC%89/Day13-%E6%96%87%E4%BB%B6%E6%93%8D%E4%BD%9C/03-%E7%AC%94%E8%AE%B0/imgs/%E8%87%AA%E5%AE%9A%E4%B9%89%E5%BC%82%E5%B8%B8.png)



### 迭代器

迭代是访问集合元素的一种方式。迭代器是一个可以记住遍历的位置的对象。迭代器对象从集合的第一个元素开始访问，直到所有的元素被访问完结束。迭代器只能往前不会后退。



#### 1. 可迭代对象

我们已经知道可以对list、tuple、str等类型的数据使用for...in...的循环语法从其中依次拿到数据进行使用，我们把这样的过程称为遍历，也叫**迭代**。

**但是，是否所有的数据类型都可以放到for...in...的语句中，然后让for...in...每次从中取出一条数据供我们使用，即供我们迭代吗？**

```python
>>> for i in 100:
...     print(i)
...
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: 'int' object is not iterable
>>>
# int整型不是iterable，即int整型不是可以迭代的
```

我们把可以通过for...in...这类语句迭代读取一条数据供我们使用的对象称之为可迭代对象(Iterable)。

#### 2. 判断对象是否可迭代

可以使用 isinstance() 判断一个对象是否是 Iterable 对象：

```python
In [50]: from collections import Iterable

In [51]: isinstance([], Iterable)
Out[51]: True

In [52]: isinstance({}, Iterable)
Out[52]: True

In [53]: isinstance('abc', Iterable)
Out[53]: True

In [54]: isinstance(mylist, Iterable)
Out[54]: False

In [55]: isinstance(100, Iterable)
Out[55]: False
```

#### 3. 可迭代对象的本质

我们分析对可迭代对象进行迭代使用的过程，发现每迭代一次（即在for...in...中每循环一次）都会返回对象中的下一条数据，一直向后读取数据直到迭代了所有数据后结束。那么，在这个过程中就应该有一个“人”去记录每次访问到了第几条数据，以便每次迭代都可以返回下一条数据。我们把这个能帮助我们进行数据迭代的“人”称为**迭代器(Iterator)**。

可迭代对象的本质就是可以向我们提供一个这样的中间“人”即迭代器帮助我们对其进行迭代遍历使用。

可迭代对象通过`__iter__`方法向我们提供一个迭代器，我们在迭代一个可迭代对象的时候，实际上就是先获取该对象提供的一个迭代器，然后通过这个迭代器来依次获取对象中的每一个数据.

那么也就是说，一个具备了`__iter__`方法的对象，就是一个可迭代对象。

```python
from collections.abc import Iterable
class Demo(object):
    def __init__(self, n):
        self.n = n
        self.current = 0
    def __iter__(self):
        pass

demo = Demo(10)
print(isinstance(demo, Iterable))  # True

for d in demo:   # 重写了 __iter__ 方法以后，demo就是一个一个可迭代对象了，可以放在for...in的后面
    print(d)

# 此时再使用for...in循环遍历，会提示 TypeError: iter() returned non-iterator of type 'NoneType'
# 这是因为，一个可迭代对象如果想要被for...in循环，它必须要有一个迭代器
```

#### 4. 迭代器Iterator

通过上面的分析，我们已经知道，迭代器是用来帮助我们记录每次迭代访问到的位置，当我们对迭代器使用next()函数的时候，迭代器会向我们返回它所记录位置的下一个位置的数据。实际上，在使用next()函数的时候，调用的就是迭代器对象的`__next__`方法（Python3中是对象的`__next__`方法，Python2中是对象的next()方法）。**所以，我们要想构造一个迭代器，就要实现它的\**next\**方法**。但这还不够，python要求迭代器本身也是可迭代的，所以我们还要为迭代器实现`__iter__`方法，而`__iter__`方法要返回一个迭代器，迭代器自身正是一个迭代器，所以迭代器的`__iter__`方法返回自身即可。

**一个实现了\**iter\**方法和\**next\**方法的对象，就是迭代器。**

```python
class MyIterator(object):
    def __init__(self, n):
        self.n = n
        self.current = 0

    # 自定义迭代器需要重写__iter__和__next__方法
    def __iter__(self):
        return self

    def __next__(self):
        if self.current < self.n:
            value = self.current
            self.current += 1
            return value
        else:
            raise StopIteration

my_it = MyIterator(10)

for i in my_it:    # 迭代器重写了__iter__方法，它本身也是一个可迭代对象
    print(i)
```

#### 5. 判断对象是否是迭代器

调用一个对象的`__iter__`方法，或者调用iter()内置函数，可以获取到一个可迭代对象的迭代器。

```python
names = ['hello', 'good', 'yes']
print(names.__iter__())  # 调用对象的__iter__()方法
print(iter(names))  # 调用iter()内置函数
```

可以使用 isinstance() 判断一个对象是否是 Iterator 对象：

```python
from collections.abc import Iterator
names = ['hello', 'good', 'yes']
print(isinstance(iter(names), Iterator))
```

#### 6. for...in...循环的本质

for **item** in **Iterable** 循环的本质就是先通过iter()函数获取可迭代对象Iterable的迭代器，然后对获取到的迭代器不断调用next()方法来获取下一个值并将其赋值给item，当遇到StopIteration的异常后循环结束。

#### 7. 迭代器的应用场景

我们发现迭代器最核心的功能就是可以通过next()函数的调用来返回下一个数据值。如果每次返回的数据值不是在一个已有的数据集合中读取的，而是通过程序按照一定的规律计算生成的，那么也就意味着可以不用再依赖一个已有的数据集合，也就是说不用再将所有要迭代的数据都一次性缓存下来供后续依次读取，这样可以节省大量的存储（内存）空间。

举个例子，比如，数学中有个著名的斐波拉契数列(Fibonacci)，数列中第一个数为0，第二个数为1，其后的每一个数都可由前两个数相加得到：

0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...

现在我们想要通过for...in...循环来遍历迭代斐波那契数列中的前n个数。那么这个斐波那契数列我们就可以用迭代器来实现，每次迭代都通过数学计算来生成下一个数。

```python
class FibIterator(object):
    """斐波那契数列迭代器"""
    def __init__(self, n):
        """
        :param n: int, 指明生成数列的前n个数
        """
        self.n = n
        # current用来保存当前生成到数列中的第几个数了
        self.current = 0
        # num1用来保存前前一个数，初始值为数列中的第一个数0
        self.num1 = 0
        # num2用来保存前一个数，初始值为数列中的第二个数1
        self.num2 = 1

    def __next__(self):
        """被next()函数调用来获取下一个数"""
        if self.current < self.n:
            num = self.num1
            self.num1, self.num2 = self.num2, self.num1+self.num2
            self.current += 1
            return num
        else:
            raise StopIteration

    def __iter__(self):
        """迭代器的__iter__返回自身即可"""
        return self


if __name__ == '__main__':
    fib = FibIterator(10)
    for num in fib:
        print(num, end=" ")
```



### 生成器

利用迭代器，我们可以在每次迭代获取数据（通过next()方法）时按照特定的规律进行生成。但是我们在实现一个迭代器时，关于当前迭代到的状态需要我们自己记录，进而才能根据当前状态生成下一个数据。为了达到记录当前状态，并配合next()函数进行迭代使用，我们可以采用更简便的语法，即**生成器(generator)。生成器是一类特殊的迭代器**。

#### 创建生成器方法1

要创建一个生成器，有很多种方法。第一种方法很简单，只要把一个列表生成式的 [ ] 改成 ( )

```python
In [15]: L = [ x*2 for x in range(5)]

In [16]: L
Out[16]: [0, 2, 4, 6, 8]

In [17]: G = ( x*2 for x in range(5))

In [18]: G
Out[18]: <generator object <genexpr> at 0x7f626c132db0>

In [19]:
```

创建 L 和 G 的区别仅在于最外层的 [ ] 和 ( ) ， L 是一个列表，而 G 是一个生成器。我们可以直接打印出列表L的每一个元素，而对于生成器G，我们可以按照迭代器的使用方法来使用，即可以通过next()函数、for循环、list()等方法使用。

```python
In [19]: next(G)
Out[19]: 0

In [20]: next(G)
Out[20]: 2

In [21]: next(G)
Out[21]: 4

In [22]: next(G)
Out[22]: 6

In [23]: next(G)
Out[23]: 8

In [24]: next(G)
---------------------------------------------------------------------------
StopIteration                             Traceback (most recent call last)
<ipython-input-24-380e167d6934> in <module>()
----> 1 next(G)

StopIteration:

In [25]:
In [26]: G = ( x*2 for x in range(5))

In [27]: for x in G:
   ....:     print(x)
   ....:     
0
2
4
6
8

In [28]:
```

#### 创建生成器方法2

generator非常强大。如果推算的算法比较复杂，用类似列表生成式的 for 循环无法实现的时候，还可以用函数来实现。

我们仍然用上一节提到的斐波那契数列来举例，回想我们在上一节用迭代器的实现方式：

```python
class FibIterator(object):
    """斐波那契数列迭代器"""
    def __init__(self, n):
        """
        :param n: int, 指明生成数列的前n个数
        """
        self.n = n
        # current用来保存当前生成到数列中的第几个数了
        self.current = 0
        # num1用来保存前前一个数，初始值为数列中的第一个数0
        self.num1 = 0
        # num2用来保存前一个数，初始值为数列中的第二个数1
        self.num2 = 1

    def __next__(self):
        """被next()函数调用来获取下一个数"""
        if self.current < self.n:
            num = self.num1
            self.num1, self.num2 = self.num2, self.num1+self.num2
            self.current += 1
            return num
        else:
            raise StopIteration

    def __iter__(self):
        """迭代器的__iter__返回自身即可"""
        return self
```

注意，在用迭代器实现的方式中，我们要借助几个变量(n、current、num1、num2)来保存迭代的状态。现在我们用生成器来实现一下。

```python
In [30]: def fib(n):
   ....:     current = 0
   ....:     num1, num2 = 0, 1
   ....:     while current < n:
   ....:         yield num1
   ....:         num1, num2 = num2, num1+num2
   ....:         current += 1
   ....:     return 'done'
   ....:

In [31]: F = fib(5)

In [32]: next(F)
Out[32]: 1

In [33]: next(F)
Out[33]: 1

In [34]: next(F)
Out[34]: 2

In [35]: next(F)
Out[35]: 3

In [36]: next(F)
Out[36]: 5

In [37]: next(F)
---------------------------------------------------------------------------
StopIteration                             Traceback (most recent call last)
<ipython-input-37-8c2b02b4361a> in <module>()
----> 1 next(F)

StopIteration: done
```

在使用生成器实现的方式中，我们将原本在迭代器`__next__`方法中实现的基本逻辑放到一个函数中来实现，但是将每次迭代返回数值的return换成了yield，此时新定义的函数便不再是函数，而是一个**生成器**了。简单来说：**只要在def中有yield关键字的 就称为 生成器**

此时按照调用函数的方式( 案例中为F = fib(5) )使用生成器就不再是执行函数体了，而是会返回一个生成器对象（ 案例中为F ），然后就可以按照使用迭代器的方式来使用生成器了。

```python
In [38]: for n in fib(5):
   ....:     print(n)
   ....:     
1
1
2
3
5

In [39]:
```

但是用for循环调用generator时，发现拿不到generator的return语句的返回值。如果想要拿到返回值，必须捕获StopIteration错误，返回值包含在StopIteration的value中：

```python
In [39]: g = fib(5)

In [40]: while True:
   ....:     try:
   ....:         x = next(g)
   ....:         print("value:%d"%x)      
   ....:     except StopIteration as e:
   ....:         print("生成器返回值:%s"%e.value)
   ....:         break
   ....:     
value:1
value:1
value:2
value:3
value:5
生成器返回值:done

In [41]:
```

**总结**

- 使用了yield关键字的函数不再是函数，而是生成器。（使用了yield的函数就是生成器）
- yield关键字有两点作用：
  - 保存当前运行状态（断点），然后暂停执行，即将生成器（函数）挂起
  - 将yield关键字后面表达式的值作为返回值返回，此时可以理解为起到了return的作用
- 可以使用next()函数让生成器从断点处继续执行，即唤醒生成器（函数）
- Python3中的生成器可以使用return返回最终运行的返回值，而Python2中的生成器不允许使用return返回一个返回值（即可以使用return从生成器中退出，但return后不能有任何表达式）。

###  使用send唤醒

我们除了可以使用next()函数来唤醒生成器继续执行外，还可以使用send()函数来唤醒执行。使用send()函数的一个好处是可以在唤醒的同时向断点处传入一个附加数据。

例子：执行到yield时，gen函数作用暂时保存，返回i的值; temp接收下次c.send("python")，send发送过来的值，c.next()等价c.send(None)

```python
In [10]: def gen():
   ....:     i = 0
   ....:     while i<5:
   ....:         temp = yield i
   ....:         print(temp)
   ....:         i+=1
   ....:
```

#### 使用send

```python
In [43]: f = gen()

In [44]: next(f)
Out[44]: 0

In [45]: f.send('haha')
haha
Out[45]: 1

In [46]: next(f)
None
Out[46]: 2

In [47]: f.send('haha')
haha
Out[47]: 3

In [48]:
```

#### 使用next函数

```python
In [11]: f = gen()

In [12]: next(f)
Out[12]: 0

In [13]: next(f)
None
Out[13]: 1

In [14]: next(f)
None
Out[14]: 2

In [15]: next(f)
None
Out[15]: 3

In [16]: next(f)
None
Out[16]: 4

In [17]: next(f)
None
---------------------------------------------------------------------------
StopIteration                             Traceback (most recent call last)
<ipython-input-17-468f0afdf1b9> in <module>()
----> 1 next(f)

StopIteration:
```

#### 使用`__next__()`方法

（不常使用）

```python
In [18]: f = gen()

In [19]: f.__next__()
Out[19]: 0

In [20]: f.__next__()
None
Out[20]: 1

In [21]: f.__next__()
None
Out[21]: 2

In [22]: f.__next__()
None
Out[22]: 3

In [23]: f.__next__()
None
Out[23]: 4

In [24]: f.__next__()
None
---------------------------------------------------------------------------
StopIteration                             Traceback (most recent call last)
<ipython-input-24-39ec527346a9> in <module>()
----> 1 f.__next__()

StopIteration:
```



### property属性

property属性是一种用起来像是实例属性一样的特殊属性，可以对应于某个方法。

```python
class Foo:
    def func(self):
        pass

    # 定义property属性
    @property
    def prop(self):
        pass

# ############### 调用 ###############
foo_obj = Foo()
foo_obj.func()  # 调用实例方法
foo_obj.prop  # 调用property属性
```

**property属性的定义和调用要注意一下几点：**

- 定义时，在实例方法的基础上添加 @property 装饰器；并且仅有一个self参数

- 调用时，无需括号

  ```python
    方法：foo_obj.func()
    property属性：foo_obj.prop
  ```

**简单的实例**

> 对于京东商城中显示电脑主机的列表页面，每次请求不可能把数据库中的所有内容都显示到页面上，而是通过分页的功能局部显示，所以在向数据库中请求数据时就要显示的指定获取从第m条到第n条的所有数据 这个分页的功能包括：
>
> - 根据用户请求的当前页和总数据条数计算出 m 和 n
> - 根据m 和 n 去数据库中请求数据

```python
# ############### 定义 ###############
class Pager:
    def __init__(self, current_page):
        # 用户当前请求的页码（第一页、第二页...）
        self.current_page = current_page
        # 每页默认显示10条数据
        self.per_items = 10 

    @property
    def start(self):
        val = (self.current_page - 1) * self.per_items
        return val

    @property
    def end(self):
        val = self.current_page * self.per_items
        return val

# ############### 调用 ###############
p = Pager(1)
p.start  # 就是起始值，即：m
p.end  # 就是结束值，即：n
```

从上述可见

- Python的property属性的功能是：property属性内部进行一系列的逻辑计算，最终将计算结果返回。

#### property属性的两种方式

- 装饰器 即：在方法上应用装饰器
- 类属性 即：在类中定义值为property对象的类属性

#### 装饰器方式

在类的实例方法上应用@property装饰器

Python中的类有经典类和新式类，新式类的属性比经典类的属性丰富。（ 如果类继object，那么该类是新式类 ）

- 经典类的实现：

  ```python
  class Goods:
      @property
      def price(self):
          return "laowang"
  
  obj = Goods()
  result = obj.price  # 自动执行 @property 修饰的 price 方法，并获取方法的返回值
  print(result)
  ```

- 新式类的实现：

  ```python
  class Goods:
      """
      只有在python3中才有@xxx.setter  @xxx.deleter
      """
      def __init__(self):
          # 原价
          self.original_price = 100
          # 折扣
          self.discount = 0.8
  
      @property
      def price(self):
          new_price = self.original_price * self.discount
          return new_price
  
      @price.setter
      def price(self, value):
          self.original_price = value
  
      @price.deleter
      def price(self):
          del self.original_price
  obj = Goods()
  obj.price          # 获取商品价格
  obj.price = 200    # 修改商品原价
  del obj.price      # 删除商品原价
  ```

**总结：**

- 经典类中的属性只有一种访问方式，其对应被 @property 修饰的方法
- 新式类中的属性有三种访问方式，并分别对应了三个被@property、@方法名.setter、@方法名.deleter修饰的方法

#### 类属性方式

- 当使用类属性的方式创建property属性时，经典类和新式类无区别。

  ```python
  class Foo:
      def get_bar(self):
          return 'laowang'
      BAR = property(get_bar)
  
  obj = Foo()
  reuslt = obj.BAR  # 自动调用get_bar方法，并获取方法的返回值
  print(reuslt)
  Copy
  ```

  property方法中有个四个参数

  - 第一个参数是方法名，调用 对象.属性 时自动触发执行方法
  - 第二个参数是方法名，调用 对象.属性 ＝ XXX 时自动触发执行方法
  - 第三个参数是方法名，调用 del 对象.属性 时自动触发执行方法
  - 第四个参数是字符串，调用 对象.属性.**doc** ，此参数是该属性的描述信息

```python
class Foo(object):
    def get_bar(self):
        print("getter...")
        return 'laowang'

    def set_bar(self, value): 
        """必须两个参数"""
        print("setter...")
        return 'set value' + value

    def del_bar(self):
        print("deleter...")
        return 'laowang'

    BAR = property(get_bar, set_bar, del_bar, "description...")

obj = Foo()

obj.BAR  # 自动调用第一个参数中定义的方法：get_bar
obj.BAR = "alex"  # 自动调用第二个参数中定义的方法：set_bar方法，并将“alex”当作参数传入
desc = Foo.BAR.__doc__  # 自动获取第四个参数中设置的值：description...
print(desc)
del obj.BAR  # 自动调用第三个参数中定义的方法：del_bar方法
Copy
```

**总结：**

- 定义property属性共有两种方式，分别是【装饰器】和【类属性】，而【装饰器】方式针对经典类和新式类又有所不同。
- 通过使用property属性，能够简化调用者在获取数据的流程。



### 正则表达式

正则表达式是一个特殊的字符序列，计算机科学的一个概念。通常被用来检索、替换那些符合某个模式(规则)的文本。

许多程序设计语言都支持利用正则表达式进行字符串操作。在Python中需要通过正则表达式对字符串进行匹配的时候，可以使用re模块。re 模块使 Python 语言拥有全部的正则表达式功能。



**特点：**

1. 灵活性、逻辑性和功能性非常强；
2. 可以迅速地用极简单的方式达到字符串的复杂控制。
3. 对于刚接触的人来说，比较晦涩难懂。

#### Python中的正则表达式

与大多数编程语言相同，正则表达式里也使用`\`作为转义字符，这就可能造成反斜杠困扰。假如你需要匹配文本中的字符`\`，那么使用编程语言表示的正则表达式里将需要4个反斜杠`\`：前两个和后两个分别用于在编程语言里转义成反斜杠，转换成两个反斜杠后再在正则表达式里转义成一个反斜杠。

```python
print(re.match('\\\\', '\hello'))  # 需要使用四个反斜杠来匹配一个 \
```

Python里的原生字符串很好地解决了这个问题，有了原生字符串，你再也不用担心是不是漏写了反斜杠，写出来的表达式也更直观。在Python 字符串前面添加`r`即可将字符串转换成为原生字符串。

```python
print(re.match(r'\\', '\hello')) # 使用两个反斜杠即可匹配一个 \
```



### 正则查找

#### 查找方法的使用

在Python中的查找匹配方法，常见的有下面四种，他们的用法大致相同，但是匹配出的结果却不同。

- match方法(只匹配字符串开头)
- search方法(扫描整个字符串，找到第一个匹配)
- findall方法(扫描整个字符串，找到所有的匹配)
- finditer方法(扫描整个字符串，找到所有的匹配，并返回一个可迭代对象)

#### match方法的使用

re.match尝试从字符串的起始位置匹配一个模式，如果不是起始位置匹配成功的话，match()就返回none。

函数语法:

```python
re.match(pattern,string,flags=0)
```

| 参数    | 描述                                                         |
| :------ | :----------------------------------------------------------- |
| pattern | 匹配的正则表达式                                             |
| string  | 要匹配的字符串。                                             |
| flags   | 标志位，用于控制正则表达式的匹配方式，如：是否区分大小写，多行匹配等等。 |

我们可以使用group(num)函数来获取匹配表达式。

```python
import re
result1 = re.match(r'H','Hello')
result2 = re.match(r'e','Hello')
print(result1.group(0)) # 'H' 匹配到的元素
print(result1.span()) # (0,1) 匹配到的元素所在位置
print(result2)  # None
Copy
```

#### search方法的使用

re.search 扫描整个字符串并返回第一个成功的匹配。

函数语法：

```python
re.search(pattern, string, flags=0)
```

示例:

```python
import re
result1 = re.search(r'He','Hello')
result2 = re.search(r'lo','Hello')

print(result1.group(0))  # He
print(result1.span()) # (0,2)
print(result2.group(0)) # lo
print(result2.span()) # (3,5)
Copy
```

#### re.match与re.search的区别

re.match只匹配字符串的开始，如果字符串开始不符合正则表达式，则匹配失败，函数返回None；而re.search匹配整个字符串，直到找到一个匹配。

示例:

```python
result1 = re.search(r'天气','今天天气不错哟')
result2 = re.match(r'天气','今天天气不错哟')
print(result1)  # <re.Match object; span=(2, 4), match='天气'>
print(result2) # None
Copy
```

#### findall 方法的使用

在字符串中找到正则表达式所匹配的所有子串，并返回一个列表，如果没有找到匹配的，则返回空列表。

**注意：** match 和 search 是匹配一次 findall 匹配所有。

语法格式：

```python
re.findall(pattern,string,flags=0)
```

示例代码：

```python
ret = re.findall(r'\d+','he23ll34')
print(ret)  # ['23', '34']
ret = re.match(r'\d+','he23ll34') 
print(ret) # None match只匹配开头，所以匹配到
ret = re.search(r'\d+','he23ll34')
print(ret) # <re.Match object; span=(2, 4), match='23'> search 只能匹配到一个数字
```

- 注意事项:

  findall方法匹配时，如果匹配规则里有分组，则只匹配分组数据。

  ```python
  ret = re.findall(r'\w+@(qq|126|163)\.com','123@qq.com;aa@163.com;bb@126.com')
  print(ret)  # ['qq', '163', '126']  只匹配到了分组里的内容
  ```

  如果正则表达式里存在多个分组，则会把多个分组匹配成元组。

  ```python
  ret = re.findall(r'\w+@(qq|126|163)(\.com)','123@qq.com;aa@163.com;bb@126.com')
  print(ret) #[('qq', '.com'), ('163', '.com'), ('126', '.com')]
  ```

  如果想要让findall匹配所有的内容，而不仅仅只是匹配正则表达式里的分组，可以使用 `?:`来将分组标记为非捕获分组。

  ```python
  ret = re.findall(r'\w+@(?:qq|126|163)\.com','123@qq.com;aa@163.com;bb@126.com')
  print(ret) # ['123@qq.com', 'aa@163.com', 'bb@126.com']
  ```

#### finditer方法的使用

和 findall 类似，在字符串中找到正则表达式所匹配的所有子串，并把它们作为一个迭代器返回。

```python
ret = re.finditer(r'\d+','he23ll34')  # 得到的结果是一个可迭代对象
for x in ret: # 遍历 ret 取出里面的每一项匹配
    print(x.group(), x.span()) # 匹配对象里的group保存了匹配的结果
```



### re.Match类介绍

当我们调用`re.match`方法、`re.search`方法，或者对`re.finditer`方法的结果进行迭代时，拿到的数据类型都是`re.Match`对象。

```python
x = re.match(r'h','hello')
y = re.search(r'e','hello')
z = re.finditer(r'l','hello')
print(type(x))  # <class 're.Match'>
print(type(y)) # <class 're.Match'>
for a in z:
    print(type(a)) # <class 're.Match'>
```

这个类里定义了相关的属性，可以直接让我们来使用。

| 属性和方法       | 说 明                                                        |
| ---------------- | ------------------------------------------------------------ |
| pos              | 搜索的开始位置                                               |
| endpos           | 搜索的结束位置                                               |
| string           | 搜索的字符串                                                 |
| re               | 当前使用的正则表达式的对象                                   |
| lastindex        | 最后匹配的组索引                                             |
| lastgroup        | 最后匹配的组名                                               |
| group(index=0)   | 某个分组的匹配结果。如果index等于0，便是匹配整个正则表达式   |
| groups()         | 所有分组的匹配结果，每个分组的结果组成一个列表返回           |
| groupdict()      | 返回组名作为key，每个分组的匹配结果座位value的字典           |
| start([group])   | 获取组的开始位置                                             |
| end([group])     | 获取组的结束位置                                             |
| span([group])    | 获取组的开始和结束位置                                       |
| expand(template) | 使用组的匹配结果来替换模板template中的内容，并把替换后的字符串返回 |

```python
ret = re.search(r'(abc)+', 'xxxabcabcabcdef')
print(ret.pos)  # 搜索开始的位置，默认是0
print(ret.endpos)  # 搜索结束的位置，默认是字符串的长度
print(ret.group(0)) # abcabcabc 匹配整个表达式
print(ret.group(1))  # abc 第一次匹配到的结果
print(ret.span()) # (3, 12) 开始和结束位置
print(ret.groups())  # 表示当正则表达式里有多个分组时，多个分组的匹配结果
```



### re.compile方法的使用

我们在使用正则表达式时，可以直接调用`re` 模块的 `match,search,findall`等方法，传入指定的正则表达式。同时，也可以调用re.compile方法，生成一个正则表达式对象，再调用这个正则表达式对象的相关方法实现匹配。

示例：

```python
re.match(r'h','hello')  # 可以使用re.match方法直接匹配
# 也可以调用re模块的compile方法，生成一个 Pattern 对象，再调用 Pattern 对象的 match方法
regex = re.compile(r'h')
regex.match('hello')

re.search(r'l','hello')
regex = re.compile(r'l')
regex.match('hello')

regex = re.compile(r'l')
regex.findall('hello')

regex = re.complie(r'l')
regex.finditer('hello')
```



### 正则修饰符

| 修饰符 | 描述                            |
| :----- | :------------------------------ |
| re.I   | 使匹配对大小写不敏感            |
| re.M   | 多行匹配，影响 ^ 和 $           |
| re.S   | 使 . 匹配包括换行在内的所有字符 |

示例：

```python
print(re.search(r'L','hello'))  # None
print(re.search(r'L', 'hello', re.I))  # 不区分大小写<re.Match object; span=(2, 3), match='l'>

# \w+$ 表示匹配以一个或者多个字母结尾
# re.M 可以进行多行匹配，每个换行都认为是一个结尾
print(re.findall(r'\w+$','i am boy\n you are girl\n he is man',re.M)) # ['boy', 'girl', 'man']
# 不实用re.M修饰符，只会匹配到最后的 man
print(re.findall(r'\w+$','i am boy\n you are girl\n he is man')) # ['man']

print(re.search(r'.','\n')) # None . 匹配除了 \n 以外的所有字符
print(re.search(r'.','\n',re.S)) # '\n'  匹配到了 \n
```



### 正则表达式模式

模式字符串使用特殊的语法来表示一个正则表达式：

1. 字母和数字表示他们自身，一个正则表达式模式中的字母和数字匹配同样的字符串。

   ```python
   re.search(r'H','Hello')  # 这里的 H 表示的就是字母 H 自身，代表有特殊含义
   ```

2. 多数字母和数字前加一个反斜杠时会拥有不同的含义。

   ```python
   ret = re.search(r'\d','he12ms90') # 这里的 \d 表示的是匹配数字
   ```

3. 标点符号只有被转义时才匹配自身，否则它们表示特殊的含义。

   ```python
   ret = re.search(r'.','hello') # 这里的 . 表示的是匹配任意字符
   ret = re.search(r'\.','he.llo')  # 这里的 \. 进行了转义，才表示标点符号自身。
   ```

4. 反斜杠本身需要使用反斜杠转义。由于正则表达式通常都包含反斜杠，所以你最好使用原始字符串来表示它们。模式元素(如 **r'\t'**，等价于`\\t` )匹配相应的特殊字符。

下表列出了正则表达式模式语法中的特殊元素，如果你使用模式的同时提供了可选的标志参数，某些模式元素的含义会改变。

#### 非打印字符

非打印字符也可以是正则表达式的组成部分。下表列出了表示非打印字符的转义序列：

| 字符 | 描述                                                         |
| :--- | :----------------------------------------------------------- |
| \cx  | 匹配由x指明的控制字符。例如， \cM 匹配一个 Control-M 或回车符。x 的值必须为 A-Z 或 a-z 之一。否则，将 c 视为一个原义的 'c' 字符。 |
| \f   | 匹配一个换页符。等价于 \x0c 和 \cL。                         |
| \n   | 匹配一个换行符。等价于 \x0a 和 \cJ。                         |
| \r   | 匹配一个回车符。等价于 \x0d 和 \cM。                         |
| \s   | 匹配任何空白字符，包括空格、制表符、换页符等等。等价于 [ \f\n\r\t\v]。注意 Unicode 正则表达式会匹配全角空格符。 |
| \S   | 匹配任何非空白字符。等价于 `[^ \f\n\r\t\v]`。                |
| \t   | 匹配一个制表符。等价于 \x09 和 \cI。                         |
| \v   | 匹配一个垂直制表符。等价于 \x0b 和 \cK。                     |

#### 特殊字符

所谓特殊字符，就是一些有特殊含义的字符。若要匹配这些特殊字符，必须首先使字符"转义"，即，将反斜杠字符`\` 放在它们前面。下表列出了正则表达式中的特殊字符：

| 特殊字符        | 描述                                                         |
| --------------- | :----------------------------------------------------------- |
| ( )             | 标记一个子表达式的开始和结束位置。子表达式可以获取供以后使用。要匹配这些字符，请使用 `\`( 和 `\`)。 |
| .               | 匹配除换行符 `\`n 之外的任何单字符。要匹配 . ，请使用 `\`. 。 |
| [               | 标记一个中括号表达式的开始。要匹配 [，请使用 `\`[。          |
| \               | 将下一个字符标记为或特殊字符、或原义字符、或向后引用、或八进制转义符。例如， 'n' 匹配字符 'n'。'\n' 匹配换行符， `\\` 匹配 `\`，而 `\(` 则匹配 ( 。 |
| {               | 标记限定符表达式的开始。要匹配 {，请使用 `\{`。              |
| \|              | 指明两项之间的一个选择。要匹配 \|，请使用 \|。               |
| \d              | 匹配一个数字字符。等价于 [0-9]。                             |
| [0-9]           | 匹配任何数字。等价于 `\d`                                    |
| \D              | 匹配一个非数字字符。等价于 `[^0-9]`。                        |
| [a-z]           | 匹配任何小写字母                                             |
| [A-Z]           | 匹配任何大写字母                                             |
| [a-zA-Z0-9]     | 匹配任何字母及数字。等价于`\w`                               |
| \w              | 匹配包括下划线的任何单词字符。等价于`[A-Za-z0-9_]`。         |
| \W              | 匹配任何非单词字符。等价于 `[^A-Za-z0-9_]`。                 |
| [\u4e00-\u9fa5] | 匹配纯中文                                                   |

#### 定位符

定位符使您能够将正则表达式固定到行首或行尾。它们还使您能够创建这样的正则表达式，这些正则表达式出现在一个单词内、在一个单词的开头或者一个单词的结尾。

定位符用来描述字符串或单词的边界，**^** 和 **$** 分别指字符串的开始与结束，**\b** 描述单词的前或后边界，**\B** 表示非单词边界。

正则表达式的定位符有：

| 特殊字符 | 描述                                                         |
| -------- | :----------------------------------------------------------- |
| ^        | 匹配输入字符串的开始位置，例如：^h匹配以h开头；在方括号表达式中时，它表示不接受该字符集合，例如`[^0-9]`匹配除了数字以外的数据。要匹配 ^ 字符本身，请使用 \^。 |
| $        | 匹配输入字符串的结尾位置。要匹配 `$` 字符本身，请使用 `\$`。 |
| \b       | 匹配一个单词边界，即字与空格间的位置。                       |
| \B       | 非单词边界匹配。                                             |

#### 限定符

限定符用来指定正则表达式的一个给定组件必须要出现多少次才能满足匹配。有 ***** 或 **+** 或 **?** 或 **{n}** 或 **{n,}** 或 **{n,m}** 共6种。

正则表达式的限定符有：

| 字符  | 描述                                                         |
| :---- | :----------------------------------------------------------- |
| *     | 匹配前面的子表达式零次或多次。例如，zo *能匹配 "z" 以及 "zoo"。* 等价于{0,}。 |
| +     | 匹配前面的子表达式一次或多次。例如，'zo+' 能匹配 "zo" 以及 "zoo"，但不能匹配 "z"。+ 等价于 {1,}。 |
| ?     | 匹配前面的子表达式零次或一次。例如，"do(es)?" 可以匹配 "do" 、 "does" 中的 "does" 、 "doxy" 中的 "do" 。? 等价于 {0,1}。 |
| {n}   | n 是一个非负整数。匹配确定的 n 次。例如，'o{2}' 不能匹配 "Bob" 中的 'o'，但是能匹配 "food" 中的两个 o。 |
| {n,}  | n 是一个非负整数。至少匹配n 次。例如，'o{2,}' 不能匹配 "Bob" 中的 'o'，但能匹配 "foooood" 中的所有 o。'o{1,}' 等价于 'o+'。'o{0,}' 则等价于 'o*'。 |
| {n,m} | m 和 n 均为非负整数，其中n <= m。最少匹配 n 次且最多匹配 m 次。例如，"o{1,3}" 将匹配 "fooooood" 中的前三个 o。'o{0,1}' 等价于 'o?'。请注意在逗号和两个数之间不能有空格。 |

**示例：**

```python
re.search(r'\s','大家好 我是 代码')  # 匹配所有的空字符
re.search(r'\S','大家') # 匹配所有的非空字符
re.search(r'\n','大家好\n我是代码') # 匹配换行
re.search(r'n$','hello python') # 匹配以 n 结尾
re.search(r'^h.+n$','hello python') # 匹配以 h 开头，中间出现一次或多次任意字符，并且以n结尾
re.search(r'^ha*','h')  # 匹配以 h 开头，a出现0次或者一次
```

**练习:**

1. 用户名匹配:由数字、大小写字母、下划线`_`和中横线`-`组成，长度为4到14位，并且不能以数字开头。

   ```python
   r'^\D[a-z0-9A-Z_\-]{3,13}', 'sH_8'
   ```

2. 匹配邮箱

   ```python
   r'^([A-Za-z0-9_\-\.])+@([A-Za-z0-9_\-\.])+\.([A-Za-z]{2,4})$
   ```

3. 匹配手机号

   ```python
   r'^((13[0-9])|(14[5|7])|(15([0-3]|[5-9]))|(18[0,5-9]))\d{8}$'
   ```

4. 匹配身份证号。

   ```python
   r'^[1-9]\d{5}(18|19|20|)\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{3}[0-9Xx]$'
   ```

5. 匹配URL地址

   ```python
   r'((ht|f)tps?):\/\/([\w\-]+(\.[\w\-]+)*\/)*[\w\-]+(\.[\w\-]+)*\/?(\?([\w\-\.,@?^=%&:\/~\+#]*)+)?'
   ```

6. 匹配QQ号

   ```python
   r'^[1-9][0-9]{4,10}$'
   ```

7. 匹配微信号

   ```python
   r'^[a-zA-Z]([-_a-zA-Z0-9]{5,19})+$'
   ```

8. 匹配车牌号

   ```python
   r'^[京津沪渝冀豫云辽黑湘皖鲁新苏浙赣鄂桂甘晋蒙陕吉闽贵粤青藏川宁琼使领A-Z]{1}[A-Z]{1}[A-Z0-9]{4}[A-Z0-9挂学
   ```



### 正则替换

Python中的re模块提供了re.sub用户替换字符串中的匹配项。

语法：

```python
re.sub(pattern,repl,string,count=0)
```

参数：

- pattern : 正则中的模式字符串。
- repl : 替换的字符串，也可为一个函数。
- string : 要被查找替换的原始字符串。
- count : 模式匹配后替换的最大次数，默认 0 表示替换所有的匹配。

```python
phone = "2004-959-559 # 这是一个电话号码"

# 删除注释
num = re.sub(r'#.*$', "", phone)
print ("电话号码 : ", num)

# 移除非数字的内容
num = re.sub(r'\D', "", phone)
print ("电话号码 : ", num)
```

repl可以使用一个字符串用来表示替换后的结果以外，还可以传入一个函数。

```python
def double(matched):
    test = int(matched.group('test'))
    return str(test * 2)


print(re.sub(r'(?P<test>\d+)', double, 'hello23hi34'))  # hello46hi68
```



### 贪婪和非贪婪模式

Python里数量词默认是贪婪的（在少数语言里也可能是默认非贪婪），总是尝试匹配尽可能多的字符；

非贪婪则相反，总是尝试匹配尽可能少的字符。

在`*,?,+,{m,n}`后面加上 `?`使贪婪变成非贪婪。

```python
>>> s="This is a number 234-235-22-423"
>>> r=re.match(".+(\d+-\d+-\d+-\d+)",s)
>>> r.group(1)
'4-235-22-423'
>>> r=re.match(".+?(\d+-\d+-\d+-\d+)",s)
>>> r.group(1)
'234-235-22-423'
>>>
```

正则表达式模式中使用到通配字，那它在从左到右的顺序求值时，会尽量“抓取”满足匹配最长字符串，在我们上面的例子里面，“.+”会从字符串的启始处抓取满足模式的最长字符，其中包括我们想得到的第一个整型字段的中的大部分，“\d+”只需一位字符就可以匹配，所以它匹配了数字“4”，而“.+”则匹配了从字符串起始到这个第一位数字4之前的所有字符。

```python
>>> re.match(r"aa(\d+)","aa2343ddd").group(1)
'2343'
>>> re.match(r"aa(\d+?)","aa2343ddd").group(1)
'2'
>>> re.match(r"aa(\d+)ddd","aa2343ddd").group(1) 
'2343'
>>> re.match(r"aa(\d+?)ddd","aa2343ddd").group(1)
'2343'
>>>
```



### 网络编程

#### 网络通信的概念

简单来说，网络是用物理链路将各个孤立的工作站或主机相连在一起，组成数据链路，从而达到资源共享和通信的目的。

使用网络的目的，就是为了联通多方然后进行通信，即把数据从一方传递给另外一方。

前面的学习编写的程序都是单机的，即不能和其他电脑上的程序进行通信。为了让在不同的电脑上运行的软件，之间能够互相传递数据，就需要借助网络的功能。

- 使用网络能够把多方链接在一起，然后可以进行数据传递
- 所谓的网络编程就是，让在不同的电脑上的软件能够进行数据传递，即进程之间的通信

![img](file:///C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/Desktop/python%E5%88%9D%E5%85%A5%E9%97%A8%EF%BC%88b%E7%AB%99%EF%BC%89/Day19-%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B/03-%E7%AC%94%E8%AE%B0/imgs/Snip20160901_55.png)

#### IP地址

生活中的地址指的就是，找到某人或某机关或与其通信的指定地点。在网络编程中，如果一台主机想和另一台主机进行沟通和共享数据，首先要做的第一件事情就是要找到对方。在互联网通信中，我们使用IP地址来查询到各个主机。

![img](file:///C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/Desktop/python%E5%88%9D%E5%85%A5%E9%97%A8%EF%BC%88b%E7%AB%99%EF%BC%89/Day19-%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B/03-%E7%AC%94%E8%AE%B0/imgs/Snip20160901_60.png)

**ip地址：用来在网络中标记一台电脑，比如192.168.1.1；在本地局域网上是唯一的。**

#### ip地址的分类

每一个IP地址包括两部分：网络地址和主机地址。IP地址通常由点分十进制(例如：192.168.1.1)的方式来表示,IP地址要和子网掩码(用来区分网络位和主机位)配合使用。

<img src="file:///C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/Desktop/python%E5%88%9D%E5%85%A5%E9%97%A8%EF%BC%88b%E7%AB%99%EF%BC%89/Day19-%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B/03-%E7%AC%94%E8%AE%B0/imgs/ip%E5%9C%B0%E5%9D%80.jpg" alt="img" style="zoom:80%;" />

##### A类地址

一个A类IP地址由1字节的网络地址和3字节主机地址组成，网络地址的最高位必须是“0”，

地址范围：1.0.0.1-126.255.255.254

子网掩码：255.0.0.0

二进制表示为：00000001 00000000 00000000 00000001 - 01111110 11111111 11111111 11111110

可用的A类网络有126个，每个网络能容纳1677214个主机

##### B类地址

一个B类IP地址由2个字节的网络地址和2个字节的主机地址组成，网络地址的最高位必须是“10”，

地址范围：128.1.0.1-191.255.255.254

子网掩码：255.255.0.0

二进制表示为：10000000 00000001 00000000 00000001 - 10111111 11111111 11111111 11111110

可用的B类网络有16384个，每个网络支持的最大主机数为256的2次方-2=65534台。

##### C类地址

一个C类IP地址由3字节的网络地址和1字节的主机地址组成，网络地址的最高位必须是“110”

范围：192.0.1.1-223.255.255.254

子网掩码：255.255.255.0

二进制表示为: 11000000 00000000 00000001 00000001 - 11011111 11111111 11111110 11111110

C类网络可达2097152个，每个网络支持的最大主机数为256-2=254台

##### D类地址

D类IP地址第一个字节以“1110”开始，它是一个专门保留的地址，并不指向特定的网络，目前这一类地址被用在多点广播（Multicast）中。

##### E类地址

以“1111”开始，为将来使用保留，仅作实验和开发用。

##### 私有地址

在这么多网络IP中，国际规定有一部分IP地址是用于我们的局域网使用，也就是属于私网IP，不在公网中使用的，它们的范围是：

```python
10.0.0.0～10.255.255.255
172.16.0.0～172.31.255.255
192.168.0.0～192.168.255.255
Copy
```

**注意事项：**

1. 每一个字节都为0的地址（“0.0.0.0”）对应于当前主机。
2. IP地址中的每一个字节都为1的IP地址（“255．255．255．255”）是当前子网的广播地址。
3. IP地址中凡是以“1111”开头的E类IP地址都保留用于将来和实验使用。
4. IP地址中不能以十进制“127”作为开头，该类地址中数字127．0．0．1到127．255．255．255用于回路测试，如：127.0.0.1可以代表本机IP地址，用 `http://127.0.0.1` 就可以测试本机中配置的Web服务器
5. 网络ID的第一个8位组也不能全置为“0”，全“0”表示本地网络。

#### 网络通信方式

##### 直接通信

<img src="file:///C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/Desktop/python%E5%88%9D%E5%85%A5%E9%97%A8%EF%BC%88b%E7%AB%99%EF%BC%89/Day19-%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B/03-%E7%AC%94%E8%AE%B0/imgs/QQ20170807-210222@2x.png" alt="img" style="zoom: 67%;" />

**说明**

> 1. 如果两台电脑之间通过网线连接是可以直接通信的，但是需要提前设置好ip地址以及网络掩码
> 2. 并且ip地址需要控制在同一网段内，例如 一台为`192.168.1.1`另一台为`192.168.1.2`则可以进行通信



##### 使用集线器通信

<img src="file:///C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/Desktop/python%E5%88%9D%E5%85%A5%E9%97%A8%EF%BC%88b%E7%AB%99%EF%BC%89/Day19-%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B/03-%E7%AC%94%E8%AE%B0/imgs/QQ20170807-210413@2x.png" alt="img" style="zoom: 50%;" />

**说明**

> 1. 当有多态电脑需要组成一个网时，那么可以通过集线器（Hub）将其链接在一起
> 2. 一般情况下集线器的接口较少
> 3. 集线器有个缺点，它以广播的方式进行发送任何数据，即如果集线器接收到来自A电脑的数据本来是想转发给B电脑，如果此时它还连接着另外两台电脑C、D，那么它会把这个数据给每个电脑都发送一份，因此会导致网络拥堵



##### 使用交换机通信

<img src="file:///C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/Desktop/python%E5%88%9D%E5%85%A5%E9%97%A8%EF%BC%88b%E7%AB%99%EF%BC%89/Day19-%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B/03-%E7%AC%94%E8%AE%B0/imgs/QQ20170807-211152@2x.png" alt="img" style="zoom:50%;" />

**说明**

> 1. 克服了集线器以广播发送数据的缺点，当需要广播的时候发送广播，当需要单播的时候又能够以单播的方式进行发送
> 2. 它已经替代了之前的集线器
> 3. 企业中就是用交换机来完成多态电脑设备的链接成网络的



##### 使用路由器连接多个网络

<img src="file:///C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/Desktop/python%E5%88%9D%E5%85%A5%E9%97%A8%EF%BC%88b%E7%AB%99%EF%BC%89/Day19-%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B/03-%E7%AC%94%E8%AE%B0/imgs/QQ20170807-211021@2x.png" alt="img" style="zoom:50%;" />

##### 复杂的通信过程

<img src="file:///C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/Desktop/python%E5%88%9D%E5%85%A5%E9%97%A8%EF%BC%88b%E7%AB%99%EF%BC%89/Day19-%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B/03-%E7%AC%94%E8%AE%B0/imgs/QQ20170807-212411@2x.png" alt="img" style="zoom: 33%;" />

**说明**

> 1. 在浏览器中输入一个网址时，需要将它先解析出ip地址来
> 2. 当得到ip地址之后，浏览器以tcp的方式3次握手链接服务器
> 3. 以tcp的方式发送http协议的请求数据 给 服务器
> 4. 服务器tcp的方式回应http协议的应答数据 给浏览器

**总结**

- MAC地址：在设备与设备之间数据通信时用来标记收发双方（网卡的序列号）
- IP地址：在逻辑上标记一台电脑，用来指引数据包的收发方向（相当于电脑的序列号）
- 网络掩码：用来区分ip地址的网络号和主机号
- 默认网关：当需要发送的数据包的目的ip不在本网段内时，就会发送给默认的一台电脑，成为网关
- 集线器：已过时，用来连接多态电脑，缺点：每次收发数据都进行广播，网络会变的拥堵
- 交换机：集线器的升级版，有学习功能知道需要发送给哪台设备，根据需要进行单播、广播
- 路由器：连接多个不同的网段，让他们之间可以进行收发数据，每次收到数据后，ip不变，但是MAC地址会变化
- DNS：用来解析出IP（类似电话簿）
- http服务器：提供浏览器能够访问到的数据



#### 端口

端口就像一个房子的门，是出入这间房子的必经之路。如果一个程序需要收发网络数据，那么就需要有这样的端口

在linux系统中，端口可以有65536（2的16次方）个之多！

既然有这么多，操作系统为了统一管理，所以进行了编号，这就是`端口号`

##### 端口号

端口是通过端口号来标记的，端口号只有整数，范围是从0到65535.端口号不是随意使用的，而是按照一定的规定进行分配。端口的分类标准有好几种，我们这里不做详细讲解，只介绍一下知名端口和动态端口。

##### 知名端口号

知名端口是众所周知的端口号，范围从0到1023,以理解为，一些常用的功能使用的号码是估计的，好比 电话号码110、10086、10010一样。一般情况下，如果一个程序需要使用知名端口的需要有root权限。

##### 动态端口号

动态端口的范围是从1024到65535

之所以称为动态端口，是因为它一般不固定分配某种服务，而是动态分配。

动态分配是指当一个系统程序或应用程序程序需要网络通信时，它向主机申请一个端口，主机从可用的端口号中分配一个供它使用。

当这个程序关闭时，同时也就释放了所占用的端口号。

##### 端口号作用

我们知道，一台拥有IP地址的主机可以提供许多服务，比如HTTP（万维网服务）、FTP（文件传输）、SMTP（电子邮件）等，这些服务完全可以通过1个IP地址来实现。那么，主机是怎样区分不同的网络服务呢？显然不能只靠IP地址，因为IP地址与网络服务的关系是一对多的关系。实际上是通过“IP地址+端口号”来区分不同的服务的。 需要注意的是，端口并不是一一对应的。比如你的电脑作为客户机访问一台WWW服务器时，WWW服务器使用“80”端口与你的电脑通信，但你的电脑则可能使用“3457”这样的端口。



## socket简介

#### 不同电脑上的进程之间如何通信

首要解决的问题是如何唯一标识一个进程，否则通信无从谈起！ 在1台电脑上可以通过进程号（PID）来唯一标识一个进程，但是在网络中这是行不通的。 其实TCP/IP协议族已经帮我们解决了这个问题，网络层的“ip地址”可以唯一标识网络中的主机，而传输层的“协议+端口”可以唯一标识主机中的应用进程（进程）。 这样利用ip地址，协议，端口就可以标识网络的进程了，网络中的进程通信就可以利用这个标志与其它进程进行交互。

**注意：**

> 所谓`进程`指的是：运行的程序以及运行时用到的资源这个整体称之为进程（在讲解多任务编程时进行详细讲解）
>
> 所谓`进程间通信`指的是：运行的程序之间的数据共享

#### 什么是socket

socket(简称 `套接字`) 是进程间通信的一种方式，它与其他进程间通信的一个主要不同是：

它能实现不同主机间的进程间通信，我们网络上各种各样的服务大多都是基于 Socket 来完成通信的

例如我们每天浏览网页、QQ 聊天、收发 email 等等。

#### 创建socket

在 Python 中 使用socket 模块的函数 socket 就可以完成：

```python
import socket
socket.socket(AddressFamily, Type)
Copy
```

**说明：**

函数 socket.socket 创建一个 socket，该函数带有两个参数：

- Address Family：可以选择 AF_INET（用于 Internet 进程间通信） 或者 AF_UNIX（用于同一台机器进程间通信）,实际工作中常用AF_INET
- Type：套接字类型，可以是 SOCK_STREAM（流式套接字，主要用于 TCP 协议）或者 SOCK_DGRAM（数据报套接字，主要用于 UDP 协议）

创建一个tcp socket（tcp套接字）

```python
import socket

# 创建tcp的套接字
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# ...这里是使用套接字的功能（省略）...

# 不用的时候，关闭套接字
s.close()
```

创建一个udp socket（udp套接字）

```python
import socket

# 创建udp的套接字
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# ...这里是使用套接字的功能（省略）...
# 不用的时候，关闭套接字
s.close()
```

**说明**

套接字使用流程 与 文件的使用流程很类似

1. 创建套接字
2. 使用套接字收/发数据
3. 关闭套接字

### UDP协议

UDP 是User Datagram Protocol的简称， 中文名是用户数据报协议。在通信开始之前，不需要建立相关的链接，只需要发送数据即可，类似于生活中，"写信"。

#### 模型

<img src="file:///C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/Desktop/python%E5%88%9D%E5%85%A5%E9%97%A8%EF%BC%88b%E7%AB%99%EF%BC%89/Day19-%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B/03-%E7%AC%94%E8%AE%B0/imgs/udpSocket.jpg" alt="img" style="zoom: 80%;" />



#### UDP网络程序-发送数据

创建一个基于udp的网络程序流程很简单，具体步骤如下：

1. 创建客户端套接字
2. 发送/接收数据
3. 关闭套接字

```python
import socket
# 1. 创建一个UDP的socket连接
udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# 2. 获取用户输入的内容
data = input('请输入内容')
# 3. 准备接收方的地址和端口号
addr = ('127.0.0.1', 8080)
# 4. 将用户的输入内容进行编码，并发送到指定地址和端口
udp_socket.sendto(data.encode('gbk'), addr)
# 5. 接收传递过来的消息，并指定接受的字节大小
recv_data = udp_socket.recvfrom(1024)
# 6. 接收到的对象是一个元组，元组里有两个元素
print(recv_data)
# 6.1 元组里的第一个数据显示接收到内容
print(recv_data[0].decode('gbk'))
# 6.2 元组里的第二个数据显示发送方的地址和端口号
print(recv_data[1])
# 7. 关闭socket连接
udp_socket.close()
```

#### UDP绑定信息

##### <1>. 绑定信息

一般情况下，在一台电脑上运行的网络程序有很多，为了不与其他的网络程序占用同一个端口号，往往在编程中，udp的端口号一般不绑定 但是如果需要做成一个服务器端的程序的话，是需要绑定的，想想看这又是为什么呢？ 如果报警电话每天都在变，想必世界就会乱了，所以一般服务性的程序，往往需要一个固定的端口号，这就是所谓的端口绑定。 ![img](../imgs/端口绑定.jpg)

##### <2>. 绑定示例

```python
from socket import *

# 1. 创建套接字
udp_socket = socket(AF_INET, SOCK_DGRAM)

# 2. 绑定本地的相关信息，如果一个网络程序不绑定，则系统会随机分配
local_addr = ('', 7788) #  ip地址和端口号，ip一般不用写，表示本机的任何一个ip
udp_socket.bind(local_addr)

# 3. 等待接收对方发送的数据
recv_data = udp_socket.recvfrom(1024) #  1024表示本次接收的最大字节数

# 4. 显示接收到的数据
print(recv_data[0].decode('gbk'))

# 5. 关闭套接字
udp_socket.close()
```

**总结**

- 一个udp网络程序，可以不绑定，此时操作系统会随机进行分配一个端口，如果重新运行此程序端口可能会发生变化
- 一个udp网络程序，也可以绑定信息（ip地址，端口号），如果绑定成功，那么操作系统用这个端口号来进行区别收到的网络数据是否是此进程的



### TCP协议

**TCP协议，传输控制协议（英语：Transmission Control Protocol，缩写为 TCP）**是一种面向连接的、可靠的、基于字节流的传输层通信协议，由IETF的RFC 793定义。

TCP通信需要经过**创建连接、数据传送、终止连接**三个步骤。

TCP通信模型中，在通信开始之前，一定要先建立相关的链接，才能发送数据，类似于生活中，"打电话"。

#### TCP特点

##### 1. 面向连接

通信双方必须先建立连接才能进行数据的传输，双方都必须为该连接分配必要的系统内核资源，以管理连接的状态和连接上的传输。

双方间的数据传输都可以通过这一个连接进行。

完成数据交换后，双方必须断开此连接，以释放系统资源。

这种连接是一对一的，因此TCP不适用于广播的应用程序，基于广播的应用程序请使用UDP协议。

##### 2. 可靠传输

1）**TCP采用发送应答机制**

TCP发送的每个报文段都必须得到接收方的应答才认为这个TCP报文段传输成功

2）**超时重传**

发送端发出一个报文段之后就启动定时器，如果在定时时间内没有收到应答就重新发送这个报文段。

TCP为了保证不发生丢包，就给每个包一个序号，同时序号也保证了传送到接收端实体的包的按序接收。然后接收端实体对已成功收到的包发回一个相应的确认（ACK）；如果发送端实体在合理的往返时延（RTT）内未收到确认，那么对应的数据包就被假设为已丢失将会被进行重传。

3）**错误校验**

TCP用一个校验和函数来检验数据是否有错误；在发送和接收时都要计算校验和。

4） **流量控制和阻塞管理**

流量控制用来避免主机发送得过快而使接收方来不及完全收下。

##### 3. TCP与UDP的区别

- 面向连接（确认有创建三方交握，连接已创建才作传输。）
- 有序数据传输
- 重发丢失的数据包
- 舍弃重复的数据包
- 无差错的数据传输
- 阻塞/流量控制

#### TCP通信模型

TCP通信模型中，在通信开始之前，一定要先建立相关的链接，才能发送数据

<img src="file:///C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/Desktop/python%E5%88%9D%E5%85%A5%E9%97%A8%EF%BC%88b%E7%AB%99%EF%BC%89/Day19-%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B/03-%E7%AC%94%E8%AE%B0/imgs/TCP%E9%80%9A%E4%BF%A1%E6%A8%A1%E5%9E%8B.png" alt="img" style="zoom:80%;" />

#### 服务区与客户端

服务器，也称伺服器，是提供计算服务的设备。由于服务器需要响应服务请求，并进行处理，因此一般来说服务器应具备承担服务并且保障服务的能力。 客户端（Client）也被称为用户端，是指与服务器相对应，为客户提供本地服务的程序。 客户端服务器架构又被称为主从式架构，简称C/S结构，是一种网络架构，它把客户端与服务器分开来，一个客户端软件的实例都可以向一个服务器或应用程序服务器发出请求。



#### TCP客户端

相比较于TCP服务端，tcp的客户端要简单很多，如果说服务器端是需要自己买手机、查手机卡、设置铃声、等待别人打电话流程的话，那么客户端就只需要找一个电话亭，拿起电话拨打即可，流程要少很多。

示例代码:

```python
from socket import *

# 创建socket
tcp_client_socket = socket(AF_INET, SOCK_STREAM)

# 目的信息
server_ip = input("请输入服务器ip:")
server_port = int(input("请输入服务器port:"))

# 链接服务器
tcp_client_socket.connect((server_ip, server_port))

# 提示用户输入数据
send_data = input("请输入要发送的数据：")
tcp_client_socket.send(send_data.encode("gbk"))

# 接收对方发送过来的数据，最大接收1024个字节
recvData = tcp_client_socket.recv(1024)
print('接收到的数据为:', recvData.decode('gbk'))

# 关闭套接字
tcp_client_socket.close()
```



#### TCP服务端

在程序中，如果想要完成一个tcp服务器的功能，需要的流程如下：

1. socket创建一个套接字
2. bind绑定ip和port
3. listen使套接字变为可以被动链接
4. accept等待客户端的链接
5. recv/send接收发送数据

示例代码：

```python
from socket import *

# 创建socket
tcp_server_socket = socket(AF_INET, SOCK_STREAM)

# 本地信息
address = ('', 7788)

# 绑定
tcp_server_socket.bind(address)

# 使用socket创建的套接字默认的属性是主动的，使用listen将其变为被动的，这样就可以接收别人的链接了
tcp_server_socket.listen(128)

# 如果有新的客户端来链接服务器，那么就产生一个新的套接字专门为这个客户端服务
# client_socket用来为这个客户端服务
# tcp_server_socket就可以省下来专门等待其他新客户端的链接
client_socket, clientAddr = tcp_server_socket.accept()

# 接收对方发送过来的数据
recv_data = client_socket.recv(1024)  # 接收1024个字节
print('接收到的数据为:', recv_data.decode('gbk'))

# 发送一些数据到客户端
client_socket.send("thank you !".encode('gbk'))

# 关闭为这个客户端服务的套接字，只要关闭了，就意味着为不能再为这个客户端服务了，如果还需要服务，只能再次重新连接
client_socket.close()
```

**TCP注意事项**

1. tcp服务器一般情况下都需要绑定，否则客户端找不到这个服务器
2. tcp客户端一般不绑定，因为是主动链接服务器，所以只要确定好服务器的ip、port等信息就好，本地客户端可以随机
3. tcp服务器中通过listen可以将socket创建出来的主动套接字变为被动的，这是做tcp服务器时必须要做的
4. 当客户端需要链接服务器时，就需要使用connect进行链接，udp是不需要链接的而是直接发送，但是tcp必须先链接，只有链接成功才能通信
5. 当一个tcp客户端连接服务器时，服务器端会有1个新的套接字，这个套接字用来标记这个客户端，单独为这个客户端服务
6. listen后的套接字是被动套接字，用来接收新的客户端的链接请求的，而accept返回的新套接字是标记这个新客户端的
7. 关闭listen后的套接字意味着被动套接字关闭了，会导致新的客户端不能够链接服务器，但是之前已经链接成功的客户端正常通信。
8. 关闭accept返回的套接字意味着这个客户端已经服务完毕
9. 当客户端的套接字调用close后，服务器端会recv解堵塞，并且返回的长度为0，因此服务器可以通过返回数据的长度来区别客户端是否已经下线



#### 文件下载案例

TCP服务器端：

```python
from socket import *


def get_file_content(file_name):
    """获取文件的内容"""
    try:
        with open(file_name, "rb") as f:
            content = f.read()
        return content
    except:
        print("没有下载的文件:%s" % file_name)


def main():
    # 创建socket
    tcp_server_socket = socket(AF_INET, SOCK_STREAM)
    # 本地信息
    address = ('', 7890)
    # 绑定本地信息
    tcp_server_socket.bind(address)
    # 将主动套接字变为被动套接字
    tcp_server_socket.listen(128)

    while True:
        # 等待客户端的链接，即为这个客户端发送文件
        client_socket, clientAddr = tcp_server_socket.accept()
        # 接收对方发送过来的数据
        recv_data = client_socket.recv(1024)  # 接收1024个字节
        file_name = recv_data.decode("utf-8")
        print("对方请求下载的文件名为:%s" % file_name)
        file_content = get_file_content(file_name)
        # 发送文件的数据给客户端
        # 因为获取打开文件时是以rb方式打开，所以file_content中的数据已经是二进制的格式，因此不需要encode编码
        if file_content:
            client_socket.send(file_content)
        # 关闭这个套接字
        client_socket.close()

    # 关闭监听套接字
    tcp_server_socket.close()
if __name__ == '__main__':
    main()
Copy
```

TCP客户端：

```python
from socket import *
def main():

    # 创建socket
    tcp_client_socket = socket(AF_INET, SOCK_STREAM)

    # 目的信息
    server_ip = input("请输入服务器ip:")
    server_port = int(input("请输入服务器port:"))

    # 链接服务器
    tcp_client_socket.connect((server_ip, server_port))

    # 输入需要下载的文件名
    file_name = input("请输入要下载的文件名：")

    # 发送文件下载请求
    tcp_client_socket.send(file_name.encode("utf-8"))

    # 接收对方发送过来的数据，最大接收1024个字节（1K）
    recv_data = tcp_client_socket.recv(1024)
    # print('接收到的数据为:', recv_data.decode('utf-8'))
    # 如果接收到数据再创建文件，否则不创建
    if recv_data:
        with open("[接收]"+file_name, "wb") as f:
            f.write(recv_data)

    # 关闭套接字
    tcp_client_socket.close()


if __name__ == "__main__":
    main()
```
