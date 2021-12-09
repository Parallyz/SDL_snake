#include"LTexture.h"

#include <vector>
#include <algorithm>
#undef main

class Snake {

	std::vector<LTexture> SnakeTextures;

public:

	Snake()
	{
		SnakeTextures = std::vector<LTexture>(3);
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
		return  SnakeTextures.back().getTextureDirection();;
	}
	void ChangeDirection(Direction newDirection)
	{
		SnakeTextures.back().setTextureDirection(newDirection);



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
			|| x <=- LTexture::TextureSize 
			|| y < 0	)
		{
			return true;
		}
		return false;
	}

	bool isHeadisOnTexture(int x, int y,Direction direction)
	{
		switch (direction)
		{
		case LEFT:
			x += LTexture::TextureSize;
			break;
		
		case UP:
			y += LTexture::TextureSize;
			break;
		
		}
		for (auto it = SnakeTextures.begin(); it != SnakeTextures.end() - 4; ++it)
		{
			if (x >= it->getPosX() && x <= it->getPosX() + LTexture::TextureSize
			&& y >= it->getPosY() && y <= it->getPosY() + LTexture::TextureSize)
			{
				return true;
			}
		}
		
		return false;
	}

	void renderSnakeTexture(LTexture& texture, Direction direction, LTexture& apple)
	{
		SDL_Rect* renderQuad = new SDL_Rect();
		int angle = 0;
		bool ifrender = true;
		switch (direction)
		{
		case LEFT: {
			angle = 180;
			renderQuad->x = texture.getPosX() - LTexture::TextureSize;
			if (texture.getID() == SnakeTextures.size()) {
				// renderQuad->x = texture.getPosX() - (LTexture::TextureSize*2);
				ifrender = false;
			}
			renderQuad->y = texture.getPosY();

		}
				 break;
		case RIGHT: {

			renderQuad->x = texture.getPosX() + LTexture::TextureSize;
			renderQuad->y = texture.getPosY();

		}
				  break;

		case UP: {
			angle = 270;
			renderQuad->x = texture.getPosX();
			renderQuad->y = texture.getPosY() - LTexture::TextureSize;

		}
			   break;

		case DOWN: {
			angle = 90;
			renderQuad->x = texture.getPosX();
			renderQuad->y = texture.getPosY() + LTexture::TextureSize;
			//grow();
		}
				 break;
		case NONE: {

			renderQuad->x = texture.getPosX();
			renderQuad->y = texture.getPosY();
		}
				 break;

		}
		renderQuad->w = texture.getWidth();
		renderQuad->h = texture.getHeight();

		texture.setTextureDirection(direction);


		texture.setXPos(renderQuad->x);
		texture.setYPos(renderQuad->y);
		if (texture.getID() == SnakeTextures.back().getID() - 1)
		{

			if (isGameOver(texture.getPosX(),texture.getPosY())
				||isHeadisOnTexture(texture.getPosX(), texture.getPosY(),direction))
			{
					SDL_Delay(10000);
			}
			if (renderQuad->x == apple.getPosX() &&
				renderQuad->y == apple.getPosY())
			{
				texture = *grow();
				apple.randPos();
				//	ifrender = false;
			}
		}

		std::cout << "Block ID: " << texture.getID() << "    X: " << texture.getPosX() << "  Y: " << texture.getPosY() << std::endl;

		if (ifrender)
			SDL_RenderCopyEx(gRenderer, texture.getSDLTexture(), NULL, renderQuad, angle, NULL, SDL_FLIP_NONE);
	}

	LTexture* grow()
	{
		LTexture* newbody = new LTexture();
		newbody->loadImageToTexture("body.png");


		std::vector<LTexture>::iterator it = SnakeTextures.end() - 2;




		newbody->setXPos(it->getPosX());
		newbody->setYPos(it->getPosY());

		SnakeTextures.insert(it, *newbody);
		it = SnakeTextures.end() - 3;
		it->setID(SnakeTextures.size() - 2);
		for (it = SnakeTextures.end() - 2; it != SnakeTextures.end(); ++it)
		{
			it->setID(it->getID() + 1);
		}




		it = SnakeTextures.end() - 2;


		return it->getTexture();


	}



	void move(LTexture* apple) {


		for (auto& it : SnakeTextures) {
			renderSnakeTexture(it, getNextDirection(it.getID()), *apple);

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



		LTexture* body1 = new LTexture();
		body1->loadImageToTexture("body.png");
		body1->setID(3);

		LTexture* body2 = new LTexture();
		body2->loadImageToTexture("body.png");
		body2->setID(4);

		LTexture* body3 = new LTexture();
		body3->loadImageToTexture("body.png");
		body3->setID(5);
		LTexture* body4 = new LTexture();
		body4->loadImageToTexture("body.png");
		body4->setID(6);
	
		LTexture* body5 = new LTexture();
		body5->loadImageToTexture("body.png");
		body5->setID(7);

		LTexture* body6 = new LTexture();
		body6->loadImageToTexture("body.png");
		body6->setID(8);
	
		LTexture* head = new LTexture();
		head->loadImageToTexture("head.png");
		head->setID(9);

		LTexture* afterHeadHelp = new LTexture();
		//body3->loadImageToTexture("test.png");
		afterHeadHelp->setID(10);


	

		tail->setXPos(0);
		tail->setYPos(0);

		SnakeTextures.resize(10);


		SnakeTextures[0] = *tail;
		SnakeTextures[1] = *body;
		SnakeTextures[2] = *body1;
		SnakeTextures[3] = *body2;
		SnakeTextures[4] = *body3;
		SnakeTextures[5] = *body4;
		SnakeTextures[6] = *body5;
		SnakeTextures[7] = *body6;
		SnakeTextures[8] = *head;
		SnakeTextures[9] = *afterHeadHelp;




		int x = 0;
		for (auto& it : SnakeTextures) {
			it.render(it.getPosX() + LTexture::TextureSize * ++x, it.getPosY() + LTexture::TextureSize);
		}

		return true;
	}

};