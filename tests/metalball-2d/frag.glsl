#version 430 core

uniform float time;
in vec4 gl_FragCoord;
out vec4 outColor;

float radius = 0.1 * 500;

bool withinCircle(vec2 point, vec2 center)
{
	center *= vec2(800, 500);
	return distance(point, center) < radius;
}

float metal(vec2 point, vec2 center)
{
	center *= vec2(800, 500);
	float dist = length(point - center);
	return radius * radius / dist / dist;
}

void main()
{
	vec2 center1 = vec2(0.5, (sin(time) + 1) / 2);
	vec2 center2 = vec2((cos(time * 1.4) + 1) / 2, 0.3);
	vec2 center3 = vec2((sin(time) + 1) / 2, (cos(time) + 1) / 2);
	vec2 center4 = vec2((cos(time) + 1) / 2.2, (sin(time) + 1) / 2.2);

	float color = metal(gl_FragCoord.xy, center1)
		+ metal(gl_FragCoord.xy, center2)
		+ metal(gl_FragCoord.xy, center3)
		+ metal(gl_FragCoord.xy, center4);

	if(color > 1)
	{
		outColor = vec4(0, color, 0, 1);
	}
	else
	{
		outColor = vec4(1, 1, 1, 1);
	}

}