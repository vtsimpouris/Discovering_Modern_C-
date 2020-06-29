#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <complex>
#include <iostream>
#include <algorithm>
#include <chrono>
#ifdef WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif
#undef main

using namespace std;


void compute_iterations(int* iter, int xdim, int ydim, int max_iter);
struct sdl_error {};
inline void sdl_check(bool allclear) { if (!allclear) throw sdl_error(); }

inline void put_pixel(SDL_Surface* screen, int x, int y, uint32_t pixel)
{
	assert(screen->format->BytesPerPixel == 4);
	auto pixel_address = reinterpret_cast<uint32_t*>(screen->pixels) + y * screen->w + x;
	*pixel_address = pixel;
}

class mandel_pixel
{
public:
	mandel_pixel(SDL_Surface* screen, int x, int y, int xdim, int ydim, int max_iter, int serial_v)
		: screen(screen), max_iter(max_iter), iter(0), c(x, y), serial_v(serial_v)
	{
		// scale y to [-1.2,1.2] and shift -0.5+0i to the center
		if (serial_v) {
			c *= 2.4f / static_cast<float>(ydim); // do it in cuda like that
			c -= complex<float>(1.2 * xdim / ydim + 0.5, 1.2);
			iterate();
		}
	}

	int iterations() const { return iter; }
	uint32_t color(int iter2) const
	{
		if (serial_v) {
			iter2 = iter;
		}
		if (iter2 == max_iter) return SDL_MapRGB(screen->format, 0, 0, 0);
		const int ci = 512 * iter2 / max_iter; // incremental value for color
		// return SDL_MapRGB(screen->format, 40*iter & 255, 66*iter & 255, 100*iter & 255);
		return iter2 < max_iter / 2 ? SDL_MapRGB(screen->format, ci, 0, 0)
			: SDL_MapRGB(screen->format, 255, ci - 255, ci - 255);
	}
	
private:
	complex<float> iterate()
	{
		complex<float> z = c;
		for (; iter < max_iter && norm(z) <= 4.0f; iter++)
			z = z * z + c;
		return z;
	};
	const int serial_v;
	SDL_Surface* screen;
	const int max_iter;
	int iter;
	complex<float> c;
};

int main(int argc, char* argv[])
{
	int serial_v;
	cout << "Enter 1 for serial version or 0 for gpu-cuda version and press Enter";
	cout << endl;
	cin >> serial_v;

	// measure time
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	const int max_iter = 300;
	int xdim = 1200, ydim = 800;
	if (argc >= 3)
		xdim = atoi(argv[1]), ydim = atoi(argv[2]);

	sdl_check(SDL_Init(SDL_INIT_VIDEO) != -1);
	SDL_Surface* screen = SDL_SetVideoMode(xdim, ydim, 32, SDL_DOUBLEBUF); sdl_check(screen);
	SDL_WM_SetCaption("Mandelbrot's Apple Manikin", "Mandelbrot's Apple Manikin");

	SDL_LockSurface(screen);

	// CUDA computation
	int *iterations;
	iterations = new int[xdim*ydim];
	compute_iterations(iterations,xdim,ydim,max_iter);
	
	for (int y = 0; y < ydim; y++)
		for (int x = 0; x < xdim; x++) {
			
			//pass the pre-calculated iterations
			int my_iter = iterations[x*ydim + y];
			mandel_pixel m(screen, x, y, xdim, ydim, max_iter, serial_v);
			put_pixel(screen, x, y, m.color(my_iter));
		}

	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	cout << endl << "Time elapsed = " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << endl;

	SDL_UnlockSurface(screen);
	SDL_Flip(screen);
	// SDL_SaveBMP(screen, "mandelbrot.bmp"); // if you want to save the fractal

	bool run = true;
	while (run) {
		// Polling for events as long as there exists some
		SDL_Event event;
		while (SDL_PollEvent(&event))
			switch (event.type) {
			case SDL_QUIT: run = false; break;
			}
	}

	SDL_Quit();
	delete[] iterations;
	return 0;
}