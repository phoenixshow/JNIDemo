package com.phoenix.javacallc;

/**
 * Java调用C代码
 */
public class JNI {
    static {
        System.loadLibrary("JavaCallC");
    }

    /**
     * 加法运算
     * @param x 加数
     * @param y 加数
     * @return 返回和
     */
    public native int add(int x, int y);

    /**
     * 字符串累加
     * @param s 待累加的字符串
     * @return 累加后的字符串
     */
    public native String sayHello(String s);

    /**
     * 给每个数组元素都加10
     * @param intArray 待计算的数组
     * @return 计算后的数组
     */
    public native int[] increaseArrayEles(int[] intArray);

    /**
     * 检查密码是否正确
     * @param pwd 密码
     * @return 正确返回200，否则返回400
     */
    public native int checkPwd(String pwd);
}
