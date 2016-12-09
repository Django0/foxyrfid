#ifndef UTILS_H
#define UTILS_H

#include "stdafx.h"

ref class Utils
{
public:
	static LONG WaitForI2CRead();
	static LONG WaitForI2CWrite();
	static LONG WaitForPassthroughActive();
};

#endif