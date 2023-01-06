#include "Triangle.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
#include <iostream>

// A function clamping the input values to the lower and higher bounds
#define CLAMP(in, low, high) ((in) < (low) ? (low) : ((in) > (high) ? (high) : in))

Triangle::Triangle()
{
	v[0] = glm::vec3(0.0f, 0.0f, 0.0f);
	v[1] = glm::vec3(0.0f, 0.0f, 0.0f);
	v[2] = glm::vec3(0.0f, 0.0f, 0.0f);

	c[0] = glm::vec3(0.0f, 0.0f, 0.0f);
	c[1] = glm::vec3(0.0f, 0.0f, 0.0f);
	c[2] = glm::vec3(0.0f, 0.0f, 0.0f);

	t[0] = glm::vec2(0.0f, 0.0f);
	t[1] = glm::vec2(0.0f, 0.0f);
	t[2] = glm::vec2(0.0f, 0.0f);
}

Triangle::Triangle(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2)
{
	v[0] = v0;
	v[1] = v1;
	v[2] = v2;

	// std::cout << "v0: " << v[0].x << " " << v[0].y << "  " << v[0].z << std::endl;
	// std::cout << "v1: " << v[1].x << " " << v[1].y << "  " << v[1].z << std::endl;
	// std::cout << "v2: " << v[2].x << " " << v[2].y << "  " << v[2].z << std::endl;

	c[0] = glm::vec3(1.0f, 1.0f, 1.0f);
	c[1] = glm::vec3(1.0f, 1.0f, 1.0f);
	c[2] = glm::vec3(1.0f, 1.0f, 1.0f);

	t[0] = glm::vec2(0.0f, 0.0f);
	t[1] = glm::vec2(0.0f, 0.0f);
	t[2] = glm::vec2(0.0f, 0.0f);

};

Triangle::Triangle(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2, glm::vec2& t0, glm::vec2& t1, glm::vec2& t2)
{
	v[0] = v0;
	v[1] = v1;
	v[2] = v2;

	t[0] = t0;
	t[1] = t1;
	t[2] = t2;

	c[0] = glm::vec3(1.0f, 1.0f, 1.0f);
	c[1] = glm::vec3(1.0f, 1.0f, 1.0f);
	c[2] = glm::vec3(1.0f, 1.0f, 1.0f);

};

void Triangle::ColorTriangle(int colorMode) {

	switch (colorMode)
	{
		case 0: // assign every triangle a random color
		{
			float r = (float)rand()/(float)RAND_MAX;
			float g = (float)rand()/(float)RAND_MAX;
			float b = (float)rand()/(float)RAND_MAX;
			
			c[0] = glm::vec3(r, g, b);
			c[1] = glm::vec3(r, g, b);
			c[2] = glm::vec3(r, g, b);

			break;
		}

		case 1: // assign every vertex a random color
		{
			float r0 = (float)rand()/(float)RAND_MAX;
			float r1 = (float)rand()/(float)RAND_MAX;
			float r2 = (float)rand()/(float)RAND_MAX;

			float g0 = (float)rand()/(float)RAND_MAX;
			float g1 = (float)rand()/(float)RAND_MAX;
			float g2 = (float)rand()/(float)RAND_MAX;

			float b0 = (float)rand()/(float)RAND_MAX;
			float b1 = (float)rand()/(float)RAND_MAX;
			float b2 = (float)rand()/(float)RAND_MAX;

			c[0] = glm::vec3(r0, g0, b0);
			c[1] = glm::vec3(r1, g1, b1);
			c[2] = glm::vec3(r2, g2, b2);

			break;
		}
	}

}

float Triangle::getMaxZ() {

	float localMaxZ = v[0].z;

	if (v[1].z > localMaxZ) {
		localMaxZ = v[1].z;
	}

	if (v[2].z > localMaxZ) {
		localMaxZ = v[2].z;
	}

	return localMaxZ;
}

float Triangle::getMinZ() {

	float localMinZ = v[0].z;

	if (v[1].z < localMinZ) {
		localMinZ = v[1].z;
	}

	if (v[2].z < localMinZ) {
		localMinZ = v[2].z;
	}

	return localMinZ;
}

void Triangle::ColorTriangle(int colorMode, float maxZ, float minZ) {

	float gb0 = (v[0].z - minZ) / (maxZ - minZ);
	float gb1 = (v[1].z - minZ) / (maxZ - minZ);
	float gb2 = (v[2].z - minZ) / (maxZ - minZ);

	c[0] = glm::vec3(0.0f, gb0, gb0);
	c[1] = glm::vec3(0.0f, gb1, gb1);
	c[2] = glm::vec3(0.0f, gb2, gb2);

}

// Rendering the triangle using OpenGL
void Triangle::RenderOpenGL(glm::mat4 &modelViewMatrix, glm::mat4 &projectionMatrix, bool isTextured)
{

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(modelViewMatrix));

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(projectionMatrix));
	
	// For textured object
	if (isTextured)
	{
		glEnable(GL_TEXTURE_2D);

		// Avoid modulating the texture by vertex color
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glBegin(GL_TRIANGLES);

			glTexCoord2f(t[0].x, t[0].y);
			glVertex3f(v[0].x, v[0].y, v[0].z);

			glTexCoord2f(t[1].x, t[1].y);
			glVertex3f(v[1].x, v[1].y, v[1].z);

			glTexCoord2f(t[2].x, t[2].y);
			glVertex3f(v[2].x, v[2].y, v[2].z);

		glEnd();

		glDisable(GL_TEXTURE_2D);


	}
	// For object with only vertex color
	else
	{
		glBegin(GL_TRIANGLES);

			glColor3f(c[0].x, c[0].y, c[0].z);
			glVertex3f(v[0].x, v[0].y, v[0].z);

			glColor3f(c[1].x, c[1].y, c[1].z);
			glVertex3f(v[1].x, v[1].y, v[1].z);

			glColor3f(c[2].x, c[2].y, c[2].z);
			glVertex3f(v[2].x, v[2].y, v[2].z);
		
		glEnd();
	}

}

/* given x and y coordinates in image space (i.e. in pixel values with respect to image coordinates) */
glm::vec3 getColorAtPixel(float x, float y, int texWidth, int texHeight, std::vector<float*> texture, int D) {

	glm::vec3 color;

		// acurate wrapping function for x coordinate
		if (x > (texWidth - 1)) {
			x = x - texWidth;
		}

		if (x < 0) {
			x = x + texWidth;
		}

		// acurate wrapping function for y coordinate
		if (y > (texHeight - 1)) {
			y = y - texHeight;
		}

		if (y < 0) {
			y = y + texHeight;
		}

		// look up and apply texture color
		color[0] = texture[D][int(y) * texWidth * 3 + int(x) * 3 + 0]; // red
		color[1] = texture[D][int(y) * texWidth * 3 + int(x) * 3 + 1]; // blue
		color[2] = texture[D][int(y) * texWidth * 3 + int(x) * 3 + 2]; // green

	return color;
}

glm::vec3 bilinearInterpolate(float x, float y, int texWidth, int texHeight, std::vector<float*> texture, int D) {
	/** the following vec3's correlate to (r, g, b) respectively **/

	// get color at u00 (getColor(floor x, floor y))
	glm::vec3 u00_color = getColorAtPixel(floor(x), floor(y), texWidth, texHeight, texture, D);

	// get color at u01 (getColor(floor x, ceil y))
	glm::vec3 u01_color = getColorAtPixel(floor(x), ceil(y), texWidth, texHeight, texture, D);

	// get color at u10 (getColor(ceil x, floor y))
	glm::vec3 u10_color = getColorAtPixel(ceil(x), floor(y), texWidth, texHeight, texture, D);

	// get color at u11 (getColor(ceil x, ceil y))
	glm::vec3 u11_color = getColorAtPixel(ceil(x), ceil(y), texWidth, texHeight, texture, D);

	// calculate t
	float t = y - floor(y);

	// calculate s
	float s = x - floor(x);

	// get u0
	glm::vec3 u0_color = u00_color + (s * (u10_color - u00_color));

	// get u1
	glm::vec3 u1_color = u01_color + (s * (u11_color - u01_color));

	// get u
	glm::vec3 u_color = u0_color + (t * (u1_color - u0_color));

	return u_color;
}


// Render the triangle on CPU
void Triangle::RenderCPU(glm::mat4 &modelViewMatrix, glm::mat4 &projectionMatrix, glm::mat4 &viewportMatrix, float (&color)[1024][1024][3], float (&depth)[1024][1024], bool isTextured, std::vector<float*> texture, int texWidth, int texHeight, int textureMethod)
{
	// update v0
	glm::vec4 a = glm::vec4(v[0].x, v[0].y, v[0].z, 1.0f); // convert to vec4
	a = modelViewMatrix * a;
	float textureZa = a.z;
	a = projectionMatrix * a;
	a = a / a[3];
	a = viewportMatrix * a;
	// std::cout << "v0: " << a.x << " " << a.y << " " << a.z << std::endl;

	// update v1
	glm::vec4 b = glm::vec4(v[1].x, v[1].y, v[1].z, 1.0f); // convert to vec4
	b = modelViewMatrix * b;
	float textureZb = b.z;
	b = projectionMatrix * b;
	b = b / b[3];
	b = viewportMatrix * b;
	// std::cout << "v1: " << b.x << " " << b.y << " " << b.z << std::endl;

	// update v2
	glm::vec4 cV = glm::vec4(v[2].x, v[2].y, v[2].z, 1.0f); // convert to vec4
	cV = modelViewMatrix * cV;
	float textureZc = cV.z;
	cV = projectionMatrix * cV;
	cV = cV / cV[3];
	cV = viewportMatrix * cV;
	// std::cout << "v2: " << cV.x << " " << cV.y << " " << cV.z << std::endl;
	
	// get max/min x and y
	float xMax = ceil(std::max({a.x, b.x, cV.x}));
	float xMin = floor(std::min({a.x, b.x, cV.x}));
	float yMax = ceil(std::max({a.y, b.y, cV.y}));
	float yMin = floor(std::min({a.y, b.y, cV.y}));

	// clamp bounding box to window
	if (yMax > (1024 - 1)) {
		yMax = 1023;
	}
	if (xMax > (1024 - 1)) {
		xMax = 1023;
	}
	if (xMin < 0) {
		xMin = 0;
	}
	if (yMin < 0) {
		yMin = 0;
	}

	// std::cout << "xMax: " << xMax << std::endl;
	// std::cout << "xMin: " << xMin << std::endl;
	// std::cout << "yMax: " << yMax << std::endl;
	// std::cout << "yMin: " << yMin << std::endl;

	// iterate through bounding pixel box
	for (unsigned int x = xMin; x < xMax; x++) {
		for (unsigned int y = yMin; y < yMax; y++) {

			float xPixel = x + 0.5;
			float yPixel = y + 0.5;

			// calcualte barycentric coordinates for pixel
			float alpha = (((-1)*(xPixel - b.x)*(cV.y - b.y))+((yPixel - b.y)*(cV.x - b.x))) / (((-1)*(a.x - b.x)*(cV.y - b.y)) + ((a.y - b.y)*(cV.x - b.x)));
			float beta = (((-1)*(xPixel - cV.x)*(a.y - cV.y))+((yPixel - cV.y)*(a.x - cV.x))) / (((-1)*(b.x - cV.x)*(a.y - cV.y)) + ((b.y - cV.y)*(a.x - cV.x)));
			float gamma = 1.0 - alpha - beta;

			float aZ = a.z;
			float bZ = b.z;
			float cZ = cV.z;

			float z = aZ * alpha + bZ * beta + cZ * gamma;
			// std::cout << "z: " << aZ << " " << bZ << " " << cZ << std::endl;

			/* Texture Calculations */

			// zinv for each vertex
			float zinvA = 1 / textureZa;
			float zinvB = 1 / textureZb;
			float zinvC = 1 / textureZc;

			// interpolate zinv for the triangle
			float zinv = alpha * zinvA + beta * zinvB + gamma * zinvC;

			// Qsca for each vertex
			glm::vec2 QscaA = t[0] / textureZa;
			glm::vec2 QscaB = t[1] / textureZb;
			glm::vec2 QscaC = t[2] / textureZc;

			/****/

			// if pixel is inside the triangle
			if (alpha >= 0 && beta >= 0 && gamma >= 0 && z <= depth[y][x]) {

				if (isTextured) { // textured

					// interpolate Qsca for pixel
					glm::vec2 Qsca;
					Qsca.x = alpha * QscaA.x + beta * QscaB.x + gamma * QscaC.x;
					Qsca.y = alpha * QscaA.y + beta * QscaB.y + gamma * QscaC.y;

					// divide Qsca by zinv
					Qsca = Qsca / zinv;

					// convert texture space to image space
					Qsca.y = Qsca.y * texHeight;
					Qsca.x = Qsca.x * texWidth;

					switch (textureMethod) {
						case 0: {
							// nearest neighbor
							Qsca.y = floor(Qsca.y);
							Qsca.x = floor(Qsca.x);

							glm::vec3 textureColor = getColorAtPixel(Qsca.x, Qsca.y, texWidth, texHeight, texture, 0);

							// look up and apply texture color
							color[y][x][0] = textureColor[0]; // red
							color[y][x][1] = textureColor[1]; // blue
							color[y][x][2] = textureColor[2]; // green

						break;
						}

						case 1: {
							// bilinear interpolation
							Qsca -= 0.5;
							glm::vec3 u_color = bilinearInterpolate(Qsca.x, Qsca.y, texWidth, texHeight, texture, 0);

							// appply color
							color[y][x][0] = u_color[0]; // red
							color[y][x][1] = u_color[1]; // blue
							color[y][x][2] = u_color[2]; // green

						break;
						}

						case 2: {
							// mipmap
							
							// get texture coordinate t_x1 for (x+1, y)
							float alphaX = (((-1)*(xPixel + 1 - b.x)*(cV.y - b.y))+((yPixel - b.y)*(cV.x - b.x))) / (((-1)*(a.x - b.x)*(cV.y - b.y)) + ((a.y - b.y)*(cV.x - b.x)));
							float betaX = (((-1)*(xPixel + 1 - cV.x)*(a.y - cV.y))+((yPixel - cV.y)*(a.x - cV.x))) / (((-1)*(b.x - cV.x)*(a.y - cV.y)) + ((b.y - cV.y)*(a.x - cV.x)));
							float gammaX = 1.0 - alphaX - betaX;
							glm::vec2 t_x1;
							t_x1.x = alphaX * QscaA.x + betaX * QscaB.x + gammaX * QscaC.x;
							t_x1.y = alphaX * QscaA.y + betaX * QscaB.y + gammaX * QscaC.y;
							t_x1 = t_x1 / zinv;
							t_x1.y = t_x1.y * texHeight;
							t_x1.x = t_x1.x * texWidth;
							
							// store du/dx and dv/dx
							glm::vec2 dx = t_x1 - Qsca;
							float dudx = dx[0];
							float dvdx = dx[1];

							// get texuture coordinate t_y1 for (x, y+1)
							float alphaY = (((-1)*(xPixel - b.x)*(cV.y - b.y))+((yPixel + 1 - b.y)*(cV.x - b.x))) / (((-1)*(a.x - b.x)*(cV.y - b.y)) + ((a.y - b.y)*(cV.x - b.x)));
							float betaY = (((-1)*(xPixel - cV.x)*(a.y - cV.y))+((yPixel + 1 - cV.y)*(a.x - cV.x))) / (((-1)*(b.x - cV.x)*(a.y - cV.y)) + ((b.y - cV.y)*(a.x - cV.x)));
							float gammaY = 1.0 - alphaY - betaY;
							glm::vec2 t_y1;
							t_y1.x = alphaY * QscaA.x + betaY * QscaB.x + gammaY * QscaC.x;
							t_y1.y = alphaY * QscaA.y + betaY * QscaB.y + gammaY * QscaC.y;
							t_y1 = t_y1 / zinv;
							t_y1.y = t_y1.y * texHeight;
							t_y1.x = t_y1.x * texWidth;
							
							// store du/dy and dv/dy
							glm::vec2 dy = t_y1 - Qsca;
							float dudy = dy[0];
							float dvdy = dy[1];

							// calculate L (clamp L so that it is not less than 1)
							float L = fmax(sqrt(pow(dudx, 2) + pow(dvdx, 2)), sqrt(pow(dudy, 2) + pow(dvdy, 2))); 
							if (L < 1.0) {
								L = 1.0;
							}

							if (L > 1024.0) {
								L = 1024.0;
							}

							// calculate D (clamp D so it is not less than 0 or greater than 10)
							float D = log2(L);
							int topD = ceil(D);
							int bottomD = floor(D);

							// std::cout << "D: " << D << std::endl;

							// fix shifts
							Qsca -= 0.5;

							// bilinear interpolate on top level (ceil(D))
							glm::vec3 u0 = bilinearInterpolate(Qsca.x, Qsca.y, texWidth, texHeight, texture, bottomD); 

							// bilinear interpolate on bottom level (floor(D))
							glm::vec3 u1 = bilinearInterpolate(Qsca.x, Qsca.y, texWidth, texHeight, texture, topD); 

							// linear interpolate on both points
							float s = D - topD;
							glm::vec3 u = u1 - (s * (u0 - u1));

							// appply color
							color[y][x][0] = u[0]; // red
							color[y][x][1] = u[1]; // blue
							color[y][x][2] = u[2]; // green

						break;
						}
					}

					depth[y][x] = z;

				} else { // colored
					// update color
					color[y][x][0] = alpha * c[0].x + beta * c[1].x + gamma * c[2].x; // red
					color[y][x][1] = alpha * c[0].y + beta * c[1].y + gamma * c[2].y; // blue
					color[y][x][2] = alpha * c[0].z + beta * c[1].z + gamma * c[2].z; // green

					// std::cout << "updating z-index from " << depth[y][x] << " to " << z << std::endl;
					// update depth
					depth[y][x] = z;
				}
			}
		}
	}		
}