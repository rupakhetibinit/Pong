#include "raylib.h"


struct Ball {
	float posX, posY;
	float speedX, speedY;
	float radius;

	void Draw()
	{
		DrawCircle(posX, posY, radius, RED);
	}
};

struct Hitter {
	float posX, posY;

	float speed;
	void Draw()
	{
		DrawRectangle(posX,posY, 10, 100, WHITE);

	}
	Rectangle getRect() {
		return Rectangle{ posX, posY, 10, 100 };
	}
};

enum State {
	STARTED, PAUSED
};

enum Win {
	LEFT, RIGHT,NONE
};

int main() 
{
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(1024, 768, "Ping Pong");
	SetTargetFPS(60);
	State state(STARTED);
	Win win = NONE;
	Ball ball;
	ball.speedX = 5;
	ball.speedY = 5;
	ball.radius = 10;
//	ball.posX = GetScreenWidth() / 2;
//	ball.posY = GetScreenHeight() / 2;
	ball.posX = 0.0f;
	ball.posY = 0.0f;
	
	Hitter leftHitter{};
	Hitter rightHitter{};
	leftHitter.posX = 50.0f;
	leftHitter.posY = float(GetScreenHeight() / 2 - 50);
	rightHitter.posX = float(GetScreenWidth() - 50);
	rightHitter.posY = float(GetScreenHeight() / 2 - 50);
	leftHitter.speed = 10;
	rightHitter.speed = 10;

	while (!WindowShouldClose())
	{	

		ball.posX +=  GetFrameTime() + ball.speedX;
		ball.posY += GetFrameTime() + ball.speedY;
		

		if (state == STARTED) {

		if (IsKeyDown(KEY_W) && leftHitter.posY > 0) {
			leftHitter.posY -= leftHitter.speed*1.1;
		}
		if (IsKeyDown(KEY_S) && leftHitter.posY < GetScreenHeight() - 100) {
			leftHitter.posY += leftHitter.speed*1.1;
		}
		if (IsKeyDown(KEY_UP) && rightHitter.posY >0) {
			rightHitter.posY -= rightHitter.speed* 1.1;
		}
		if (IsKeyDown(KEY_DOWN) && rightHitter.posY <= GetScreenHeight() - 100) {
			rightHitter.posY += rightHitter.speed * 1.1;
		}

		if (ball.posY <= 0) {
			ball.speedY *= -1;
		}
		if (ball.posY > GetScreenHeight()) {
			ball.speedY *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.posX,ball.posY }, ball.radius, leftHitter.getRect())) {
			ball.speedX *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.posX,ball.posY }, ball.radius, rightHitter.getRect())) {
			ball.speedX *= -1;
		}
		if (ball.posX <= 0) {
			state = PAUSED;
			win = RIGHT;
		}
		if (ball.posX >= GetScreenWidth()) {
			state = PAUSED;
			win = LEFT;
		}

		}

		if (IsKeyPressed(KEY_SPACE)) {
			state = STARTED;
			win = NONE;
			leftHitter.posX = 50.0f;
			leftHitter.posY = float(GetScreenHeight() / 2 - 50);
			rightHitter.posX = float(GetScreenWidth() - 50);
			rightHitter.posY = float(GetScreenHeight() / 2 - 50);
			leftHitter.speed = 10;
			rightHitter.speed = 10;
			ball.speedX = 5;
			ball.speedY = 5;
			ball.radius = 10;
			//	ball.posX = GetScreenWidth() / 2;
			//	ball.posY = GetScreenHeight() / 2;
			ball.posX = 0.0f;
			ball.posY = 0.0f;
		}



		BeginDrawing();
			ClearBackground(BLACK);
			if (win == LEFT) {
				DrawText("Last win by Left", GetScreenWidth() / 2, GetScreenHeight() / 2 + 30, 30, DARKGREEN);
			}
			else if(win == RIGHT) {
				DrawText("Last win by Right", GetScreenWidth() / 2, GetScreenHeight() / 2 + 30, 30, DARKGREEN);
			}
			if (state == PAUSED) {
				DrawText("PRESS SPACE TO PLAY", GetScreenWidth() / 2, GetScreenHeight() / 2, 30, DARKGREEN);
			}
			else if(state == STARTED || state==NONE){

				leftHitter.Draw();
				rightHitter.Draw();
				ball.Draw();
			}

			DrawFPS(10,10);



		EndDrawing();
	}

	CloseWindow();

	return 0;
}