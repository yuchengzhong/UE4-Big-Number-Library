// Copyright 2022 Suika Studio. All Rights Reserved.
#include "SGraphPinBigInteger.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "EdGraphSchema_K2.h"
#include "ScopedTransaction.h"

void SGraphPinBigInteger::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

TSharedRef<SWidget> SGraphPinBigInteger::GetDefaultValueWidget()
{
	return SNew(SBox)
			.MinDesiredWidth(18)
			.MaxDesiredWidth(400)
	[
		SNew(SEditableTextBox)
				.Style(FEditorStyle::Get(), "Graph.EditableTextBox")
				.Text(this, &SGraphPinBigInteger::GetTypeInValue)
				.SelectAllTextWhenFocused(true)
				.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
				.IsReadOnly(this, &SGraphPinBigInteger::GetDefaultValueIsReadOnly)
				.OnTextCommitted(this, &SGraphPinBigInteger::SetTypeInValue)
				.ForegroundColor(FSlateColor::UseForeground())
	];
}

FText SGraphPinBigInteger::GetTypeInValue() const
{
	FBigInteger Deserialized = FBigInteger(FBigInteger::BigIntegerFromInt32Base(0));
	const bool bIsValid = Deserialized.Deserialize(GraphPinObj->GetDefaultAsString());
	if(!bIsValid)
	{
		//return FText::FromString("*Invalid BI");
		return FText::FromString("0");
	}
	return FText::FromString(FBigInteger::BigIntegerToStringABCBase(Deserialized));//Todo
}

void SGraphPinBigInteger::SetTypeInValue(const FText& NewTypeInValue, ETextCommit::Type) const
{
	if (GraphPinObj->IsPendingKill())
	{
		return;
	}
	const BigInt TempBigInt = FBigInteger::BigIntegerFromStringBase(NewTypeInValue.ToString());
	const FString Converted = FBigInteger(TempBigInt).BigIntegerSerialize();
	if(!GraphPinObj->GetDefaultAsString().Equals(Converted))
	{
		const FScopedTransaction Transaction( NSLOCTEXT("GraphEditor", "ChangeBigIntegerPinValue", "Change Big Integer Pin Value" ) );
		GraphPinObj->Modify();
		//Todo NewTypeInValue -> Serialized BigInt
		//Serialized: (Bits = (123,321,...,))   [BIG_NUMBER_BITS_COUNT] in total
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, Converted);
	}
}

bool SGraphPinBigInteger::GetDefaultValueIsReadOnly() const
{
	return GraphPinObj->bDefaultValueIsReadOnly;
}
