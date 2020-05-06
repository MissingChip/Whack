#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform vec4 color;

void main()
{
    /*if(TexCoord.x>0.97 || TexCoord.x<0.03 || TexCoord.y>0.97 || TexCoord.y<0.03){
        FragColor = vec4(color.rgb*0.8, color.a);
    } else{
        FragColor = vec4(color);
    }*/
    vec2 diff = TexCoord-vec2(0.5, 0.5);
    float m = 1-sqrt(length(diff));
    //if(m<0.42) m = 0;
    if(m>0.85){
        FragColor = vec4(color.rgb, sqrt(color.a));
    }
    else if(m>0.837){
        FragColor = vec4(vec3(0), color.a);
    }
    else{
        FragColor = vec4(color.rgb*m, color.a);
    }
}