#欢迎来到这个项目!

##介绍

 1. 它是个音乐播放器
 2. 集合了 sdl   libzplay 以及 libiconv
 3. 我写的代码最核心的是红黑树的实现和控件的实现
 4. 有可能发展成为一个GUI框架
 5. 两个命名空间 Orz(平台无关) Program(平台相关)
 6. 仅供学习交流

###截图

截图1
![](https://github.com/endlesstravel/MusicPlayerWithOpenLib/blob/screenshot/screenshot01.png)

截图2
![](https://github.com/endlesstravel/MusicPlayerWithOpenLib/blob/screenshot/screenshot02.png)

###工作方式
解释为资源型程序,并非自顶端往下一条线发展
其中 三个部分 互相访问
device   
platfrom  
manage
从名字上就很好理解了,具体见main.cpp文件的使用

animate sprite 和 cotrol??(Text,Button,...) 通过manage间接,用户不容许直接访问

其中也受到了开源游戏引擎Ogre的影响,所有有点它的风格.

###完成度

从非编程人员的角度上看:
- [ ] 和bilibili上一模一样
- [ ] 具有和播放器一样的功能(除了网页模块)
-     [x] 进度条
-     [x] 时间
-     [ ] 玻璃网背景
-     [ ] 粒子效果
-     [ ] 3D三角形背景
- [x]背景一样
- 
- 从程序员的角度看:
- [x] 实现了动画
- [ ] 控件
-     [x] 文本控件 ControlText
-     [x] 按钮控件 ControlButton
-     [x] 滚动条控件 ControlBar
-     [x] 列表控件 ControlList
-     [ ] 聚合控件 ConrolPage
-     [ ] 其他控件 ControlXX??
- [x] 统一加载控件,创建控件
- [ ] 统一管理控件,以实现控件焦点的概念
- [ ] 利用XML文件组织画面排版
- [ ] .........

###其他
其实这个项目的名字,不太符合它的内容.因为这是一个音乐播放器.

>灵感源自哔哩哔哩的[这个视频](http://www.bilibili.com/video/av1750418)

>悄悄告诉你,这是用[StackEdit](https://stackedit.io/)在线编辑器写的 : )


##部署
*获取源文件<br>
*获取附件 resource.zip, dll.zip<br>
*在项目中添加 源文件 sdl  libzplay 和 libiconv的头文件和链接库<br>
*注释掉头文件orz_option.h里的 #define CodeDebug(否则会有红色调试线条出现)
*编译<br>
*在目录下解压resource.zip, dll.zip<br>
**`!!!!!重要`修改resource\playlist.m3u添加歌曲,运行<br>
