/*******************************************************
 * Homework 1: Rasterization                           *
 *-----------------------------------------------------*
 * Here you will implement the circle rasterization    *
 * method decribed in the handout.                                           *
 * To compile this in linux:                           *
 *        g++ hw1.cpp                                  *
 * Then, run the program as follows:                   *
 *        ./a.out 200                                  *
 * to generate a 200x200 image containing a circular   *
 * arc.  Note that the coordinate system we're using   *
 * places pixel centers at integer coordinates and     *
 * has the origin at the lower left.                   *
 * Your code will generate a .ppm file containing the  *
 * final image. These images can be viewed using       *
 * "display" in Linux or Irfanview in Mac/Windows.     *
 *******************************************************/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
using namespace std;

// We'll store image info as globals; not great programming practice
// but ok for this short program.
int radius;
bool **image;
///////
///////
void renderPixel(int x, int y) {
    assert(x >= 0 && y >= 0 && x <= radius && y <= radius);
    image[x][y] = 1;
	image[y][x] = 1;
    // TODO:  light up the pixel's symmetric counterpart

	/*pk calc
	if (x >= y)
	{
		return;
	}
	else 
	{
		if (PK < 0)
		{
			PK = PK + (4 * x) + 6;
			x = x + 1;
		}
		else
		{
			PK = PK + (4 * (x - y)) + 10;
			x = x + 1;
			y = y - 1;
		}
		//
		renderPixel(x, y, PK);
	}
	*/
}

void rasterizeArc(int r) {
    // TODO:  rasterize the arc using renderPixel to light up pixels
	radius = r;
	int PK = 3 - (2 * radius);
	//x0 and y0
	//int x = 0;
	int y = radius;

	for (int x = 0; x <= radius; x++) 
	{
		if (x > y) 
		{
			return;
		}
		else 
		{
			if (PK < 0)
			{
				PK = PK + (4 * x) + 6;
				//x = x + 1;
			}
			else
			{
				PK = PK + (4 * (x - y)) + 10;
				//x = x + 1;
				y = y - 1;
			}
			//
			renderPixel(x, y);
		}
	}
}

// You shouldn't need to change anything below this point.

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " circleSize\n";
        return 0;
    }

#ifdef _WIN32
    sscanf_s(argv[1], "%d", &radius);
#else
    sscanf(argv[1], "%d", &radius);
#endif
    if (radius <= 0) {
        cout << "Image must be of positive size.\n";
        return 0;
    }

    // reserve image as 2d array
    image = new bool*[radius+1];
    for (int i = 0; i <= radius; i++) image[i] = new bool[radius+1];

    rasterizeArc(radius);

    char filename[50];
#ifdef _WIN32
    sprintf_s(filename, 50, "circle%d.ppm", radius);
#else
    sprintf(filename, "circle%d.ppm", radius);
#endif

    ofstream outfile(filename);
    outfile << "P3\n# " << filename << "\n";
    outfile << radius+1 << ' ' << radius+1 << ' ' << 1 << endl;

    for (int i = 0; i <= radius; i++)
    for (int j = 0; j <= radius; j++)
        outfile << image[radius-i][j] << " 0 0\n";

    // delete image data
    for (int i = 0; i <= radius; i++) delete [] image[i];
    delete [] image;
    return 0;
}
