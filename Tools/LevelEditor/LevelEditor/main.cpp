#include <iostream>
#include <fstream>

//Level 1 tile data
const std::string LEVEL1_ROOM1_FILENAME = "Level1_Room1.bin";
const int LEVEL1_ROOM1_ROWS = 12;
const int LEVEL1_ROOM1_COLS = 20;
const unsigned char LEVEL1_ROOM1[LEVEL1_ROOM1_ROWS][LEVEL1_ROOM1_COLS] =
{
	{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 4},
	{4, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 4},
	{4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{4, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{4, 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}
};

int main()
{
	std::string filename = LEVEL1_ROOM1_FILENAME;
	unsigned char rows = LEVEL1_ROOM1_ROWS;
	unsigned char cols = LEVEL1_ROOM1_COLS;

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
			output.write((const char*)LEVEL1_ROOM1[r], bytes);
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