#欢迎来到这个项目!

##介绍

 1. 它是个音乐播放器
 2. 集合了 sdl   libzplay 以及 libiconv
 3. 我写的代码最核心的是红黑树的实现和控件的实现
 4. 有可能发展成为一个 UI 框架(见截图3)
 5. 两个命名空间 Orz(平台无关) Program(平台相关)
 6. 此项目仅供学习交流

###截图

截图1
![](https://raw.githubusercontent.com/endlesstravel/MusicPlayerWithOpenLib/demo/screenshot01.png)

截图2
![](https://raw.githubusercontent.com/endlesstravel/MusicPlayerWithOpenLib/demo/screenshot02.png)

截图3
![](https://raw.githubusercontent.com/endlesstravel/MusicPlayerWithOpenLib/demo/tree.png)

###工作方式
解释为资源型程序,并非自顶端往下一条线发展

其中 三个部分 它们可以互相访问,都是各自的友元<br>
         |- display<br>
device --|- sound<br>
         |- input<br>
platfrom  <br>
manager<br>
从名字上就很好理解了,具体见main.cpp文件和其他源文件的使用<br>

animate sprite 和 cotrol??(Text,Button,...) 通过manage间接,用户不容许直接访问

其中也受到了开源游戏引擎Ogre的影响,所有有点它的风格.

###完成度

- 从非编程人员的角度上看:
- [ ] 和bilibili上一模一样
- [ ] 具有和播放器一样的功能(除了网页模块)
      - [x] 进度条
      - [x] 显示时间
      - [x] 控制时间(空格暂停/单击时间条调整进度)
      - [x] 拖拽播放
      - [ ] 玻璃网背景
      - [ ] 粒子效果
      - [ ] 3D三角形背景
- [x] 背景一样<br>


- 从程序员的角度看:
- [x] 可以自动修改注册表,使.MP3文件默认为这个播放
- [x] 勉强可以运行了
- [x] 实现了动画
- [x] 控件
      - [x] 文本控件 ControlText
      - [x] 按钮控件 ControlButton
      - [x] 滚动条控件 ControlBar
      - [x] 列表控件 ControlList

- [x] 统一加载控件,创建控件
- [x] 统一管理控件,以实现控件焦点的概念
- [ ] 利用XML文件组织画面排版
- [ ] .........

###其他
其实这个项目的名字,不太符合它的内容.因为这是一个音乐播放器.

>灵感源自哔哩哔哩的[这个视频](http://www.bilibili.com/video/av1750418)

