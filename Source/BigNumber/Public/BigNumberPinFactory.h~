// Copyright Suika Studio. All Rights Reserved.
#pragma once
#include "BigInteger.h"
#include "BigDecimal.h"
#include "UnrealEd.h"
#include "EdGraphUtilities.h"
#include "EdGraphSchema_K2.h"

#include "SGraphPinBigDecimal.h"
#include "SGraphPinBigInteger.h"
//Todo
#include "KismetPins/SGraphPinString.h"

class FBigNumberPinFactory : public FGraphPanelPinFactory
{
	virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override
	{
		if (InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct && InPin->PinType.PinSubCategoryObject == FBigInteger::StaticStruct())//TBaseStructure<FBigInteger>::Get()
		{
			TSharedPtr<SGraphPin> CurrentPin =  SNew(SGraphPinBigInteger, InPin);
			CurrentPin->SetPinColorModifier(FLinearColor::White);
			return CurrentPin;
		}
		else if (InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct && InPin->PinType.PinSubCategoryObject == FBigDecimal::StaticStruct())
		{
			TSharedPtr<SGraphPin> CurrentPin =  SNew(SGraphPinBigDecimal, InPin);
			CurrentPin->SetPinColorModifier(FLinearColor::White);
			return CurrentPin;
		}
		return nullptr;
	}
};