#include "M2Element.h"
#include <assert.h>
#include <string.h>
#include <algorithm>

UInt32 M2Lib::M2Element::FileOffset = 0;

M2Lib::M2Element::M2Element()
	: Count(0)
	, Offset(0)
	, DataSize(0)
	, Data(0)
	, Align(16)
{
}

M2Lib::M2Element::~M2Element()
{
	if (Data)
	{
		delete[] Data;
	}
}

void* M2Lib::M2Element::GetLocalPointer(UInt32 GlobalOffset)
{
	assert(GlobalOffset >= Offset);
	GlobalOffset -= Offset;
	assert(GlobalOffset < (UInt32)DataSize);
	return &Data[GlobalOffset];
}

bool M2Lib::M2Element::Load(std::fstream& FileStream)
{
	if (!DataSize)
		return true;

	Data = new UInt8[DataSize];
	FileStream.seekg(Offset + FileOffset, std::ios::beg);
	FileStream.read((Char8*)Data, DataSize);

	return true;
}

bool M2Lib::M2Element::Save(std::fstream& FileStream)
{
	if (!DataSize)
		return true;

	FileStream.seekp(Offset + FileOffset);
	FileStream.write((Char8*)Data, DataSize);

	return true;
}

void M2Lib::M2Element::SetDataSize(UInt32 NewCount, UInt32 NewDataSize, bool CopyOldData)
{
	if (Align != 0)
	{
		UInt32 Mod = NewDataSize % Align;
		if (Mod)
		{
			NewDataSize += Align - Mod;
		}
	}

	if (NewDataSize <= (UInt32)DataSize)
	{
		DataSize = NewDataSize;
		Count = NewCount;
		memset(Data, 0, NewDataSize);
		return;
	}

	UInt8* NewData = new UInt8[NewDataSize];
	if (Data)
	{
		if (CopyOldData)
		{
			if (NewDataSize > DataSize)
				memset(&NewData[DataSize], 0, NewDataSize - DataSize);
			memcpy(NewData, Data, DataSize > NewDataSize ? NewDataSize : DataSize);
		}
		else
		{
			memset(NewData, 0, NewDataSize);
		}
		delete[] Data;
	}
	else
	{
		memset(NewData, 0, NewDataSize);
	}

	Data = NewData;
	DataSize = NewDataSize;
	Count = NewCount;
}

void M2Lib::M2Element::Clone(M2Element* Source, M2Element* Destination)
{
	Destination->SetDataSize(Source->Count, Source->DataSize, false);
	memcpy(Destination->Data, Source->Data, Source->DataSize);
}

void M2Lib::M2Element::SetFileOffset(UInt32 offset)
{
	FileOffset = offset;
}
