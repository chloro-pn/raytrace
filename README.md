# raytrace

基于c++11的光线追踪渲染器，独立于绘图平台。

2020-04-08:

目前处理了相机的移动和旋转以及光线和三角形的相交计算逻辑。目前的光照模型非常简单，仅仅根据光线方向与表面法相量的夹角大小与环境光进行设置，
严格来说算不上光照模型，在此仅为了验证其他程序逻辑的正确性（比如说相机逻辑）。

用以上光照模型渲染的第一张图片！

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/1.png" width="600" height="450">

背景颜色黑色，环境光白色，环境光反射系数: kr = 0.5, kg = 0.45, kb = 0.33。像素颜色等于环境光颜色 * 环境光反射系数 * cos(a) a为法向量与光线
方向夹角。

调整相机角度，正视四面体

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/2.png" width="600" height="450">

可以看到目前对于三角形边界的处理还是有点问题，应该是由射线与三角形相交计算部分导致，目前采用计算交点与三个顶点组成的向量夹角之和
是否等于360度判断交点是否在三角形内，这种处理方法对边界情况处理不够好，从图中可以看到某些边被识别为背景，某些边不够平滑。

添加从文件读取stl文件并构建actor的功能，本渣渣笔记本果然算不动呢：）

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/3.png" width="600" height="450">

从stl文件读取的空心的立方块。

2020-04-09:

今天实现了lambert光照模型，目前仅反射一次，并且由于场景中没有其他物体，漫反射仅考虑光源。
提供一个平行光源，方向为（-1，-1，-1）。

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/4.png" width="600" height="450">

可以看到图中部分表面由于被自身其他部分遮挡，产生阴影效果：）

下午修正了lambert光照模型，目前不考虑物体表面输入的间接光源（被其他表面反射的光线），仅考虑平行光源和环境光的输入。
同时调整平行光源的方向使其偏离特殊情况，更具真实感。不过可以看到边界处锯齿状很明显，且由于相交算法不稳定导致的黑点。
当当当当！

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/5.png" width="600" height="450">

饭前抽空实现了基于超级采样的抗锯齿机制，每个像素采点由1个变为5个，分别为中心点和上下左右四个边界点，下面是抗锯齿之后的效果。
可以看到边界处明显的锯齿现象减弱了不少：）

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/6.png" width="600" height="450">

饭后又抽空添加了一个点光源。。。需要把之前的平行光修改的非常暗才能看到点光源的效果：）

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/7.png" width="600" height="450">

2020-04-10:

添加了纹理的基本框架但没有具体的纹理映射算法，用简单的坐标系计算一个纹理颜色进行渲染，为了显示光照和纹理的综合效果，首先
展示无纹理的光照模型：

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/8.png" width="600" height="450">

加上纹理之后的综合模型：

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/9.png" width="600" height="450">

下午进一步修正了lambert模型，考虑物体表面接受的间接光源（但是目前只考虑法向方向的间接输入），间接光源的追踪最大深度
目前定义为三层，为了清晰显示结果关闭了纹理。（随着模型的细化本渣渣笔记本越来越顶不住了😢）

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/10.png" width="600" height="450">

可以看到与之前相比，某些原来是阴影的部分被本身表面的反射光点亮了：）

2020-04-11:
学习蒙塔卡洛积分，准备进一步修正lambert模型。

2020-04-12:
开启多线程加速，加上本来机器启动了超线程（https://blog.csdn.net/cheng__lu/article/details/98884263） 渲染能跑
到占用近400%cpu负载（本来机器单cpu 2核），速度快了不少。
在此基础上准备进行明暗处理消除三角面片的光照误差。

下午完成了phong模型，引入了镜面反射，以下是无镜面反射（lambert模型），镜面反射1（高光指数n = 5），镜面反射2（高光指数n = 20）
三幅图片，为了显示明显的差别故将漫反射系数，环境光等调的很低。

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/11.png" width="600" height="450">

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/12.png" width="600" height="450">

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/13.png" width="600" height="450">

高光指数大较大的图片明显镜面光更集中，由于镜面反射系数调整的很大，因此两幅图的镜面光强度看不出明显差别。

2020-04-13:

通过三角形重心法插值像素，手工导入纹理图片进行渲染：

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/14.png" width="600" height="450">

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/15.png" width="600" height="450">

建立顶点坐标和纹理坐标的映射关系目前不是我能够处理的。。只能上手工了。

2020-04-14:
到今天为止这个渲染器刚好经过了一个星期的样子，目前也完成了大部分预期的功能，一直以来都想尝试
写一个光栅或者光线追踪渲染器，最近由于疫情闲赋在家，终于实现了这个梦想。

目前没有完成的部分：1.明暗处理，因为要对stl文件进行进一步处理得到每个顶点的法相信息。
2.蒙塔卡洛积分，换句话说目前仅考虑了光照的直接入射光源，没有考虑表面物体反射，原因是：第一
运算量可能有点大，目前这台笔记本可能顶不住。第二 等明暗处理部分完成，否则会影响曲面的反射效果。

这两块内容准备先放置一下，等回到学校再考虑吧，还有一个原因是机子里没有3维建模软件，目前用的几个例子都是之前做课题的
时候算例，之后要观察其他效果需要构建一个特别的场景。
