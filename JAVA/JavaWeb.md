# JavaWeb 快速手册

## SpringBoot

### 快速尝试

```java
// 启动类， 简单来说就是用来启动项目的
@SpringBootApplication
public class Test3Application {
    public static void main(String[] args) {
        SpringApplication.run(Test3Application.class, args);
    }
}
```

运行这个启动类就可以开机服务器， 默认端口号 8080

```java
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

// 加上这个注解就代表这是一个请求处理了
@RestController
public class FirstTry {
    // 代表浏览器请求 /Hello这个地址调用这个方法
    @RequestMapping("/Hello")
    public String hello(){
        System.out.println("hello world");
        return "hello";
    }
}
```

访问网址为 `[localhost:8080/Hello](http://localhost:8080/Hello)`



### HTTP 协议

> HTTP 请求数据的格式

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230723222610594.png" alt="image-20230723222610594" style="zoom:80%;" />

常见的请求体

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230723222434136.png" alt="image-20230723222434136" style="zoom:80%;" />

> HTTP 相应数据的格式

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230723222958244.png" alt="image-20230723222958244" style="zoom:80%;" />

相应状态码：

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230723223033628.png" alt="image-20230723223033628" style="zoom:80%;" />



### 参数的接受

#### 接受简单参数

```java
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class RequestInfo {

    @RequestMapping("/GetSimpleInfo")
    public String getInfo(String name, Integer age, String school){
        // 参数名与请求的名字要一样，不然会产生NULL
        System.out.println(name + " " + age + " " + school);
        return "OK";
    }
}
```

如果不一样，就需要添加注解

`@RequestParam(name = "---")`

```java
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class RequestInfo {
    @RequestMapping("/GetSimpleInfo")
    public String getInfo(@RequestParam(name = "name") String myName, Integer age, String school){
        System.out.println(myName + " " + age + " " + school);
        return "OK";
    }
}
```

> `@RequestParam(name = "name")` 的required默认是ture，表示参数必须传递
>
> 如果不希望必须传递，则改为false `@RequestParam(name = "name", required = false)`



#### 接受实体参数

如果请求参数过多， 可以将他封装为实体类

```java
//类的代码
package org.yyym.cclass;

public class User {
    //参数要都存在
    public String name;
    public Integer age;
    public String school;

    //下面的代码必须但可以自动生成
    @Override
    public String toString() {
        return "User{" +
                "name='" + name + '\'' +
                ", age=" + age +
                ", school='" + school + '\'' +
                '}';
    }
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public Integer getAge() {
        return age;
    }
    public void setAge(Integer age) {
        this.age = age;
    }
    public String getSchool() {
        return school;
    }
    public void setSchool(String school) {
        this.school = school;
    }
}

```

```java
@RequestMapping("/GetClassInfo1")
public String getClassInfo(User user){
    System.out.println(user);
    return "OK";
}
```

如果参数里面还有类

即 `User` 类里面还有 `Address`

```java
代码与之前完全一样
```

请求方式如下：

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230723233553160.png" alt="image-20230723233553160" style="zoom:80%;" />

#### 数组 / 集合 参数

应用场景为复选框组件

数组请求方式如下：

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230724170848517.png" alt="image-20230724170848517" style="zoom:80%;" />

数组接收端如下：

```java
@RequestMapping("/GetVector")
public String getVector(String[] name){
    System.out.println(Arrays.toString(name));
    return "OK";
}
```

集合接收端为：

```java
@RequestMapping("/GetVector")
public String getVector(@RequestParam List<String> name){
    System.out.println(name);
    return "OK";
}
```



#### 时间参数

服务端要统一接收的格式(使用注解)

```java
@RequestMapping("/GetTime")
public String getTime(@DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss") LocalDateTime time){
    System.out.println(time);
    return "OK";
}
```



#### Json格式

Json数据必须使用post请求，写在请求体之中

一般使用实体类来接收，要加上注解并且参数名要一致

```java
@RequestMapping("/GetJson")
public String getJson(@RequestBody User user){
    System.out.println(user);
    return "OK";
}
```

同时如果是多层嵌套，则和之前的方法一样



#### 路径参数

也就是说， 参数成了访问网址的一部分

假设请求时发送的内容为 1 ，则请求地址为 `..../path/1` , 100 就是 `..../path/100`

服务端接收方法

```java
@RequestMapping("/path/{var}")
public String getPath(@PathVariable Integer var){
    System.out.println(var);
    return "OK";
}

@RequestMapping("/path/{var}/{name}")
public String getPath(@PathVariable Integer var, @PathVariable String name){
    System.out.println(var + " " + name);
    return "OK";
}
```



### 返回数据

#### @ResponseBody 注解

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230724175110535.png" alt="image-20230724175110535" style="zoom:80%;" />

#### 返回规范

为了统一管理返回给前端数据的格式规范，一般都是返回一个Result类

类如下：

```java
package org.yyym.cclass;

public class Result {
    private Integer code; //响应码 ： 1成功， 0 失败
    private String msg; //提示信息
    private Object data; //返回的数据

    public Result(){}
    public Result(Integer code, String msg, Object data){
        this.code = code; this.msg = msg; this.data = data;
    }
	// 必须要有get / set 方法
    public Integer getCode() {  return code; }
    public void setCode(Integer code) {  this.code = code; }
    public String getMsg() { return msg; }
    public void setMsg(String msg) { this.msg = msg; }
    public Object getData() { return data; }
    public void setData(Object data) { this.data = data;}

    public static Result success(Object data){
        return new Result(1, "success", data);
    }
    public static Result success(){
        return new Result(1, "success", null);
    }
    public static Result error(String msg){
        return new Result(0, msg, null);
    }
}
```



#### 分层解耦

 如果逻辑全部写在一份代码里，那么将会变得难以维护以及复用性差，所以我们使用分层解耦



> 三层架构

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230724181929227.png" alt="image-20230724181929227" style="zoom:80%;" />

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230724181859553.png" alt="image-20230724181859553" style="zoom:80%;" />

我们现在尝试书写一下基础的分层目标是查询Mysql中的员工信息

> Dao 端

```java
package org.yyym.emp;
import java.util.List;

// 我们面向接口编程，所有的实现查询数据的类都需要实现这个接口
// 用接口也更方便使用多态
public interface GetInfo {
    // 获取数据
    List<Emp> getInfo();
}
```

```java
package org.yyym.emp.getInfoMethod;
import org.yyym.emp.Emp;
import org.yyym.emp.GetInfo;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class GetInfoFromMysql implements GetInfo {
    private String url = "jdbc:mysql://127.0.0.1:3306/yyym?useSSL=false";
    private String username = "root";
    private String password = "qq3109778990";
    @Override
    public List<Emp> getInfo() {
        try {
            Connection connection = DriverManager.getConnection(url, username, password);
            String code = 
                "SELECT workno , name, gender, age, idcard, workAddress FROM emp WHERE ! (idcard IS NULL);";
            Statement stmt = connection.createStatement();
            ResultSet rs = stmt.executeQuery(code);
            List<Emp> info = new ArrayList<>();
            while (rs.next()){
                String workNum = rs.getString(1), name = rs.getString(2);
                String gender = rs.getString(3); Integer age = rs.getInt((4));
                String idCard = rs.getString(5), workAddress = rs.getString(6);
                    info.add(new Emp(workNum, name, gender, age,idCard, workAddress));
            }
            return info;
        } catch (SQLException e) {
            System.out.println("数据库读取异常");
            throw new RuntimeException(e);
        }
    }
}
```



> Service 端

```java
package org.yyym.emp;
import java.util.List;
// 定义接口，所有处理逻辑的类都继承此接口，然后再service里面实现
public interface Service {
    List<Emp> service();
}
```

```java
package org.yyym.emp.infoProcessMethod;
import org.yyym.emp.Emp;
import org.yyym.emp.GetInfo;
import org.yyym.emp.Service;
import org.yyym.emp.getInfoMethod.GetInfoFromMysql;
import java.util.List;

public class ProcessByOne implements Service {
    // 多态的写法，定义接口对象
    private GetInfo getInfo = new GetInfoFromMysql();
    @Override
    public List<Emp> service() {
        List<Emp> emp = getInfo.getInfo();
        emp.stream()
                .forEach(emp_ -> {
                    String city = emp_.workAddress;
                    emp_.workAddress = (city.equals("深圳") || city.equals("上海") ? "一线城市" : "二线城市");
                });
        emp.stream()
                .forEach(emp_ -> emp_.idCard = "不予展示");
        return emp;
    }
}

```

> Controller

```java
@RestController
public class RequestInfo {
	private Service service = new ProcessByOne();
    @RequestMapping("/Project/Emp")
    public Result getEmp(){
        List<Emp> emp = service.service();
        return Result.success(emp);
    }
}
```



**现在进行解耦操作**

可以发现如果我们查询的方式发生改变，或者逻辑发生改变，我们会关联到其他部分, 因为有

 `private GetInfo getInfo = new GetInfoFromMysql();` 

`    private Service service = new ProcessByOne();`

所以我们不能直接 `new`



#### 控制反转（IOC）/ 依赖注入（DI）

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230724203019136.png" alt="image-20230724203019136" style="zoom:80%;" />

简单叙述：

如果需要这个类创建时将其放入容器，就需要再类前面加上 `@Component`

如果需要内容由容器里面提供，则加上注解 `@Autowired`

所以上述代码部分变为：

```java
@Component
public class ProcessByOne implements Service {
    @Autowired
    private GetInfo getInfo;
    @Override
    public List<Emp> service() {
        ....
    }
}
```

```java
@RestController
public class RequestInfo {
    @Autowired
    private Service service;
    @RequestMapping("/Project/Emp")
    public Result getEmp(){
    }
}
```

如果需要切换， 将 `@Component` 注释即可

拓展：

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230724204403489.png" alt="image-20230724204403489" style="zoom:80%;" />

如果 `Service`接口由两个实现类并且全部都有`@Component` ，那么这个时候运行程序会报错

不过可以通过其他的方式让他生效

1. 如果需要某个`@Component` 生效， 你可以在其之上加上`@Primary` 
2. 在 `@Autowired` 上加上 `@Qualifier("processByOne")` 属性 (括号里面写类名，首字母小写)
3. 与第二个同理， 不过括号里面的内容不一样 `@Resource(name = "processByOne")`



## Mybatis

是为了更加方便的操作数据库

> 配置数据库连接信息

在 SpringBoot 的默认文件 `application.properties` 中配置信息

```
spring.datasource.driver-class-name=com.mysql.cj.jdbc.Driver
spring.datasource.url=jdbc:mysql://localhost:3306/yyym
spring.datasource.username=root
spring.datasource.password=qq3109778990
```





## lombok

```java
@Data //生成Getter / Setter / toString
@NoArgsConstructor // 生成无参构造
@AllArgsConstructor // 生成有参构造
```



## 拦截器
