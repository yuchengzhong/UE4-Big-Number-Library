// Copyright 2022 Suika Studio. All Rights Reserved.
#include "FBigIntegerCustomization.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "BigIntegerCustomization"

TSharedRef<IPropertyTypeCustomization> FBigIntegerCustomization::MakeInstance()
{
	return MakeShareable(new FBigIntegerCustomization());
}

void FBigIntegerCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	uint32 NumChildren;
	StructPropertyHandle->GetNumChildren(NumChildren);

	for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex)
	{
		const TSharedRef< IPropertyHandle > ChildHandle = StructPropertyHandle->GetChildHandle(ChildIndex).ToSharedRef();

		if (ChildHandle->GetProperty()->GetName() == TEXT("Bits"))
		{
			BitsPropertyHandle = ChildHandle;
		}
	}
	//check(BitsPropertyHandle.IsValid());


	HeaderRow.NameContent()
	[
		StructPropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	[
		SNew(SBox)
		.MinDesiredWidth(18)
		.MaxDesiredWidth(400)
		[
			SNew(SEditableTextBox)
				.Style(FEditorStyle::Get(), "Graph.EditableTextBox")
				.Text(this, &FBigIntegerCustomization::GetTypeInValue)
				.SelectAllTextWhenFocused(true)
				.Visibility(this, &FBigIntegerCustomization::GetDefaultValueVisibility)
				.IsReadOnly(this, &FBigIntegerCustomization::GetDefaultValueIsReadOnly)
				.OnTextCommitted(this, &FBigIntegerCustomization::SetTypeInValue)
				.ForegroundColor(FSlateColor::UseForeground())
		]
	];
}

void FBigIntegerCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

FText FBigIntegerCustomization::GetTypeInValue() const
{
	if(!BitsPropertyHandle)
	{
		return FText::FromString("0");
	}
	FString Serialized;
	if(FPropertyAccess::Success != BitsPropertyHandle->GetValueAsFormattedString( Serialized ))
	{
		return FText::FromString("Unknown structure property(Big Integer - Bits)");
	}
	Serialized = "(Bits = " + Serialized + ")";
	FBigInteger CurrentBigInteger;
	CurrentBigInteger.Deserialize(Serialized);
	return FText::FromString(FBigInteger::BigIntegerToStringABCBase(CurrentBigInteger));
}

void FBigIntegerCustomization::SetTypeInValue(const FText& NewTypeInValue, ETextCommit::Type) const
{
	if(!BitsPropertyHandle)
	{
		return;
	}
	const BigInt DesiredBigInteger = FBigInteger::BigIntegerFromStringBase(NewTypeInValue.ToString());
	const FString Serialized = FBigInteger(DesiredBigInteger).BigIntegerSerialize(true);
	check(FPropertyAccess::Success == BitsPropertyHandle->SetValueFromFormattedString(Serialized))
}

bool FBigIntegerCustomization::GetDefaultValueIsReadOnly() const
{
	return false;
}

EVisibility FBigIntegerCustomization::GetDefaultValueVisibility() const
{
	return EVisibility::Visible;
}

#undef LOCTEXT_NAMESPACE
