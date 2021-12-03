#include"LTexture.h"

#include <vector>
#include <algorithm>
#undef main
enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};
class Snake {
	int xPosDirection;
	int yPosDirection;
	int lengthSnake;
	Direction currentDirection;
	Direction previousDirection;
	std::vector<LTexture> SnakeTextures;
	LTexture* directionTexture;


public:
	int getlengthSnake() {
		return lengthSnake;
	}
	Snake()
	{
		lengthSnake = 3;
		directionTexture = NULL;
		SnakeTextures = std::vector<LTexture>(lengthSnake);
		currentDirection = Direction::RIGHT;
		previousDirection = Direction::RIGHT;
		xPosDirection = 0;
		yPosDirection = 0;
	}

	Direction getCurrentDirection()
	{
		return currentDirection;
	}
	Direction getPreviousDirection()
	{
		return previousDirection;
	}
	void ChangeDirection(Direction newDirection)
	{
		xPosDirection = SnakeTextures.front().getPosX();
		yPosDirection = SnakeTextures.front().getPosY();
		previousDirection = currentDirection;
		currentDirection = newDirection;

		
	}
	bool ifDirectionChanged() {
		return previousDirection == currentDirection;
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

		std::vector<LTexture>::iterator it;

		for (auto& it : SnakeTextures) {
			it.free();
		}
		directionTexture->free();

	}
	~Snake() { free(); }

	void moveHorizontal(int x,int y, bool isRight)
	{
		int z = 0;
		
		for (auto& it : SnakeTextures) {	
			if(isRight)
				it.render(x + LTexture::TextureSize * ++z , y );		
			else{
				it.render(x + LTexture::TextureSize * ++z, y,180);

			}
		}

	}
	void moveVertical( int x,int y, bool isUp)
	{		
		int z = 0;
		if (isUp)
		{
			
		//	std::iter_swap(SnakeTextures.begin(), SnakeTextures.end()-1 );
			
		}
		if(!ifDirectionChanged())
		for (auto& it : SnakeTextures) {
			if(!isUp)
				it.render(x ,y+ LTexture::TextureSize * (++z),90);
			else {
				it.render(x, y + LTexture::TextureSize * (++z), 270);

			}
		}
		else {
			for (auto& it : SnakeTextures) {
				if (y < getYPosDirection()) {

				if (!isUp)
					it.render(x, y + LTexture::TextureSize * (++z), 90);
				else {
					it.render(x, y + LTexture::TextureSize * (++z), 270);

				}
				}
			}
			for (auto& it : SnakeTextures) {
				if (currentDirection==RIGHT)
					it.render(x + LTexture::TextureSize * ++z, y);
				else {
					it.render(x + LTexture::TextureSize * ++z, y, 180);

				}
			}
		}
		//directionTexture->render(x, y);

	}


	bool InitSnake()
	{
		LTexture* tail = new LTexture();
		tail->loadImageToTexture("tail.png");
		tail->setID(2);

		LTexture* head = new LTexture();
		head->loadImageToTexture("head.png");
		head->setID(0);


		LTexture* body = new LTexture();
		body->loadImageToTexture("body.png");
		body->setID(1);

		directionTexture = new LTexture();
		directionTexture->loadImageToTexture("L.png");

		SnakeTextures[0] = *tail;
		SnakeTextures[1] = *body;
		SnakeTextures[2] = *head;

		

		/*int x = 0;
		for (auto& it : SnakeTextures) {
			it.render(it.getPosX() + LTexture::TextureSize * ++x, it.getPosY() + LTexture::TextureSize);
		}*/

		return true;
	}

};