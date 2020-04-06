#include <iostream>
#include <fstream>

//Level 1 tile data
const std::string LEVEL1_ROOM1_FILENAME = "Level1_Room1.bin";
const int LEVEL1_ROOM1_ROWS = 92;
const int LEVEL1_ROOM1_COLS = 21;
const unsigned char LEVEL1_ROOM1[LEVEL1_ROOM1_ROWS][LEVEL1_ROOM1_COLS] =
{
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x20, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x81, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x07, 0x07, 0x04, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x04, 0x07, 0x07, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x05, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x05, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x05, 0x11, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x05, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x07, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x07, 0x22, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x07, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x20, 0x00, 0x40, 0x00, 0x00, 0x20, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x20, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x11, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x22, 0x00, 0x00, 0x22, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x05, 0x00, 0x05, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x20, 0x40, 0x00, 0x20, 0x40, 0x20, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x00, 0x05, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x05, 0x07, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x07, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x05, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x05, 0x07, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x40, 0x20, 0x40, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x07, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0b, 0x07, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x08, 0x0b, 0x0b, 0x0b, 0x0b, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x05, 0x08, 0x08, 0x08, 0x08, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x07, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x07, 0x0b, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x07, 0x05, 0x08, 0x05, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x05, 0x40, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x07, 0x04, 0x0b, 0x04, 0x0b, 0x07, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x04, 0x08, 0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}
};

const std::string LEVEL1_ROOM2_FILENAME = "Level1_Room2.bin";
const int LEVEL1_ROOM2_ROWS = 15;
const int LEVEL1_ROOM2_COLS = 22;
const unsigned char LEVEL1_ROOM2[LEVEL1_ROOM2_ROWS][LEVEL1_ROOM2_COLS] =
{
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04},
	{0x05, 0x00, 0x00, 0x04, 0x11, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x11, 0x05, 0x81, 0x00, 0x05},
	{0x04, 0x05, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x05, 0x00, 0x05},
	{0x04, 0x05, 0x00, 0x05, 0x05, 0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x05, 0x05, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05},
	{0x04, 0x05, 0x00, 0x05, 0x04, 0x04, 0x05, 0x00, 0x00, 0x05, 0x00, 0x05, 0x05, 0x00, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x05, 0x04},
	{0x04, 0x05, 0x00, 0x05, 0x04, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05},
	{0x04, 0x05, 0x00, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x05, 0x05, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x05},
	{0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x00, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05},
	{0x05, 0x00, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x05, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x05},
	{0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x05},
	{0x04, 0x05, 0x00, 0x05, 0x05, 0x05, 0x05, 0x05, 0x00, 0x05, 0x00, 0x05, 0x00, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05},
	{0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x05, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x04},
	{0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x05, 0x05, 0x05, 0x05, 0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}
};

const std::string LEVEL1_ROOM3_FILENAME = "Level1_Room3.bin";
const int LEVEL1_ROOM3_ROWS = 46;
const int LEVEL1_ROOM3_COLS = 20;
const unsigned char LEVEL1_ROOM3[LEVEL1_ROOM3_ROWS][LEVEL1_ROOM3_COLS] =
{
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x07, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x05, 0x05, 0x05, 0x05, 0x05, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x22, 0x00, 0x00, 0x05, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x05, 0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x22, 0x00, 0x22, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x20, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x22, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0b, 0x0b, 0x05, 0x00, 0x00, 0x00, 0x00, 0x20, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x22, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x00, 0x05, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}
};

int main()
{
	std::string filename = LEVEL1_ROOM2_FILENAME;
	unsigned char rows = LEVEL1_ROOM2_ROWS;
	unsigned char cols = LEVEL1_ROOM2_COLS;

	std::ofstream output;
	std::string path = "../../../GameDev2D/Assets/Data/" + filename;
	output.open(path, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);

	if (output.is_open() == true)
	{
		//Save how many ROWS and COLUMNS are in the Room
		output.write((const char*)& rows, sizeof(rows));
		output.write((const char*)& cols, sizeof(cols));

		//Loop through and save each row of Tile data
		for (int r = rows - 1; r >= 0; r--)
		{
			//How many bytes to save
			size_t bytes = sizeof(unsigned char) * cols;

			//The tile data array to SAVE
			output.write((const char*)LEVEL1_ROOM2[r], bytes);
		}
		output.close();


		std::cout << "Saving successful\n\n";
	}
	else
	{
		std::cout << "Saving failed!\n\n";
	}

	system("pause");
	return 0;
}