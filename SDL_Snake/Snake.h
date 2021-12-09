#include"LTexture.h"

#include <vector>
#include <algorithm>
#undef main

class Snake {

	std::vector<LTexture> SnakeTextures;

public:

	Snake()
	{
		SnakeTextures = std::vector<LTexture>(2);
	}

	Direction getCurrentDirection()
	{
		return SnakeTextures.back().getTextureDirection();
	}
	Direction getNextDirection(int idTexture) {
		for (auto& it : SnakeTextures) {
			if (it.getID() - 1 == idTexture)
			{
				
				return it.getTextureDirection();
			}
		}
		return currentDirection;
	}
	void ChangeDirection(Direction newDirection)
	{
		SnakeTextures.back().setPreviousDirection(SnakeTextures.back().getTextureDirection());
		SnakeTextures.back().setTextureDirection(newDirection);
<<<<<<< HEAD
=======



>>>>>>> ac54b742082ca33e05d70a8d517958ce73e26ac8
	}


	void free() {

		std::vector<LTexture>::iterator it;

		for (auto& it : SnakeTextures) {
			it.free();
		}


	}
	~Snake() { free(); }

	bool isGameOver(int x, int y)
	{

		if (x >= SCREEN_WIDTH
			|| y >= SCREEN_HEIGHT
			|| x <= 0//- LTexture::TextureSize 
			|| y < 0)
		{
			return true;
		}
		return false;
	}

	bool isHeadisOnTexture(int x, int y, Direction direction)
	{
		/*switch (direction)
		{
		case LEFT:
			x += LTexture::TextureSize;
			break;

		case UP:
			y += LTexture::TextureSize;
			break;

		}*/
		for (auto it = SnakeTextures.begin(); it != SnakeTextures.end() - 2; ++it)
		{
			if (x >= it->getPosX() && x <= it->getPosX() + LTexture::TextureSize
				&& y >= it->getPosY() && y <= it->getPosY() + LTexture::TextureSize)
			{
				return true;
			}
		}

		return false;
	}

	void renderSnakeTexture( LTexture& texture)
	{
		SDL_Rect* renderQuad = new SDL_Rect();



		renderQuad->x = texture.getPosX();
		renderQuad->y = texture.getPosY();

		renderQuad->w = texture.getWidth();
		renderQuad->h = texture.getHeight();

<<<<<<< HEAD
		texture.setTextureDirection(direction);
		
		
		texture.setXPos(renderQuad->x);
		texture.setYPos(renderQuad->y);
		if (ifGameOver())
	{
			SDL_Delay(1);
		}
	if (renderQuad->x == apple.getPosX() &&
		renderQuad->y == apple.getPosY() &&
		texture.getID() == SnakeTextures.back().getID() - 1)
	{
			grow();
		apple.randPos();
	}
=======
>>>>>>> ac54b742082ca33e05d70a8d517958ce73e26ac8

		std::cout << "Block ID: " << texture.getID() << "    X: " << texture.getPosX() << "  Y: " << texture.getPosY() << std::endl;


		SDL_RenderCopyEx(gRenderer, texture.getSDLTexture(), NULL, renderQuad, texture.getAngle(), NULL, SDL_FLIP_NONE);

	}

	LTexture* grow()
	{
		LTexture* newbody = new LTexture();
		newbody->loadImageToTexture("body.png");


		std::vector<LTexture>::iterator it = SnakeTextures.end() - 1;




		newbody->setXPos(it->getPosX());
		newbody->setYPos(it->getPosY());

		SnakeTextures.insert(it, *newbody);
		it = SnakeTextures.end() - 2;
		it->setID(SnakeTextures.size() - 1);
		for (it = SnakeTextures.end() - 1; it != SnakeTextures.end(); ++it)
		{
			it->setID(it->getID() + 1);
		}




		it = SnakeTextures.end() - 1;


		return it->getTexture();


	}

	bool changeDirection(int index, LTexture& texture, Direction direction, LTexture& apple) {

		bool isGrow = false;
		switch (direction)
		{
		case LEFT: {

			texture.setAngle(180);

			texture.setXPos(texture.getPosX() - LTexture::TextureSize);
			texture.setYPos(texture.getPosY());
			if(index == SnakeTextures.size()&&direction!=texture.getPreviousDirection()) {
				if (texture.getPreviousDirection() == UP)
				{
					texture.setXPos(texture.getPosX() - LTexture::TextureSize);
					texture.setYPos(texture.getPosY() + LTexture::TextureSize);


				}
				if (texture.getPreviousDirection() == DOWN)
				{
					texture.setYPos(texture.getPosY() - LTexture::TextureSize);
					texture.setXPos(texture.getPosX() - LTexture::TextureSize);

				}
			}
		}
		
		 break;
		case RIGHT: {
			texture.setAngle(0);

			texture.setXPos(texture.getPosX() + LTexture::TextureSize);
			texture.setYPos(texture.getPosY());
			if (index == SnakeTextures.size() && direction != texture.getPreviousDirection()) {
				if (texture.getPreviousDirection() == UP)
				{
					texture.setXPos(texture.getPosX() + LTexture::TextureSize );
					texture.setYPos(texture.getPosY() + LTexture::TextureSize);

				}
				if (texture.getPreviousDirection() == DOWN)
				{
					texture.setXPos(texture.getPosX() + LTexture::TextureSize );
					texture.setYPos(texture.getPosY() - LTexture::TextureSize );

				}
			}

		}
		 break;

		case UP: {
			texture.setAngle(270);
			texture.setXPos(texture.getPosX());
			texture.setYPos(texture.getPosY() - LTexture::TextureSize);

			if (index == SnakeTextures.size() && direction != texture.getPreviousDirection()) {
				if (texture.getPreviousDirection() == RIGHT)
				{
					texture.setXPos(texture.getPosX() - LTexture::TextureSize);
					texture.setYPos(texture.getPosY() - LTexture::TextureSize);


				}
				if (texture.getPreviousDirection() == LEFT)
				{
					texture.setXPos(texture.getPosX() + LTexture::TextureSize);
					texture.setYPos(texture.getPosY() - LTexture::TextureSize);

				}
			}
		}
			   break;

		case DOWN: {
			texture.setAngle(90);

		
			texture.setXPos(texture.getPosX());
			texture.setYPos(texture.getPosY() + LTexture::TextureSize);
			if (index == SnakeTextures.size() && direction != texture.getPreviousDirection()) {
				if (texture.getPreviousDirection() == RIGHT)
				{
						texture.setXPos(texture.getPosX() - LTexture::TextureSize );
						texture.setYPos(texture.getPosY() + LTexture::TextureSize);


				}
				if (texture.getPreviousDirection() == LEFT)
				{
					texture.setXPos(texture.getPosX() + LTexture::TextureSize);
					texture.setYPos(texture.getPosY() + LTexture::TextureSize);

				}
			}

		}
				 break;


		}
		texture.setPreviousDirection(texture.getTextureDirection());
		texture.setTextureDirection(direction);

		if (index == (SnakeTextures.size()))
		{

			/*if (isGameOver(texture.getPosX(), texture.getPosY())
				|| isHeadisOnTexture(texture.getPosX(), texture.getPosY(), direction))
			{
				SDL_Delay(10000);
			}
			if (texture.getPosX() == apple.getPosX() &&
				texture.getPosY() == apple.getPosY())
			{
				isGrow = true;

			}*/

		}
		return isGrow;
	}


	void move(LTexture* apple) {

		int i = 1;
		bool isGrow = false;
		for (auto& it : SnakeTextures) {
			isGrow = changeDirection(i++,it, getNextDirection(it.getID()), *apple);
			 renderSnakeTexture(it );

		}
		if (isGrow)
		{
			grow();
		}
	}

	bool InitSnake()
	{
		LTexture* tail = new LTexture();
		tail->loadImageToTexture("tail.png");
		tail->setID(1);


		LTexture* body = new LTexture();
		body->loadImageToTexture("body.png");
		body->setID(2);

		LTexture* head = new LTexture();
		head->loadImageToTexture("head.png");
		head->setID(3);





		tail->setXPos(0);
		tail->setYPos(0);

	
		SnakeTextures.resize(3);

		SnakeTextures[0] = *tail;
		SnakeTextures[1] = *body;

		SnakeTextures[2] = *head;
	




		int x = 0;
		for (auto& it : SnakeTextures) {
			it.setXPos(it.getPosX() + LTexture::TextureSize * ++x);
			it.setYPos(it.getPosY() + LTexture::TextureSize);

			it.render(it.getPosX() , it.getPosY());
		}

		return true;
	}

};