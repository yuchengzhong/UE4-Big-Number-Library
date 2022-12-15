// Copyright 2022 Suika Studio. All Rights Reserved.
#include "FBigDecimalCustomization.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "BigDecimalCustomization"

TSharedRef<IPropertyTypeCustomization> FBigDecimalCustomization::MakeInstance()
{
	return MakeShareable(new FBigDecimalCustomization());
}

void FBigDecimalCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
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
		else if(ChildHandle->GetProperty()->GetName() == TEXT("Decimal"))
		{
			DecimalPropertyHandle = ChildHandle;
		}
		else if(ChildHandle->GetProperty()->GetName() == TEXT("Zero"))
		{
			ZeroPropertyHandle = ChildHandle;
		}
	}
	//check(BitsPropertyHandle.IsValid());
	//check(DecimalPropertyHandle.IsValid());
	//check(ZeroPropertyHandle.IsValid());
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
				.Text(this, &FBigDecimalCustomization::GetTypeInValue)
				.SelectAllTextWhenFocused(true)
				.Visibility(this, &FBigDecimalCustomization::GetDefaultValueVisibility)
				.IsReadOnly(this, &FBigDecimalCustomization::GetDefaultValueIsReadOnly)
				.OnTextCommitted(this, &FBigDecimalCustomization::SetTypeInValue)
				.ForegroundColor(FSlateColor::UseForeground())
		]
	];
}

void FBigDecimalCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

FText FBigDecimalCustomization::GetTypeInValue() const
{
	if(!DecimalPropertyHandle || !ZeroPropertyHandle || !BitsPropertyHandle)
	{
		return FText::FromString("0");
	}
	FString BitsSerialized;
	if(FPropertyAccess::Success != BitsPropertyHandle->GetValueAsFormattedString( BitsSerialized ))
	{
		return FText::FromString("Unknown structure property(Big Decimal - Bits)");
	}
	BitsSerialized = "Bits = " + BitsSerialized;
	//
	FString DecimalSerialized;
	if(FPropertyAccess::Success != DecimalPropertyHandle->GetValueAsFormattedString( DecimalSerialized ))
	{
		return FText::FromString("Unknown structure property(Big Decimal - Decimal)");
	}
	DecimalSerialized = "Decimal = " + DecimalSerialized;
	//
	FString ZeroSerialized;
	if(FPropertyAccess::Success != ZeroPropertyHandle->GetValueAsFormattedString( ZeroSerialized ))
	{
		return FText::FromString("Unknown structure property(Big Decimal - Zero)");
	}
	ZeroSerialized = "Zero = " + ZeroSerialized;
	//
	FBigDecimal CurrentBigDecimal;
	CurrentBigDecimal.Deserialize("(" + DecimalSerialized + ","+ ZeroSerialized + ","+  BitsSerialized + ")");
	return FText::FromString(FBigDecimal::BigDecimalToStringABCBase(CurrentBigDecimal));
}

void FBigDecimalCustomization::SetTypeInValue(const FText& NewTypeInValue, ETextCommit::Type) const
{
	if(!DecimalPropertyHandle || !ZeroPropertyHandle || !BitsPropertyHandle)
	{
		return;
	}
	const FBigDecimal DesiredBigDecimal = FBigDecimal::BigDecimalFromStringBase(NewTypeInValue.ToString());
	FString SerializedDecimal, SerializedZero, SerializedBits;
	DesiredBigDecimal.BigDecimalSerializeComponent(SerializedDecimal, SerializedZero, SerializedBits);
	check(FPropertyAccess::Success == DecimalPropertyHandle->SetValueFromFormattedString(SerializedDecimal))
	check(FPropertyAccess::Success == ZeroPropertyHandle->SetValueFromFormattedString(SerializedZero))
	check(FPropertyAccess::Success == BitsPropertyHandle->SetValueFromFormattedString(SerializedBits))
}

bool FBigDecimalCustomization::GetDefaultValueIsReadOnly() const
{
	return false;
}

EVisibility FBigDecimalCustomization::GetDefaultValueVisibility() const
{
	return EVisibility::Visible;
}

#undef LOCTEXT_NAMESPACE
