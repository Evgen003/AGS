#version 330 core

uniform vec4 color1;
uniform vec4 color2;

in vec2 position;

out vec4 fragColor;

void main ()
{
	
	if(position.x-position.y<=0){
		fragColor=color1;
	}
	else {
		fragColor=color2;
	}
}
