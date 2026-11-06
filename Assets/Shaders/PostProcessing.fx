cbuffer PostProcessingBuffer : register(b0)
{
    int mode;
    float param0;
    float param1;
    float param2;
};

Texture2D textureMap0 : register(t0);
Texture2D textureMap1 : register(t1);
Texture2D textureMap2 : register(t2);
Texture2D textureMap3 : register(t3);

SamplerState textureSampler : register(s0);

struct VS_INPUT
{
    float3 position : POSITION;
    float2 texcoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 textCoord : TEXCOORD;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = float4(input.position, 1.0f);
    output.textCoord = input.texcoord;
    return output;
}
float4 PS(VS_OUTPUT input) : SV_TARGET
{
    float4 finalColor = 0.0f;
    
    if (mode == 0)
    {
        finalColor = textureMap0.Sample(textureSampler, input.textCoord);
    }
    else if (mode == 1) // monochrome
    {
        float4 color = textureMap0.Sample(textureSampler, input.textCoord);
        finalColor = (color.r + color.g + color.b) / 3.0f;
    }
    else if (mode == 2) // invert
    {
        float4 color = textureMap0.Sample(textureSampler, input.textCoord);
        finalColor = 1.0f - color;
    }
    else if (mode == 3) // mirror
    {
        float2 textCoord = input.textCoord;
        textCoord.x += param0;
        textCoord.y += param1;
        finalColor = textureMap0.Sample(textureSampler, textCoord);
    }
    else if (mode == 4) // blur
    {
        float u = input.textCoord.x;
        float v = input.textCoord.y;
        finalColor =
        textureMap0.Sample(textureSampler, float2(u, v))
        + textureMap0.Sample(textureSampler, float2(u - param0, v))
        + textureMap0.Sample(textureSampler, float2(u + param0, v))
        + textureMap0.Sample(textureSampler, float2(u, v - param1))
        + textureMap0.Sample(textureSampler, float2(u, v + param1))
        + textureMap0.Sample(textureSampler, float2(u + param0, v + param1))
        + textureMap0.Sample(textureSampler, float2(u - param0, v + param1))
        + textureMap0.Sample(textureSampler, float2(u + param0, v - param1))
        + textureMap0.Sample(textureSampler, float2(u - param0, v - param1));
        finalColor += 0.12f;

    }
    else if (mode == 5) // combine2
    {
        float4 color0 = textureMap0.Sample(textureSampler, input.textCoord);
        float4 color1 = textureMap1.Sample(textureSampler, input.textCoord);
        color1.a += param0;
        finalColor = (color0 * (1.0f - color1.a)) + (color1 * color1.a);
    }
    else if (mode == 6) // motion blur
    {
        //skip for now
    }
    else if (mode ==7) // chromatic abaration
    {
        float2 distortion = float2(param0, -param1);
        float4 redChannel = textureMap0.Sample(textureSampler, input.textCoord + distortion.x * input.textCoord);
        float4 greenChannel = textureMap0.Sample(textureSampler, input.textCoord);
        float4 blueChannel = textureMap0.Sample(textureSampler, input.textCoord + distortion.y * input.textCoord);
        finalColor = float4(redChannel.r, greenChannel.g, blueChannel.b, 1.0f);
    }
    else if (mode == 8) // wave
    {
        float waveValue = input.textCoord.x * (3.14159f * param0);
        float2 texCoord = input.textCoord;
        texCoord.y += sin(waveValue) * param1;
        finalColor = textureMap0.Sample(textureSampler, texCoord);
    }
    return finalColor;
}