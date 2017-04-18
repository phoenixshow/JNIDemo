# JNIDemo
    利用JNI/NDK实现Java与C的互通    
    
##NDKDemo
1. Module app演示了环境配置
2. Module JavaCallC演示了Java 调用 C 代码执行加法运算、字符串运算、数组运算、字符串比较
3. Module CCallJava演示了C 调用 Java 代码，包括无参、有参、静态方法
4. Module CCallJava2演示了直接使用编译好的.so文件
5. Module MTXX演示了利用反编译得到的美图秀秀的.so文件实现照片的高亮、黑白、怀旧、还原效果
6. Module Boiler演示了获取C代码得到的锅炉压力值，并在自定义控件中用Canvas绘制压力值
7. Module Uninstall演示了软件卸载做问卷调查功能，在5.0以下模拟器测试有效
8. Module MTXXNDK演示了用Java和C分别给图片做一键美白，通过耗时比较体现C的优势
    
主要代码来自杨光福、周蔚
