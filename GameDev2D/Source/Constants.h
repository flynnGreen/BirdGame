#pragma once

const float TILE_SIZE = 64.0f;
const float HALF_TILE_SIZE = 32.0f;

const unsigned short TILE_COLLISION_FILTER = 0x0001;
const unsigned short PLAYER_COLLISION_FILTER = 0x0002;

const float CAMERA_SPEED = 10.0f;

const int LEVEL1_ROOM_NUM = 3;
const std::string LEVEL1_NAMES[LEVEL1_ROOM_NUM] = { "Level1_Room1", "Level1_Room2", "Level1_Room3" };