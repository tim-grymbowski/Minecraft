#version 150
    
/* TODO: Get the matrix as a uniform instead */
    
in vec3 pos;
out vec3 pos_c;
mat4 mat_proj = mat4(
	1050.0/1680.0 * 1.0/tan(0.5), 	0.0,		      0.0,             0.0,
	0.0,				1.0/tan(0.5),         0.0,             0.0,
	0.0,				0.0,		      1000.0/999.0,    0.0,
	0.0,				0.0,		      -1000.0/999.0,   1.0
);
void main() {
	pos_c = pos;
	gl_Position = mat_proj * vec4(pos, pos.z);
}
