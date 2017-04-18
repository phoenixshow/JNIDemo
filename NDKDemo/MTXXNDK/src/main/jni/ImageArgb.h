int alpha(int color){
    return (color >> 24) & 0xFF;
}
int red(int color){
    return (color >> 16) & 0xFF;
}
int green(int color){
    return (color >> 8) & 0xFF;
}
int blue(int color){
    return color & 0xFF;
}
int ARGB(int alpha, int red, int green, int blue){
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}
