#pragma once
#include "../Included.h"

typedef struct WorldToScreenMatrix { float Matrix[4][4]; };

typedef struct Vector2D { float PositionX; float PositionY; };

typedef struct Vector3D { float PositionX; float PositionY; float PositionZ; };

//Function to calculate the distance between 2 (3D Objects)
float Get3dDistance(Vector3D FromPlayer, Vector3D ToPlayer);

//Function to calculate the distance between 2 (2D Objects)
float Get2dDistance(Vector2D FromPlayer, Vector2D ToPlayer);

//Function to detect if we need to draw a player on the screen
bool WorldToScreen(Vector3D  MainPlayer, Vector3D TargetPlayer, WorldToScreenMatrix GameMatrix);

//Function to calculate our angle from an other player (Mouse Angle)
Vector2D CalculateAngle(Vector3D MainPlayer, Vector3D Enemy);
