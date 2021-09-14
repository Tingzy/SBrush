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
}