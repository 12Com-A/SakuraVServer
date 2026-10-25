# SakuraV 木马

SakuraVServer 一款简易的远程木马控制端

SakuraVServer [服务端](https://github.com/12Com-A/SakuraVServer)
 
## 目录

- [上手指南](#上手指南)
  - [开发前的配置要求](#开发前的配置要求)
  - [部署](#部署步骤)
- [原理](#原理)
- [作者](#作者)

### 上手指南

注意：禁止用于任何违法用途 仅供学习与参考

###### 开发前的配置要求

1. 一台电脑 x86架构
2. 一个公网IP

###### **部署步骤**

第一步：下载项目源码

```sh
git clone https://github.com/12Com-A/SakuraV.git
```

第二步：使用Visual Studio 打开项目

- 使用VS2026打开 SakuraVServer.slnx 文件


<img width="452" height="24" alt="image" src="https://github.com/user-attachments/assets/78822803-f7b9-4534-9cfe-111ed5d82b5a" />

- 在SakuraVServer.cpp 修改控制端口（要与服务端保持一致）

```cpp
addr.sin_port = htons(8073);
```
- 将8073修改成你想要的端口

第四步：

- 构建即可

### 原理

- 循环监听端口连接
- 连接成功后发送指令

### 作者

Commkom 开发者
Email：commkom@qq.com

### 版权说明

该项目签署了 MIT 授权许可，详情请参阅 [LICENSE.txt](https://github.com/12Com-A/SakuraVServer/LICENSE.txt)
