// Copyright 2022 Suika Studio. All Rights Reserved.
#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Math/BigInt.h"
#include "BigInteger.generated.h"

#define BIG_NUMBER_BITS 320
#define BIG_NUMBER_BITS_COUNT BIG_NUMBER_BITS/32
#define BIG_NUMBER_GAP 1000
typedef TBigInt<BIG_NUMBER_BITS, true> BigInt;

USTRUCT(BlueprintType)
struct FBigInteger
{
	static constexpr uint32 UZero32 = 0x00000000; 
	static constexpr uint32 UMax32 = 0xffffffff; 
	static constexpr int64 U32Mask = 0x00000000ffffffff;
	
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> Bits;
	
public:
	static int32 FindDecimalPointBase(const FString& In);

	FBigInteger();

	static BigInt MultiplyByDecimalStringBase(const FString& A, const BigInt& B);

	static BigInt BigIntegerPowerBigIntegerBy32Base(const BigInt& A, int32 B);

	static BigInt BigIntegerFlipBigIntegerBase(const BigInt& A);
	//Conversion
	static BigInt BigIntegerFromInt32Base(int32 A);

	static BigInt BigIntegerFromInt64Base(int64 A);

	static BigInt BigIntegerFromStringPureBase(const FString& A);

	static BigInt BigIntegerFromStringBase(const FString& A);

	static FString BigIntegerToStringDecBase(const FBigInteger& A);

	//Todo, over Z bug
	static FString BigIntegerToStringABCBase(const FBigInteger& A);
	//Serialize
	FString BigIntegerSerialize(bool bUseForCustomizeDetailPanel = false) const;
	//Deserialize
	bool Deserialize(const FString& A);

	static BigInt GetDigitMarkValueBase(const FString& A);

	static BigInt Flip(const BigInt& A);

	void BitsFromBigIntBase(const BigInt& A);

	explicit FBigInteger(const BigInt& A);

	static BigInt FromBits(const TArray<int32>& A);

	static BigInt FromBits(const FBigInteger& A);

	BigInt Content() const;
};
