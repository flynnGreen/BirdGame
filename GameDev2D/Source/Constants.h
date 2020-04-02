#pragma once
#include <GameDev2D.h>

const float TILE_SIZE = 64.0f;
const float HALF_TILE_SIZE = 32.0f;

const unsigned short TILE_COLLISION_FILTER = 0x0001;
const unsigned short PLAYER_COLLISION_FILTER = 0x0002;

const float CAMERA_SPEED = 10.0f;

const int LEVEL1_ROOM_NUM = 3;
const std::string LEVEL1_NAMES[LEVEL1_ROOM_NUM] = { "Level1_Room1", "Level1_Room2", "Level1_Room3" };

const float PLAYER_WIDTH = 34.0f;
const float PLAYER_HEIGHT = 63.0f;
const float PLAYER_HALF_WIDTH = 17.0f;
const float PLAYER_HALF_HEIGHT = 31.5f;

const float PLAYER_MAX_SPEED = 480.0f;
const float PLAYER_ACCELERATION = 2100.0f;
const float PLAYER_AIR_ACCELERATION_PCT = 0.6f;

const float PLAYER_WALK_ANIMATION_FRAMESPEED = 15.0f;
const float PLAYER_JUMP_SPEED = 420.0f;
const float PLAYER_IDLE_CUT_OFF_VELOCITY = 12.0f;

const float PLAYER_SPAWN_X[LEVEL1_ROOM_NUM] = { 288.0f, 96.0f, 448.0f };
const float PLAYER_SPAWN_Y[LEVEL1_ROOM_NUM] = { 224.0f, 798.0f, 192.0f };

const GameDev2D::Vector2 GRAVITY(0.0f, -650.0f);