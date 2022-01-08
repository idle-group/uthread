# 1. 课程设计任务、要求、目的

## 1.1 课程设计任务

 依据操作系统课程所介绍的线程知识，实现一个用户级线程库。

## 1.2 课程设计目的和要求

- 建立用户级线程库
- 至少包括线程的创建、撤销、状态转换等，以及线程切换
- 库写好后，构建一个程序，演示线程库的使用

# 2. 开发环境

Visual Studio 2022

# 3. 相关原理及算法

实现的核心为线程的创建和调度，具体流程如下：

<img src="image/image-20220108181910799.png" alt="image-20220108181910799" style="zoom:50%;" />

<img src="image/image-20220108182105843.png" alt="image-20220108182105843" style="zoom:50%;" />

<img src="image/image-20220108182120996.png" alt="image-20220108182120996" style="zoom:50%;" />

![image-20220108182136962](image/image-20220108182136962.png style="zoom:50%;")

<img src="image/image-20220108182159078.png" alt="image-20220108182159078" style="zoom:50%;" />

<img src="image/image-20220108182218736.png" alt="image-20220108182218736" style="zoom:50%;" />

<img src="image/image-20220108182233576.png" alt="image-20220108182233576" style="zoom:50%;" />

<img src="image/image-20220108182245245.png" alt="image-20220108182245245" style="zoom:50%;" />

<img src="image/image-20220108182258155.png" alt="image-20220108182258155" style="zoom:50%;" />

<img src="image/image-20220108182310046.png" alt="image-20220108182310046" style="zoom:50%;" />

<img src="image/image-20220108182328875.png" alt="image-20220108182328875" style="zoom:50%;" />

<img src="image/image-20220108182346034.png" alt="image-20220108182346034" style="zoom:50%;" />

<img src="image/image-20220108182403380.png" alt="image-20220108182403380" style="zoom:50%;" />

<img src="image/image-20220108182416313.png" alt="image-20220108182416313" style="zoom:50%;" />

<img src="image/image-20220108182429286.png" alt="image-20220108182429286" style="zoom:50%;" />

<img src="image/image-20220108182441861.png" alt="image-20220108182441861" style="zoom:50%;" />

<img src="image/image-20220108182457898.png" alt="image-20220108182457898" style="zoom:50%;" />

<img src="image/image-20220108182518132.png" alt="image-20220108182518132" style="zoom:50%;" />

<img src="image/image-20220108182533036.png" alt="image-20220108182533036" style="zoom:50%;" />

<img src="image/image-20220108182549782.png" alt="image-20220108182549782" style="zoom:50%;" />

<img src="image/image-20220108182604191.png" alt="image-20220108182604191" style="zoom:50%;" />

<img src="image/image-20220108182619611.png" alt="image-20220108182619611" style="zoom:50%;" />

<img src="image/image-20220108182640122.png" alt="image-20220108182640122" style="zoom:50%;" />

<img src="image/image-20220108182656661.png" alt="image-20220108182656661" style="zoom:50%;" />

# 4. 系统结构和主要的算法设计思路

> 已在上面（3）中分析

# 5. 程序实现---主要数据结构

描述所设计系统的关键数据结构。

# 6. 程序实现---主要程序清单

描述所设计系统的核心程序、关键函数的程序清单。

# 7. 程序运行的主要界面和结果截图

列出系统运行的主要界面和运行结果截图。

# 8. 总结和感想体会

在本次的OS课程设计中，我最大的收获是加深了对线程的理解。**线程是在一个地址空间下启动并交替执行的程序，用户级线程用用户管理。**

# 参考文献

无

# 附录

无

 
