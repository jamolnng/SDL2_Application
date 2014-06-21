#pragma once

#include <SDL.h>

class LTexture
{
	public:
		//Initializes variables
		LTexture(SDL_Renderer* r);

		//Deallocates memory
		~LTexture(void);

		//Loads image at specified path
		bool loadFromFile(char* path);

	#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
	#endif

		//Creates blank texture
		bool createBlank(int width, int height, SDL_TextureAccess = SDL_TEXTUREACCESS_STREAMING);

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha modulation
		void setAlpha(Uint8 alpha);

		//Renders texture at given point
		void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Set self as render target
		void setAsRenderTarget(void);

		//Gets image dimensions
		int getWidth(void);
		int getHeight(void);

		//Pixel manipulators
		bool lockTexture(void);
		bool unlockTexture(void);
		void* getPixels(void);
		void copyPixels(void* pixels);
		int getPitch(void);
		Uint32 getPixel32(unsigned int x, unsigned int y);

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
		void* mPixels;
		int mPitch;

		//Image dimensions
		int mWidth;
		int mHeight;

		SDL_Renderer* gRenderer;
};