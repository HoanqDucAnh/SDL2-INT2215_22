class Thingy
{
	int mPosX, mPosY;

	int mVelX, mVelY;
public:
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	static const int DOT_VEL = 10;

	Thingy();

	void handleEvent(SDL_Event& e);

	void move();

	void render();

};

void Thingy::render()
{
	gDotTexture.render( mPosX, mPosY );
}

void Thingy::move()
{
    mPosX += mVelX;

    if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH))
    {
        mPosX -= mVelX;
    }

    mPosY += mVelY;

    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT))
    {
        mPosY -= mVelY;
    }
}
