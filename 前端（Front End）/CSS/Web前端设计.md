# Web前端设计

## html的基本框架

```html
<!DOCTYPE html>
<html lang = "zh-CN">
	<head>
		<meta charset="UTF-8">
		<title>yyym 的小书店</title>
	</head>
	<body>
		
	</body>
</html>
```

## 原信息 \<meta\>标签

**\<meta\>标签属性和值**

|   http-equiv    |    name     |  content  |
| :-------------: | :---------: | :-------: |
|     expires     |   author    | some_text |
|     refresh     | description |           |
| X-UA-Compatible |  keywords   |           |
|                 |  generator  |           |
|                 |   revised   |           |
|                 |   robots    |           |
|                 |  viewport   |           |

**解释一些常用的**

* `http-equiv`

  * expires:

    > 浏览器大多数会采取累积式加速的方法，将曾经访问过的网站存放在浏览器缓存里，在搜索某个内容时，会在浏览器的缓存中先进行搜索，如果找不到才会继续在网上搜索下载。而expires是用来试着网页在缓存区的到期时间，expires必须采用GMT的时间格式
    >
    > `<meta http-equiv = "expires" content = "Fri, 5, Mar 2023 10:10:10 GMT + 8">`

  * refresh

    > 用于刷新和重定向网页
    >
    > content的内容代表等待的时间，而后面的URL如果有指定，那么就去访问该URL，如果没有指定URL，则自动刷新该页面
    >
    > `<meta http-equiv = "refresh" content = "5"; URL = "https://www.luogu.com.cn">`

  * X-UA-Compatible

    > X-UA-Compatible是为了兼容而生
    >
    > 用来指定使用某个特定IE浏览器的渲染方式
    >
    > `<meta http-equiv = "X-UA-Compatible" content = "IE=edge">`
    >
    > `"IE=edge"`指使用最新的IE内核进行渲染
    >
    > `<meta http-equiv = "X-UA-Compatible" content = "IE=edge， chrome=1">`
    >
    > `"IE=edge， chrome=1"`指如果用户安装了Google Chrome Frame，就用他来渲染，否则使用最新IE内核

* `name`

  * robots

    > robots的参数有**all** , **none** , **index** , **noindex** , **follow** , **nofollow** , 默认情况下为 all
    >
    > **all** : 允许搜索机器人检索网页，网页的链接可以被访问
    >
    > **none** : 不允许搜索机器人检索网页，网页的链接不可以被访问
    >
    > **index** ： 允许搜索机器人检索网页，可以让 robot/spider登录
    >
    > **noindex** ： 不允许搜索机器人检索网页，网页的链接可以被访问，不让 robot/spider登录
    >
    > **follow** ： 网页的链接可以被访问
    >
    > **nofollow** ： 不允许搜索机器人检索网页，网页的链接可以被访问， 不让 robot/spider顺着此页链接往下探查

  * keywords + description

    > 关键词及描述
    >
    > 自动搜索机器人会自动在Internet上搜索，如果没有这两项，机器人将无法将你网站加入检索数据库，用户也就无法搜索到，机器人将会根据关键词的密度进行排序。
    >
    > 提高被搜索到的优先级可以查阅SEO（搜索引擎优化），这是一种根据搜索引擎的搜索规则来提高自然排名的方法

  * author

    > 输入作者
    >
    > `<meta name = "author" content="yyym">`

  * viewport

    > viewport指浏览的视图，也就是网页的实际显示区域
    >
    > 如果希望网页在移动设备中以网页原本画面显示，可以这样：
    >
    > `<meta name="viewport" content="width=device-width", inital-scale="1.0">`
    >
    > `"width=device-width"`值视窗等于设备的宽度
    >
    > `inital-scale=`代表按实际比例显示，无任何缩放

**代码示例**

```html
<!DOCTYPE html>
<html lang = "zh-CN">
    <head>
        <meta charset = "UTF-8">
        <title>yyym's bookstore</title>
        <meta http-equiv="X-UA-Compatible" content="edge, chorme = 1">
        <meta name="author" content="yyym_SCNU">
        <meta name="keywords" content="书店, yyym, bookstore, book">
        <meta name="description" content="这是一个初学者的第一次前端小尝试，想做一个用于售卖图书的网页">
        <meta name="viewport" content="width = device-width, initial-scale=1.0">
    </head>
    <body>
        <h1>啥也没有</h1>
    </body>
</html>
```

