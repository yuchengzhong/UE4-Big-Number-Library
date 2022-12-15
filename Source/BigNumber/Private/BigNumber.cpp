// Copyright 2022 Suika Studio. All Rights Reserved.
#pragma once
#include "BigNumber.h"
#include "FBigIntegerCustomization.h"
#include "FBigDecimalCustomization.h"

#define LOCTEXT_NAMESPACE "FBigNumberModule"

void FBigNumberModule::StartupModule()
{
	// Register Pins
	BigNumberPinFactory = MakeShareable(new FBigNumberPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(BigNumberPinFactory);
	
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout("BigInteger", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FBigIntegerCustomization::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout("BigDecimal", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FBigDecimalCustomization::MakeInstance));
	PropertyModule.NotifyCustomizationModuleChanged();
}

void FBigNumberModule::ShutdownModule()
{
	if (BigNumberPinFactory.IsValid())
	{
		FEdGraphUtilities::UnregisterVisualPinFactory(BigNumberPinFactory);
	}
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomPropertyTypeLayout("BigInteger");
	PropertyModule.UnregisterCustomPropertyTypeLayout("BigDecimal");
	PropertyModule.NotifyCustomizationModuleChanged();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBigNumberModule, BigNumber)