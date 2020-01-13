#pragma once

#include "Modules/ModuleManager.h"

class FSpeechlyModule : public IModuleInterface
{
public:
	virtual void StartupModule() override {}
	virtual void ShutdownModule() override {}
};
