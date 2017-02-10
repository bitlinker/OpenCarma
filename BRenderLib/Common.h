#pragma once

#include <stdint.h>

#include <vector>
#include <list>
#include <string>
#include <memory>

#define BR_API

class BR_API Matrix23
{
public:
    Matrix23()
    {
        mValue[0] = 1.F;
        mValue[1] = 0.F;
        mValue[2] = 0.F;
        mValue[3] = 1.F;
        mValue[4] = 0.F;
        mValue[5] = 0.F;
    }
public:
    float mValue[6];
};

class BR_API Matrix34
{
public:
    Matrix34()
    {
        for (uint32_t i = 0; i < 12; ++i)
        {
            mValue[i] = 0.F;
        }
        mValue[0] = mValue[4] = mValue[8] = 1.F; // TODO: check
    }

public:
    float mValue[12];
};

class BR_API BBox
{
public:
    BBox()
    {
        for (uint32_t i = 0; i < 3; ++i)
            mPos[i] = mSize[i] = 0.F;
    }

	bool empty() const
	{
		return mSize[0] == 0.F && mSize[1] == 0.F && mSize[2] == 0.F;
	}

public:
    float mPos[3];
    float mSize[3];
};

class BR_API Color
{
public:
    Color()
        : mValue(0)
    {
    }

    explicit Color(uint32_t rgba) // TODO: check
        : mValue(rgba)
    {
    }

public:
    uint32_t mValue;
};