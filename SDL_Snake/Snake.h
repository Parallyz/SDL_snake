#include"LTexture.h"

#include <vector>
#include <algorithm>
#undef main

class Snake {

	int lengthSnake;
	Direction currentDirection;

	std::vector<LTexture> SnakeTextures;



public:
	int getlengthSnake() {
		return lengthSnake;
	}
	Snake()
	{
		currentDirection = RIGHT;
		lengthSnake = 3;

		SnakeTextures = std::vector<LTexture>(lengthSnake);



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
		SnakeTextures.back().setTextureDirection(newDirection);
	}


	void free() {

		std::vector<LTexture>::iterator it;

		for (auto& it : SnakeTextures) {
			it.free();
		}


	}
	~Snake() { free(); }

	/*void moveHorizontal(int x, int y, bool isRight)
	{
		int z = 0;

		for (auto& it : SnakeTextures) {
			if (isRight)
				it.render(x + LTexture::TextureSize * ++z, y);
			else {
				it.render(x + LTexture::TextureSize * ++z, y, 180);

			}
		}

	}*/
	//void moveVertical( int x,int y, bool isUp)
	//{		
	//	int z = 0;
	//	if (isUp)
	//	{
	//		
	//	//	std::iter_swap(SnakeTextures.begin(), SnakeTextures.end()-1 );
	//		
	//	}
	//	
	//	for (auto& it : SnakeTextures) {
	//		if(!isUp)
	//			it.render(x ,y+ LTexture::TextureSize * (++z),90);
	//		else {
	//			it.render(x, y + LTexture::TextureSize * (++z), 270);

	//		}
	//	}
	//	
	//		for (auto& it : SnakeTextures) {
	//			if (y < getYPosDirection()) {

	//			if (!isUp)
	//				it.render(x, y + LTexture::TextureSize * (++z), 90);
	//			else {
	//				it.render(x, y + LTexture::TextureSize * (++z), 270);

	//			}
	//			}
	//		}
	//		for (auto& it : SnakeTextures) {
	//			if (currentDirection==RIGHT)
	//				it.render(x + LTexture::TextureSize * ++z, y);
	//			else {
	//				it.render(x + LTexture::TextureSize * ++z, y, 180);

	//			}
	//		}
	//	
	//	//directionTexture->render(x, y);

	//}
	void renderSnakeTexture(LTexture& texture, Direction direction,LTexture& apple)
	{
		SDL_Rect* renderQuad = new SDL_Rect();
		int angle = 0;
		switch (direction)
		{
		case LEFT: {
			angle = 180;
			renderQuad->x = texture.getPosX() - LTexture::TextureSize;
			renderQuad->y = texture.getPosY();

		}
				 break;
		case RIGHT: {

			renderQuad->x = texture.getPosX() + LTexture::TextureSize ;
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
			grow();
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

		if (renderQuad->x == apple.getPosX() &&
			renderQuad->y == apple.getPosY())
		{
			grow();
			apple.randPos();
		}

		std::cout << "Block ID: " << texture.getID() << "    X: " << texture.getPosX() << "  Y: " << texture.getPosY() << std::endl;

		SDL_RenderCopyEx(gRenderer, texture.getTexture(), NULL, renderQuad, angle, NULL, SDL_FLIP_NONE);
	}

	void grow()
	{
		LTexture* newbody = new LTexture();
		newbody->loadImageToTexture("body.png");

		newbody->setID(SnakeTextures.size());

		SnakeTextures.back().setID(SnakeTextures.size() + 1);
		SnakeTextures.reserve(SnakeTextures.size() + 1);
		lengthSnake = SnakeTextures.size() + 1;

		std::vector<LTexture>::iterator it = SnakeTextures.end() - 1;

		SnakeTextures.insert(it, *newbody);
	}

	void move(LTexture * apple) {


		for (auto &it : SnakeTextures) {
			if (getNextDirection(it.getID())==it.getTextureDirection())
			{
				renderSnakeTexture(it, it.getTextureDirection(),*apple);

			}
			else {

			renderSnakeTexture(it, getNextDirection(it.getID()),*apple);
			}

		}
	}

	bool InitSnake()
	{
		LTexture* tail = new LTexture();
		tail->loadImageToTexture("tail.png");
		tail->setID(1);



		LTexture* head = new LTexture();
		head->loadImageToTexture("head.png");
		head->setID(6);


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

		tail->setXPos(0);
		tail->setYPos(0);

		SnakeTextures.resize(6);

		SnakeTextures[0] = *tail;
		SnakeTextures[1] = *body;
		SnakeTextures[2] = *body1;
		SnakeTextures[3] = *body2;
		SnakeTextures[4] = *body3;
		SnakeTextures[5] = *head;




		int x = 0;
		for (auto& it : SnakeTextures) {
			it.render(it.getPosX() + LTexture::TextureSize * ++x, it.getPosY() + LTexture::TextureSize);
		}

		return true;
	}

};