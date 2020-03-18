#pragma once

#include <GameDev2D.h>

namespace GameDev2D
{
	class Tile : public GameObject
	{
	public:
		Tile(unsigned char row, unsigned char col, bool hasCollider);
		virtual ~Tile();

		enum Type
		{
			Empty = 0x00,   // (0000 0000)
			Main = 0x04,	// (0000 0100)

			//TODO: Add more tile types here

		};

		virtual Type GetType() = 0;

		virtual void Update(double delta) override;
		virtual void Draw(SpriteBatch* spriteBatch = nullptr) override;
		virtual void Reset() override;

		unsigned char GetRow();
		unsigned char GetColumn();

	protected:
		unsigned char m_Row;
		unsigned char m_Column;
	};
}