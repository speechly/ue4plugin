#pragma once

#include "Modules/ModuleManager.h"

class FSpeechgrinderModule : public IModuleInterface
{
public:
	virtual void StartupModule() override {}
	virtual void ShutdownModule() override {}
};
