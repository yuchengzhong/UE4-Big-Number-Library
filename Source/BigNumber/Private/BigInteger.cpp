// Copyright 2022 Suika Studio. All Rights Reserved.
#include "BigInteger.h"

int32 FBigInteger::FindDecimalPointBase(const FString& In)
{
	int32 PointLocation = In.Find(".");
	if(PointLocation < 0)
	{
		PointLocation = In.Find(",");
	}
	return PointLocation;
}

FBigInteger::FBigInteger()
{
	Bits.SetNumZeroed(BIG_NUMBER_BITS_COUNT);
}

BigInt FBigInteger::MultiplyByDecimalStringBase(const FString& A, const BigInt& B)
{
	BigInt Result = BigInt(static_cast<int64>(0));
	const int32 PointLocation = FindDecimalPointBase(A);
	check(PointLocation >= 0)
	const TCHAR* Chars = GetData(A);
	const int32 Length = A.Len();
	for(int i=0;i<Length;i++)
	{
		const TCHAR CurrentChar = Chars[i];
		if(CurrentChar > static_cast<TCHAR>('0') && CurrentChar <= static_cast<TCHAR>('9'))//Todo: Check if can skip 0
		{
			if(i < PointLocation)
			{
				Result += BigIntegerPowerBigIntegerBy32Base(BigInt(static_cast<int64>(10)),PointLocation - i - 1) *BigInt(static_cast<int64>(CurrentChar - static_cast<TCHAR>('0'))) *B;
			}
			else
			{
				Result += (BigInt(static_cast<int64>(CurrentChar - static_cast<TCHAR>('0'))) * B) /BigIntegerPowerBigIntegerBy32Base(BigInt(static_cast<int64>(10)), i - PointLocation) ;
			}
		}
	}
	return Result;
}

BigInt FBigInteger::BigIntegerPowerBigIntegerBy32Base(const BigInt& A, int32 B)
{
	int32 N = B;
	if(N<0 || A.IsNegative())
	{
		return BigInt(static_cast<int64>(0));
	}
	BigInt Result = 1;
	BigInt Mul = A;
	while(N)
	{
		if(N&1) Result *= Mul;
		Mul = Mul * Mul;
		N >>= 1;
	}
	return BigInt(Result);
}

BigInt FBigInteger::BigIntegerFlipBigIntegerBase(const BigInt& A)
{
	return Flip(A);
}

BigInt FBigInteger::BigIntegerFromInt32Base(int32 A)
{
	if (A >= 0)
	{
		return BigInt(A);
	}
	else
	{
		constexpr int32 Loop = BIG_NUMBER_BITS / 32;
		TArray<uint32> Bits;
		Bits.Add(A);
		for(int32 i=0; i < Loop - 1; i++)
		{
			Bits.Add(UMax32);
		}
		return BigInt(Bits.GetData());
	}
}

BigInt FBigInteger::BigIntegerFromInt64Base(int64 A)
{
	if (A >= 0)
	{
		return BigInt(A);
	}
	else
	{
		constexpr int32 Loop = BIG_NUMBER_BITS / 32;
		TArray<uint32> Bits;
		const int32 LowBits = static_cast<int32>(A & U32Mask);//0xffffffff
		const int32 HighBits = static_cast<int32>((A>>32) & U32Mask);//0xffffffff
		Bits.Add(LowBits);
		Bits.Add(HighBits);
		for(int32 i=0; i < Loop - 2; i++)
		{
			Bits.Add(UMax32);
		}
		return BigInt(Bits.GetData());
	}
}

BigInt FBigInteger::BigIntegerFromStringPureBase(const FString& A)
{
	BigInt Result = 0;
	BigInt CurrentBase = 1;
	FString TrimmedNumber = A.TrimStartAndEnd();
	const TCHAR* Chars = GetData(TrimmedNumber);
	const int32 Length = TrimmedNumber.Len();
	bool bNegative = false;
	for(int i=0;i<Length;i++)
	{
		const TCHAR CurrentChar = Chars[Length - i - 1];
		if(i == Length -1 && CurrentChar == static_cast<TCHAR>('-'))
		{
			bNegative = true;
			continue;
		}
		const int64 Exp = CurrentChar - static_cast<TCHAR>('0');
		if(Exp < 0 || Exp > 9)
		{
			continue;
		}
		Result = BigInt(Exp)
			* CurrentBase + Result;
		CurrentBase = CurrentBase * 10;
	}
	return bNegative ? BigIntegerFlipBigIntegerBase(Result) : Result;
}

BigInt FBigInteger::BigIntegerFromStringBase(const FString& A)
{
	/*
		 * Valid String:
		 * 1234567
		 * -1234567
		 * 00000
		 * 00000A1234B
		 * 0.123456A
		 * -123456B
		 */
	BigInt Result = 0;
	FString TrimmedNumber = A.TrimStartAndEnd();
	if(A.Len()<=0)
	{
		return BigInt(static_cast<int64>(0));
	}
	const TCHAR* Chars = GetData(TrimmedNumber);
	bool bNegative = false;
	if(Chars[0] == static_cast<TCHAR>('*'))
	{
		return BigInt(static_cast<int64>(0));
	}
	if(Chars[0] == static_cast<TCHAR>('-'))
	{
		bNegative = true;
		TrimmedNumber = TrimmedNumber.RightChop(1);
		Chars = GetData(TrimmedNumber);
	}
	const int32 Length = TrimmedNumber.Len();
	FString CurrentSubNumber = "";
	bool bContainDecimal = false;
	
	for(int i=0;i<Length;i++)
	{
		const TCHAR CurrentChar = Chars[i];
		if(CurrentChar >= static_cast<TCHAR>('0') && CurrentChar <= static_cast<TCHAR>('9'))
		{
			CurrentSubNumber += CurrentChar;
		}
		else if(CurrentChar >= static_cast<TCHAR>('A') && CurrentChar <= static_cast<TCHAR>('Z'))
		{
			//...
			FString CurrentDigitMark = "";
			CurrentDigitMark += CurrentChar;
			if(CurrentSubNumber.Len() <= 0)
			{
				Result = Result + GetDigitMarkValueBase(CurrentDigitMark);
			}
			else
			{
				if(bContainDecimal)
				{
					Result = Result + FBigInteger::MultiplyByDecimalStringBase(CurrentSubNumber, GetDigitMarkValueBase(CurrentDigitMark));//Decimal
				}
				else
				{
					Result = Result + BigIntegerFromStringPureBase(CurrentSubNumber) * GetDigitMarkValueBase(CurrentDigitMark);
				}
				CurrentSubNumber = "";
			}
			bContainDecimal = false;
		}
		else if(CurrentChar == static_cast<TCHAR>('.') || CurrentChar == static_cast<TCHAR>(','))//Related to floating point mul big int //Todo
		{
			CurrentSubNumber += CurrentChar;
			bContainDecimal = true;
		}
		else
		{
			continue;
		}
	}
	if(CurrentSubNumber.Len() != 0)
	{
		if(bContainDecimal)
		{
			Result = Result + FBigInteger::MultiplyByDecimalStringBase(CurrentSubNumber, BigInt(static_cast<int64>(1)));//Decimal
		}
		else
		{
			Result = Result + BigIntegerFromStringPureBase(CurrentSubNumber);
		}
		bContainDecimal = false;
	}
	return bNegative ? FBigInteger::BigIntegerFlipBigIntegerBase(Result) : Result;
}

FString FBigInteger::BigIntegerToStringDecBase(const FBigInteger& A)
{
	BigInt Remain = A.Content();
	bool bNegative = false;
	FString Result = "";
	if(Remain.IsNegative())
	{
		bNegative = true;
		Remain = FBigInteger::BigIntegerFlipBigIntegerBase(Remain);
	}
	if(Remain.IsZero())
	{
		Result = "0";
		return Result;
	}
	const BigInt Dec = BigInt(static_cast<int64>(10));
	while(Remain > 0)
	{
		BigInt CurrentDigit = Remain % Dec;
		Result = FString::FromInt(CurrentDigit.ToInt()) + Result;
		Remain /= Dec;
	}
	if(Result.Len() <= 0 )
	{
		Result = "0";
	}
	return bNegative ? "-" + Result : Result;
}

FString FBigInteger::BigIntegerToStringABCBase(const FBigInteger& A)
{
	BigInt Remain = A.Content();
	bool bNegative = false;
	if(Remain.IsNegative())
	{
		bNegative = true;
		Remain = FBigInteger::BigIntegerFlipBigIntegerBase(Remain);
	}
	FString Result = "";
	char CurrentMark = 'A' - 1;
	while(Remain > 0)
	{
		BigInt CurrentDigit = Remain % BigInt(BIG_NUMBER_GAP);
		if(CurrentDigit != 0)
		{
			FString ModifiedMark = FString("");
			if(CurrentMark > 'Z')
			{
				//Error, exceed limit
			}
			else if(CurrentMark >= 'A')
			{
				ModifiedMark += CurrentMark;
			}
			Result = FString::FromInt(CurrentDigit.ToInt()) + ModifiedMark + Result;
		}
		CurrentMark++;
		Remain /= BIG_NUMBER_GAP;
	}
	if(Result.Len() <=0)
	{
		Result = "0";
	}
	if(bNegative)
	{
		Result = "-" + Result;
	}
	return Result;
}

FString FBigInteger::BigIntegerSerialize(bool bUseForCustomizeDetailPanel) const
{
	//(Bits = (123,321,...,))
	check(Bits.Num() ==BIG_NUMBER_BITS_COUNT)
	FString Result = bUseForCustomizeDetailPanel ? "(" : "(Bits = (";
	for(int32 i=0;i<BIG_NUMBER_BITS_COUNT;i++)
	{
		Result += FString::FromInt(Bits[i]);
		if(i!=BIG_NUMBER_BITS_COUNT-1)
		{
			Result += ",";
		}
	}
	Result += bUseForCustomizeDetailPanel ? ")" : "))";
	return Result;
}

bool FBigInteger::Deserialize(const FString& A)
{
	if(A.IsEmpty())
	{
		return false;
	}
	if(Bits.Num()!=BIG_NUMBER_BITS_COUNT)
	{
		Bits.SetNumZeroed(BIG_NUMBER_BITS_COUNT);
	}
	check(Bits.Num() ==BIG_NUMBER_BITS_COUNT)
	const int32 DataLocation = A.Find("=");
	FString ParenthesizedString = A.RightChop(DataLocation + 1);
	const int32 LeftParenthesisLocation = ParenthesizedString.Find("(");
	if(LeftParenthesisLocation >=0)
	{
		ParenthesizedString = ParenthesizedString.RightChop(LeftParenthesisLocation + 1);
	}
	const int32 RightParenthesisLocation = ParenthesizedString.Find(")");
	if(RightParenthesisLocation >=0)
	{
		ParenthesizedString = ParenthesizedString.Left(RightParenthesisLocation);
	}
	check(ParenthesizedString.Find(")") < 0)
	check(ParenthesizedString.Find("(") < 0)
	TArray<FString> Results;
	Results.Reserve(BIG_NUMBER_BITS_COUNT);
	ParenthesizedString.ParseIntoArray(Results,TEXT(","), true);
	//check(Results.Num() == BIG_NUMBER_BITS_COUNT)
	if(Results.Num() != BIG_NUMBER_BITS_COUNT)
	{
		return false;
	}
	if(Bits.Num() !=BIG_NUMBER_BITS_COUNT)
	{
		Bits.SetNumZeroed(BIG_NUMBER_BITS_COUNT);
	}
	check(Bits.Num() ==BIG_NUMBER_BITS_COUNT)
	for(int32 i=0;i<BIG_NUMBER_BITS_COUNT;i++)
	{
		Bits[i] = FCString::Atoi(*Results[i]);
	}
	return true;
}

BigInt FBigInteger::GetDigitMarkValueBase(const FString& A)
{
	if(A.Len() <= 0)
	{
		return BigInt(static_cast<int64>(1));
	}
	else if(GetData(A)[0] < static_cast<TCHAR>('A') || GetData(A)[0] > static_cast<TCHAR>('Z'))
	{
		return BigInt(static_cast<int64>(0));
	}
	const int32 Rank = static_cast<int32>(GetData(A)[0] - static_cast<TCHAR>('A')) + 1;
	return BigIntegerPowerBigIntegerBy32Base(BigInt(static_cast<int64>(BIG_NUMBER_GAP)), Rank);
}

BigInt FBigInteger::Flip(const BigInt& A)
{
	const BigInt FlippedBigInteger = (~A) + BigInt(static_cast<int64>(1));
	return FlippedBigInteger;
}

void FBigInteger::BitsFromBigIntBase(const BigInt& A)
{
	const uint32* ABits = A.GetBits();
	Bits.SetNumZeroed(BIG_NUMBER_BITS_COUNT);
	FMemory::Memcpy(Bits.GetData(), ABits,BIG_NUMBER_BITS_COUNT * sizeof(uint32));
}

FBigInteger::FBigInteger(const BigInt& A)
{
	BitsFromBigIntBase(A);
}

BigInt FBigInteger::FromBits(const TArray<int32>& A)
{
	TArray<uint32> B;
	B.SetNumZeroed(BIG_NUMBER_BITS_COUNT);
	FMemory::Memcpy(B.GetData(), A.GetData(),BIG_NUMBER_BITS_COUNT * sizeof(uint32));
	return BigInt(B.GetData());
}

BigInt FBigInteger::FromBits(const FBigInteger& A)
{
	return FBigInteger::FromBits(A.Bits);
}

BigInt FBigInteger::Content() const
{
	return FBigInteger::FromBits(Bits);
}
