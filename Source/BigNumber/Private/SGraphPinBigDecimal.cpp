// Copyright 2022 Suika Studio. All Rights Reserved.
#include "SGraphPinBigDecimal.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "EdGraphSchema_K2.h"
#include "ScopedTransaction.h"

void SGraphPinBigDecimal::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SGraphPinBigDecimal::GetDefaultValueWidget()
{
	return SNew(SBox)
			.MinDesiredWidth(18)
			.MaxDesiredWidth(400)
	[
		SNew(SEditableTextBox)
				.Style(FEditorStyle::Get(), "Graph.EditableTextBox")
				.Text(this, &SGraphPinBigDecimal::GetTypeInValue)
				.SelectAllTextWhenFocused(true)
				.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
				.IsReadOnly(this, &SGraphPinBigDecimal::GetDefaultValueIsReadOnly)
				.OnTextCommitted(this, &SGraphPinBigDecimal::SetTypeInValue)
				.ForegroundColor(FSlateColor::UseForeground())
	];
}

FText SGraphPinBigDecimal::GetTypeInValue() const
{
	FBigDecimal Deserialized = FBigDecimal(FBigInteger::BigIntegerFromInt32Base(0));
	const bool bIsValid = Deserialized.Deserialize(GraphPinObj->GetDefaultAsString());
	if(!bIsValid)
	{
		//return FText::FromString("*Invalid BD");
		return FText::FromString("0.0");
	}
	return FText::FromString(FBigDecimal::BigDecimalToStringABCBase(Deserialized));//Todo
}

void SGraphPinBigDecimal::SetTypeInValue(const FText& NewTypeInValue, ETextCommit::Type) const
{
	if (GraphPinObj->IsPendingKill())
	{
		return;
	}
	const FString NewTypeInValueString = NewTypeInValue.ToString();
	const FBigDecimal TempBigDecimal = FBigDecimal::BigDecimalFromStringBase(NewTypeInValueString);
	const FString Converted = TempBigDecimal.BigDecimalSerialize();
	if(!GraphPinObj->GetDefaultAsString().Equals(Converted))
	{
		const FScopedTransaction Transaction( NSLOCTEXT("GraphEditor", "ChangeBigDecimalPinValue", "Change Big Decimal Pin Value" ) );
		GraphPinObj->Modify();
		//Serialized: (Decimal = 1234, Zero = 4, Bits = (123,321,...,))   [BIG_NUMBER_BITS_COUNT] in total
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, Converted);
	}
}

bool SGraphPinBigDecimal::GetDefaultValueIsReadOnly() const
{
	return GraphPinObj->bDefaultValueIsReadOnly;
}
