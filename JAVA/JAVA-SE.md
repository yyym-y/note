# JAVA 快速手册



## 基本说明

在定义变量以及运算符使用优先级、注释、类型转换循环、条件等等与 C / C++一致，可以按照 C / C++ 习惯直接使用

值得注意的一点 : 

JAVA 的 float 类型是直接使用 double 类型的，不用强转， 如果非要用 float， 则需 `float a = 1.00f;`



##  数组的声明与使用

**PS：数组的使用与 C / C++ 一致，都是通过下标[]访问**



> 声明：一共有三种声明方式

```java
// 先声明再分配内存
int arr[];
arr = new int[10];
//声明后立马分配内存，推荐使用？
int arr2[] = new int[10];
int[] arr3 = new int[10];  // 工程上更推荐这个方法

/*同理二维数组 -> n 维数组*/

int[][] arr4 = new int[2][4]
```



> 初始化

```java
// 一维数组
int[] arr = new int[]{1,2,3,4,5};
int[] arr2 = {1,2,3,4,50};
// 二维数组
int[][] arr3 = {{1,2,3}, {1,2,3,4}, {1,2,3,4,5}};
int[][] arr4 = {{1,2,3}, new int[5], new int[10]};
```



> 常用方法
>
> > `arr.length`	获取数组长度
>
> > `Arrays.fill(int[] a, int value)` 		`Arrays.fill(int[] a, int Begin, int End, int value)`
> >
> > 主要功能类比为 C/C++的 memset函数，主要是实现将一段赋成同一个值,  注意范围是 $[\mathrm{Begin} , \mathrm{End})$
> >
> > ```java
> > int[] arr = new int[10];
> > Arrays.fill(arr,1);
> > Arrays.fill(arr, 3, 6, 2);
> > for(int i = 0 ; i < arr.length ; i++)
> >     System.out.print(arr[i] + " ");
> > 
> > //1 1 1 2 2 2 1 1 1 1 
> > ```
>
> > `Arrays.sort(int[] a)` 排序
>
> > `Arrays.copyOf(int[] arr, int newLength)`
> >
> > Arrays的copyOf()方法传回的数组是**新的数组对象**，改变传回数组中的元素值，不会影响原来的数组。
> >
> > copyOf()的第二个自变量指定要建立的**新数组长度**，如果新数组的长度**超过**原数组的长度，则**保留**数组默认,即 $0$
> >
> > ```java
> > int[] arr1 = {1, 2, 3, 4, 5}; 
> > int[] arr2 = Arrays.copyOf(arr1, 5);
> > int[] arr3 = Arrays.copyOf(arr1, 10);
> > for(int i = 0; i < arr2.length; i++) 
> >     System.out.print(arr2[i] + " "); 
> > System.out.println();
> > for(int i = 0; i < arr3.length; i++) 
> >     System.out.print(arr3[i] + " ");
> > /*
> > 1 2 3 4 5 
> > 1 2 3 4 5 0 0 0 0 0
> > */
> > ```
>
> > `Arrays.copyOfRange(int[] arr, int Begin, int End)`
> >
> > 同理 $\mathrm{Begin}$ 必须在数组范围内，$\mathrm{End}$ 可以超出范围，超出用 $0$ 填充
>
> > `Arrays.binarySearch(int[] a, int key)`   /    `Arrays.binarySearch(int[] a, int Begin, int End, int key)`
> >
> > 二分搜索



## 面向对象编程

### 成员方法

当成 C / C++ 的函数来看待即可

基本的定义方法为：

```java
权限修饰符 返回值类型 方法名(参数类型 参数名....){
    ....
    //return ~
}
//举例
public class Main {
    public static void Test(int num){
        System.out.print(num + " ");
        System.out.println("and Hello world!");
    }
    public static void main(String[] args) {
        Test(10);
    }
}
```

**注意，静态方法只能操作静态方法**



> `this`  与 C++ 一致



### 构造函数

```java
public class Learn {
    int learnTime;
    public Learn(int learnTime){
        this.learnTime = learnTime;
    }
    public Learn(){
        this(10); // 可以在无参构造函数里面调用有参构造函数
    }

    public static void main(String[] args){
        Learn yyym = new Learn();
        System.out.println(yyym.learnTime + "学时");
        Learn lr580 = new Learn(100);
        System.out.println(lr580.learnTime + "学时");
    }
}
```



> 对于对象的基本操作与 C++ 一致



### 对象的销毁

将对象设为 `null` 即可销毁

```java
public static void main(String[] args){
    Learn yyym = new Learn();
    yyym = null; // 销毁
}
```



### 继承

**JAVA只支持单继承，不支持多继承**

```java
class Animal {
    public int eyeNum, mouth;
}
class Dog extends Animal{}
class Wang extends Animal{}
```



### Object 类

Java中绝大部分类都可以溯源到 Object 类，所以 Object 的常用方法要掌握

> `getClass()`

```Java
public static void main(String[] args) {
    Learn yyym = new Learn(100);
    System.out.println(yyym.getClass());
    System.out.println(yyym.getClass().getName()); // 此时返回的已经是String的形式了
}
/*
class Learn
Learn
*/
```



> `toString()`

可以重写，使用时通常重写

```java
public static void main(String[] args) {
    Learn yyym = new Learn(100);
    System.out.println(yyym.toString());
}
// Learn@b4c966a
```



> `equals()`

比较的方式有两种，分别为 `==` 和 `equals()`, 前者比较内存是否一致， 后者比较内容是否一致

```java
class Person {
    int id;
    String name;
    public Person(int id, String name){
        this.id = id; this.name = name;
    }
    public boolean equals(Object obj){
        if(this == obj) return true; //确保具有自反性
        if(obj == null) return false; // 确保不会出现RE
        if(this.getClass() != obj.getClass()) return false;
        Person other = (Person) obj; //向下转型
        // String 比较用自带的equals
        return this.id == other.id && this.name.equals(other.name);
    }
}
public class Main {
    public static void main(String[] args) {
        Person A = new Person(123, "a");
        Person B = new Person(256, "b");
        Person C = new Person(263, "c");
        Person D = new Person(123, "a");
        System.out.println(A.equals(B));
        System.out.println(A.equals(D));
        System.out.println(B.equals(C));
    }
}
```



### 向上/下转型

实际上就是父类子类之间的相互转换

```java
class Animal {
    public int eyeNum, mouth;
}
class Dog extends Animal{}

public class Main {
    public static void main(String[] args) {
        Animal animal = new Animal();
        Dog dog = new Dog();

        Animal upper = dog; //向上转型
        //Dog lower = (Dog)animal; // 向下转型（不能这样做）animal是原生态的Animal
        Animal tem = new Dog();
        Dog lower = (Dog)tem;
    }
}
```



### instanceof

instanceof 是用来判断对象类型的，主要还是用于上下类型转换

`a instanceof B` 为 判断 a 是否可以转化为 B 的一个实例

```java
public class Main {
    public static void main(String[] args) {
        Animal animal = new Animal();
        Dog dog = new Dog();
        Animal dog2 = new Dog();
        Person lr580 = new Person(123, "580");
        System.out.println(animal instanceof Dog);
        System.out.println(dog instanceof Animal);
        //System.out.println(lr580 instanceof Dog); 会报错，因为两者之间没有继承关系
    }
}
/*
false
true
*/
```



> 方法重载
>
> **与 C++ 一致**



### final 关键字

如果是修饰与普通变量， 将其看成 const 对待，表示常量

修饰类以及方法的时候区别对待

> 当用final修饰一个类时，表明这个类不能被继承

> final类中的成员变量可以根据需要设为final，但是要注意final类中的所有成员方法都会被隐式地指定为final方法。

> 修饰方法：把方法锁定，以防任何继承类修改它的含义
>
> >  类的private方法会隐式地被指定为final方法。



### 多态 / 抽象类 / 接口

多态 ： 一个函数可以操作多种类：

```java
class China {
    public void printName(){
        System.out.println("China");
    }
}
class Guangdong extends China{
    public void printName(){
        System.out.println("广东");
    }
}
class SCNU extends China{
    public void printName(){
        System.out.println("SCNU");
    }
}
public class Main {
    public static void Test(China put){
        put.printName(); // 介个就叫多态
    }
    public static void main(String[] args) {
        China a = new China();
        Guangdong b = new Guangdong();
        SCNU c = new SCNU();
        Test(a); Test(b); Test(c);
    }
}

```

一般来说父类会写成抽象类：也可以写成接口，值得注意的是，一个类可以implement多个接口

注意如果类或接口前面有权限限制符，那么必须分文件写。

```java
public abstract class China{
    abstract void printName();
}
interface other2{ // 接口在本文件
    void PrintOther();
}
#########其他文件############
public interface other1 {
    void PrintArea();
}
###########################
class Guangdong extends China{
    public void printName(){
        System.out.println("广东");
    }
}
class SCNU extends China implements other1, other2{
    public void printName(){
        System.out.println("SCNU");
    }
    public void PrintArea(){
        System.out.println("10");
    }
    public void PrintOther(){
        System.out.println("Other");
    }
}
public class Main {
    public static void Test(China put){
        put.printName();
        if(put instanceof SCNU){
            ((SCNU) put).PrintOther();
            ((SCNU) put).PrintArea();
        }
    }
    public static void main(String[] args) {
        Guangdong b = new Guangdong();
        SCNU c = new SCNU();
        Test(b); Test(c);
    }
}
```



### 包和内部类

主要解决的问题是类名重合的问题，所以可以通过包名进行确定

```java
package TEST;
public class USE {
    ...
}
```

使用的时候有两种方法

```java
import TEST.*; // 全部
import TEST.USE; // 导入一个
```

内部类的基本形式：

```java
public class Outer {
    public class Inner{
        
    }
}
```

内部类可以使用外部类的所有内容，包括private                                                                                                                                                                                                                                                   

内部类存在的意义主要是为了高内聚 ，低耦合，即代码更加的可观简洁

public 的内部类可以在外部定义

```java
public class Outer {
    int num1 = 10;
    public class Inner{
        int num2;
        public void print(){
            num2 = num1;
            num1 --;
            System.out.println(num1 + " " + num2);
        }
    }
    public void show(){
        Inner in = new Inner();
        in.print();
    }
}
public class Main {
    public static void main(String[] args) {
        Outer out = new Outer();
        out.show();
        Outer.Inner Test = out.new Inner(); //要用定义好的外部类定义内部类
        for(int temp = 1 ; temp < 5 ; temp++)
            Test.print();
        out.show();
    }
}
/*
9 10
8 9
7 8
6 7
5 6
4 5
*/
```



> 匿名内部类

与Javascript 一样的匿名方法， 即重写过程放在实例化的过程中



## 核心技术

### 异常处理

发生异常会直接结束进程，为了进程持续下去，提出了异常处理

#### 捕获异常

基本的形式长成这个样子：

```java
try{
    问题代码
}catch(错误类型1 e){
    解决方案1
}catch(错误类型2 e){
    解决方案2
}finally{
    ....
}
```

例子

```java
public class Main {
    public static void main(String[] args) {
        try{
            int num = 1;
            System.out.println(15 / (--num));
        }catch(ArithmeticException e){
            System.out.println("分母为0");
        }catch (Exception e){
            System.out.println("error");
        }finally {
            System.out.println("done");
        }
    }
}
```

值得注意的是，如果try块里面的代码报错了，那么从报错的代码开始，后面的所有的代码都不会执行

常见异常

|           Exception            |           名称           |                        原因                        |
| :----------------------------: | :----------------------: | :------------------------------------------------: |
|     RunTimeException（RE）     |      运行时抛出异常      |                   以下五个均为RE                   |
|      ArithmeticException       |       算数逻辑异常       |                      除数为 0                      |
|      NullPointerException      |        空指针异常        | 字符串变量未初始化 /  对象空间为空时调用方法和属性 |
| ArrayIndexOutOfBoundsException | 数组索引（下标）越界异常 |        访问数组时超出数组索引（下标）范围。        |
|       ClassCastException       |       类型转换异常       |    将一个对象投射到一个子类，而子类不是一个实例    |
|     NumberFormatException      |      数字格式化异常      |      将“01L”转化为数字 / 超出转换类型数值范围      |



#### 自定义异常

自定义异常用一个实例演示，假设我们自定义一个注册异常，表示这个用户名给使用了

```java
public class UserNameException extends Exception{
    public UserNameException(String exceptionInfo){
        super(exceptionInfo);
    }
    public UserNameException(){
        this("There are some errors with the username");
    }
}
public class Main {
    public static void main(String[] args) {
        try{
            String userName = "yyym";
            checkUserName(userName);
        }catch (UserNameException e){
            e.printStackTrace();
        }
    }
    public static void checkUserName(String userName) throws UserNameException{
        if(userName.equals("yyym"))
            throw new UserNameException("用户名存在");
    }
}
/*
UserNameException: 用户名存在
	at Main.checkUserName(Main.java:15)
	at Main.main(Main.java:8)
*/
```



#### 抛出异常

实际上在上面的例子已经使用了抛出异常

可以一直抛，直到有人处理



### 字符串

#### 字符串相关操作

> 连接 ： 字符串之间用 `+` 直接连接， 其它类型也一样，反正自主类型转换

> 字符串查找 ：  `str.indexOf(String s / char a)`  `str.lastIndexOf(String s / char a)`
>
> 分别为 ： 第一次出现的下标 ， 最后一次出现的下标

> 获取字串 `str.substring(int Begin)`   `str.substring(int Begin, int End)`

> 去除前端后端空格 `str.trim()`

> 字符串替换 `str.replace(String a, String b)` 	a 为原字符串， b为替换字符串

> `str.startsWith(String a)`  	`str.endsWith(String b)`

> `str.equals(String a)`  	`str.equalsIgnoreCase(String a)` 	`str.CompareTo(String a)`

> `str.toLowerCase()` 	`str.toUppercase()`	

> 分割 ： `str.split(String a)` 	`str.split(String a, int splitTimes)`



#### 格式化字符串（常用）

**时间**

```java
public class Main {
    public static void main(String[] args) {
        Date date = new Date();
        System.out.println("今年是" + String.format("%tY", date) + ",月份是" + String.format("%tb", date));
    }
}
```

日期类

|  转换符   |               说明                |         示例          |
| :-------: | :-------------------------------: | :-------------------: |
| %te / %td | 一个月中的某一天（1\~31）/(01~31) |        3 / 03         |
| %tb / %tB |     月份简称/全程（根据语境）     | Feb / 二月 / February |
| %ta / %tA |        星期几（简称/全程）        |   Mon/星期一/Monday   |
| %tY / %ty |        四位年份 / 两位年份        |       2008 / 08       |
|    %tm    |               月份                |           3           |
|    %tj    |      一年的第几天（001~366）      |          085          |

时间类

......百度吧....



日期时间结合

....自己查...



其他

接就这样吧.....



#### 正则表达式

挖个坑（：））））



#### 字符串生成器

挖个坑（：））））



### 常用库类

#### Integer 类

#### Double 类

#### Boolean 类

#### Character 类

#### Number 类

是上面所有类的老爸

#### Math 类

#### Random 类

#### BigInteger 类

就是高精度罢了

#### BigDecimal 类

高精度的浮点数

#### System 类

#### Scanner 类

这个类主要负责读入的功能， 具体的使用参照下面的代码：

```java
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String lineContent = sc.nextLine(); // <- 这个是读取一行
        int a = sc.nextInt();
        // 同理有 sc.nextBoolean(); sc.nextDouble(); sc.next() <- 这个是只读取一个String
        sc.close(); // 用完关闭
    }
}
```



#### Data 类

#### Calendar 类

#### RunTime 类



### 集合类

整体可以看成 C++ SLT 库

首先 **List** , **Set** 都连接了 **Collection** 接口

#### Collection 接口

|       方法       |      描述      |
| :--------------: | :------------: |
|     add(E e)     |  添加到该集合  |
| remove(Object o) | 将指定对象移除 |
|    isEmpty()     |    是否为空    |
|    iterator()    |   返回迭代器   |
|      size()      |    返回大小    |

#### List 接口

List添加了两个方法

|            方法            |      描述      |
| :------------------------: | :------------: |
|       get(int index)       | 获取索引的元素 |
| set(int index, Object obj) | 设置索引的元素 |

可以将List看成链表

使用方法如下

```java
List<Integer> arr = new ArrayList<>();
List<Integer> arr2 = new LinkedList<>();
```

PS:

* ArrayList基于动态数组实现的非线程安全的集合；LinkedList基于链表实现的非线程安全的集合。
* 对于随机index访问的get和set方法，一般ArrayList的速度要优于LinkedList。因为ArrayList直接通过数组下标直接找到元素；LinkedList要移动指针遍历每个元素直到找到为止。
* 新增和删除元素，一般LinkedList的速度要优于ArrayList。因为ArrayList在新增和删除元素时，可能扩容和复制数组；LinkedList实例化对象需要时间外，只需要修改指针即可。
* LinkedList集合不支持 高效的随机随机访问（RandomAccess）
* ArrayList的空间浪费主要体现在在list列表的结尾预留一定的容量空间，而LinkedList的空间花费则体现在它的每一个元素都需要消耗相当的空间

```java
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<Integer> arr = new ArrayList<>();
        for(int temp = 1 ; temp <= 10 ; temp++)
                arr.add(temp);
        //arr[5] = 10; 不可以用[]访问
        arr.set(5, 10);
        for(int temp = 0 ; temp < 10 ; temp++)
            System.out.print(arr.get(temp) + " ");
    }
}
```

#### Set 集合

#### map 集合

#### Entry 类

### 枚举与泛型

### lambda表达式和流处理

#### Lambda表达式

主要是对某些匿名内部类的写法进行简化

核心原则 ： 可推导可省略

基本格式：

```java
() -> {}
```

一般可以简化的原则是 ：

匿名内部类是一个接口，而且接口只需要重写一个抽象方法

示例：

```java
public class Main {
    public static void main(String[] args) {
        new Thread(new Runnable(){
            @Override
            public void run() {
                System.out.println("新线程中run方法被执行了");
            }
        }).start();
    }
}
########################################################
public class Main {
    public static void main(String[] args) {
        new Thread(() -> {System.out.println("新线程中run方法被执行了");}).start();
    }
}
```



除此之外还可以省略，规则如下：

* 参数类型可以省略
* 方法体中只有一句代码时大括号， return， 那一句代码的分号可以省略
* 方法只有一个参数，小括号可以省略

所以：

```java
public class Main {
    public static void main(String[] args) {
        new Thread(() -> System.out.println("新线程中run方法被执行了")).start();
    }
}
```



#### Stream 流

将数组和数据当成流来处理，简化了许多的操作

为了更方便的演示，我们先做好了许多准备工作：

```java
import java.util.List;

public class Author implements Comparable{
    private Long id;
    private String name;
    private Integer age;
    private String intro;
    private List<Book> books;
    public Author(Long id, String name, Integer age, String intro, List<Book> books){
        this.id = id; this.name = name; this.age = age; this.intro = intro; this.books = books;
    }
    public void setBooks(List<Book> put){
        this.books = put;
    }
    public String getName(){
        return this.name;
    }
    public Integer getAge(){
        return this.age;
    }
    @Override
    public int compareTo(Object o) {
        return age - ((Author) o).age;
    }
    public List<Book> getBooks(){
        return this.books;
    }
}
```

```java
public class Book {
    private Long id;
    private String name;
    private String category;
    private Integer score;
    private String intro;
    public Book(Long id, String name, String category, Integer score, String intro){
        this.id = id; this.name = name; this.category = category; this.score = score; this.intro = intro;
    }
    public String getCategory() {
        return category;
    }
}
```

```java
private static List<Author>getAuthors() {
    //数据初始化
    Author author = new Author(1L, "蒙多", 33, "一个从菜刀中明悟哲理的祖安人", null);
    Author author2 = new Author(2L, "亚拉索", 15, "狂风也追逐不上他的思考速度", null);
    Author author3 = new Author(3L, "易", 14, "是这个世界在限制他的思维", null);
    Author author4 = new Author(3L, "易", 14, "是这个世界在限制他的思维", null);
    //书籍列表
    List<Book> books1 = new ArrayList<>();
    List<Book> books2 = new ArrayList<>();
    List<Book> books3 = new ArrayList<>();
    books1.add(new Book(1L, "刀的两侧是光明与黑暗", "哲学,爱情", 88, "用一把刀划分了爱恨"));
    books1.add(new Book(2L, "一个人不能死在同一把刀下", "个人成长,爱情", 99, "讲述如何从失败中明悟真理"));

    books2.add(new Book(3L, "那风吹不到的地方", "哲学", 85, "带你用思维去领略世界的尽头"));
    books2.add(new Book(3L, "那风吹不到的地方", "哲学", 85, "带你用思维去领略世界的尽头"));
    books2.add(new Book(4L, "吹或不吹","爱情,个人传记", 56, "一个哲学家的恋爱观注定很难把他所在的时代理解"));

    books3.add(new Book(5L, "你的剑就是我的剑", "爱情", 56, "无法想象一个武者能对他的伴侣这么的宽容"));
    books3.add(new Book(6L, "风与剑", "个人传记", 100, "两个哲学家灵魂和肉体的碰撞会激起怎么样的火花呢?"));
    books3.add(new Book(6L, "风与剑","个人传记", 100, "两个哲学家灵魂和肉体的碰撞会激起怎么样的火花呢?"));

    author.setBooks(books1);
    author2.setBooks (books2);
    author3.setBooks(books3);
    author4.setBooks(books3);

    return new ArrayList<>(Arrays.asList(author, author2, author3, author4));
}
```



> **创建流**

单列集合 ： 父接口为 collection ： `集合对象.steam()`

```java
List<Author> authors = getAuthors();
Stream<Author> stream = authors.stream();
```

数组 ： `Arrays.stream(数组)` 或者 `Steam.of()`

```java
Integer[] arr = {1,2,3,4,5,6,7};
Stream<Integer> stream = Arrays.stream(arr);
Stream<Integer> stream2 = Stream.of(arr);
```

双列集合：map ： 转化为单列集合之后再创建

```java
Map<String, Integer> map = new HashMap<>();
map.put("蜡笔小新",19);
map.put("黑子",17);
map.put("日向翔阳",16);
Stream<Map.Entry<String, Integer>> stream = map.entrySet().stream();
```



> 中间操作 ： `filter`

对流中的元素按条件进行过滤，符合过滤条件的才会留在流中

filiter 里面的参数是一个Predicate 对象，我们要重写里面的比较函数：

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    authors.stream()
        .filter(new Predicate<Author>() {
            @Override
            public boolean test(Author author) { //进入函数判断
                return false;
            }
        }).forEach(new Consumer<Author>() { //终结操作，后面讲
        	@Override
        	public void accept(Author author) {
            	System.out.print(author.getName() + " ");
        	}
    	});
}
```

现在如果我们需要打印姓名长度大于一的作家，就可以重写函数并且结合匿名函数

如下：

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    authors.stream()
        .filter(author -> author.getName().length() > 1)
        .forEach(author -> System.out.print(author.getName() + " "));
}
```



>中间操作 ：`map` 

对流里面的元素进行计算和转换

现在如果我们需要将流里面的Author转化为String， 即只操作作家的名字

我们需要使用map来实现

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    authors.stream()
        .map(new Function<Author, Object>() { //<- 这个Object 是你期望转换的形式
        })
}
```

重写：

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    authors.stream()
        .map(new Function<Author, String>() {
            @Override
            public String apply(Author author) {
                return author.getName();
            }
        }).forEach(s -> System.out.print(s + " "));
}
```

转化为匿名表达式：

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    authors.stream()
        .map(author -> author.getName())
        .forEach(s -> System.out.print(s + " "));
}
```



> 中间操作 `distinct`

去重操作

**PS ：去重依赖的是equals方法，所以要重写equals方法和hashCode方法**

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    authors.stream()
        .distinct()
        .forEach(author -> System.out.print(author.getName() + " "));
}
```



> 中间操作 ：`sorted`

排序

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    authors.stream()
        .sorted()
        .forEach(author -> System.out.println(author.getName() + " " + author.getAge()));
}
```

如果使用无参的sorted， 则需要类里面连接Comparable接口并实现，否则使用有参构造

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    authors.stream()
        .sorted((o1, o2) -> o1.getAge() - o2.getAge())
        .forEach(author -> System.out.println(author.getName() + " " + author.getAge()));
}
```



> 中间操作 : `limit`

控制流的长度

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    authors.stream()
        .limit(2)
        .forEach(author -> System.out.print(author.getName() + " "));
}
```



> 中间操作 ： `skip`

跳过流的前 $n$ 个元素

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    authors.stream()
        .skip(1)
        .forEach(author -> System.out.print(author.getName() + " "));
}
```



> 中间操作 ： `flatMap`

将流里面的元素转化为多个元素，其结果必须是流

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    authors.stream()
        .flatMap(author -> author.getBooks().stream())
        .flatMap(book -> Arrays.stream(book.getCategory().split(",")))
        .distinct()
        .forEach(name -> System.out.print(name + " "));
}
```



> 终结操作 ：`forEach`

对每一个元素进行遍历操作



> 终结操作 ： `count`

获取流中元素的个数



> 终结操作 ： `max` / `min`

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    Optional<Integer> max = authors.stream()
        .flatMap(author -> author.getBooks().stream())
        .map(book -> book.getScore())
        .max((a, b) -> a - b);
    System.out.print(max.get());
}
```

max返回的是 Optional的实例，Optional后面讲解



> 终结操作 ：`collect`

将流转化为集合

```java
public static void main(String[] args) {
        List<Author> authors = getAuthors();
        List<String> name = authors.stream()
                .map(author -> author.getName())
                .collect(Collectors.toList());
        Set<String> name2 = authors.stream()
                .map(author -> author.getName())
                .collect(Collectors.toSet());
        Map<String, Integer> map = authors.stream() // key不能重复，要么提前去重， 要么加上(a , b) -> a)
            .collect(Collectors.toMap(author -> author.getName(), author -> author.getAge(), (a , b) -> a));
}
```



> 终结操作之匹配 `anyMatch`

判断是否存在

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    boolean bool = authors.stream()
        .map(author -> author.getAge())
        .anyMatch(age -> age < 20);
    System.out.print(bool);
}
```



> 终结操作之匹配 `allMatch`

是否所有都符合条件

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    boolean bool = authors.stream()
        .map(author -> author.getAge())
        .allMatch(age -> age >= 18);
    System.out.print(bool);
}
```



> 终结操作之匹配 `noneMatch`

判断所有是不是都不符合条件

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    boolean bool = authors.stream()
        .map(author -> author.getAge())
        .noneMatch(age -> age >= 100);
    System.out.print(bool);
}
```



> 终结操作之匹配 `findAny`

获取任意一个符合条件的情况

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    Optional<Author> author = authors.stream()
        .filter(author1 -> author1.getAge() < 18)
        .findAny();
    System.out.print(author.get().getName());
}
```

返回值为 Optional 对象



> 终结操作之匹配 `findFirst`

获取第一个符合条件的情况



>  终结操作 `reduce` 

reduce 的内部效果可以理解为：

```java
T result = identify;
for(T element : this steam)
    result = accumulate.apply(result, element);
return result
```

最后返回的结果是是唯一的，而我们的reduce就是之前方法的抽象简化

例子 ： 求所有作家的年龄之和

第一种重载方式如下：

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    Integer a = authors.stream()
        .map(author -> author.getAge())
        .reduce(identfy, new BinaryOperator<Integer>() {
            @Override
            public Integer apply(Integer result, Integer element) {
                return null;
            }
        });
}
```

具体含义和上面的一致，我们可以简化为：

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    Integer a = authors.stream()
        .map(author -> author.getAge())
        .reduce(0, (result, element) -> result + element);
    System.out.print(a);
}
```

第二种重载形式，只有一个函数，默认吧第一个参数作为初始值

只不过返回类型为Optional

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    Optional<Integer> a = authors.stream()
        .map(author -> author.getAge())
        .reduce((result, element) -> result + element);
    System.out.print(a.get());
}
```



#### Optional

Optional 主要是为了防止空指针异常



> 将对象封装为Optional对象

```java
public static void main(String[] args) {
    Author author = getAuthor();
    Optional<Author> optionalAuthor = Optional.ofNullable(author);
}
```

> 具体的使用如下：

```java
public static Author getAuthor(){
    return new Author(1L, "Test", 10, "none", null);
    //return null;
}
public static void main(String[] args) {
    Author author = getAuthor();
    Optional<Author> optionalAuthor = Optional.ofNullable(author);
    optionalAuthor.ifPresent(author1 -> System.out.print(author1.getName()));
}
/*
NULL -> 
------
...  -> Test
*/
```



> 安全的获取值

`orElseGet`

为空的时候返回默认值，否则返回原值

```java
public static Author getAuthor(){
    //return new Author(1L, "Test", 10, "none", null);
    return null;
}
public static void main(String[] args) {
    Author author = getAuthor();
    Optional<Author> author1 = Optional.ofNullable(author);
    System.out.println(
        author1.orElseGet(() -> new Author(1L, "Test2", 10, "none", null)).getName());
}
// Test2
```



`orElseThrow`

为空的时候抛出异常，否则返回原值

```java
public static Author getAuthor(){
    //return new Author(1L, "Test", 10, "none", null);
    return null;
}
public static void main(String[] args) {
    Author author = getAuthor();
    Optional<Author> author1 = Optional.ofNullable(author);
    try{
        System.out.println(
            author1.orElseThrow(() -> new UserNameException()) //之前定义的
        );
    }catch (UserNameException e){
        System.out.println("自定义异常");
    }
}
```



> 判断是否为空 : `isPresent`



> 类似的方法

Optional 提供了 `filter`, `map` 方法，和之前的一样



#### 函数式接口

接口里面只有一个抽象方法就是一个函数式接口



#### 方法引用

挖个坑



#### 一点小优化

观察这段代码

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    authors.stream()
        .map(author -> author.getAge())
        .map(age -> age + 10)
        .map(age -> age / 2)
        .forEach(age -> System.out.println(age));
}
```

map里面的参数都是 Integer类型的，而计算都会转化为基本数据类型，所以数据多的情况下会浪费时间

所以可以转化为 int 类型

```java
public static void main(String[] args) {
    List<Author> authors = getAuthors();
    authors.stream()
        .mapToInt(author -> author.getAge())
        .map(age -> age + 10)
        .map(age -> age / 2)
        .forEach(age -> System.out.println(age));
}
```

这样会更优



### I / O 流

#### File 类

File 类是文件以及路径的抽象表示

> 构造方式如下：

```java
File f1 = new File("D:\\DeskTop\\Use\\ab.txt");
```

创建时输入的地址可以数不存在的路径



> 常用方法

```java
public static void main(String[] args) throws Exception {
    File f1 = new File("D:\\DeskTop\\Use\\ab.txt");
    File f2 = new File("D:\\DeskTop\\Use");
    System.out.println(f1.length()); //判断大小 ： PS : 如果是文件夹，只会显示文件夹的星系，不是总大小
    System.out.println(f1.exists()); // 判断是否存在
    System.out.println(f1.getName()); //获取名字(包含后缀)
    System.out.println(f1.isFile());  // 判断时候为文件
    System.out.println(f2.isDirectory());  // 判断是否为文件夹
    System.out.println(f1.lastModified()); // 最后修改时间 ， 返回值为毫秒值，要转换
    System.out.println(f1.getPath()); // 获取创建时候的目录
    System.out.println(f2.getAbsolutePath()); // 获取绝对路径
    File f3 = new File("\\DeskTop\\Use\\bbb.txt");
    System.out.println(f3.createNewFile()); // 创建文件
    System.out.println(f3.createNewFile()); // 存在返回 false
    File f4 = new File("\\DeskTop\\Use\\aaa\\bbb\\ccc\\ddd");
    File f5 = new File("\\DeskTop\\Use\\kkk");
    System.out.println(f5.mkdir()); // 创建文件夹， 只能创建一级文件夹
    System.out.println(f4.mkdirs()); // 创建文件夹， 可以创建多级文件夹
    System.out.println(f2.delete()); // 删除， 只能删除文件， 空文件夹， 多重空文件夹
    System.out.println(f4.delete());
    System.out.println(f5.delete());
    String[] list = f2.list(); // 获取目录所有的文件的名字
    File[] files = f2.listFiles(); // 获取一级目录的file文件
}
```



#### I / O 流

> 文件字节输入流

封装的对象为 **FileInputStream**

两种构造方法

```java
public static void main(String[] args) throws Exception {
    File file = new File("D://DeskTop//Use//bbb.txt");
    FileInputStream fileInputStream = new FileInputStream(file);
    FileInputStream fileInputStream2 = new FileInputStream("D://DeskTop//Use//bbb.txt");
}
```

* 读一个字节： `read()`

```java
System.out.println(fileInputStream.read());
System.out.println((char) fileInputStream.read());
// 读完返回 -1
```

读完后必须关闭释放资源

```java
fileInputStream.close();
```

* 读取成字节数组 `read(byte[] a)`

```java
public static void main(String[] args) throws Exception {
    File file = new File("D://DeskTop//Use//bbb.txt");
    FileInputStream fileInputStream = new FileInputStream(file);
    byte[] bytes = new byte[1024];
    int len = fileInputStream.read(bytes); // 返回字节数量，读完返回-1
    String s = new String(bytes, 0, len); // 解码的时候注意控制长度
    System.out.println(s);
    fileInputStream.close();
}
```

* 读取全部字节 `readAllbytes()`

```java
public static void main(String[] args) throws Exception {
    File file = new File("D://DeskTop//Use//bbb.txt");
    FileInputStream fileInputStream = new FileInputStream(file);
    byte[] bytes = fileInputStream.readAllBytes();
    String s = new String(bytes);
    System.out.println(s);
    fileInputStream.close();
}
```





> 文件字节输出流

封装的对象为 **FileOutputStream**

构造方式同理

```java
public static void main(String[] args) throws Exception {
    File file = new File("D://DeskTop//Use//bbb.txt");
    FileOutputStream fileOutputStream = new FileOutputStream(file);
    FileOutputStream fileOutputStream2 = new FileOutputStream("D://DeskTop//Use//bbb.txt");
}
```

* **写一个字节出去 `write(byte a)`**

```java
public static void main(String[] args) throws Exception {
    File file = new File("D://DeskTop//Use//bbb.txt");
    FileOutputStream fileOutputStream = new FileOutputStream(file);
    FileOutputStream fileOutputStream2 = new FileOutputStream("D://DeskTop//Use//bbb.txt");
    fileOutputStream.write('a');
    fileOutputStream.close();
}
```

* **写一个字节数组出去 `write(byte[] a)`**

```java
public static void main(String[] args) throws Exception {
    File file = new File("D://DeskTop//Use//bbb.txt");
    FileOutputStream fileOutputStream = new FileOutputStream(file);
    FileOutputStream fileOutputStream2 = new FileOutputStream("D://DeskTop//Use//bbb.txt");
    byte[] bytes = "yyym-----yyym".getBytes();
    fileOutputStream.write(bytes);
    fileOutputStream.close();
}
```

* **写一个字节数组的部分出去 `write(byte[] a, int Begin, int End)`**

```java
public static void main(String[] args) throws Exception {
    File file = new File("D://DeskTop//Use//bbb.txt");
    FileOutputStream fileOutputStream = new FileOutputStream(file);
    FileOutputStream fileOutputStream2 = new FileOutputStream("D://DeskTop//Use//bbb.txt");
    byte[] bytes = "yyym-----yyym".getBytes();
    fileOutputStream.write(bytes, 0, 5);
    fileOutputStream.close();
}
```

* **将覆盖模式变成追加模式**

定义管道的时候加上 `true`

```java
File file = new File("D://DeskTop//Use//bbb.txt");
FileOutputStream fileOutputStream = new FileOutputStream(file, true);
```




> 文件字符输入流

封装的对象为 **FileReader**

创建方式同理

```java
public static void main(String[] args) throws Exception {
    File file = new File("D://DeskTop//Use//bbb.txt");
    FileReader fileReader = new FileReader(file);
    FileReader fileReader2 = new FileReader("D://DeskTop//Use//bbb.txt");
}
```

* **读取方式**

`read()` : 读取一个字符， 没有数据返回 -1

`read(char[] buffer)`  返回读取了多少个字符， 没有返回 -1

```java
public static void main(String[] args) throws Exception {
    File file = new File("D://DeskTop//Use//bbb.txt");
    FileReader fileReader.close();
    fileReader2.close();= new FileReader(file);
    FileReader fileReader2 = new FileReader("D://DeskTop//Use//bbb.txt");
    int read = fileReader.read();
    char[] chars = new char[1024];
    int len = fileReader.read(chars);
    System.out.println((char) read);
    System.out.println(new String(chars, 0, len));
    fileReader.close();
    fileReader2.close();
}
```



> 文件字符输入流

封装的对象为 **FileWriter**

其实大部分都一样，不过多描述了

* 构造，与前面一样
* 写一个字符 `write(int c)`
* 写一个字符串 `write(String str)`
* 写一个字符串的一部分 `write(String str, int Begin, int End)`
* 写一个字符数组 `write(char[] buff)`
* 写一个字符数组的一部分 `write(char[] buff, int Begin, int End)`
* 将覆盖模式转化为追加模式  :  构造时加上 `true`



**PS : 字符输出的时候必须要刷新缓冲区才能生效， 只有关闭或者刷新缓冲区才能生效**

```java
public static void main(String[] args) throws Exception {
    File file = new File("D://DeskTop//Use//bbb.txt");
    FileWriter fileWriter = new FileWriter(file, true);
    fileWriter.write("ddd");
    fileWriter.flush(); // 刷新
    fileWriter.close(); // 关闭
}
```



> 安全的释放资源

除了 try - catch - finally 外，**try - with - resource** 更简单

```java
try(资源对象){
    ...
}catch(Ex.. e){
    
}
```

所有的资源对象都实现了 AutoCloseable 接口

示例：

```java
public static void main(String[] args) throws Exception {
    try(FileOutputStream fileOutputStream = new FileOutputStream("D://DeskTop//Use//bbb.txt")){
        System.out.println("代码");
    }catch (Exception e){
        System.out.println("释放");
    }
}
```



#### 缓冲流

对于上述的四种操作，如果每次都直接的操纵硬件，会导致效率急剧下降，所以我们提供了缓冲流

即：给所有的操作加上了缓存，实际使用的时候直接使用缓冲流即可

> FileInputStream   $\Longrightarrow$  BufferedInputStream
>
> FileOutputStream   $\Longrightarrow$  BufferedOutputStream
>
> FileReader    $\Longrightarrow$   BufferedReader
>
> FileWriter    $\Longrightarrow$   BufferedWriter



#### 转换流

主要的常见是将字符流在不同的编码格式里面相互转换

> 字符输入转换流

**InputStreamReader**

创建形式有两种

```java
public static void main(String[] args) throws Exception {
    File file = new File("D://DeskTop//Use//bbb.txt");
    FileInputStream fileInputStream = new FileInputStream(file); // 先用字节流
    InputStreamReader inputStreamReader = new InputStreamReader(fileInputStream); // 默认字符集
    InputStreamReader inputStreamReader1 = new InputStreamReader(fileInputStream, "GBK"); // 可以指定编码格式
}
```

> 字符输出转换流

创建形式有两种

```java
public static void main(String[] args) throws Exception {
    File file = new File("D://DeskTop//Use//bbb.txt");
    FileOutputStream fileOutputStream = new FileOutputStream(file);
    OutputStreamWriter outputStreamWriter = new OutputStreamWriter(fileOutputStream);
    OutputStreamWriter outputStreamWriter1 = new OutputStreamWriter(fileOutputStream, "GBK");
}
```



#### 打印流

#### 数据流

实现的功能是将 Java 中的基本数据类型转化为内容保存在文件里面

有两个类 ：

> `DataInputStream`  数据输入流
>
> `DataOutputStream`  数据输出流

```java
public static void main(String[] args) throws Exception {
    File file = new File("D://DeskTop//Use//bbb.txt");
    FileOutputStream outputStream = new FileOutputStream(file);
    int a = 10, b = 20, c = 30, d = 40;
    double e = 100, f = 1000, g = 10000;
    String str = "aaaa", str2 = "bbbb", str3 = "cccc";
    try(DataOutputStream dataOutputStream = new DataOutputStream(outputStream)){
        dataOutputStream.writeInt(a); dataOutputStream.writeInt(b);
        dataOutputStream.writeInt(c); dataOutputStream.writeInt(d);
        dataOutputStream.writeDouble(e); dataOutputStream.writeDouble(f);
        dataOutputStream.writeDouble(g); dataOutputStream.writeUTF(str);
        dataOutputStream.writeUTF(str2); dataOutputStream.writeUTF(str3);
    }catch (Exception err){
        System.out.println("error");
    }

    try(DataInputStream dataInputStream = new DataInputStream(new FileInputStream(file))){
        System.out.println(dataInputStream.readInt());
        System.out.println(dataInputStream.readInt());
        System.out.println(dataInputStream.readInt());
        System.out.println(dataInputStream.readInt());
        System.out.println(dataInputStream.readDouble());
        System.out.println(dataInputStream.readDouble());
        System.out.println(dataInputStream.readDouble());
        System.out.println(dataInputStream.readUTF());
    }catch (Exception err){
        System.out.println("error");
    }
}
```

**必须写入的数据类型完全一致，如果写入4个int，但读了2个int，2的str会报错**



#### 序列化流

把java对象写在文件里

封装的对象为 `ObjectInputStream ` 和 `ObjectOutputStream`

```java
public class CCC implements Serializable {  // 想序列化必须连接 Serializable
    public String name = "55555";
    public int num = 10;

    private long password;
    public void Print(){
        System.out.println("Hello World");
    }
    public void Print2(){
        System.out.println("不想序列化");
    }
    public long getPassword(){
        return password;
    }
    public CCC(String name, long password){
        this.name = name; this.password = password;
    }
}

```



```java
public static void main(String[] args) throws Exception {
    File file = new File("D://DeskTop//Use//kkk.txt");
    CCC test = new CCC("yyym", 123456);
    try(ObjectOutputStream objectOutputStream = new ObjectOutputStream(new FileOutputStream(file))){
        objectOutputStream.writeObject(test);
    }catch (Exception e){
        System.out.println("error");
    }

    try(ObjectInputStream objectInputStream = new ObjectInputStream(new FileInputStream(file))){
        CCC ccc = (CCC) objectInputStream.readObject();
        ccc.Print();
        ccc.Print2();
    }catch (Exception e){
        System.out.println("error");
    }
}
```

如果类里面有些不想被序列化，可以加上：`transient `

```java
import java.io.Serializable;

public class CCC implements Serializable {
    public String name = "55555";
    public int num = 10;

    private transient long password;
    public void Print(){
        System.out.println("Hello World");
    }
    public void Print2(){
        System.out.println("不想序列化");
        // public 不能用 transient 修饰
    }
    public long getPassword(){
        return password;
    }
    public CCC(String name, long password){
        this.name = name; this.password = password;
    }
}
```



### 多线程

最简单的解释，就是程序一会执行以下这个，一会执行以下那个，非常花心

最真实的案例，当你打开原神，原神会加载资源，同时会播放动画

加载资源和播放动画可以看成两个进程，这样你才能原神，启动！！！



> 并发		并行

并发 ： 在同一时刻，有多个指令在单个CPU上交替进行

并行： 在同一时刻， 有多个指令在多个CPU上同时进行



#### 实现多线程

有三种实现方式

> 类直接继承自 Thread 类

```java
public class Mythread extends Thread{
    @Override
    public void run() {
        for(int temp = 10 ; temp <= 10000 ; temp++)
            System.out.println(getName() + "\t在运行");
    }
}

######################################################
    
public static void main(String[] args) throws Exception {
    Mythread t1 = new Mythread();
    Mythread t2 = new Mythread();
    t1.setName("线程1 - ");  t2.setName("线程2 - ");
    t1.start();  t2.start();
}

/*
...
线程2 - 	在运行
线程2 - 	在运行
线程2 - 	在运行
线程1 - 	在运行
线程1 - 	在运行
线程2 - 	在运行
线程2 - 	在运行
线程2 - 	在运行
....
*/
```



> 实现 Runnable 接口的方式

```java
public class MyThread implements Runnable{
    @Override
    public void run() {
        for(int temp = 10 ; temp <= 10000 ; temp++)
            System.out.println(Thread.currentThread().getName() + "\t在运行");
    }
}

#########################################
    
    public static void main(String[] args) throws Exception {
    Thread t1 = new Thread(new MyThread());
    Thread t2 = new Thread(new MyThread());
    t1.setName("线程1 - ");  t2.setName("线程2 - ");
    t1.start();  t2.start();
}
```



> 使用 Callable 接口和Future接口 （主要是因为线程有返回值）

```java
import java.util.concurrent.Callable;

public class MyThread implements Callable<Integer> {

    @Override
    public Integer call() throws Exception {
        int Sum = 0;
        for(int temp = 1 ; temp <= 100 ; temp++){
            Sum += temp;
            System.out.println(Thread.currentThread().getName() + "加到了" + temp);
        }
        return Sum;
    }
}

####################################
    
    public static void main(String[] args) throws Exception {
    MyThread myThread = new MyThread();
    FutureTask<Integer> t1 = new FutureTask<>(myThread);
    FutureTask<Integer> t2 = new FutureTask<>(myThread);
    Thread thread = new Thread(t1); thread.setName("线程一 : - ");
    Thread thread2 = new Thread(t2); thread2.setName("线程二 : - ");
    thread.start(); thread2.start();
}
```



#### Thread 常用方法

> **getName()**		获取此线程的名字



> **setName(String name)**		设置线程的名字 PS ： 构造方法也可以设置名字

PS ： main方法线程的名字就叫 main， 默认的名字叫 Thread-（序号）



> **static Thread currentThread()**		获取当前线程



> **static void sleep(long time) **		让进程休息时间，单位为毫秒

PS ： 当休息结束后，不会执行下方的代码，而是重新争夺线程



> **setPriority(int priority)** 	设置线程优先级

PS： 优先级越高越容易抢到执行权，但不是一定会抢到



> **int getPriority()**		获取线程优先级

PS : 默认优先级为 5



> **setDaemon()**		设置为守护线程

守护线程 ： 当其他线程结束的时候，守护线程就没有存在的必要了，也就会停止了

值得注意的是：守护线程不会立马停止，而是等一或

```java 
public class MyThread2 extends Thread{
    @Override
    public void run() {
        for(int temp = 1 ; temp <= 3 ; temp++){
            System.out.println(getName() + " " + temp);
        }
    }
}
###################################################
public class MyThread extends Thread{
    @Override
    public void run() {
        for(int temp = 1 ; temp <= 100000 ; temp++)
            System.out.println(getName() + " " + temp);
    }
}
###################################################
    public static void main(String[] args) throws Exception {
    MyThread t1 = new MyThread();
    MyThread2 t2 = new MyThread2();
    t1.setDaemon(true); //设置为守护线程
    t1.setName("守护线程");  t2.setName("线程一");
    t1.start(); t2.start();
}
/*
线程一 1
线程一 2
守护线程 1
线程一 3
守护线程 2
守护线程 3
守护线程 4
守护线程 5
*/
```



> **yield()**		出让线程 / 礼让线程

用一句话概括就是，如果我这个线程正在被执行，那么当执行到这段代码的时候，就会不在继续执行，再次竞争执行权

可以让线程执行的更加均匀

```java
public class MyThread extends Thread{
    @Override
    public void run() {
        for(int temp = 1 ; temp <= 5 ; temp++)
            System.out.println(getName() + " " + temp);
    }
}
##################################################
public class MyThread2 extends Thread{
    @Override
    public void run() {
        for(int temp = 1 ; temp <= 5 ; temp++){
            System.out.println(getName() + " " + temp);
            Thread.yield();
        }
    }
}
#################################################
    public static void main(String[] args) throws Exception {
    MyThread t1 = new MyThread();
    MyThread2 t2 = new MyThread2();
    t1.setName("线程一");  t2.setName("线程二");
    t1.start(); t2.start();
}
/*
线程一 1
线程一 2
线程二 1
线程一 3
线程二 2
线程一 4
线程二 3
线程一 5
线程二 4
线程二 5
*/
```



> **join()**			插入线程

实际实现效果， 在一个线程结束后才会执行另一个线程

```java
t.join();
// 把 t 线程插入当前线程之前
```



#### 线程的生命周期

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230716174730054.png" alt="image-20230716174730054" style="zoom:80%;" />

#### 同步代码块 / 方法

> 同步代码块

说句通俗易懂的话，就是设置你的代码快在被某个线程执行的时候不会被抢夺走

现在有个例子，如果电影院要卖100张票，设置三个线程同时买票，同时每次买票休息100ms

原始代码如下

```java
public class MyThread extends Thread{
    static int ticket = 0;

    public MyThread(String name) {
        super(name);
    }
    
    @Override
    public void run() {
        while (true){
            if(ticket < 100){
                try {
                    sleep(100);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                ticket++;
                System.out.println(getName() + "在卖第" + ticket + "张票");
            }else{
                break;
            }
        }
    }
}
###################################################################
    public static void main(String[] args) throws Exception {
    MyThread t1 = new MyThread("线程一");
    MyThread t2 = new MyThread("线程二");
    MyThread t3 = new MyThread("线程三");
    t1.start(); t2.start(); t3.start();
}
```

这个时候会有异常结果：

```
.....
线程二在卖第97张票
线程二在卖第99张票
线程一在卖第99张票
线程三在卖第99张票
线程二在卖第102张票
线程三在卖第101张票
线程一在卖第100张票
```

可以尝试自己分析以下

为了解决这类问题，我们需要进行同步代码块操作

基本格式如下：

```java
synchronized(锁对象){
    需要同步的代码
}
```

这个锁对象可以是任意对象，但必须是 static

所以代码变为：

```java
public class MyThread extends Thread{
    static int ticket = 0;
    static Object obj = new Object();
    public MyThread(String name) {
        super(name);
    }

    @Override
    public void run() {
        while (true){
            synchronized (obj){
                if(ticket < 100){
                    try {
                        sleep(100);
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                    ticket++;
                    System.out.println(getName() + "在卖第" + ticket + "张票");
                }else{
                    break;
                }
            }
        }
    }
}
```

关于锁对象，如果你希望是唯一的，那么可以设成这个

```java
synchronized (MyThread.class){
    ....
}
```



> 同步方法

基本的格式为 ：

```java
修饰符 synchronized 返回类型 方法名(方法参数) {...}
```

锁对象不能自己指定

* 非静态 ： this

* 静态 ： 当前类的字节码文件对象



PS ： `StringBuffer` 是线程安全的，它每一个方法都是同步的， `StringBuilder` 则是不安全的



#### lock 锁

使用 `lock` 可以更加自由的实现对于锁的开启以及关闭

不过lock 不能直接实例化， 而是需要调用它的实现方法

一般lock有两个常用的方法， `lock.lock()` , `lock.unlock()`

```java
public static Lock lock = new ReentrantLock();
lock.lock();
lock.unlock();
```

不过为了更加优雅的将锁释放，所以更推荐使用  try-catch-finally

如下：

```java
public class MyThread extends Thread{
    static int ticket = 0;
    public MyThread(String name) {
        super(name);
    }
    public static Lock lock = new ReentrantLock();
    
    @Override
    public void run() {
        while (true){
            try{
                lock.lock();
                if(ticket >= 100) break;
                sleep(10);
                ticket++;
                System.out.println(getName() + " " + ticket);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            } finally {
                lock.unlock(); // 在finally里面释放资源
            }
        }
    }
}
```



#### 死锁

死锁是一种错误，要避免犯错

死锁实际上就是锁的嵌套， 无论如何都不能将锁嵌套起来



#### 等待唤醒机制

等待唤醒机制希望线程有规律的运行；

可以理解为有两个角色，一个负责生成，一个负责消费，

只有先生产才能消费

基本的思路如代码所示：



挖个坑：）



### 网络编程

#### 一些概念

> 常见的软件构造有 

CS / BS

CS : 客户端 / 服务器

BS ： 浏览器 / 服务器

> 通信的软件架构CS\BS的各有什么区别和优缺点

CS:   客户端服务端模式需要开发客户端

BS:   浏览器服务端模式不需要开发客户端

CS:   适合定制专业化的办公类软件如: IDEA、网游

BS:   适合移动互联网应用，可以在任何地方随时访问的系统

> 网络编程三要素

* IP

  * 设备在网络中的地址，是唯一的标识

  * > IPV4 : 目前已经被分配完毕
    >
    > IPV6 ： 为了解决IPV4不够用出现的
    >
    > > 为了解决IPV4不够用，也可以使用局域网 IP
    > >
    > > 特殊的 IP ： **127.0.0.1** （永远表示本机）
    > >
    > > 常见的 CMD命令
    > >
    > > * `ipconfig` 查看本机IP地址
    > > * `ping`

* 端口号

  * 应用程序在设备中唯一的标识

    > 端口取值范围为 ： $0$ ~ $65535$
    >
    > $0$ ~ $1023$ 用于一些知名的网络服务或者应用
    >
    > $1024$ 以上的端口号给我们自己使用
    >
    > **一个端口号只能给一个应用程序使用**

* 协议

  * 数据在网络中传输的规则, 常见的协议有UDP、TCP、http、https、ftp

    > **UDP协议（面向无连接）**
    >
    > 速度快，有大小限制，一次最多发送64kb，数据不安全，容易丢失数据
    >
    > **TCP协议（面向连接）**
    >
    > 速度慢，没有大小限制，数据安全



#### InetAddress 类

这个类就是用来表示 IP地址的， 这个类不能直接 new ，要使用其静态方法

创建方法有两个：

```java
public static void main(String[] args) throws Exception {
    InetAddress address = InetAddress.getByName("192.168.64.1"); // 通过 IP 来获取对象
    InetAddress address2 = InetAddress.getByName("DESKTOP-SS0ALGC");
    System.out.println(address2);
    System.out.println(address);
}
```

常见方法：

```java
public static void main(String[] args) throws Exception {
    InetAddress address = InetAddress.getByName("192.168.64.1"); // 通过 IP 来获取对象
    String name = address.getHostName(); //获取主机名， 如果ip错误则会返回ip
    String ip = address.getHostAddress(); //获取ip地址
    System.out.println(name);
    System.out.println(ip);
}
```



#### 使用 UDP协议

发送端：

```java
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class Send {
    public static void main(String[] args) throws Exception {
        //创建 DatagramSocket, 可以理解为快递公司
        //在构造的时候可以选择有参构造或者无参构造
        // 有参构造 ： 指定端口号， 无参构造： 随机可以使用的端口号
        DatagramSocket ds = new DatagramSocket();
        String content = "这是我要发的内容 - this is the content which I want to send";
        byte[] bytes = content.getBytes();
        InetAddress address = InetAddress.getByName("127.0.0.1"); // 设置要发送的地址
        int port = 10086; //指定要发送的端口号
        DatagramPacket dp = new DatagramPacket(bytes, bytes.length, address, port); // 打包数据
        ds.send(dp);
        ds.close();
    }
}
```

接收端

```java
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;


public class Receive {
    public static void main(String[] args) throws IOException {
        //接收时一定要绑定端口号，并且一定要和发送的端口号保持一致
        DatagramSocket ds = new DatagramSocket(10086);
        byte[] bytes = new byte[1024];
        DatagramPacket dp = new DatagramPacket(bytes, bytes.length);
        ds.receive(dp);
        ds.close();

        // 一些常用的方法 :
        byte[] data = dp.getData(); //实际上和bytes内容一样
        int length = dp.getLength(); //获取数据的长度
        InetAddress address = dp.getAddress(); //得到是哪个IP发来的内容
        int port = dp.getPort(); //获取对方是从哪个端口发来的信息
        System.out.println(length);
        System.out.println(address);
        System.out.println(port);

        // 关于解析数据，因为为了防止解析中文乱码的问题，使用之前IO流的转换流来解决
        System.out.println(new String(data, 0, length));
    }
}
```



> UDP 的三种发送方式

**单播**  ： 只给一台电脑发送数据

**组播** ： 给一组电脑发送数据

> 组播地址 ： 224.0.0.0 ~ 239.255.255.255
>
> 其中 224.0.0.0 ~ 224.0.0.255 为预留地址

代码示例：

发送

```java
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

public class Send {
    public static void main(String[] args) throws Exception {
        // 组播需要创建的对象是 MulticastSocket
        MulticastSocket ms = new MulticastSocket();
        String content = "这是我要发的内容 - this is the content which I want to send";
        byte[] bytes = content.getBytes();
        InetAddress address = InetAddress.getByName("224.0.0.1"); // 设置组播地址
        int port = 10086; //指定要发送的端口号
        DatagramPacket dp = new DatagramPacket(bytes, bytes.length, address, port); // 打包数据
        ms.send(dp);
        ms.close();
    }
}
```

接收

```java
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

public class Receive {
    public static void main(String[] args) throws IOException {
        //接收时一定要绑定端口号，并且一定要和发送的端口号保持一致
        MulticastSocket ms = new MulticastSocket(10086);

        // 将本机地址加入组播地址中
        InetAddress address = InetAddress.getByName("224.0.0.1");
        ms.joinGroup(address);

        byte[] bytes = new byte[1024];
        DatagramPacket dp = new DatagramPacket(bytes, bytes.length);
        ms.receive(dp);
        ms.close();

        // 关于解析数据，因为为了防止解析中文乱码的问题，使用之前IO流的转换流来解决
        System.out.println(new String(bytes, 0, dp.getLength()));
    }
}
```



**广播** ： 给所有电脑发送数据

> 广播地址 255.255.255.255

```java
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

public class Send {
    public static void main(String[] args) throws Exception {
        // 组播需要创建的对象是 MulticastSocket
        MulticastSocket ms = new MulticastSocket();
        String content = "这是我要发的内容 - this is the content which I want to send";
        byte[] bytes = content.getBytes();
        InetAddress address = InetAddress.getByName("255.255.255.255"); // 设置广播地址
        int port = 10086; //指定要发送的端口号
        DatagramPacket dp = new DatagramPacket(bytes, bytes.length, address, port); // 打包数据
        ms.send(dp);
        ms.close();
    }
}
// 会给局域网所有电脑发送消息
```



#### 使用 TCP协议

Client端（发送数据）

```java
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;

public class Client {
    public static void main(String[] args) throws IOException {
        // 如果连接不上会报错
        Socket socket = new Socket("127.0.0.1", 10086);
        OutputStream outputStream = socket.getOutputStream(); // 获取输出流
        String content = "内容 - content";
        outputStream.write(content.getBytes());
        outputStream.close();
        socket.close();
    }
}
// 可以尝试使用 try-with-sources
```

Service端

```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.Buffer;
import java.nio.charset.StandardCharsets;

public class Server {
    public static void main(String[] args) throws IOException {
        ServerSocket ss = new ServerSocket(10086);
        //死等，如果没有客户端来连接，则会一直等下去， 连接好了则会返回客户端的连接对象
        Socket accept = ss.accept();

        InputStream inputStream = accept.getInputStream();
        
        // 以下操作是为了解决中文乱码的问题
        InputStreamReader inputStreamReader = new InputStreamReader(inputStream, StandardCharsets.UTF_8);
        BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
        int ch;
        while((ch = bufferedReader.read()) != -1)
            System.out.printf("%c", (char)ch);

        inputStream.close();
        ss.close();
    }
}
// 可以尝试使用 try-with-sources
```



如果客户端发完后没有主动关闭连接， 那么服务器就会一直卡死在read上，所以如果不希望一致在read上等待，就需要在客户端上加上 ：

`socket.shutdownInput();`  或者 `socket.shutdownOutput();`



#### 三次握手和四次挥手

三次握手 ： 确保连接的建立

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230717195838217.png" alt="image-20230717195838217" style="zoom:80%;" />

四次挥手： 确保连接断开，且数据处理完毕

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230717200056694.png" alt="image-20230717200056694" style="zoom:80%;" />



> 拓展

如果需要不同的文件名， 可以使用Java 里面的UUID类

```java
public static void main(String[] args) {
    UUID uuid = UUID.randomUUID();
    System.out.println(uuid);
}
//5570a64a-3d66-48cd-87c5-31083cc2a734
```

转换：

```java
public static void main(String[] args) {
    String str = UUID.randomUUID().toString().replace("-", "");
    System.out.println(str);
}
//fd6c767f56514d05b6c6bec42fa5acf8
```



### 数据库操作

 ```java
 package JDBK;
 
 import java.sql.Connection;
 import java.sql.DriverManager;
 import java.sql.SQLException;
 import java.sql.Statement;
 
 public class JDBK {
     public static void main(String[] args) throws ClassNotFoundException, SQLException {
         Class.forName("com.mysql.jdbc.Driver");
         String url = "jdbc:mysql://127.0.0.1:3306/yyym"; // 最后面是数据库名称
         String username = "root";
         String password = "qq3109778990";
         Connection connection = DriverManager.getConnection(url, username, password);
 
         String code = "UPDATE name SET name = \"JAVA\" WHERE id = 456;"; // mysql语句
 
         Statement stmt = connection.createStatement();
 
         int i = stmt.executeUpdate(code);
 
         System.out.println(i);
 
         stmt.close();
         connection.close();
     }
 }
 ```

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230719205802539.png" alt="image-20230719205802539" style="zoom:80%;" />

如果不希望有安全提示，可以将其中的代码改为：

```java
String url = "jdbc:mysql://127.0.0.1:3306/yyym?useSSL=false"
```



查询

```java
package JDBK;

import java.sql.*;

public class JDBK {
    public static void main(String[] args) throws ClassNotFoundException, SQLException {
        Class.forName("com.mysql.jdbc.Driver");
        String url = "jdbc:mysql://127.0.0.1:3306/yyym?useSSL=false"; // 最后面是数据库名称
        String username = "root";
        String password = "qq3109778990";
        Connection connection = DriverManager.getConnection(url, username, password);

        Statement stmt = connection.createStatement();

        String sql = "SELECT name, age, workaddress FROM emp WHERE name LIKE '__';";

        ResultSet rs = stmt.executeQuery(sql);

        while(rs.next()){
            String name = rs.getString(1);
            int age = rs.getInt(2);
            String workAddress = rs.getString(3);
            System.out.println(name + " " + age + " " + workAddress);
        }

        rs.close();
        stmt.close();
        connection.close();
    }
}
```

