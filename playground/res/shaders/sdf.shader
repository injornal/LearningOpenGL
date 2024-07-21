#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
uniform float rotAngle;
// out vec4 position_out;
void main() {
    mat3 rot = mat3(
        1, 0, 0,
        0, cos(radians(rotAngle)), -sin(radians(rotAngle)),
        0, sin(radians(rotAngle)), cos(radians(rotAngle))
    );
    gl_Position = mat4 (
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0.5, 0, 1
    ) * vec4(rot * vec3(position.xyz), 1.0);
    //    gl_Position = vec4(rot * vec3(position.xyz), 1.0);
    // position_out = vec4(position.xy + .5, position.zw);
}

#shader fragment
#version 330 core

// in vec4 position_out;
out vec4 color;

uniform vec4 uColor;

void main() {
    // vec3 circle = vec3(.5, .5, .3);
    // float dist = length(position_out.xy - circle.xy) - circle.z;
    // color = dist > 0 ? vec3(0, uColor.gb) : vec3(uColor.rg, 0);
    // color = color * (1. - exp(-4.0 * abs(dist)));
    color = uColor;
}
