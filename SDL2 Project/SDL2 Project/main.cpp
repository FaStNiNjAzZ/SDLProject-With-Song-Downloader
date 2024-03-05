/*#include <SDL.h>
#include <stdio.h>
//Screen dimension constantsconst 
int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	printf("running");
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{//Get window surface
			screenSurface = SDL_GetWindowSurface(window);
			//Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
			//Update the surface
			SDL_UpdateWindowSurface(window);
			//Hack to get window to stay up
			SDL_Event e;
			bool quit = false;
			while (quit == false)
			{
				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT) quit = true;
				}
			}
		}
	}
	//Destroy window
	SDL_DestroyWindow( window );
	//Quit SDL 
	SDL_Quit();
	return 0;
}*/

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <stdio.h>
#include <windows.h>
#include <cstdio>
#include <iostream>
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma comment(lib, "Urlmon.lib")
using namespace std;

#include "MyEngineSubsystem.h"
#include <string>
using namespace ExampleNS;

// Functions
int downloader();

int main(int argc, char* argv[])
{
	MyEngineSubsystem mes;
	mes.test();
	// returns zero on success else non-zero
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}
	SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1000, 1000, 0);

	// triggers the program that controls
	// your graphics hardware and sets flags
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

	// creates a surface to load an image into the main memory
	SDL_Surface* surface;

	// please provide a path for your image
	surface = IMG_Load("images/bmw.jpg");

	// loads image to our graphics hardware memory.
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);

	// clears main-memory
	SDL_FreeSurface(surface);

	// let us control our image position
	// so that we can move it with our keyboard.
	SDL_Rect dest;

	// connects our texture with dest to control position
	SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

	// adjust height and width of our image box.
	dest.w /= 6;
	dest.h /= 6;

	// sets initial x-position of object
	dest.x = (1000 - dest.w) / 2;

	// sets initial y-position of object
	dest.y = (1000 - dest.h) / 2;

	// controls animation loop
	int close = 0;

	// speed of box
	int speed = 300;

	// animation loop
	while (!close) {
		SDL_Event event;

		// Events management
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_QUIT:
				// handling of close button
				close = 1;
				break;

			case SDL_KEYDOWN:
				// keyboard API for key pressed
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_W:
				case SDL_SCANCODE_UP:
					dest.y -= speed / 30;
					break;
				case SDL_SCANCODE_A:
				case SDL_SCANCODE_LEFT:
					dest.x -= speed / 30;
					break;
				case SDL_SCANCODE_S:
				case SDL_SCANCODE_DOWN:
					dest.y += speed / 30;
					break;
				case SDL_SCANCODE_D:
				case SDL_SCANCODE_RIGHT:
					dest.x += speed / 30;
					break;
				case SDL_SCANCODE_ESCAPE:
					SDL_Quit();
					break;
				case SDL_SCANCODE_9:
					downloader();
					break;
				default:
					break;
				}
			}
		}

		// right boundary
		if (dest.x + dest.w > 1000)
			dest.x = 1000 - dest.w;

		// left boundary
		if (dest.x < 0)
			dest.x = 0;

		// bottom boundary
		if (dest.y + dest.h > 1000)
			dest.y = 1000 - dest.h;

		// upper boundary
		if (dest.y < 0)
			dest.y = 0;

		// clears the screen
		SDL_RenderClear(rend);
		SDL_RenderCopy(rend, tex, NULL, &dest);

		// triggers the double buffers
		// for multiple rendering
		SDL_RenderPresent(rend);

		// calculates to 60 fps
		SDL_Delay(1000 / 60);
	}

	// destroy texture
	SDL_DestroyTexture(tex);

	// destroy renderer
	SDL_DestroyRenderer(rend);

	// destroy window
	SDL_DestroyWindow(win);

	// close SDL
	SDL_Quit();

	return 0;
}


// Program to download the home page 
// of google.com to a file named 
// myfile.txt. the file can be 
// found in the same working directory 
// from which the project runs 
int downloader()
{

	printf("How To Download Songs:\n");
	printf("1. Go to newgrounds.com/audio.\n");
	printf("2. Take the song ID from the end of the URL. For example https://www.newgrounds.com/audio/listen/739991, the 739991 is the song ID.\n");
	printf("3. Paste the song ID below.\n");
	
	string songIDInput;
	std::cout << "> ";
	std::cin >> songIDInput;


	// the URL to download from 
	wchar_t srcURL[43] = L"https://www.newgrounds.com/audio/download/";
	wchar_t idURL[2] = L"1";
	const wchar_t* finalURL = wcscat(srcURL, idURL);

	// the destination file 
	const wchar_t* destFile = L"downloads/myfile.mp3";

	// URLDownloadToFile returns S_OK on success 
	if (S_OK == URLDownloadToFile(NULL, srcURL, destFile, 0, NULL))
	{

		printf("Saved to 'myfile.mp3'");

		return 0;

	}

	else
	{

		printf("Failed");

		return -1;

	}

}