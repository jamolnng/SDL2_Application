#include "BooleanBitArray.h"

BooleanBitArray::BooleanBitArray(void)
{
	bbArray = 0;
}

BooleanBitArray::~BooleanBitArray(void)
{
}

unsigned int BooleanBitArray::size() const
{
	return sizeof(unsigned _int32) * 8;
}

bool BooleanBitArray::setBit(unsigned int index, bool val)
{
	if(val)
	{
		bbArray |= val << index;
	}
	else
	{
		bbArray &= ~(1 << index);
	}
	return checkBit(index) == val;
}

#pragma warning (push)
#pragma warning (disable : 4800)
//Disabled because only two possible values are 0 and 1 i.e. true and false
bool BooleanBitArray::checkBit(unsigned int index)
{
	return bbArray & (1 << index);
}
#pragma warning (pop)

BooleanBitArray BooleanBitArray::operator=(BooleanBitArray& _bbArray)
{
	bbArray = _bbArray.bbArray;
	return *this;
}

void BooleanBitArray::clear(void)
{
	bbArray = 0;
}

bool BooleanBitArray::operator==(BooleanBitArray& _bbArray)
{
	return bbArray == _bbArray.bbArray;
}

BooleanBitArray BooleanBitArray::operator&=(BooleanBitArray& _bbArray)
{
	bbArray &= _bbArray.bbArray;
	return *this;
}

BooleanBitArray BooleanBitArray::operator&(BooleanBitArray& _bbArray)
{
	return (*this &= _bbArray);
}

BooleanBitArray BooleanBitArray::operator|=(BooleanBitArray& _bbArray)
{
	bbArray |= _bbArray.bbArray;
	return *this;
}

BooleanBitArray BooleanBitArray::operator|(BooleanBitArray& _bbArray)
{
	return (*this |= _bbArray);
}

bool BooleanBitArray::operator[](unsigned int index)
{
	return checkBit(index);
}

bool BooleanBitArray::operator!=(BooleanBitArray& _bbArray)
{
	return !this->operator==(_bbArray);
}