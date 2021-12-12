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
		return SnakeTextures.back().getTextureDirection();;
	}
	void ChangeDirection(Direction newDirection)
	{
		SnakeTextures.back().setPreviousDirection(SnakeTextures.back().getTextureDirection());
		SnakeTextures.back().setTextureDirection(newDirection);



	}


	void free() {

		std::vector<LTexture>::iterator it;

		for (auto& it : SnakeTextures) {
			it.free();
		}


	}
	~Snake() { free(); }

	bool isOverOfScreen(int x, int y)
	{

		if (x >= SCREEN_WIDTH
			|| y >= SCREEN_HEIGHT
			|| x < 0
			|| y < 0)
		{
			return true;
		}
		return false;
	}

	bool isHeadisOnTexture(int x, int y)
	{

		for (auto it = SnakeTextures.begin(); it != SnakeTextures.end() - 2; ++it)
		{
			if (x >= it->getPosX() && x < it->getPosX() + LTexture::TextureSize
				&& y >= it->getPosY() && y < it->getPosY() + LTexture::TextureSize)
			{
				return true;
			}
		}

		return false;
	}

	void renderSnakeTexture(LTexture& texture)
	{
		SDL_Rect* renderQuad = new SDL_Rect();



		renderQuad->x = texture.getPosX();
		renderQuad->y = texture.getPosY();

		renderQuad->w = texture.getWidth();
		renderQuad->h = texture.getHeight();


		std::cout << "Block ID: " << texture.getID() << "    X: " << texture.getPosX() << "  Y: " << texture.getPosY() << std::endl;


		SDL_RenderCopyEx(gRenderer, texture.getSDLTexture(), NULL, renderQuad, texture.getAngle(), NULL, SDL_FLIP_NONE);

	}

	void grow()
	{
		LTexture* newbody = new LTexture();
		
		std::vector<LTexture>::iterator it = SnakeTextures.begin() ;

		
		newbody->setXPos(it->getPosX());
		newbody->setYPos(it->getPosY());
		newbody->setTextureDirection((SnakeTextures.begin())->getTextureDirection());


		switch (it->getTextureDirection())
		{
		case UP:
		{
			it->setYPos(it->getPosY() + LTexture::TextureSize);
		}
		break;
		case DOWN:
		{
			it->setYPos(it->getPosY() - LTexture::TextureSize);
		}
		break;
		case RIGHT:
		{
			it->setXPos(it->getPosX() - LTexture::TextureSize);
		}
		break;
		case LEFT:
		{
			it->setXPos(it->getPosX() + LTexture::TextureSize);
		}
		break;
		}

		it = SnakeTextures.begin()+1;
	
		SnakeTextures.insert(it, *newbody);

		int i = 1;
		
	
		for (auto &it:SnakeTextures)
		{
			it.loadImageToTexture("body.png");
			it.setID(i++);
			
		}

		SnakeTextures[0].loadImageToTexture("tail.png");
		SnakeTextures[SnakeTextures.size() - 2].loadImageToTexture("head.png");
		SnakeTextures[SnakeTextures.size() - 1].~LTexture();


	


	}

	bool changeDirection(int index, LTexture& texture, Direction direction, LTexture& apple) {

		bool isGrow = false;
		switch (direction)
		{
		case LEFT: {

			texture.setAngle(180);

			texture.setXPos(texture.getPosX() - LTexture::TextureSize);
			texture.setYPos(texture.getPosY());
			if (index == SnakeTextures.size() && direction != texture.getPreviousDirection()) {
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
					texture.setXPos(texture.getPosX() + LTexture::TextureSize);
					texture.setYPos(texture.getPosY() + LTexture::TextureSize);

				}
				if (texture.getPreviousDirection() == DOWN)
				{
					texture.setXPos(texture.getPosX() + LTexture::TextureSize);
					texture.setYPos(texture.getPosY() - LTexture::TextureSize);

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
					texture.setXPos(texture.getPosX() - LTexture::TextureSize);
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

		if (index == (SnakeTextures.size()) - 1)
		{

			if (isOverOfScreen(texture.getPosX(), texture.getPosY())
				|| isHeadisOnTexture(texture.getPosX(), texture.getPosY())
				)
			{
				SDL_Delay(5000);
				IMG_Quit();
				SDL_Quit();
			}
			if (texture.getPosX() == apple.getPosX() &&
				texture.getPosY() == apple.getPosY())
			{
				isGrow = true;

			}

		}
		return isGrow;
	}


	void move(LTexture* apple) {

		int i = 1;
		bool isGrow = false;
		for (auto& it : SnakeTextures) {
			if (it.getID() == (SnakeTextures.end() - 2)->getID())
			{
				isGrow = changeDirection(i++, it, getNextDirection(it.getID()), *apple);
			}
			else {

				changeDirection(i++, it, getNextDirection(it.getID()), *apple);
			}
			renderSnakeTexture(it);

		}
		if (isGrow)
		{
			grow();
			apple->randPos();
			isGrow = false;
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

		LTexture* head1 = new LTexture();
		head1->setID(4);
		SnakeTextures.resize(4);


		tail->setXPos(0);
		tail->setYPos(0);




		SnakeTextures[0] = *tail;
		SnakeTextures[1] = *body;

		SnakeTextures[2] = *head;
		SnakeTextures[3] = *head1;


		


		int x = 0;
		for (auto& it : SnakeTextures) {
			it.setXPos(it.getPosX() + LTexture::TextureSize * ++x);
			it.setYPos(it.getPosY() + LTexture::TextureSize);

			it.render(it.getPosX(), it.getPosY());
		}

		return true;
	}

};