#version 460 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

uniform float gamma;

uniform float exposure;

vec4 GammaCorrection(vec4 color)
{
    return vec4(pow(color.rgb, vec3(1.0 / gamma)), color.a);
}

vec4 none()
{
    return vec4(vec3(texture(screenTexture, TexCoords)), 1.0);
}

vec4 inverse_color()
{
    return vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);
}

vec4 gray()
{ 
    vec4 color = texture(screenTexture, TexCoords);
    float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
    return vec4(vec3(average, average, average), 1.0);
}

const float offset = 1.0 / 300.0;  

vec2 offsets[9] = vec2[](
    vec2(-offset,  offset),
    vec2( 0.0f,    offset),
    vec2( offset,  offset),
    vec2(-offset,  0.0f),  
    vec2( 0.0f,    0.0f),  
    vec2( offset,  0.0f),  
    vec2(-offset, -offset),
    vec2( 0.0f,   -offset),
    vec2( offset, -offset) 
);

float sharpen_kernel[9] = float[](
    -1, -1, -1,
    -1,  9, -1,
    -1, -1, -1
);

vec4 sharpen()
{
    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
    {
        col += sampleTex[i] * sharpen_kernel[i];
    }

    return vec4(col, 1.0);
}

vec2 blur_offsets[9] = vec2[](
    vec2(-1,  1),        
    vec2( 0,  1),   
    vec2( 1,  1),        
    vec2(-1,  0),     
    vec2( 0,  0),
    vec2( 1,  0),     
    vec2(-1, -1),        
    vec2( 0, -1),   
    vec2( 1, -1)         
);

float blur_kernel[9] = float[](
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16  
);

vec4 blur()
{
    vec3 sampleTex[9];
    for (int i=0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
    {
        col += sampleTex[i] * blur_kernel[i];
    }

    return vec4(col, 1.0);
}

float edge_detection_kernel[9] = float[](
    1, 1, 1,
    1, -8, 1,
    1, 1, 1  
);

vec4 edge_detection()
{
    vec3 sampleTex[9];
    for (int i=0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
    {
        col += sampleTex[i] * edge_detection_kernel[i];
    }

    return vec4(col, 1.0);
}

vec4 ToneMapping_ReinHard(vec4 hdrColor)
{
    vec3 mapped = hdrColor.rgb / (hdrColor.rgb + vec3(1.0));
    return vec4(mapped, hdrColor.a);
}

vec4 ToneMapping_Exposure(vec4 hdrColor)
{
    vec3 mapped = vec3(1) - exp(-hdrColor.rgb * exposure);
    return vec4(mapped, hdrColor.a);
}

void main()
{ 
    vec4 color = none();
    color = GammaCorrection(ToneMapping_Exposure(color));
    FragColor = color;
}