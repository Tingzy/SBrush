#include "draw.h"
#include "common.h"

void addVertice(float xpos, float ypos)
{
	point_count++;
	float xpos_converted;
	float ypos_converted;

	//Use 1920x1080 resolution.
	xpos_converted =  1 - (2 * (1920 - xpos) / 1920);
	ypos_converted = 1 - 2 * ypos / 1080;

	//Add point to vertice vector.
	g_vertex_buffer_data.push_back(xpos_converted);
	g_vertex_buffer_data.push_back(ypos_converted);
	g_vertex_buffer_data.push_back(0.0f);
	color_vector.push_back(color_object[0]);
	color_vector.push_back(color_object[1]);
	color_vector.push_back(color_object[2]);
}

void changeColor(float xpos, float ypos)
{
	float xpos_converted;
	float ypos_converted;

	//Use 1920x1080 resolution.
	xpos_converted = 1 - (2 * (1920 - xpos) / 1920);
	ypos_converted = 1 - 2 * ypos / 1080;

	if (-0.98 <= xpos_converted && xpos_converted <= -0.95 && 0.85 <= ypos_converted && ypos_converted <= 0.9)
	{
		color_toggle = red;
	}
	else if (-0.98 <= xpos_converted && xpos_converted <= -0.95 && 0.78 <= ypos_converted && ypos_converted <= 0.83)
	{
		color_toggle = green;
	}
	else if (-0.98 <= xpos_converted && xpos_converted <= -0.95 && 0.71 <= ypos_converted && ypos_converted <= 0.76)
	{
		color_toggle = blue;
	}
	switch (color_toggle)
	{
	case red: 
		color_object[0] = 1.0;
		color_object[1] = 0.0;
		color_object[2] = 0.0;
		break;
	case green: 
		color_object[0] = 0.0;
		color_object[1] = 1.0;
		color_object[2] = 0.0;
		break;
	case blue: 
		color_object[0] = 0.0;
		color_object[1] = 0.0;
		color_object[2] = 1.0;
		break;
	}
}