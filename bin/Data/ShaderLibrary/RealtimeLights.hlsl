#ifndef __REALTIME_LIGHTS_HLSL__
#define __REALTIME_LIGHTS_HLSL__

struct Light
{
    float3 direction;
    half3 color;
};

///////////////////////////////////////////////////////////////////////////////
//                             Light                                         //
///////////////////////////////////////////////////////////////////////////////
Light GetMainLight()
{
    Light light;
    light.direction = g_MainLightPosition.xyz;
    light.color = g_MainLightColor.rgb;
    return light;
}

#endif
