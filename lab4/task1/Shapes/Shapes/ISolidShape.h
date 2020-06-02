#pragma once
#include "IShape.h"

class IShape;

class ISolidShape : public IShape
{
public:
	virtual uint32_t GetFillColor() const = 0;
};
