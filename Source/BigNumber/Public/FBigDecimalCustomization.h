// Copyright 2022 Suika Studio. All Rights Reserved.
#pragma once
#include "PropertyEditorModule.h"
#include "BigDecimal.h"

#pragma once

class FBigDecimalCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

private:
	TSharedPtr<IPropertyHandle> DecimalPropertyHandle;
	TSharedPtr<IPropertyHandle> ZeroPropertyHandle;
	TSharedPtr<IPropertyHandle> BitsPropertyHandle;
	
	FText GetTypeInValue() const;
	//On commit
	void SetTypeInValue(const FText& NewTypeInValue, ETextCommit::Type) const;
	
	//Not using
	bool GetDefaultValueIsReadOnly() const;
	EVisibility GetDefaultValueVisibility() const;
};
