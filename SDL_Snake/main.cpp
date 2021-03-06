

#include"Snake.h"


void close(Snake* snake)
{
	snake->free();


	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;


	IMG_Quit();
	SDL_Quit();
}

bool LoadTexturesToSnake(Snake* snake)
{

	bool success = true;


	if (!snake->InitSnake())
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}


	return success;
}

int main(int argc, char* argv[])
{
	
	Snake* mSnake = new Snake();
	
	
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!LoadTexturesToSnake(mSnake))
		{
			printf("Failed to load media!\n");
		}
		else
		{

			bool quit = false;

			SDL_Event e;

			int posX = 0;
			int posY = 0;

			bool start = true;
			
			LTexture* apple = new LTexture();
			apple->loadImageToTexture("apple.png");
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
						if (mSnake->getCurrentDirection() != UP &&
							mSnake->getCurrentDirection() != DOWN)
						{
							mSnake->ChangeDirection(Direction::UP);
						}
					}
					else if (currentKeyStates[SDL_SCANCODE_DOWN])
					{
						if (mSnake->getCurrentDirection() != UP &&
							mSnake->getCurrentDirection() != DOWN)
						{
							mSnake->ChangeDirection(Direction::DOWN);

						}
					}
					else if (currentKeyStates[SDL_SCANCODE_LEFT])
					{
						if (mSnake->getCurrentDirection() != LEFT &&
							mSnake->getCurrentDirection() != RIGHT)
						{
							mSnake->ChangeDirection(Direction::LEFT);

						}
					}
					else if (currentKeyStates[SDL_SCANCODE_RIGHT])
					{
						if (mSnake->getCurrentDirection() != LEFT &&
							mSnake->getCurrentDirection() != RIGHT)
						{
							mSnake->ChangeDirection(Direction::RIGHT);

						}
					}
				}

				SDL_RenderClear(gRenderer);
				apple->renderApple(start);
				mSnake->move(apple);

			//	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);
				

				start = false;

				SDL_Delay(120);
				
				SDL_RenderPresent(gRenderer);
			}
			apple->free();
		}
		
	}

	
	close(mSnake);

	return 0;
}