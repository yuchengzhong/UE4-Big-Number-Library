// Copyright 2022 Suika Studio. All Rights Reserved.
#pragma once
#include "BigDecimal.h"

#include "CoreMinimal.h"
#include "Internationalization/Text.h"
#include "SGraphPin.h"
#include "Templates/SharedPointer.h"
#include "Types/SlateEnums.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"

class SWidget;
class UEdGraphPin;

class SGraphPinBigDecimal : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SGraphPinBigDecimal) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);
	private:
	
protected:
	// SGraphPin interface
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;

	FText GetTypeInValue() const;
	//On commit
	void SetTypeInValue(const FText& NewTypeInValue, ETextCommit::Type) const;
	//Not using
	bool GetDefaultValueIsReadOnly() const;
};