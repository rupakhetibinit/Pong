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

int main() 
{
	InitWindow(1024, 768, "Ping Pong");
	SetTargetFPS(60);
	Ball ball;
	ball.speedX = 5;
	ball.speedY = 5;
	ball.radius = 10;
//	ball.posX = GetScreenWidth() / 2;
//	ball.posY = GetScreenHeight() / 2;
	ball.posX = 0.0f;
	ball.posY = 0.0f;

	while (!WindowShouldClose())
	{	
		ball.posX +=  GetFrameTime() + ball.speedX;
		ball.posY += GetFrameTime() + ball.speedY;
		
		if (IsKeyDown(KEY_W)) {

		}
		if (IsKeyDown(KEY_S)) {

		}
		if (IsKeyDown(KEY_UP)) {

		}
		if (IsKeyDown(KEY_DOWN)) {

		}


		BeginDrawing();

			ClearBackground(BLACK);

			DrawRectangle(50, GetScreenHeight() / 2 - 50, 10, 100,WHITE);
			DrawRectangle(GetScreenWidth() - 50, GetScreenHeight()  / 2 - 50, 10, 100,WHITE);
			ball.Draw();


			DrawFPS(10,10);



		EndDrawing();
	}

	CloseWindow();

	return 0;
}