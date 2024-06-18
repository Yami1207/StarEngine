#ifndef __MACROS_HLSL__
#define __MACROS_HLSL__

// 转换纹理坐标
#define TRANSFORM_TEX(tex, name) ((tex.xy) * name##_ST.xy + name##_ST.zw)

#endif
