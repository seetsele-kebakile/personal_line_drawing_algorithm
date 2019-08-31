/*Note:  this sample was meant to give me a deeper understanding of the hurdles 
which need to be overcome when making line drawing algorithms. I am fully aware 
of already existing line drawing algorithms such as Bresenham's line drawing algorithm and Xiaolin Wu's
algorithm . I am  a 15 year old male and I live in Africa,the land of terrible internet.
I am also fairly new to programming so please excuse any naive pieces of code :). 
I am open to any suggestions and improvement. thanks.*/


#include"SDL.h"
#include"SDL_video.h"

#define WIDTH 800
#define HEIGHT 600

void drawpixel(Uint32* pixel, int x, int y, int r, int g, int b, int a)
{
	pixel[x + (y * 800)] = (Uint32)r << 24 | g << 16 | b << 8 | a;
}
void joinpoints(Uint32* pixels, int x1, int y1, int x2, int y2,int r, int g, int b, int a)
{
	int nx = (x2 >= x1) ? (x2 - x1) + 1 : (x1 - x2) + 1;
	int ny = (y2 >= y1) ? (y2 - y1) + 1 : (y1 - y2) + 1;

	if (nx == 1 || ny == 1)
	{
		if (nx > ny)
		{
			for (int c = x1;c <= x2;c++) { drawpixel(pixels, c, y1, r, g, b, a); }
		}
		else {
			for (int c = y1;c <= y2;c++) { drawpixel(pixels, x1, c, r, g, b, a); }
		}
		
	}
	int inc = 0;
	if (nx >= ny) { inc = (x2 >= x1) ? 1 : -1; }
	else { inc = (y2 >= y1) ? 1 : -1; }
	int cond = (((nx * ny) / 2) / 2) + 0.5f;
	for (int c = 1; c <= cond * 2;c++)
	{
		drawpixel(pixels, x1, y1, r, g, b, a);
		if (c == cond)
		{
			inc *= -1;x1 = x2;y1 = y2;
		}
		else {
			if (nx >= ny) {
				x1 += inc;
			}
			else {
				y1 += inc;
			}
		}

		
	}
}
void drawline(Uint32* pixel,int x1, int y1, int x2, int y2,int r, int g, int b, int a)
{
	if (x1 > x2)
	{
		int tempval = x2;
			x2 = x1;
			x1 = tempval; 
                        tempval = y2;
		         y2  = y1;
		
		
y1=tempval; 
	}
		
	
	int xdif = (x1 > x2) ? x1 - x2 : x2 - x1;
	int ydif = (y1 > y2) ? y1 - y2 : y2 - y1;
	int largestdif = (xdif >= ydif) ? xdif : ydif;
	int smallestdif = (xdif >= ydif) ? ydif : xdif;
	if (smallestdif < 2)
	{
		joinpoints(pixel, x1, y1, x2, y2,r,g,b,a);
	}
	else {
		int startx = x1;int starty = y1;int endx = x1;int endy = y1;
		int xinc = x1;int yinc = y1;
		float gradient = largestdif / smallestdif;;
		for (int counter = 0;counter < smallestdif;counter++)
		{
			if (xdif >= ydif)
			{
				endx = (gradient * (counter + 1));
				endx += (x2 > x1) ? xinc : -xinc;
				(y2 > y1) ? endy++ : endy--;
				joinpoints(pixel, startx, starty, endx, endy,r,g,b,a);
				startx = endx;starty = endy;
			}
			else {
				endy = (gradient * (counter + 1));
				endy += (y2 > y1)?yinc:-yinc;
				(x2 > x1) ? endx++ : endx++;
				joinpoints(pixel, startx, starty, endx, endy,r,g,b,a);
				startx = endx;starty = endy;
			}
		}
	}
}


int  main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	SDL_Window* win;
	SDL_Renderer* rnd;
	SDL_Texture* framebuffer;
	
	bool isrunning = true;
	
	win = SDL_CreateWindow("graphics_learning", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	rnd = SDL_CreateRenderer(win, -1,SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(rnd, WIDTH, HEIGHT);
	framebuffer = SDL_CreateTexture(rnd, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	SDL_Event ev;

	Uint32* pixels = new Uint32[WIDTH * HEIGHT];
	
	

	while (isrunning)
	{
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				isrunning = false;
			}
		}

		SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
		SDL_RenderClear(rnd);
		
		drawline(pixels, 100, 100, 500, 100, 255, 165, 0, 255);
		drawline(pixels, 100, 100, 100, 500, 255, 165, 0, 255);
		drawline(pixels, 500, 100, 500, 500, 255, 165, 0, 255);
		drawline(pixels, 100, 500, 500, 500, 255, 165, 0, 255);
		drawline(pixels, 100, 100, 500, 500, 255, 165, 0, 255);
		drawline(pixels, 100, 500, 500, 100, 255, 165, 0, 255);
		drawline(pixels, 300, 100, 300, 500, 255, 165, 0, 255);
		drawline(pixels, 100, 300, 500, 300, 255, 165, 0, 255);
	
		SDL_UpdateTexture(framebuffer, NULL, pixels, WIDTH * sizeof(Uint32));
	
		SDL_RenderCopy(rnd, framebuffer, NULL, NULL);

		SDL_RenderPresent(rnd);
	}
	free(pixels);
	SDL_DestroyTexture(framebuffer);
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(rnd);
	SDL_Quit();
	return 0;
}
