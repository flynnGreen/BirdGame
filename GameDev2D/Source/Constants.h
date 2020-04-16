#pragma once
#include <GameDev2D.h>

const float UI_BUFFER = 5.0f;

const float TILE_SIZE = 64.0f;
const float HALF_TILE_SIZE = 32.0f;

const unsigned short TILE_COLLISION_FILTER = 0x0001;
const unsigned short PLAYER_COLLISION_FILTER = 0x0002;
const unsigned short PLATFORM_COLLISION_FILTER = 0x0004;
const unsigned short SPIKES_COLLISION_FILTER = 0x0008;
const unsigned short ENEMY_COLLISION_FILTER = 0x0010;
const unsigned short PICKUP_COLLISION_FILTER = 0x0020;

const float CAMERA_SPEED = 10.0f;

const int LEVEL1_ROOM_NUM = 3;
const std::string LEVEL1_NAMES[LEVEL1_ROOM_NUM] = { "Level1_Room1", "Level1_Room2", "Level1_Room3" };
const std::string LEVEL1_MUSIC[LEVEL1_ROOM_NUM] = { "Room1Music", "Room2Music", "Room3Music" };

const float PLAYER_WIDTH = 34.0f;
const float PLAYER_HEIGHT = 63.0f;
const float PLAYER_HALF_WIDTH = 17.0f;
const float PLAYER_HALF_HEIGHT = 31.5f;

const float PLAYER_MAX_SPEED = 480.0f;
const float PLAYER_ACCELERATION = 2100.0f;
const float PLAYER_AIR_ACCELERATION_PCT = 0.6f;

const float PLAYER_WALK_ANIMATION_FRAMESPEED = 10.0f;
const float PLAYER_JUMP_SPEED = 420.0f;
const float PLAYER_IDLE_CUT_OFF_VELOCITY = 12.0f;

const float PLAYER_SPAWN_X[LEVEL1_ROOM_NUM] = { 288.0f, 96.0f, 448.0f };
const float PLAYER_SPAWN_Y[LEVEL1_ROOM_NUM] = { 224.0f, 798.0f, 160.0f };

const GameDev2D::Vector2 GRAVITY(0.0f, -650.0f);

//Platform consts
const int PLATFORM_NUM_SEGMENTS = 2;
const float PLATFORM_SEGMENT_WIDTH = 64.0f;
const float PLATFORM_SEGMENT_HEIGHT = 27.0f;

const int MOVING_PLATFORM_NUM = 3;
const int STILL_PLATFORM_NUM = 2;

const GameDev2D::Vector2 PLATFORM1_START_POS(786.0f, 5568.0f);
const GameDev2D::Vector2 PLATFORM1_DISPLACEMENT(-120.0f, 0.0f);

const GameDev2D::Vector2 PLATFORM2_START_POS(448.0f, 448.0f);
const GameDev2D::Vector2 PLATFORM2_DISPLACEMENT(80.0f, 80.0f);

const GameDev2D::Vector2 PLATFORM3_START_POS(576.0f, 800.0f);
const GameDev2D::Vector2 PLATFORM3_DISPLACEMENT(120.0f, 0.0f);

const GameDev2D::Vector2 STILL_PLATFORM1_START_POS(320.0f, 2610.5f);
const GameDev2D::Vector2 STILL_PLATFORM2_START_POS(320.0f, 1984.0f);

const GameDev2D::Vector2 PLATFORM_START_POSITION[MOVING_PLATFORM_NUM] = { PLATFORM1_START_POS, PLATFORM2_START_POS, PLATFORM3_START_POS };
const GameDev2D::Vector2 PLATFORM_DISPLACEMENT[MOVING_PLATFORM_NUM] = { PLATFORM1_DISPLACEMENT, PLATFORM2_DISPLACEMENT, PLATFORM3_DISPLACEMENT };
const double PLATFORM_DURATION[MOVING_PLATFORM_NUM] = { 3.5, 3.0, 3.5 };

const GameDev2D::Vector2 STILL_PLATFORM_START_POSITION[STILL_PLATFORM_NUM] = { STILL_PLATFORM1_START_POS, STILL_PLATFORM2_START_POS };

//Spikes
const float SPIKES_WIDTH = 64.0f;
const float SPIKES_HEIGHT = 25.0f;

const GameDev2D::Vector2 SPIKES_START_POS(864.0f, 480.0f);
const GameDev2D::Vector2 SPIKES_DISPLACEMENT(0.0f, 352.0f);
const double SPIKES_DURATION = 5.0;

//Sexy Fish consts
const float SEXY_SPEED = 50.0;
const double SEXY_COLLISION_IGNORE_DURATION = 1.0;

const GameDev2D::Vector2 SEXY1_START_POS(576.0f, 4704.0f);
const float SEXY1_DISPLACEMENT_X = 96.0f;

const GameDev2D::Vector2 SEXY2_START_POS(608.0f, 3424.0f);
const float SEXY2_DISPLACEMENT_X = 90.0f;

const GameDev2D::Vector2 SEXY3_START_POS(384.0f, 288.0f);
const float SEXY3_DISPLACEMENT_X = 90.0f;

//Phantom consts
const float EYE_SPEED = 60.0;

const GameDev2D::Vector2 EYE_START_POS(1120.0f, 448.0f);
const float EYE_DISPLACEMENT_Y = 200.0f;

//NPC consts
const float NPC_SPEED = 50.0;
const double NPC_COLLISION_IGNORE_DURATION = 1.0;

const GameDev2D::Vector2 NPC1_START_POS(576.0f, 4704.0f);
const float NPC1_DISPLACEMENT_X = 96.0f;

//Item box consts
//1 = seed, 2 = millet, 3 = egg
const double ITEM_BOX_SCALE_TIMER = 0.25;

const int ROOM_1_ITEM_BOX_NUM = 6;

const unsigned char ROOM_1_ITEM_BOX_1_ROW = 20;
const unsigned char ROOM_1_ITEM_BOX_1_COLUMN = 11;
const unsigned int ROOM_1_ITEM_BOX_1_ITEM = 2;

const unsigned char ROOM_1_ITEM_BOX_2_ROW = 33;
const unsigned char ROOM_1_ITEM_BOX_2_COLUMN = 5;
const unsigned int ROOM_1_ITEM_BOX_2_ITEM = 2;

const unsigned char ROOM_1_ITEM_BOX_3_ROW = 43;
const unsigned char ROOM_1_ITEM_BOX_3_COLUMN = 18;
const unsigned int ROOM_1_ITEM_BOX_3_ITEM = 1;

const unsigned char ROOM_1_ITEM_BOX_4_ROW = 63;
const unsigned char ROOM_1_ITEM_BOX_4_COLUMN = 8;
const unsigned int ROOM_1_ITEM_BOX_4_ITEM = 1;

const unsigned char ROOM_1_ITEM_BOX_5_ROW = 75;
const unsigned char ROOM_1_ITEM_BOX_5_COLUMN = 8;
const unsigned int ROOM_1_ITEM_BOX_5_ITEM = 1;

const unsigned char ROOM_1_ITEM_BOX_6_ROW = 77;
const unsigned char ROOM_1_ITEM_BOX_6_COLUMN = 2;
const unsigned int ROOM_1_ITEM_BOX_6_ITEM = 1;

const unsigned char ROOM_1_ITEM_BOX_ROWS[ROOM_1_ITEM_BOX_NUM] = { ROOM_1_ITEM_BOX_1_ROW,
																  ROOM_1_ITEM_BOX_2_ROW,
																  ROOM_1_ITEM_BOX_3_ROW,
																  ROOM_1_ITEM_BOX_4_ROW,
																  ROOM_1_ITEM_BOX_5_ROW,
																  ROOM_1_ITEM_BOX_6_ROW };

const unsigned char ROOM_1_ITEM_BOX_COLUMNS[ROOM_1_ITEM_BOX_NUM] = { ROOM_1_ITEM_BOX_1_COLUMN,
																	 ROOM_1_ITEM_BOX_2_COLUMN,
																	 ROOM_1_ITEM_BOX_3_COLUMN,
																	 ROOM_1_ITEM_BOX_4_COLUMN,
																	 ROOM_1_ITEM_BOX_5_COLUMN,
																	 ROOM_1_ITEM_BOX_6_COLUMN };

const float ROOM_1_ITEM_BOX_POSITION_X[ROOM_1_ITEM_BOX_NUM] = { ROOM_1_ITEM_BOX_1_COLUMN * TILE_SIZE + HALF_TILE_SIZE,
																ROOM_1_ITEM_BOX_2_COLUMN * TILE_SIZE + HALF_TILE_SIZE,
																ROOM_1_ITEM_BOX_3_COLUMN * TILE_SIZE + HALF_TILE_SIZE,
																ROOM_1_ITEM_BOX_4_COLUMN * TILE_SIZE + HALF_TILE_SIZE,
																ROOM_1_ITEM_BOX_5_COLUMN * TILE_SIZE + HALF_TILE_SIZE,
																ROOM_1_ITEM_BOX_6_COLUMN * TILE_SIZE + HALF_TILE_SIZE };

const float ROOM_1_ITEM_BOX_POSITION_Y[ROOM_1_ITEM_BOX_NUM] = { ROOM_1_ITEM_BOX_1_ROW * TILE_SIZE + HALF_TILE_SIZE,
																ROOM_1_ITEM_BOX_2_ROW * TILE_SIZE + HALF_TILE_SIZE,
																ROOM_1_ITEM_BOX_3_ROW * TILE_SIZE + HALF_TILE_SIZE,
																ROOM_1_ITEM_BOX_4_ROW * TILE_SIZE + HALF_TILE_SIZE,
																ROOM_1_ITEM_BOX_5_ROW * TILE_SIZE + HALF_TILE_SIZE,
																ROOM_1_ITEM_BOX_6_ROW * TILE_SIZE + HALF_TILE_SIZE };

const int ROOM_1_ITEM_BOX_ITEMS[ROOM_1_ITEM_BOX_NUM] = { ROOM_1_ITEM_BOX_1_ITEM,
														 ROOM_1_ITEM_BOX_2_ITEM,
														 ROOM_1_ITEM_BOX_3_ITEM,
														 ROOM_1_ITEM_BOX_4_ITEM,
														 ROOM_1_ITEM_BOX_5_ITEM,
														 ROOM_1_ITEM_BOX_6_ITEM };

const int ROOM_2_ITEM_BOX_NUM = 2;

const unsigned char ROOM_2_ITEM_BOX_1_ROW = 12;
const unsigned char ROOM_2_ITEM_BOX_1_COLUMN = 7;
const unsigned int ROOM_2_ITEM_BOX_1_ITEM = 2;

const unsigned char ROOM_2_ITEM_BOX_2_ROW = 12;
const unsigned char ROOM_2_ITEM_BOX_2_COLUMN = 18;
const unsigned int ROOM_2_ITEM_BOX_2_ITEM = 3;

const unsigned char ROOM_2_ITEM_BOX_ROWS[ROOM_2_ITEM_BOX_NUM] = { ROOM_2_ITEM_BOX_1_ROW,
																  ROOM_2_ITEM_BOX_2_ROW };

const unsigned char ROOM_2_ITEM_BOX_COLUMNS[ROOM_2_ITEM_BOX_NUM] = { ROOM_2_ITEM_BOX_1_COLUMN,
																	 ROOM_2_ITEM_BOX_2_COLUMN };

const float ROOM_2_ITEM_BOX_POSITION_X[ROOM_2_ITEM_BOX_NUM] = { ROOM_2_ITEM_BOX_1_COLUMN * TILE_SIZE + HALF_TILE_SIZE,
																ROOM_2_ITEM_BOX_2_COLUMN * TILE_SIZE + HALF_TILE_SIZE };

const float ROOM_2_ITEM_BOX_POSITION_Y[ROOM_2_ITEM_BOX_NUM] = { ROOM_2_ITEM_BOX_1_ROW * TILE_SIZE + HALF_TILE_SIZE,
																ROOM_2_ITEM_BOX_2_ROW * TILE_SIZE + HALF_TILE_SIZE };

const int ROOM_2_ITEM_BOX_ITEMS[ROOM_2_ITEM_BOX_NUM] = { ROOM_2_ITEM_BOX_1_ITEM,
														 ROOM_2_ITEM_BOX_2_ITEM };

const int ROOM_3_ITEM_BOX_NUM = 1;

const unsigned char ROOM_3_ITEM_BOX_1_ROW = 39;
const unsigned char ROOM_3_ITEM_BOX_1_COLUMN = 13;
const unsigned int ROOM_3_ITEM_BOX_1_ITEM = 4;

const unsigned char ROOM_3_ITEM_BOX_ROWS[ROOM_3_ITEM_BOX_NUM] = { ROOM_3_ITEM_BOX_1_ROW };

const unsigned char ROOM_3_ITEM_BOX_COLUMNS[ROOM_3_ITEM_BOX_NUM] = { ROOM_3_ITEM_BOX_1_COLUMN };

const float ROOM_3_ITEM_BOX_POSITION_X[ROOM_3_ITEM_BOX_NUM] = { ROOM_3_ITEM_BOX_1_COLUMN * TILE_SIZE + HALF_TILE_SIZE };

const float ROOM_3_ITEM_BOX_POSITION_Y[ROOM_3_ITEM_BOX_NUM] = { ROOM_3_ITEM_BOX_1_ROW * TILE_SIZE + HALF_TILE_SIZE };

const int ROOM_3_ITEM_BOX_ITEMS[ROOM_3_ITEM_BOX_NUM] = { ROOM_3_ITEM_BOX_1_ITEM };