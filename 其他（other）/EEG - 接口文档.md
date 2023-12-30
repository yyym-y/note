# EEG - 接口文档

### 说明

* **后端返回数据统一格式（Json）**

  > 数据错误返回格式
  >
  > ```JSON
  > {
  >     "code": 0, // 正确1 / 错误0
  >     "msg": "error", // 返回提示信息
  >     "data": null // 正确会返回数据
  > }
  > ```
  >
  > 数据正确返回格式
  >
  > ```JSON
  > {
  >     "code": 1,
  >     "msg": "success",
  >     "data": "info"
  > }
  > ```



* 数据请求风格为 **Restful风格**

  > get请求（常用）—> 对应查询操作
  > post请求（常用）—> 对应新增操作
  > put请求 —> 对应修改操作
  > delete请求 —> 对应删除操作



* 关于报头信息

  > 除了 /LogIn 包含且以内的接口都需要在报头携带 JWT令牌
  >
  > 报头格式如下：
  >
  > ```
  > Authorization: ... // JWT 令牌
  > ```



* 跨域问题

  后端已经做了跨域处理，前端不需要考虑



### 初始页面图片 （/LogIn）

请求方式 `Get`

* 请求参数 ： `null`

* 返回参数示例

  > ```json
  > {
  >  "code": 1,
  >  "msg": "success",
  >  "data": {
  >      "Pic1": "https://gitee.com/....",
  >      "Pic2": "https://gitee.com/....",
  >      "Pic3": "https://gitee.com/...."
  >  }
  > }
  > ```
  >
  > 具体图片的数量及名字之后确定
  
* 数据库位置 ： EEG / LogIn_Pic



### 登录校验 （/LogIn/Check）

请求方式 `Get`

* 请求参数 

  > ```json
  > {
  >     "userName" : "yyym",
  >     "password" : "12345"
  > }
  > ```

* 返回参数

  > 错误
  >
  > ```json
  > {
  > "code": 0,
  > "msg": "UserNameOrPasswordError",
  > "data": null
  > }
  > ```
  >
  > 正确
  >
  > ```json
  > {
  > "code": 1,
  > "msg": "success",
  > "data": {
  >   "JWT": "......",
  >   "userName": "yyym",
  >   "id" : 1
  >   }
  > }
  > ```
  >
  > JWT 处返回具体的令牌





### 文件上传 （/Upload）

请求方式 `post`

* 请求参数

  > 在 `body` 的 `form-data` 上携带相应的文件

* 返回参数

  > 错误
  >
  > ```json
  > {
  > "code": 0,
  > "msg": ".....", // 不同错误返回不同的信息
  > "data": null
  > }
  > ```
  >
  > 正确
  >
  > ```json
  > {
  > "code": 1,
  > "msg": "success",
  > "data": {
  >     "time" : [.....],
  >     "channel" : ["...", "....", ...],
  >     "info" : [
  >      	[....], [....], ... // 数量与channel数量一致           
  >     ]
  > }
  > ```



