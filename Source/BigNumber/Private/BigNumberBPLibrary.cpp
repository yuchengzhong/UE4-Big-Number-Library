// Copyright 2022 Suika Studio. All Rights Reserved.
#include "BigNumberBPLibrary.h"
#include <cmath>
UBigNumberBPLibrary::UBigNumberBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

int32 UBigNumberBPLibrary::NumDigitOfInt32(int32 A)
{
	if (A == INT32_MIN) return 10 + 1;
	if (A < 0) return NumDigitOfInt32(-A);
	if (A >= 10000) {
		if (A >= 10000000) {
			if (A >= 100000000) {
				if (A >= 1000000000)
					return 10;
				return 9;
			}
			return 8;
		}
		if (A >= 100000) {
			if (A >= 1000000)
				return 7;
			return 6;
		}
		return 5;
	}
	if (A >= 100) {
		if (A >= 1000)
			return 4;
		return 3;
	}
	if (A >= 10)
		return 2;
	return 1;
}

int32 UBigNumberBPLibrary::NumDigitOfInt64(int64 A)
{
	if (A == INT64_MIN) return 19 + 1;
	if (A < 0) return NumDigitOfInt64(-A);

	if (A >= 10000000000) {
		if (A >= 100000000000000) {
			if (A >= 10000000000000000) {
				if (A >= 100000000000000000) {
					if (A >= 1000000000000000000)
						return 19;
					return 18;
				}
				return 17;
			}
			if (A >= 1000000000000000)
				return 16;
			return 15;
		} 
		if (A >= 1000000000000) {
			if (A >= 10000000000000)
				return 14;
			return 13;
		}
		if (A >= 100000000000)
			return 12;
		return 11;
	}
	if (A >= 100000) {
		if (A >= 10000000) {
			if (A >= 100000000) {
				if (A >= 1000000000)
					return 10;
				return 9;
			}
			return 8;
		}
		if (A >= 1000000)
			return 7;
		return 6;
	}
	if (A >= 100) {
		if (A >= 1000) {
			if (A >= 10000)
				return 5;
			return 4;
		}
		return 3;
	}
	if (A >= 10)
		return 2;
	return 1;
}


FBigInteger UBigNumberBPLibrary::BigIntegerFromInt32(int32 A)
{
	return FBigInteger(FBigInteger::BigIntegerFromInt32Base(A));
}

FBigInteger UBigNumberBPLibrary::BigIntegerFromInt64(int64 A)
{
	return FBigInteger(FBigInteger::BigIntegerFromInt64Base(A));
}

FBigInteger UBigNumberBPLibrary::BigIntegerFromStringPure(FString A)//Todo: move to FBigInteger
{
	return FBigInteger(FBigInteger::BigIntegerFromStringPureBase(A));
}

FBigInteger UBigNumberBPLibrary::BigIntegerFromString(FString A)//Todo: move to FBigInteger
{
	return FBigInteger(FBigInteger::BigIntegerFromStringBase(A));
}

FBigInteger UBigNumberBPLibrary::BigIntegerFromSingleString(FString A)
{
	return FBigInteger(FBigInteger::GetDigitMarkValueBase(A));
}

int32 UBigNumberBPLibrary::BigIntegerToInt32(FBigInteger A)
{
	return static_cast<int32>(A.Content().ToInt());
}

int64 UBigNumberBPLibrary::BigIntegerToInt64(FBigInteger A)
{
	return A.Content().ToInt();
}

FString UBigNumberBPLibrary::BigIntegerToStringHex(FBigInteger A)
{
	FString Text(TEXT("0x"));
	constexpr int32 Loop = BIG_NUMBER_BITS / 32;
	const uint32* Bits = A.Content().GetBits();
	for(int32 i = 0; i < Loop; i++)
	{
		Text += FString::Printf(TEXT("%08x"), Bits[Loop - i - 1]);
	}
	return Text;
}

FString UBigNumberBPLibrary::BigIntegerToStringDec(FBigInteger A)
{
	return FBigInteger::BigIntegerToStringDecBase(A);
}

FString UBigNumberBPLibrary::BigIntegerToStringABC(FBigInteger A)
{
	return FBigInteger::BigIntegerToStringABCBase(A);
}

FString UBigNumberBPLibrary::BigIntegerToStringFA(FBigInteger A, int Digit)
{
	//Todo
	return A.Content().ToString();
}

FBigInteger UBigNumberBPLibrary::BigIntegerAddBigInteger(FBigInteger A, FBigInteger B)
{
	return FBigInteger(A.Content() + B.Content());
}

FBigInteger UBigNumberBPLibrary::BigIntegerSubtractBigInteger(FBigInteger A, FBigInteger B)
{
	return FBigInteger(A.Content() - B.Content());
}

FBigInteger UBigNumberBPLibrary::BigIntegerMultiplyBigInteger(FBigInteger A, FBigInteger B)
{
	return FBigInteger(A.Content() * B.Content());
}

FBigInteger UBigNumberBPLibrary::BigIntegerDivideBigInteger(FBigInteger A, FBigInteger B)
{
	return FBigInteger(A.Content() / B.Content());
}
//Compare
bool UBigNumberBPLibrary::BigIntegerEqualBigInteger(FBigInteger A, FBigInteger B)
{
	return A.Content().IsEqual(B.Content());
}

bool UBigNumberBPLibrary::BigIntegerNotEqualBigInteger(FBigInteger A, FBigInteger B)
{
	return !A.Content().IsEqual(B.Content());
}

bool UBigNumberBPLibrary::BigIntegerLargerBigInteger(FBigInteger A, FBigInteger B)
{
	//IsGreater only works when positive(bug? maybe
	if(A.Content().IsNegative())
	{
		if(B.Content().IsNegative())
		{
			return FBigInteger::BigIntegerFlipBigIntegerBase(A.Content()).IsLess(FBigInteger::BigIntegerFlipBigIntegerBase(B.Content()));
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(B.Content().IsNegative())
		{
			return true;
		}
		else
		{
			return A.Content().IsGreater(B.Content());
		}
	}
}

bool UBigNumberBPLibrary::BigIntegerLargerOrEqualBigInteger(FBigInteger A, FBigInteger B)
{
	//IsGreaterOrEqual only works when positive(bug? maybe
	if(A.Content().IsNegative())
	{
		if(B.Content().IsNegative())
		{
			return FBigInteger::BigIntegerFlipBigIntegerBase(A.Content()).IsLessOrEqual(FBigInteger::BigIntegerFlipBigIntegerBase(B.Content()));
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(B.Content().IsNegative())
		{
			return true;
		}
		else
		{
			return A.Content().IsGreaterOrEqual(B.Content());
		}
	}
}

bool UBigNumberBPLibrary::BigIntegerLessBigInteger(FBigInteger A, FBigInteger B)
{
	if(A.Content().IsNegative())
	{
		if(B.Content().IsNegative())
		{
			return FBigInteger::BigIntegerFlipBigIntegerBase(A.Content()).IsGreater(FBigInteger::BigIntegerFlipBigIntegerBase(B.Content()));
		}
		else
		{
			return true;
		}
	}
	else
	{
		if(B.Content().IsNegative())
		{
			return false;
		}
		else
		{
			return A.Content().IsLess(B.Content());
		}
	}
}

bool UBigNumberBPLibrary::BigIntegerLessOrEqualBigInteger(FBigInteger A, FBigInteger B)
{
	if(A.Content().IsNegative())
	{
		if(B.Content().IsNegative())
		{
			return FBigInteger::BigIntegerFlipBigIntegerBase(A.Content()).IsGreaterOrEqual(FBigInteger::BigIntegerFlipBigIntegerBase(B.Content()));
		}
		else
		{
			return true;
		}
	}
	else
	{
		if(B.Content().IsNegative())
		{
			return false;
		}
		else
		{
			return A.Content().IsLessOrEqual(B.Content());
		}
	}
}

FBigInteger UBigNumberBPLibrary::BigIntegerFlipBigInteger(FBigInteger A)
{
	return FBigInteger(FBigInteger::BigIntegerFlipBigIntegerBase(A.Content()));
}

bool UBigNumberBPLibrary::bBigIntegerIsNegativeBigInteger(FBigInteger A)
{
	return A.Content().IsNegative();
}

FBigInteger UBigNumberBPLibrary::BigIntegerAbsBigInteger(FBigInteger A)
{
	return A.Content().IsNegative() ? BigIntegerFlipBigInteger(A) : A;
}

FBigInteger UBigNumberBPLibrary::BigIntegerPowerBigInteger(FBigInteger A, FBigInteger B)
{
	BigInt N = B.Content();
	if(N< 0 || A.Content().IsNegative())
	{
		return FBigInteger(FBigInteger::BigIntegerFromInt32Base(0));
	}
	BigInt Result = 1;
	BigInt Mul = A.Content();
	while(N.IsGreaterThanZero())
	{
		if((N&1).IsGreaterThanZero())
		{
			Result *= Mul;
		}
		Mul = Mul * Mul;
		N >>= 1;
	}
	return FBigInteger(Result);
}
FBigInteger UBigNumberBPLibrary::BigIntegerPowerBigIntegerBy32(FBigInteger A, int32 B)
{
	return FBigInteger(FBigInteger::BigIntegerPowerBigIntegerBy32Base(A.Content(),B));
}

FBigInteger UBigNumberBPLibrary::BigIntegerAddBigIntegerBy64(FBigInteger A, int64 B)
{
	return FBigInteger(A.Content() + BigIntegerFromInt64(B).Content());
}

FBigInteger UBigNumberBPLibrary::BigIntegerSubtractBigIntegerBy64(FBigInteger A, int64 B)
{
	return FBigInteger(A.Content() - BigIntegerFromInt64(B).Content());
}

FBigInteger UBigNumberBPLibrary::BigIntegerMultiplyBigIntegerBy64(FBigInteger A, int64 B)
{
	return FBigInteger(A.Content() * BigIntegerFromInt64(B).Content());
}

FBigInteger UBigNumberBPLibrary::BigIntegerDivideBigIntegerBy64(FBigInteger A, int64 B)
{
	return FBigInteger(A.Content() / BigIntegerFromInt64(B).Content());
}

FBigInteger UBigNumberBPLibrary::BigIntegerAddBigIntegerBy32(FBigInteger A, int32 B)
{
	return FBigInteger(A.Content() + FBigInteger::BigIntegerFromInt32Base(B));
}

FBigInteger UBigNumberBPLibrary::BigIntegerSubtractBigIntegerBy32(FBigInteger A, int32 B)
{
	return FBigInteger(A.Content() - FBigInteger::BigIntegerFromInt32Base(B));
}

FBigInteger UBigNumberBPLibrary::BigIntegerMultiplyBigIntegerBy32(FBigInteger A, int32 B)
{
	return FBigInteger(A.Content() * FBigInteger::BigIntegerFromInt32Base(B));
}

FBigInteger UBigNumberBPLibrary::BigIntegerDivideBigIntegerBy32(FBigInteger A, int32 B)
{
	return FBigInteger(A.Content() / FBigInteger::BigIntegerFromInt32Base(B));
}

//Decimal
FBigDecimal UBigNumberBPLibrary::BigDecimalFromInt32(int32 A)
{
	return FBigDecimal(FBigInteger::BigIntegerFromInt32Base(A));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalFromInt64(int64 A)
{
	return FBigDecimal(FBigInteger::BigIntegerFromInt64Base(A));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalFromBigInteger(FBigInteger A)
{
	return FBigDecimal(A.Content());
}

FBigDecimal UBigNumberBPLibrary::BigDecimalFromFloat(float A)
{
	const FString String = FString::SanitizeFloat(A);
	return BigDecimalFromStringPure(String);
}

FBigDecimal UBigNumberBPLibrary::BigDecimalFromStringPure(FString A)
{
	return FBigDecimal::BigDecimalFromStringPureBase(A);
}

FBigDecimal UBigNumberBPLibrary::BigDecimalFromString(FString A)
{
	return FBigDecimal::BigDecimalFromStringBase(A);
}

int32 UBigNumberBPLibrary::BigDecimalToInt32(FBigDecimal A)
{
	return BigIntegerToInt32(FBigInteger(A.Content()));
}

int64 UBigNumberBPLibrary::BigDecimalToInt64(FBigDecimal A)
{
	return BigIntegerToInt64(FBigInteger(A.Content()));
}

float UBigNumberBPLibrary::BigDecimalToFloat(FBigDecimal A)
{
	//Todo:Optimize
	const bool bIsNegative = bBigDecimalIsNegativeBigDecimal(A);
	A = bIsNegative ? BigDecimalFlipBigDecimal(A) : A;
	const double DecimalPart = static_cast<double>(A.Decimal)/static_cast<double>(Digits[A.Zero + NumDigitOfInt32(A.Decimal)]);
	const double Result = static_cast<double>(A.Content().ToInt()) + DecimalPart;
	return bIsNegative ? -static_cast<float>(Result) : static_cast<float>(Result);
}

FBigInteger UBigNumberBPLibrary::BigDecimalToBigInteger(FBigDecimal A)
{
	return FBigInteger(A.Content());
}

FString UBigNumberBPLibrary::BigDecimalToStringHex(FBigDecimal A)
{
	FBigDecimal Corrected = FBigDecimal::CorrectSign(A);
	if(Corrected.Content() == FBigInteger::BigIntegerFromInt32Base(0) && Corrected.Decimal < 0)
	{
		const FString IntegerPart = BigIntegerToStringHex(FBigInteger(Corrected.Content()));
		const FString DecimalPart = "0." + Corrected.PaddingZero() + FString::FromInt(-Corrected.Decimal);
		return "-" + IntegerPart + "+" + DecimalPart;
	}
	const FString IntegerPart = BigIntegerToStringHex(FBigInteger(Corrected.Content()));
	const FString DecimalPart = "0." + Corrected.PaddingZero() + FString::FromInt(Corrected.Decimal);
	return IntegerPart + "+" + DecimalPart;
}

FString UBigNumberBPLibrary::BigDecimalToStringDec(FBigDecimal A)
{
	return FBigDecimal::BigDecimalToStringDecBase(A);
}

FString UBigNumberBPLibrary::BigDecimalToStringABC(FBigDecimal A)
{
	return FBigDecimal::BigDecimalToStringABCBase(A);
}

FBigDecimal UBigNumberBPLibrary::BigDecimalFlipBigDecimal(FBigDecimal A)
{
	return FBigDecimal::BigDecimalFlipBigDecimalBase(A);
}

bool UBigNumberBPLibrary::bBigDecimalIsNegativeBigDecimal(FBigDecimal A)
{
	return A.Content() == FBigInteger::BigIntegerFromInt32Base(0) ? (A.Decimal < 0) : A.Content().IsNegative();
}

bool UBigNumberBPLibrary::bBigDecimalIsZeroBigDecimal(FBigDecimal A)
{
	return A.Content() == 0 && A.Decimal == 0;
}

FBigDecimal UBigNumberBPLibrary::BigDecimalAbsBigDecimal(FBigDecimal A)
{
	return bBigDecimalIsNegativeBigDecimal(A) ? BigDecimalFlipBigDecimal(A) : A;
}
//Todo
void UBigNumberBPLibrary::DecimalAdd(int32 A, int32 B, uint8 AZeros, uint8 BZeros, int32& Result, uint8& ZeroResult, int32& CarryResult)
{
	const bool ASign = A > 0;
	const bool BSign = B > 0;
	A = FMath::Abs(A);
	B = FMath::Abs(B);
	const int32 AL = NumDigitOfInt32(A) + AZeros;
	const int32 BL = NumDigitOfInt32(B) + BZeros;
	const int32 MaxDigit = FMath::Max(AL,BL);
	const int32 MaxDigitDividingPoint = Digits[MaxDigit];
	if(AL < BL)
	{
		A = A * Digits[BL-AL]/Digits[AZeros];
	}
	if(AL > BL)
	{
		B = B * Digits[AL-BL]/Digits[BZeros];
	}
	//Result
	Result = (ASign ? A : -A) + (BSign ? B : -B);
	CarryResult = 0;
	const bool RSign = Result > 0;
	Result = FMath::Abs(Result);
	if(Result > MaxDigitDividingPoint)
	{
		Result = Result - MaxDigitDividingPoint;
		CarryResult = 1;
	}
	ZeroResult = MaxDigit - NumDigitOfInt32(Result);//Todo
	Result = RSign ? Result : -Result;
	CarryResult = RSign ? CarryResult : -CarryResult;
}

int32 UBigNumberBPLibrary::DecimalInverse(int32 Decimal, uint8 Zeros)
{
	Decimal = FMath::Abs(Decimal);
	const int32 AL = NumDigitOfInt32(Decimal);
	const int32 MaxDigitDividingPoint = Digits[AL + Zeros];
	return MaxDigitDividingPoint - Decimal;
}

FBigDecimal UBigNumberBPLibrary::BigDecimalAddBigDecimal(FBigDecimal A, FBigDecimal B)
{
	A.NormalizeDecimalAndZero();
	B.NormalizeDecimalAndZero();
	const BigInt BigZero = FBigInteger::BigIntegerFromInt32Base(0);
	const BigInt BigOne = FBigInteger::BigIntegerFromInt32Base(1);
	//XX.YY + ZZ.W -> YY + W0 = 1KY -> XX+ZZ+1 : Y
	int32 DecimalAddResult = 0;
	uint8 DecimalAddZeroResult = 0;
	int32 DecimalAddResultCarry = 0;
	//Make Decimal Negative if
	//A.Decimal = A.Content() < BigZero ? -A.Decimal : A.Decimal;
	A.Decimal = A.Content().IsNegative() ? -A.Decimal : A.Decimal;
	//B.Decimal = B.Content() < BigZero ? -B.Decimal : B.Decimal;
	B.Decimal = B.Content().IsNegative() ? -B.Decimal : B.Decimal;
	DecimalAdd(A.Decimal, B.Decimal, A.Zero, B.Zero, DecimalAddResult, DecimalAddZeroResult, DecimalAddResultCarry);
	FBigDecimal Result = FBigDecimal(A.Content() + B.Content() + FBigInteger::BigIntegerFromInt32Base(DecimalAddResultCarry), DecimalAddResult,DecimalAddZeroResult);//Todo
	if(Result.Content() != BigZero)
	{
		if(!Result.Content().IsNegative() && Result.Decimal < 0)
		{
			Result = FBigDecimal(Result.Content() - BigOne, DecimalInverse(DecimalAddResult, DecimalAddZeroResult),DecimalAddZeroResult);//Todo
		}
		else if(Result.Content().IsNegative() && Result.Decimal > 0)
		{
			Result = FBigDecimal(Result.Content() + BigOne, DecimalInverse(DecimalAddResult, DecimalAddZeroResult),DecimalAddZeroResult);//Todo
			if(Result.Content() == BigZero)
			{
				Result.Decimal = - Result.Decimal;
			}
		}
	}
	Result.NormalizeDecimalAndZero();
	return Result;
}

FBigDecimal UBigNumberBPLibrary::BigDecimalSubtractBigDecimal(FBigDecimal A, FBigDecimal B)
{
	return BigDecimalAddBigDecimal(A, BigDecimalFlipBigDecimal(B));
}//Pass

template <int32 Bits, bool bSigned>
int32 UBigNumberBPLibrary::NumDigitOfAny(TBigInt<Bits, bSigned> A)
{
	int Digit = 1;
	while (A != 0) 
	{
		A = A / 10;
		if(A != 0){++Digit;}
	}
	return Digit;
}

template <int32 Bits, bool bSigned>
TBigInt<Bits, bSigned> UBigNumberBPLibrary::RemoveTailZeroOfAny(TBigInt<Bits, bSigned> A)
{
	TBigInt<Bits, bSigned> Result = A;
	while (Result % 10 == 0) 
	{
		Result = Result / 10;
	}
	return Result;
}

template <int32 AugBits>
TBigInt<320 + AugBits, false> UBigNumberBPLibrary::AugmentBigInteger(const BigInt& A)
{
	const uint32* Bits = A.GetBits();
	TArray<uint32> NewBits;
	constexpr int32 Loop = BIG_NUMBER_BITS / 32;
	for(int32 i = 0; i < Loop; i++)
	{
		NewBits.Add(Bits[i]);
	}
	for(int32 i=0;i<AugBits/32;i++)
	{
		NewBits.Add(UZero32);//0x00000000
	}
	return TBigInt<320 + AugBits, false>(NewBits.GetData());
}//Todo

template <int32 SourceAugBits>
BigInt UBigNumberBPLibrary::ReduceBigInteger(const TBigInt<320 + SourceAugBits, false>& A)
{
	const uint32* Bits = A.GetBits();
	TArray<uint32> NewBits;
	constexpr int32 Loop = BIG_NUMBER_BITS / 32;
	for(int32 i = 0; i < Loop; i++)
	{
		NewBits.Add(Bits[i]);
	}
	return BigInt(NewBits.GetData());
}//Todo

BigInt UBigNumberBPLibrary::AugmentDecimalPart(int32 A, uint8 AZeros, int32 AugTo)
{
	const int32 Digit = NumDigitOfInt32(A) + AZeros;
	const int32 CompensateZero = FMath::Max(AugTo - Digit, 0);
	const BigInt Result = BigInt(A) * FBigInteger::BigIntegerFromInt32Base(Digits[CompensateZero]);
	return Result;
}

//Todo :Sign
FBigDecimal UBigNumberBPLibrary::BigDecimalMultiplyBigDecimal(FBigDecimal A, FBigDecimal B)
{
	A.NormalizeDecimalAndZero();//Todo: Optimize
	B.NormalizeDecimalAndZero();
	//
	const bool bIsNegativeA = bBigDecimalIsNegativeBigDecimal(A);
	const bool bIsNegativeB = bBigDecimalIsNegativeBigDecimal(B);
	const bool bIsNegative = bIsNegativeA != bIsNegativeB;
	A = bIsNegativeA ? BigDecimalFlipBigDecimal(A) : A;
	B = bIsNegativeB ? BigDecimalFlipBigDecimal(B) : B;
	//
	constexpr int32 AugBitCount = 128;//Well over 320 will be truncated
	constexpr int32 CompensateTo = BIG_NUMBER_MAX_DIGIT;
	typedef TBigInt<BIG_NUMBER_BITS + AugBitCount, false> BigIntTemp;

	const BigIntTemp Multiplier = BigIntTemp(Digits[CompensateTo]);//It's legal when positive
	const BigIntTemp FinalReducer = Multiplier * Multiplier ;
	const BigIntTemp AugAInteger = AugmentBigInteger<AugBitCount>(A.Content());
	const BigIntTemp AugBInteger = AugmentBigInteger<AugBitCount>(B.Content());
	const BigIntTemp AugADecimal = AugmentBigInteger<AugBitCount>(AugmentDecimalPart(A.Decimal, A.Zero, CompensateTo));
	const BigIntTemp AugBDecimal = AugmentBigInteger<AugBitCount>(AugmentDecimalPart(B.Decimal, B.Zero, CompensateTo));
	const BigIntTemp AugA = AugAInteger * Multiplier + AugADecimal;
	const BigIntTemp AugB = AugBInteger * Multiplier + AugBDecimal;
	const BigIntTemp ResultSource = AugA * AugB;
	const BigIntTemp ResultInteger = ResultSource / FinalReducer;
	const BigIntTemp ResultDecimal = ResultSource % FinalReducer;

	int64 ResultDecimal64 = ResultDecimal.ToInt();
	const int32 DecimalAugDigit = NumDigitOfInt64(ResultDecimal64);
	const uint8 ZeroCount = static_cast<uint8>(FMath::Max(0,2 * CompensateTo - DecimalAugDigit));
	//check(ZeroCount < BIG_NUMBER_MAX_DIGIT);
	if(ResultDecimal64 == 0)
	{
		return FBigDecimal(ReduceBigInteger<AugBitCount>(ResultInteger),0, 0);
	}
	ResultDecimal64 = ResultDecimal64 / Digits[DecimalAugDigit - BIG_NUMBER_MAX_DIGIT];
	const int32 ResultDecimal32 = ResultDecimal64;

	const FBigDecimal Result = FBigDecimal(ReduceBigInteger<AugBitCount>(ResultInteger),FBigDecimal::NormalizeDecimal(ResultDecimal32), ZeroCount);
	return bIsNegative ? BigDecimalFlipBigDecimal(Result) : Result;
}
FBigDecimal UBigNumberBPLibrary::BigDecimalDivideBigDecimal(FBigDecimal A, FBigDecimal B)
{
	//A*100 / B*10 /10
	A.NormalizeDecimalAndZero();//Todo: Optimize
	B.NormalizeDecimalAndZero();
	check(!bBigDecimalIsZeroBigDecimal(B))
	//
	const bool bIsNegativeA = bBigDecimalIsNegativeBigDecimal(A);
	const bool bIsNegativeB = bBigDecimalIsNegativeBigDecimal(B);
	const bool bIsNegative = bIsNegativeA != bIsNegativeB;
	A = bIsNegativeA ? BigDecimalFlipBigDecimal(A) : A;
	B = bIsNegativeB ? BigDecimalFlipBigDecimal(B) : B;
	//
	constexpr int32 AugBitCount = 128;//Well over 320 will be truncated
	constexpr int32 CompensateTo = BIG_NUMBER_MAX_DIGIT;
	typedef TBigInt<BIG_NUMBER_BITS + AugBitCount, false> BigIntTemp;

	const BigIntTemp Multiplier = BigIntTemp(Digits[CompensateTo]);//It's legal when positive
	const BigIntTemp Multiplier2 = Multiplier * Multiplier ;
	const BigIntTemp AugAInteger = AugmentBigInteger<AugBitCount>(A.Content());
	const BigIntTemp AugBInteger = AugmentBigInteger<AugBitCount>(B.Content());
	const BigIntTemp AugADecimal = AugmentBigInteger<AugBitCount>(AugmentDecimalPart(A.Decimal, A.Zero, CompensateTo));
	const BigIntTemp AugBDecimal = AugmentBigInteger<AugBitCount>(AugmentDecimalPart(B.Decimal, B.Zero, CompensateTo));
//The different part to Multiplication
	const BigIntTemp AugA = AugAInteger * Multiplier2 + AugADecimal * Multiplier;
	const BigIntTemp AugB = AugBInteger * Multiplier + AugBDecimal;
	const BigIntTemp ResultSource = AugA / AugB;
	const BigIntTemp ResultInteger = ResultSource / Multiplier;
	const BigIntTemp ResultDecimal = ResultSource % Multiplier;
//
	int64 ResultDecimal64 = ResultDecimal.ToInt();
	const int32 DecimalAugDigit = NumDigitOfInt64(ResultDecimal64);
	const uint8 ZeroCount = CompensateTo - static_cast<uint8>(DecimalAugDigit);
	check(ZeroCount<BIG_NUMBER_MAX_DIGIT);
	if(ResultDecimal64 == 0)
	{
		return FBigDecimal(ReduceBigInteger<AugBitCount>(ResultInteger),0, 0);
	}
	//check(DecimalAugDigit - BIG_NUMBER_MAX_DIGIT >= 0)
	ResultDecimal64 = ResultDecimal64 / Digits[FMath::Max(0,DecimalAugDigit - BIG_NUMBER_MAX_DIGIT)];
	const int32 ResultDecimal32 = ResultDecimal64;
	const FBigDecimal Result = FBigDecimal(ReduceBigInteger<AugBitCount>(ResultInteger),FBigDecimal::NormalizeDecimal(ResultDecimal32), ZeroCount);
	return bIsNegative ? BigDecimalFlipBigDecimal(Result) : Result;
}

FBigDecimal UBigNumberBPLibrary::BigDecimalAddBigInteger(FBigDecimal A, FBigInteger B)
{
	return BigDecimalAddBigDecimal(A, BigDecimalFromBigInteger(B));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalSubtractBigInteger(FBigDecimal A, FBigInteger B)
{
	return BigDecimalSubtractBigDecimal(A, BigDecimalFromBigInteger(B));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalMultiplyBigInteger(FBigDecimal A, FBigInteger B)
{
	return BigDecimalMultiplyBigDecimal(A, BigDecimalFromBigInteger(B));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalDivideBigInteger(FBigDecimal A, FBigInteger B)
{
	return BigDecimalDivideBigDecimal(A, BigDecimalFromBigInteger(B));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalAddInt32(FBigDecimal A, int32 B)
{
	return BigDecimalAddBigDecimal(A, BigDecimalFromInt32(B));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalSubtractInt32(FBigDecimal A, int32 B)
{
	return BigDecimalSubtractBigDecimal(A, BigDecimalFromInt32(B));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalMultiplyInt32(FBigDecimal A, int32 B)
{
	return BigDecimalMultiplyBigDecimal(A, BigDecimalFromInt32(B));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalDivideInt32(FBigDecimal A, int32 B)
{
	return BigDecimalDivideBigDecimal(A, BigDecimalFromInt32(B));
}

FBigDecimal UBigNumberBPLibrary::Int32DivideBigDecimal(int32 A, FBigDecimal B)
{
	return BigDecimalDivideBigDecimal(BigDecimalFromInt32(A), B);
}

FBigDecimal UBigNumberBPLibrary::BigDecimalAddInt64(FBigDecimal A, int64 B)
{
	return BigDecimalAddBigDecimal(A, BigDecimalFromInt64(B));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalSubtractInt64(FBigDecimal A, int64 B)
{
	return BigDecimalSubtractBigDecimal(A, BigDecimalFromInt64(B));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalMultiplyInt64(FBigDecimal A, int64 B)
{
	return BigDecimalMultiplyBigDecimal(A, BigDecimalFromInt64(B));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalDivideInt64(FBigDecimal A, int64 B)
{
	return BigDecimalDivideBigDecimal(A, BigDecimalFromInt64(B));
}

FBigDecimal UBigNumberBPLibrary::Int64DivideBigDecimal(int64 A, FBigDecimal B)
{
	return BigDecimalDivideBigDecimal(BigDecimalFromInt64(A), B);
}

FBigDecimal UBigNumberBPLibrary::BigDecimalAddFloat(FBigDecimal A, float B)
{
	return BigDecimalAddBigDecimal(A, BigDecimalFromFloat(B));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalSubtractFloat(FBigDecimal A, float B)
{
	return BigDecimalSubtractBigDecimal(A, BigDecimalFromFloat(B));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalMultiplyFloat(FBigDecimal A, float B)
{
	return BigDecimalMultiplyBigDecimal(A, BigDecimalFromFloat(B));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalDivideFloat(FBigDecimal A, float B)
{
	return BigDecimalDivideBigDecimal(A, BigDecimalFromFloat(B));
}

FBigDecimal UBigNumberBPLibrary::FloatDivideBigDecimal(float A, FBigDecimal B)
{
	return BigDecimalDivideBigDecimal(BigDecimalFromFloat(A), B);
}
//Comparison
bool UBigNumberBPLibrary::BigDecimalEqualBigDecimal(FBigDecimal A, FBigDecimal B)
{
	A.NormalizeDecimalAndZero();
	B.NormalizeDecimalAndZero();
	return BigIntegerEqualBigInteger(FBigInteger(A.Content()), FBigInteger(B.Content())) && A.Decimal == B.Decimal && A.Zero == B.Zero;
}

bool UBigNumberBPLibrary::BigDecimalNotEqualBigDecimal(FBigDecimal A, FBigDecimal B)
{
	return !BigDecimalEqualBigDecimal(A,B);
}

bool UBigNumberBPLibrary::BigDecimalLargerBigDecimal(FBigDecimal A, FBigDecimal B)
{
	if(BigIntegerLargerBigInteger(FBigInteger(A.Content()), FBigInteger(B.Content())))
	{
		return true;
	}
	else if(BigIntegerEqualBigInteger(FBigInteger(A.Content()), FBigInteger(B.Content())))
	{
		return BigIntegerLargerBigInteger(FBigInteger(AugmentDecimalPart(A.Decimal, A.Zero, BIG_NUMBER_MAX_DIGIT)), FBigInteger(AugmentDecimalPart(B.Decimal, B.Zero, BIG_NUMBER_MAX_DIGIT)));
	}
	else//Less
	{
		return false;
	}
}

bool UBigNumberBPLibrary::BigDecimalLargerOrEqualBigDecimal(FBigDecimal A, FBigDecimal B)
{
	if(BigIntegerLargerBigInteger(FBigInteger(A.Content()), FBigInteger(B.Content())))
	{
		return true;
	}
	else if(BigIntegerEqualBigInteger(FBigInteger(A.Content()), FBigInteger(B.Content())))
	{
		return BigIntegerLargerOrEqualBigInteger(FBigInteger(AugmentDecimalPart(A.Decimal, A.Zero, BIG_NUMBER_MAX_DIGIT)), FBigInteger(AugmentDecimalPart(B.Decimal, B.Zero, BIG_NUMBER_MAX_DIGIT)));
	}
	else
	{
		return false;
	}
}

bool UBigNumberBPLibrary::BigDecimalLessBigDecimal(FBigDecimal A, FBigDecimal B)
{
	if(BigIntegerLessBigInteger(FBigInteger(A.Content()), FBigInteger(B.Content())))
	{
		return true;
	}
	else if(BigIntegerEqualBigInteger(FBigInteger(A.Content()), FBigInteger(B.Content())))
	{
		return BigIntegerLessBigInteger(FBigInteger(AugmentDecimalPart(A.Decimal, A.Zero, BIG_NUMBER_MAX_DIGIT)), FBigInteger(AugmentDecimalPart(B.Decimal, B.Zero, BIG_NUMBER_MAX_DIGIT)));
	}
	else
	{
		return false;
	}
}

bool UBigNumberBPLibrary::BigDecimalLessOrEqualBigDecimal(FBigDecimal A, FBigDecimal B)
{
	if(BigIntegerLessBigInteger(FBigInteger(A.Content()), FBigInteger(B.Content())))
	{
		return true;
	}
	else if(BigIntegerLessOrEqualBigInteger(FBigInteger(A.Content()), FBigInteger(B.Content())))
	{
		return BigIntegerLessOrEqualBigInteger(FBigInteger(AugmentDecimalPart(A.Decimal, A.Zero, BIG_NUMBER_MAX_DIGIT)), FBigInteger(AugmentDecimalPart(B.Decimal, B.Zero, BIG_NUMBER_MAX_DIGIT)));
	}
	else
	{
		return false;
	}
}
//Others

//Not precise, use double sqrt instead
FBigDecimal UBigNumberBPLibrary::BigDecimalSquareRoot(FBigDecimal A)
{
	/*
	if(BigDecimalLessOrEqualBigDecimal(A, BigDecimalFromInt32(0)))
	{
		return BigDecimalFromInt32(0);
	}
	if(BigDecimalEqualBigDecimal(A, BigDecimalFromInt32(1)))
	{
		return BigDecimalFromInt32(1);
	}
	if(BigDecimalLargerBigDecimal(A, FBigDecimal(BigInt(static_cast<int64>(100)))))
	{
		return BigDecimalMultiplyInt32(BigDecimalSquareRoot(BigDecimalDivideInt32(A, 100)),10);
	}
	FBigDecimal T = BigDecimalDivideInt32(A, 8);
	T = BigDecimalAddFloat(T, 0.5);
	FBigDecimal R = BigDecimalDivideBigDecimal(BigDecimalMultiplyInt32(A, 2),BigDecimalAddInt32(A, 4));
	T = BigDecimalAddBigDecimal(T, R);
	int32 C = 10;
	while(C--)
	{
		T = BigDecimalDivideInt32(BigDecimalAddBigDecimal(T, BigDecimalDivideBigDecimal(A, T)), 2);
	}
	T.NormalizeDecimalAndZero();
	return T;
	*/
	if(BigDecimalLessOrEqualBigDecimal(A, BigDecimalFromInt32(0)))
	{
		return BigDecimalFromInt32(0);
	}
	if(BigDecimalLargerBigDecimal(A, FBigDecimal(BigInt(static_cast<int64>(100)))))
	{
		return BigDecimalMultiplyInt32(BigDecimalSquareRoot(BigDecimalDivideInt32(A, 100)),10);
	}
	return FBigDecimal(sqrt(A.ToDoubleBase()));
}

FBigDecimal UBigNumberBPLibrary::BigDecimalReciprocal(FBigDecimal A)
{
	return BigDecimalDivideBigDecimal(BigDecimalFromInt32(1), A);
}

FBigDecimal UBigNumberBPLibrary::BigDecimalReciprocalF2(FBigDecimal A)
{
	//1/sqrt(1-x*x);
	FBigDecimal R = BigDecimalSubtractBigDecimal(BigDecimalFromInt32(1),BigDecimalMultiplyBigDecimal(A, A));
	return BigDecimalReciprocal(BigDecimalSquareRoot(R));
}
/*
FBigDecimal UBigNumberBPLibrary::BigDecimalSimpson(FBigDecimal A, FBigDecimal B, int32 Flag)
{
	FBigDecimal BSA = BigDecimalSubtractBigDecimal(B,A);
	FBigDecimal C = BigDecimalAddBigDecimal(A, BigDecimalDivideBigDecimal(BSA, BigDecimalFromInt32(2)));
	if(Flag==1)
	{
		FBigDecimal BSA6 = BigDecimalDivideBigDecimal(BSA, BigDecimalFromInt32(6));
		FBigDecimal L = BigDecimalReciprocal(A);
		FBigDecimal M = BigDecimalMultiplyInt32(BigDecimalReciprocal(C), 4);
		FBigDecimal R = BigDecimalReciprocal(B);
		FBigDecimal F = BigDecimalAddBigDecimal(BigDecimalAddBigDecimal(L,M),R);
		return BigDecimalMultiplyBigDecimal(F, BSA6);
	}
	else //if(Flag==2)
	{
		FBigDecimal BSA6 = BigDecimalDivideBigDecimal(BSA, BigDecimalFromInt32(6));
		FBigDecimal L = BigDecimalReciprocalF2(A);
		FBigDecimal M = BigDecimalMultiplyInt32(BigDecimalReciprocalF2(C), 4);
		FBigDecimal R = BigDecimalReciprocalF2(B);
		FBigDecimal F = BigDecimalAddBigDecimal(BigDecimalAddBigDecimal(L,M),R);
		return BigDecimalMultiplyBigDecimal(F, BSA6);
	}
}

FBigDecimal UBigNumberBPLibrary::BigDecimalASR(FBigDecimal A, FBigDecimal B, FBigDecimal Eps, FBigDecimal A2, int32 Flag)
{
	FBigDecimal C = BigDecimalAddBigDecimal(A, BigDecimalDivideInt32(BigDecimalSubtractBigDecimal(B,A),2));
	FBigDecimal L = BigDecimalSimpson(A, C, Flag);
	FBigDecimal R = BigDecimalSimpson(C, B, Flag);
	FBigDecimal LPR = BigDecimalAddBigDecimal(L, R);
	FBigDecimal LPRSA2 = BigDecimalSubtractBigDecimal(LPR, A2);
	if(BigDecimalLessOrEqualBigDecimal(BigDecimalAbsBigDecimal(LPRSA2),BigDecimalMultiplyInt32(Eps,15)))
	{
		return BigDecimalAddBigDecimal(LPR, BigDecimalDivideInt32(LPRSA2, 15));
	}
	FBigDecimal EPSD2 = BigDecimalDivideInt32(Eps,2);
	FBigDecimal LLL = BigDecimalASR(A, C, EPSD2, L,Flag);
	FBigDecimal RRR = BigDecimalASR(C, B, EPSD2, R,Flag);
	return BigDecimalAddBigDecimal(LLL,RRR);
}

FBigDecimal UBigNumberBPLibrary::BigDecimalASR(FBigDecimal A, FBigDecimal B, FBigDecimal Eps, int32 Flag)
{
	return BigDecimalASR(A, B, Eps, BigDecimalSimpson(A, B,Flag),Flag);
}
*/
FBigDecimal UBigNumberBPLibrary::BigDecimalPowInt32(FBigDecimal A, int32 B)
{
	if(B<0)
	{
		return Int32DivideBigDecimal(1, BigDecimalPowInt32(A,-B));
	}
	FBigDecimal Result = FBigDecimal(1);
	while(B)
	{
		if(B&1)
		{
			Result = BigDecimalMultiplyBigDecimal(A, Result);
		}
		A = BigDecimalMultiplyBigDecimal(A, A);
		B >>= 1;
	}
	return Result;
}

FBigDecimal UBigNumberBPLibrary::BigDecimalLn(FBigDecimal A)
{
	if(BigDecimalLessOrEqualBigDecimal(A, BigDecimalFromInt32(0)))
	{
		return BigDecimalFromInt32(0);
	}
	/*Failed
	return BigDecimalASR(BigDecimalFromInt32(1),A,FBigDecimal(1, 6),1);
	*/
	//Use Taylor series expansion instead
	const FBigDecimal Ln100 = FBigDecimal(BigInt(4),605170185,0);//4.60517018599
	if(BigDecimalLargerBigDecimal(A, FBigDecimal(BigInt(static_cast<int64>(100)))))
	{
		return BigDecimalAddBigDecimal(BigDecimalLn(BigDecimalDivideInt32(A, 100)),Ln100);
	}
	return FBigDecimal(log(A.ToDoubleBase()));
}

/*
FBigDecimal UBigNumberBPLibrary::BigDecimalExp(FBigDecimal A)
{
	if(bBigDecimalIsNegativeBigDecimal(A))
	{
		return BigDecimalReciprocal(BigDecimalExp(BigDecimalFlipBigDecimal(A)));
	}
	BigInt N = A.Content();
	FBigDecimal e1 = BigDecimalPowInt32(e,n);
	FBigDecimal e2 = eee(x);
	return e1*e2;//计算结果
}
*/


