# Library for OIers 介绍

![Static Badge](https://img.shields.io/badge/g%2B%2B-11.4.0-blue)

## 简介

一个各种简单功能的库。

## 内容

### 高精度

[洛谷上写的](https://www.luogu.com.cn/article/erudth23)

就是以`char`储存255为单位的高精度。

### 数学

因为有挺多都实现过了，这里就写了卡塔兰数和埃筛。

### 快读快写

利用`getchar`和`putchar`的。

这个就比较常见了。

## 安装

把本项目根目录下的`lib`和`include`的文件复制到对应位置即可。

或者，在`Docker`上直接使用配置好的环境：
```bash
$ docker pull ghcr.nju.edu.cn/gokiburisoldier/lo_env
$ docker tag ghcr.nju.edu.cn/gokiburisoldier/lo_env lo_env
$ docker run -it lo_env
```
