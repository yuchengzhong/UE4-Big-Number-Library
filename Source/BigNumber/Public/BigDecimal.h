// Copyright 2022 Suika Studio. All Rights Reserved.
#pragma once
#include "BigInteger.h"
#include "BigDecimal.generated.h"

USTRUCT(BlueprintType)
struct FBigDecimal
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Decimal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Zero;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> Bits;


#define BIG_NUMBER_MAX_DIGIT 9
public:
	static uint8 ZeroCount(const FString& S);

	FString PaddingZero() const;

	FBigDecimal();

	void BitsFromBigIntBase(const BigInt& A);

	explicit FBigDecimal(const BigInt& A, const uint32& B, const uint8& C);
	
	explicit FBigDecimal(const uint32& B, const uint8& C);

	explicit FBigDecimal(const BigInt& A);

	explicit FBigDecimal(const BigInt& A, const int32& B, const uint8& C);

	explicit FBigDecimal(const BigInt& A, const float& B);

	explicit FBigDecimal(const BigInt& A, const double& B);
	
	explicit FBigDecimal(const double& A);

	double ToDoubleBase() const;
	static int32 NormalizeDecimal(int32 A);

	void NormalizeDecimalAndZero();

	BigInt Content() const;

	static FBigDecimal CorrectSign(const FBigDecimal& A);

	void CorrectSign();

	static FBigDecimal BigDecimalFlipBigDecimalBase(FBigDecimal A);

	//Conversion
	static FBigDecimal BigDecimalFromStringPureBase(FString A);

	static FBigDecimal BigDecimalFromStringBase(FString A);

	static FString BigDecimalToStringDecBase(const FBigDecimal& A);

	static FString BigDecimalToStringABCBase(const FBigDecimal& A);
	//Serialize
	FString BigDecimalSerialize() const;

	void BigDecimalSerializeComponent(FString& DecimalString, FString& ZeroString, FString& BitsString) const;
	
	bool Deserialize(const FString& A);
};
