#include <vector>

// A vector of vertices.
extern std::vector <GLfloat> g_vertex_buffer_data;
extern int point_count;

enum color_palette { red, green, blue };

extern color_palette color_toggle;
extern GLfloat color_object[3];
extern std::vector <GLfloat> color_vector;