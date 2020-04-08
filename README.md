# raytrace

基于c++11的光线追踪渲染器，独立于绘图平台。

2020-04-08:

目前处理了相机的移动和旋转以及光线和三角形的相交计算逻辑。目前的光照模型非常简单，仅仅根据光线方向与表面法相量的夹角大小与环境光进行设置，
严格来说算不上光照模型，在此仅为了验证其他程序逻辑的正确性（比如说相机逻辑）。

用以上光照模型渲染的第一张图片！

<img src="https://github.com/chloro-pn/raytrace/blob/master/pic/1.png" width="450" height="300">

背景颜色黑色，环境光白色，环境光反射系数: kr = 0.5, kg = 0.45, kb = 0.33。像素颜色等于环境光颜色 * 环境光反射系数 * cos(a) a为法向量与光线
方向夹角。
