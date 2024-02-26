# 平台
**Windows 11 x64**下找到**bin/Win/SDL_project.exe**即可运行游戏
# C语言环境
* MinGW w64 11.0  CLion
# 编译选项

* CMake: Bundled Version: 3.27.8

* Build Tool: ninja.exe

* C Compile gcc.exe

* C++ Compile g++.exe

* Debuger: Bundled GDB Version: 13.2

编译参数：默认

# 使用的第三方库
* SDL库
# 游戏方式
## （1）键位设置
1. 菜单界面：鼠标点击**start/quit**即可**开始/结束**游戏
2. 游戏界面：只有键盘**Space**键一个输入。长按蓄力，放开跳跃
3. 死亡界面：鼠标点击**Home Page/restart/quit**即可**返回主页/开始/结束**游戏
## （2）游戏玩法
1. 三种特殊块：**红包块、唱片块、TNT块**。停留在三种特殊块上**3秒**可获得 **+5分/放音乐/爆炸** 的buff/debuff
2. 基本规则：参考微信跳一跳,且分数越高难度随之增高（如可加分的红包块不再刷新、出现TNT块、跳板变小等等）
3. 不要让你的棋子脱离跳板！开始你的游戏吧
# 游戏特色

>**地形生成**

&nbsp; &nbsp; &nbsp; &nbsp; 跳板能够随机并且连续地生成

>**物理模拟**

&nbsp; &nbsp; &nbsp; &nbsp; 精确地判定棋子是否真的落在跳板上


>**本地记录**

&nbsp; &nbsp; &nbsp; &nbsp; 使用fread/fwrite读取和记录最高分, 即使退出游戏你还是可以向朋友炫耀你的最高分(
