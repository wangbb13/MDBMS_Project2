# MDBMS_project2

## Debug 出的问题

1、循环变量的类型

```c++
std::size_t p = N; p >= 0; --p
// 错误，无符号类型
```

2、循环内部创建的变量在循环一次后不会保存。

3、point-wise算法的问题

​	首先，与baseline算法相比，得到的结果数量较少

​	于是，推断 Tail Set 剪枝过多，我真是机智 :happy:

## 优化

1、不要创建一个set或vector再插入；（需要验证是否有效）