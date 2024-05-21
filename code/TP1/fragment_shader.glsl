#version 330 core

in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform bool isMesh;

out vec4 color;


void main(){

    vec4 hm = texture(texture0,TexCoord);
    vec4 tex1 = texture(texture1, TexCoord);
    vec4 tex2 = texture(texture2, TexCoord);
    vec4 tex3 = texture(texture3, TexCoord);

    float height = texture(texture0,TexCoord).r;

    float weight1 = smoothstep(0, 0.8, height);
    float weight2 = smoothstep(0.8, 0.9, height);
    float weight3 = smoothstep(0.9, 1, height);


    vec4 mixTex = mix(tex1, tex2, weight1);
    mixTex = mix(mixTex, tex3, weight2 + weight3);


    if(isMesh)
        color = vec4(0, 0, 0.5,1) ;
    else
        color = mixTex;
}
