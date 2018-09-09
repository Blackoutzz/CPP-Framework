#include "Game.h"

//Function to calculate the distance between 2 (3D Objects)
float Get3dDistance(Vector3D FromPlayer, Vector3D ToPlayer) {
	return(sqrtf((ToPlayer.PositionX - FromPlayer.PositionX) * (ToPlayer.PositionX - FromPlayer.PositionX) + (ToPlayer.PositionY - FromPlayer.PositionY) * (ToPlayer.PositionY - FromPlayer.PositionY) + (ToPlayer.PositionZ - FromPlayer.PositionZ) * (ToPlayer.PositionZ - FromPlayer.PositionZ)));
}

//Function to calculate the distance between 2 (2D Objects)
float Get2dDistance(Vector2D FromPlayer, Vector2D ToPlayer) {
	return(sqrtf((ToPlayer.PositionX - FromPlayer.PositionX) * (ToPlayer.PositionX - FromPlayer.PositionX) + (ToPlayer.PositionY - FromPlayer.PositionY) * (ToPlayer.PositionY - FromPlayer.PositionY)));
}

//Function to detect if we need to draw a player on the screen
bool WorldToScreen(Vector3D  MainPlayer, Vector3D TargetPlayer, WorldToScreenMatrix GameMatrix)
{
	TargetPlayer.PositionX = GameMatrix.Matrix[0][0] * MainPlayer.PositionX + GameMatrix.Matrix[0][1] * MainPlayer.PositionY + GameMatrix.Matrix[0][2] * MainPlayer.PositionZ + GameMatrix.Matrix[0][3];
	TargetPlayer.PositionY = GameMatrix.Matrix[1][0] * MainPlayer.PositionX + GameMatrix.Matrix[1][1] * MainPlayer.PositionY + GameMatrix.Matrix[1][2] * MainPlayer.PositionZ + GameMatrix.Matrix[1][3];

	float w = GameMatrix.Matrix[3][0] * MainPlayer.PositionX + GameMatrix.Matrix[3][1] * MainPlayer.PositionY + GameMatrix.Matrix[3][2] * MainPlayer.PositionZ + GameMatrix.Matrix[3][3];

	if (w < 0.01f)
		return false;

	float invw = 1.0f / w;
	TargetPlayer.PositionX *= invw;
	TargetPlayer.PositionY *= invw;
	int width = 1280;
	int height = 720;

	float X = width / 2;
	float Y = height / 2;

	X += 0.5 * TargetPlayer.PositionX * width + 0.5;
	Y -= 0.5 * TargetPlayer.PositionY * height + 0.5;

	TargetPlayer.PositionX = X;
	TargetPlayer.PositionY = Y;

	return true;
}

//Function to calculate our angle from an other player (Mouse Angle)
Vector2D CalculateAngle(Vector3D MainPlayer, Vector3D Enemy)
{
	Vector2D MainAngle;
	Vector3D Delta;

	Delta.PositionX = (MainPlayer.PositionX - Enemy.PositionX);
	Delta.PositionY = (MainPlayer.PositionY - Enemy.PositionY);
	Delta.PositionZ = (MainPlayer.PositionZ - Enemy.PositionZ);

	float Hyp = sqrt(Delta.PositionX*Delta.PositionX + Delta.PositionY * Delta.PositionY);

	MainAngle.PositionX = (float)(asinf(Delta.PositionZ / Hyp) * 57.295779513082f);
	MainAngle.PositionY = (float)(atanf(Delta.PositionY / Delta.PositionX) * 57.295779513082f);

	if (Delta.PositionX >= 0.0)
	{
		MainAngle.PositionY += 180.0f;
	}
	return MainAngle;
}
