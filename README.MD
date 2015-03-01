#欢迎来到这个项目!

##介绍

 1. 它是个音乐播放器
 2. 集合了 sdl   libzplay 以及 libiconv
 3. 我写的代码最核心的是红黑树的实现和控件的实现
 4. 有可能发展成为一个GUI框架
 5. 两个命名空间 Orz(平台无关) Program(平台相关)
 6. 仅供学习交流

###工作方式
解释为资源型程序,并非自顶端往下一条线发展
其中 三个部分 互相访问
device   
platfrom  
manage
从名字上就很好理解了,具体见main.cpp文件的使用

animate sprite 和 cotrol??(Text,Button,...) 通过manage间接,用户不容许直接访问

###其他
其实这个项目的名字不太符合它的内容.因为这是一个音乐播放器
灵感源自哔哩哔哩的[这个视频](http://www.bilibili.com/video/av1750418)

>悄悄告诉你,这是用[StackEdit](https://stackedit.io/)在线编辑器写的 : )


##部署
*获取源文件
*获取附件 resource.zip, dll.zip
*在项目中添加 源文件 sdl  libzplay 和 libiconv的头文件和链接库
*编译
*在目录下解压resource.zip, dll.zip
*运行