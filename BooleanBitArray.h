#pragma once

class BooleanBitArray
{
	public:
		BooleanBitArray(void);
		~BooleanBitArray(void);
		BooleanBitArray operator=(BooleanBitArray&);
		bool operator==(BooleanBitArray&);
		bool operator!=(BooleanBitArray&);
		BooleanBitArray operator&=(BooleanBitArray&);
		BooleanBitArray operator&(BooleanBitArray&);
		BooleanBitArray operator|=(BooleanBitArray&);
		BooleanBitArray operator|(BooleanBitArray&);
		bool operator[](unsigned int);
		inline unsigned int size(void) const;
		bool setBit(unsigned int, bool);
		bool checkBit(unsigned int);
		void clear(void);

	protected:
		unsigned _int32 bbArray;
};