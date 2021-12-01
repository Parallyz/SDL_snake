#define SDL_MAIN_HANDLED

#include<iostream>
#include<SDL.h>
#include <SDL_image.h>
#include <list>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path

	LTexture* loadFromFile(std::string path);



	void free();



	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

	int getPosX();
	int getPosY();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;

	int PosX;
	int PosY;
};
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

LTexture* HeadTexture = new LTexture;
LTexture* TailTexture = new LTexture;
LTexture* BodyTexture = new LTexture;
LTexture* DirectionTexture = new LTexture;


class Snake {
	int xPosDirection;
	int yPosDirection;
	int lenghtSnake = 2;
	Direction currentDirection;
	Direction previousDirection;
	std::list<LTexture>* SnakeTextures;

public:
	Snake()
	{
		lenghtSnake = 2;
		this->SnakeTextures = new std::list<LTexture>();
		currentDirection = RIGHT;
		previousDirection = RIGHT;
		xPosDirection = 0;
		yPosDirection = 0;

	}

	Direction getCurrentDirection()
	{
		return currentDirection;
	}

	void ChangeDirection(Direction newDirection)
	{
		xPosDirection = SnakeTextures->front().getPosX();
		yPosDirection = SnakeTextures->front().getPosY();
		previousDirection = currentDirection;
		currentDirection = newDirection;
	}
	int getXPosDirection()
	{
		return xPosDirection;
	}
	int getYPosDirection()
	{
		return xPosDirection;
	}
	void free() {

		std::list<LTexture>::iterator it;

		for (it = SnakeTextures->begin(); it != SnakeTextures->end(); ++it) {
			it->free();
		}
		delete	this->SnakeTextures;
	}
	~Snake() { free(); }

	void renderHorizontal(int x, int y)
	{
		std::list<LTexture>::iterator it;
		int i = SnakeTextures->begin()->getWidth();
		for (it = SnakeTextures->begin(); it != SnakeTextures->end(); ++it) {
			it->render(x - i, y);
			i += SnakeTextures->begin()->getWidth();
		}

	}
	void renderVertical(int x, int y,bool isUp)
	{
		std::list<LTexture>::iterator it;
		int i = SnakeTextures->begin()->getWidth();
		for (it = SnakeTextures->begin(); it != SnakeTextures->end(); ++it) {
			if(!isUp)
				it->render(x, y - i);
			else {
				it->render(x, y + i);
			}
			i += SnakeTextures->begin()->getWidth();
		}

	}

	void SwapHeadWithTail()
	{
		std::list<LTexture>::iterator first;
		std::list<LTexture>* newSnake;
		newSnake->push_back(*head);
		newSnake->push_back(*body);
		newSnake->push_back(*body);
		newSnake->push_back(*body);
		newSnake->push_back(*body);
		newSnake->push_back(*body);


		LTexture* tail = TailTexture->loadFromFile("tail.png");

		this->SnakeTextures->push_back(*tail);
		//std::swap(first, last);
	}

	bool loadFromFile()
	{
		LTexture* head = HeadTexture->loadFromFile("head.png");
		LTexture* body = BodyTexture->loadFromFile("body.png");
		LTexture* direction = DirectionTexture->loadFromFile("L.png");

		this->SnakeTextures->push_back(*head);
		this->SnakeTextures->push_back(*body);
		this->SnakeTextures->push_back(*body);
		this->SnakeTextures->push_back(*body);
		this->SnakeTextures->push_back(*body);
		this->SnakeTextures->push_back(*body);


		LTexture* tail = TailTexture->loadFromFile("tail.png");

		this->SnakeTextures->push_back(*tail);

		return true;
	}

};
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();



Snake* mSnakeTexture = new Snake;

//Buttons objects


LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	PosX = 0;
	PosY = 0;

}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

LTexture* LTexture::loadFromFile(std::string path)
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
	return this;

}

void LTexture::free()
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


void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	this->PosX = x;
	this->PosY = y;


	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

int LTexture::getPosX()
{
	return PosX;
}

int LTexture::getPosY()
{
	return PosY;
}
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{


			}
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}

		}
	}

	return success;
}
void close()
{
	//Free loaded images
	mSnakeTexture->free();
	delete mSnakeTexture;
	delete HeadTexture;
	delete TailTexture;
	delete BodyTexture;
	delete DirectionTexture;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load sprites
	if (!mSnakeTexture->loadFromFile())
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}


	return success;
}

int main()
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{

			bool quit = false;

			SDL_Event e;

			int posX = 1;
			int posY = 1;


			while (!quit)
			{



				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

					if (currentKeyStates[SDL_SCANCODE_UP])
					{
						if (mSnakeTexture->getCurrentDirection() != UP &&
							mSnakeTexture->getCurrentDirection() != DOWN)
						{
							mSnakeTexture->ChangeDirection(UP);
						}
					}
					else if (currentKeyStates[SDL_SCANCODE_DOWN])
					{
						if (mSnakeTexture->getCurrentDirection() != UP &&
							mSnakeTexture->getCurrentDirection() != DOWN)
						{
							mSnakeTexture->ChangeDirection(DOWN);

						}
					}
					else if (currentKeyStates[SDL_SCANCODE_LEFT])
					{
						if (mSnakeTexture->getCurrentDirection() != LEFT &&
							mSnakeTexture->getCurrentDirection() != RIGHT)
						{
							mSnakeTexture->ChangeDirection(LEFT);

						}
					}
					else if (currentKeyStates[SDL_SCANCODE_RIGHT])
					{
						if (mSnakeTexture->getCurrentDirection() != LEFT &&
							mSnakeTexture->getCurrentDirection() != RIGHT)
						{
							mSnakeTexture->ChangeDirection(RIGHT);

						}
					}






				}

				SDL_RenderClear(gRenderer);


				switch (mSnakeTexture->getCurrentDirection())
				{
				case UP:
				{
					std::cout << mSnakeTexture->getCurrentDirection() << std::endl;
					if (posY <= 0)
					{
						SDL_Delay(1);
					}
					posY--;
					mSnakeTexture->renderVertical(posX, posY,true);
				}
				break;
				case DOWN:
				{
					if (posY >= SCREEN_HEIGHT)
					{
						SDL_Delay(1);
					}
					posY++;
					mSnakeTexture->renderVertical(posX, posY,false);
				}
				break;
				case RIGHT:
				{
					if (posX >= SCREEN_WIDTH)
					{
						SDL_Delay(1);
					}
					posX++;
					mSnakeTexture->renderHorizontal(posX, posY);
				}
				break;
				case LEFT:
				{
					mSnakeTexture->SwapHeadWithTail();
					if (posX <= 0)
					{
						SDL_Delay(1);
					}
					posX--;
					mSnakeTexture->renderHorizontal(posX, posY);
				}
				break;
				}
				std::cout << "X: " << posX<<"Y: "<<posY<<std::endl;
				SDL_RenderPresent(gRenderer);
			}
		}
	}


	close();

	return 0;
}