#pragma once
#include "CodeMeat_Core/Deps/Math.h"
#include "CodeMeat_Core/Deps/Commons.h"
#include "CodeMeat_Core/Deps/Output.h"

class Buffer
{
private:
	virtual void Bind() = 0;
	virtual void Init() = 0;
protected:
	Buffer() {}
	virtual ~Buffer() {}
};

