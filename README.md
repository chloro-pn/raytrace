# raytrace

基于c++11的光线追踪渲染器，独立于绘图平台。

2020-04-08:

目前处理了相机的移动和旋转以及光线和三角形的相交计算逻辑。目前的光照模型非常简单，仅仅根据光线方向与表面法相量的夹角大小与环境光进行设置，
严格来说算不上光照模型，在此仅为了验证其他程序逻辑的正确性（比如说相机逻辑）。

用以上光照模型渲染的第一张图片！

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/1.png" width="450" height="300">

背景颜色黑色，环境光白色，环境光反射系数: kr = 0.5, kg = 0.45, kb = 0.33。像素颜色等于环境光颜色 * 环境光反射系数 * cos(a) a为法向量与光线
方向夹角。

调整相机角度，正视四面体

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/2.png" width="450" height="300">

可以看到目前对于三角形边界的处理还是有点问题，应该是由射线与三角形相交计算部分导致，目前采用计算交点与三个顶点组成的向量夹角之和
是否等于360度判断交点是否在三角形内，这种处理方法对边界情况处理不够好，从图中可以看到某些边被识别为背景，某些边不够平滑。

添加从文件读取stl文件并构建actor的功能，本渣渣笔记本果然算不动呢：）

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/3.png" width="450" height="300">

从stl文件读取的空心的立方块。