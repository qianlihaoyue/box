c语言第三个作品。

依然采用了<a href="https://www.easyx.cn">easyx</a>图形库，v2.0里有控制台推箱子游戏。



<h2>Todo</h2>
<<<<<<< HEAD

* [x] 撤销 z
=======
* [ ] 撤销 z   
>>>>>>> 65275209db5c4e6dcedd7668356deb67312b4617
* [ ] 自定义地图，从文件读取地图
* [ ] 选关模式
* [ ] bgm
* [ ] 优化撤销功能
* [ ] 优化UI
* [ ] 代码添加注释，虽然我现在已经有点看不懂了



<h2>主体思路</h2>

* 地图即是一个二维数组，储存值对应表

  |  0   |  1   |  2   |   3    |  4   |   5    |  6   |   7    |
  | :--: | :--: | :--: | :----: | :--: | :----: | :--: | :----: |
  | 空地 |  人  |  墙  | 空箱子 |  星  | 人和星 |      | 实箱子 |

  

* 共存问题 直接转为 加减问题，比如`人（1）+星（4）=人和星共存（5）`
