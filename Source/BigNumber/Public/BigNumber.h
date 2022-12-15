// Copyright 2022 Suika Studio. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "BigNumberPinFactory.h"
#include "UnrealEd.h"
#include "EdGraphUtilities.h"
#include "Modules/ModuleManager.h"

class FBigNumberModule : public IModuleInterface
{
	TSharedPtr<FBigNumberPinFactory> BigNumberPinFactory;
	
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
private:
};
