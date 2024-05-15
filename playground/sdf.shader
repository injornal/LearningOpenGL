#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
out vec4 position_out;
void main() {
   gl_Position = position;
   position_out = vec4(position.xy + .5, position.zw);
}

#shader fragment
#version 330 core
in vec4 position_out;
out vec3 color;
void main() {
   vec3 circle = vec3(.5, .5, .3);
   float dist = length(position_out.xy - circle.xy) - circle.z;
   color = dist > 0 ? vec3(0, 1, 1) : vec3(1, 1, 0);
   color = color * (1. - exp(-4.0 * abs(dist)));
}
