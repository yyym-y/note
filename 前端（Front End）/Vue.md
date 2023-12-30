# Vue



## watch（监听器）



## 普通组件的的注册

* 局部注册

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230828143542924.png" alt="image-20230828143542924" style="zoom:80%;" />

组件名和组件对象一样时，可以直接简写

* 全局注册

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230828143659936.png" alt="image-20230828143659936" style="zoom:80%;" />

## scoped

在组件中使用scoped时，样式只会影响当前组件



## data

在vue例中， data是函数

```vue
data() {
	return {
		...
	}
}
```



## 组件通行

组件之间的数据通信

* 父子关系

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230828144217071.png" alt="image-20230828144217071" style="zoom:80%;" />

儿子无法修改数据，需要通知父组件修改

组件名要使用Multiple-word

传值：

father

```vue
<template>
  <div>
    <son :info="num"></son>
  </div>
</template>

<script>
import son from '@/components/Son-info'
export default {
    data() {
        return {
            'num': 10
        }
    },
    components: {
        son
    }
}
</script>
```



son

```vue
<template>
  <div>
    <div>{{ info }}</div>
  </div>
</template>

<script>
export default {
    props: ['info']
}
</script>
```



son 通知 father 修改

father

```vue
<template>
  <div>
    <son :info="num" @changeInfo="fatherWay"></son>
  </div>
</template>

<script>
import son from '@/components/Son-info'
export default {
    data() {
        return {
            num : 10
        }
    },
    components: {
        son
    },
    methods: {
      fatherWay(Newvalue) {
        this.num = Newvalue
      }
    }
}
</script>
```

son

```vue
<template>
  <div>
    <div @click="change">{{ info }}</div>
  </div>
</template>

<script>
export default {
    props: ['info'],
    methods: {
      change() {
        this.$emit("changeInfo", 1000)
      }
    }
}
</script>
```

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230828151244260.png" alt="image-20230828151244260" style="zoom:80%;" />

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230828151412094.png" alt="image-20230828151412094" style="zoom:80%;" />



* 非父子关系

* * 兄弟

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230828151606632.png" alt="image-20230828151606632" style="zoom:80%;" />

* * 跨层级

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230828151710049.png" alt="image-20230828151710049" style="zoom:80%;" />



## v-model

<img src="C:/Users/%E9%98%B4%E9%93%AD%E6%B4%8B/AppData/Roaming/Typora/typora-user-images/image-20230828151915741.png" alt="image-20230828151915741" style="zoom:80%;" />



## .sync

