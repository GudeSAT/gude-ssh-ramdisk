# gude-ssh-ramdisk

允许您为指定的ios/ipados版本启动restoreramdisk

（仅适用于CHECKM8兼容设备！）

环境安装地址： https://www.goodsat.cn/2576/

```
支持macOS catalina 10.15或者更高系统版本, 必须安装xcode!!!

暂时不支持Linux和Windows
```
SHSH2备份网站:

 https://tsssaver.1conan.com/
 
 https://shsh.host/

只有这样而已

如果提示找不到ldid2，按照以下方法安装：
打开终端输入git clone https://github.com/xerub/ldid.git回车
输入cd ldid回车
输入make回车
最后输入cp ldid2 /usr/local/bin回车
ok，安装完成

使用方法演示：

1.解压

2.打开终端输入sudo chmod -R 777 加上文件夹路径，回车输入电脑密码，再次回车即可

3.终端继续输入cd 解压文件的路径回车

4.继续在终端输入./RamdiskMaker -d iPhone8,1 -i 15.3.1 -b n71map -s bla/blob.shsh2回车

5.根据终端提示操作即可

```
（ 如果发现有其他问题，请联系我，我会帮助你修复使用它 )

( 我是小白，依赖环境问题可能写的不全，大家多担待点 )

（ https://www.goodsat.cn 古德制作 ）

（ 感谢所有人对我的支持，我会继续努力的 )

