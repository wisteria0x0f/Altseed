﻿#pragma once

#include "../ace.ReferenceObject.h"
#include "../ace.Core.Base.h"
#include "ace.File.h"

namespace ace
{
	class StaticFile : public IReference
	{
	private:
	public:
		virtual ~StaticFile() { };

#ifndef SWIG
		virtual const std::vector<uint8_t>& GetBuffer() const = 0;
#endif
		virtual const achar* GetFullPath() const = 0;

		virtual void* GetData() = 0;
		virtual int32_t GetSize() = 0;
	};
}