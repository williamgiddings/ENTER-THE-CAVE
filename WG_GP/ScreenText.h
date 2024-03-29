/**
* @author Benjamin Williams <bwilliams@lincoln.ac.uk> modified by Phil Carlisle to use SDL_ttf instead of sttbimage
*
* @brief  A file which renders text to the screen.
* @notes  Consult the lecture slides for the usage of this class.
*/

//Include guard
#pragma once

#define _CRT_SECURE_NO_WARNINGS 1

//Import standard libraries
#include <string>
#include <cstdarg>
#include "SDL.h"


//Import SDL_ttf
#include "SDL_ttf.h"

class ScreenText
{
public:
	//Dimensions, positions & scale
	int width = 0, height = 0;
	int x = 0, y = 0;
	/// <summary>
	/// Creates a new instance of a ScreenText object. Attaches it to the window, and loads in a font from a given path.
	/// </summary>
	/// <param name="window">The window which the text will be drawn to.</param>
	/// <param name="fontPath">The path to load the font from (for this text).</param>
	ScreenText(SDL_Window* window, const std::string& fontPath, int fontsize = 32);

	/// <summary>
	/// Called when this instance has been destroyed.
	/// </summary>
	~ScreenText(void);

	/// <summary>
	/// Renders the text to screen.
	/// </summary>
	void render(void);

	/// <summary>
	/// Moves the text to another place on screen.
	/// </summary>
	/// <param name="x">The x position.</param>
	/// <param name="y">The y position.</param>
	void move(int x, int y);

	//Set colour
	void setColor(unsigned int color);
	void setColor(unsigned char r, unsigned char g, unsigned char b);
	void setColor(const SDL_Color color);

	/// <summary>
	/// Sets the text to render before render() is called.
	/// </summary>
	/// <param name="path">The text.</param>
	void setText(const std::string& text);

	/// <summary>
	/// Sets the text, along with the x, y position, (optional) font size and (optional) colour.
	/// </summary>
	/// <param name="text">The text.</param>
	/// <param name="posX">The x position.</param>
	/// <param name="posY">The y position.</param>
	/// <param name="fontSize">The font size.</param>
	/// <param name="r">The red component.</param>
	/// <param name="g">The green component.</param>
	/// <param name="b">The blue component.</param>
	void setText(const std::string& text, const int posX, const int posY,const bool bCenterText=false, const int fontSize = 48, const int r = 255, const int g = 255, const int b = 255);


	void setFontSize(const int fontSize);
	/// <summary>
	/// Updates and remakes the surface after any state changes.
	/// </summary>
	void updateSurface(void);
	SDL_Color color = { 255,255,255,255 };
private:

	//Helper functions
	bool loadFontData(const std::string& fontPath);
	void createTextSurface(void);

	//Internals/passed
	SDL_Renderer* renderer = NULL;
	SDL_Window* window = NULL;

	
	
	int fontScale = 32;

	//Current colour
	
	SDL_Color backgroundcolour = { 0,0,0,0 };

	//Current text
	std::string text;

	// path to font so we can reload for different point sizes
	std::string fontpath;

	// pointer to SDL TTF font
	TTF_Font * fontptr = NULL;

	//Buffers
	SDL_Surface* textSurface = NULL;
	SDL_Texture* textTexture = NULL;
};