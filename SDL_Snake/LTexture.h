#include "InitSDL.h"

class LTexture
{
public:
	static const int TextureSize = 24;

	LTexture()
	{
		//Initialize
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		PosX = 0;
		PosY = 0;
		ID = 0;

	}
	void setXPos(int x) { PosX = x; }
	void setYPos(int y) { PosY = y; }

	~LTexture()
	{
		//Deallocate
		free();
	}
	void setID(int id)
	{
		ID = id;
	}

	bool  loadImageToTexture(std::string path)
	{
		//Get rid of preexisting texture
		free();

		//The final texture
		SDL_Texture* newTexture = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), "");
		}
		else
		{
			//Color key image
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0xFF, 0xFF));

			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
			if (newTexture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			}
			else
			{
				//Get image dimensions
				mWidth = loadedSurface->w;
				mHeight = loadedSurface->h;
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}

		//Return success
		mTexture = newTexture;
		return true;

	}

	void free()
	{
		//Free texture if it exists
		if (mTexture != NULL)
		{
			SDL_DestroyTexture(mTexture);
			mTexture = NULL;
			mWidth = 0;
			mHeight = 0;
			PosX = 0;
			PosY = 0;
		}
	}


	void render(int x, int y, double angle = NULL, SDL_Rect* clip = NULL, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)
	{
		//Set rendering space and render to screen
		SDL_Rect renderQuad = { x, y, mWidth, mHeight };

		this->PosX = x;
		this->PosY = y;

		std::cout << "Block ID: " << this->ID << "  X: " << x << "  Y: " << y << std::endl;
		//Set clip rendering dimensions
		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		//Render to screen
		SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
	}

	int getWidth()
	{
		return mWidth;
	}

	int getHeight()
	{
		return mHeight;
	}

	int getPosX()
	{
		return PosX;
	}

	int getPosY()
	{
		return PosY;
	}
private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;

	int PosX;
	int PosY;
	int ID;
};