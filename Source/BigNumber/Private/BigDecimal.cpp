// Copyright 2022 Suika Studio. All Rights Reserved.
#include "BigDecimal.h"

uint8 FBigDecimal::ZeroCount(const FString& S)
{
	const int32 Len = S.Len();
	uint8 Zeros = 0;
	while(S.Mid(Zeros,1) == "0" && Zeros < Len)
	{
		Zeros++;
	}
	return Zeros;
}

FString FBigDecimal::PaddingZero() const
{
	FString Zeros;
	for(int i=0;i < Zero;i++)
	{
		Zeros += "0";
	}
	return Zeros;
}

FBigDecimal::FBigDecimal(): Decimal(0), Zero(0)
{
	Bits.SetNumZeroed(BIG_NUMBER_BITS_COUNT);
}

void FBigDecimal::BitsFromBigIntBase(const BigInt& A)
{
	const uint32* ABits = A.GetBits();
	Bits.SetNumZeroed(BIG_NUMBER_BITS_COUNT);
	FMemory::Memcpy(Bits.GetData(), ABits,BIG_NUMBER_BITS_COUNT * sizeof(uint32));
}

FBigDecimal::FBigDecimal(const BigInt& A, const uint32& B, const uint8& C): Decimal(B), Zero(C)
{
	BitsFromBigIntBase(A);
}

FBigDecimal::FBigDecimal(const uint32& B, const uint8& C): Decimal(B), Zero(C)
{
	Bits.SetNumZeroed(BIG_NUMBER_BITS_COUNT);
}

FBigDecimal::FBigDecimal(const BigInt& A): Decimal(0), Zero(0)
{
	BitsFromBigIntBase(A);
}

FBigDecimal::FBigDecimal(const BigInt& A, const int32& B, const uint8& C): Decimal(B), Zero(C)
{
	BitsFromBigIntBase(A);
}

FBigDecimal::FBigDecimal(const BigInt& A, const float& B)
{
	BitsFromBigIntBase(A);
	//2147483647 -> 10 -> Keep 9 only
	FString Converted = FString::SanitizeFloat(B);
	const int32 PointLocation = FBigInteger::FindDecimalPointBase(Converted);
	Converted = Converted.RightChop(PointLocation + 1);
	//Better clamp here
	Converted = Converted.Left(BIG_NUMBER_MAX_DIGIT);//Todo: Need optimize
	Zero = ZeroCount(Converted);
	Decimal = FCString::Atoi(*Converted);
}

FBigDecimal::FBigDecimal(const BigInt& A, const double& B)
{
	BitsFromBigIntBase(A);
	FString Converted = FString::Printf(TEXT("%f"), B);
	const int32 PointLocation = FBigInteger::FindDecimalPointBase(Converted);
	Converted = Converted.RightChop(PointLocation + 1);
	//Better clamp here
	Converted = Converted.Left(BIG_NUMBER_MAX_DIGIT);//Todo: Need optimize
	Zero = ZeroCount(Converted);
	Decimal = FCString::Atoi(*Converted);
}

FBigDecimal::FBigDecimal(const double& A)
{
	FString Converted = FString::Printf(TEXT("%f"), A);
	FBigDecimal NewDecimal = BigDecimalFromStringPureBase(Converted);
	Bits.SetNumZeroed(BIG_NUMBER_BITS_COUNT);
	FMemory::Memcpy(Bits.GetData(), NewDecimal.Bits.GetData(),BIG_NUMBER_BITS_COUNT * sizeof(uint32));
	Zero = NewDecimal.Zero;
	Decimal = NewDecimal.Decimal;
}

double FBigDecimal::ToDoubleBase() const
{
	return FCString::Atod(*BigDecimalToStringDecBase(*this));
}

int32 FBigDecimal::NormalizeDecimal(int32 A)
{
	if(A == 0) return 0;
	while (A % 10 == 0)
	{
		A /= 10;
	}
	return A;
}

void FBigDecimal::NormalizeDecimalAndZero()
{
	if(Decimal == 0) {Zero = 0;}
	Decimal = NormalizeDecimal(Decimal);
}

BigInt FBigDecimal::Content() const
{
	TArray<uint32> B;
	B.SetNumZeroed(BIG_NUMBER_BITS_COUNT);
	FMemory::Memcpy(B.GetData(), Bits.GetData(),BIG_NUMBER_BITS_COUNT * sizeof(uint32));
	return BigInt(B.GetData());
}

FBigDecimal FBigDecimal::CorrectSign(const FBigDecimal& A)
{
	FBigDecimal Result = A;
	if(A.Content().IsGreaterThanZero())
	{
		if(A.Decimal < 0)//123.-123
		{
			//Need Correct
			Result.Decimal = -Result.Decimal;
			Result.BitsFromBigIntBase(FBigInteger::Flip(Result.Content()));
		}
	}
	else if(A.Content().IsLessThanZero())
	{
		if(A.Decimal < 0)//-123.-123
		{
			//Need Correct
			Result.Decimal = -Result.Decimal;
		}
	}
	Result.NormalizeDecimalAndZero();
	return Result;
}

void FBigDecimal::CorrectSign()
{
	FBigDecimal Result = FBigDecimal::CorrectSign(*this);
	BitsFromBigIntBase(Result.Content());//Todo Optimaze
	Decimal = Result.Decimal;
}

FBigDecimal FBigDecimal::BigDecimalFlipBigDecimalBase(FBigDecimal A)
{
	if(A.Content() == FBigInteger::BigIntegerFromInt32Base(0))
	{
		return FBigDecimal(A.Content(),-A.Decimal,A.Zero);
	}
	else
	{
		return FBigDecimal(FBigInteger::BigIntegerFlipBigIntegerBase(A.Content()),A.Decimal,A.Zero);
	}
}

FBigDecimal FBigDecimal::BigDecimalFromStringPureBase(FString A)
{ 
	/*Accept only like xxx.yyy, -xxx.yyy*/
	int32 NegativeMarkIndex = -1;
	bool bIsNegative = false;
	if(A.FindChar(static_cast<TCHAR>('-'), NegativeMarkIndex))
	{
		A = A.RightChop(NegativeMarkIndex + 1);
		bIsNegative = true;
	}
	const int32 PointLocation = FBigInteger::FindDecimalPointBase(A);
	if(PointLocation <= 0)
	{
		if(PointLocation == 0)//.12345
		{
			FString DecimalPart = A.RightChop(1);
			DecimalPart = DecimalPart.Left(BIG_NUMBER_MAX_DIGIT);
			const uint8 Zeros = FBigDecimal::ZeroCount(DecimalPart);
			const int32 Decimal = FCString::Atoi(*DecimalPart);
			const FBigDecimal Result = FBigDecimal(0, Decimal, Zeros);
			return bIsNegative ? BigDecimalFlipBigDecimalBase(Result) : Result;
		}
		else//12345
		{
			const FString IntegerPart = A;
			const FBigDecimal Result = FBigDecimal(FBigInteger::BigIntegerFromStringPureBase(IntegerPart));
			return bIsNegative ? BigDecimalFlipBigDecimalBase(Result) : Result;
		}
	}
	const FString IntegerPart = A.Left(PointLocation);
	FString DecimalPart = A.RightChop(PointLocation + 1);
	DecimalPart = DecimalPart.Left(BIG_NUMBER_MAX_DIGIT);
	const uint32 Decimal = FCString::Atoi(*DecimalPart);
	const uint8 Zeros = FBigDecimal::ZeroCount(DecimalPart);
	const FBigDecimal Result = FBigDecimal(FBigInteger::BigIntegerFromStringPureBase(IntegerPart), Decimal, Zeros);
	return bIsNegative ? BigDecimalFlipBigDecimalBase(Result) : Result;
}

FBigDecimal FBigDecimal::BigDecimalFromStringBase(FString A)
{
	/*Accept Digital Mark like ABC*/
	int32 NegativeMarkIndex = -1;
	bool bIsNegative = false;
	if(A.FindChar(static_cast<TCHAR>('-'), NegativeMarkIndex))
	{
		A = A.RightChop(NegativeMarkIndex + 1);
		bIsNegative = true;
	}
	const int32 PointLocation = FBigInteger::FindDecimalPointBase(A);
	if(PointLocation <= 0)
	{
		if(PointLocation == 0)//.12345
		{
			FString DecimalPart = A.RightChop(1);
			DecimalPart = DecimalPart.Left(BIG_NUMBER_MAX_DIGIT);
			const uint8 Zeros = FBigDecimal::ZeroCount(DecimalPart);
			const int32 Decimal = FCString::Atoi(*DecimalPart);
			const FBigDecimal Result = FBigDecimal(0, Decimal, Zeros);
			return bIsNegative ? BigDecimalFlipBigDecimalBase(Result) : Result;
		}
		else//12345
		{
			const FString IntegerPart = A;
			const FBigDecimal Result = FBigDecimal(FBigInteger::BigIntegerFromStringBase(IntegerPart));
			return bIsNegative ? BigDecimalFlipBigDecimalBase(Result) : Result;
		}
	}
	const FString IntegerPart = A.Left(PointLocation);
	FString DecimalPart = A.RightChop(PointLocation + 1);
	DecimalPart = DecimalPart.Left(BIG_NUMBER_MAX_DIGIT);
	const uint32 Decimal = FCString::Atoi(*DecimalPart);
	const uint8 Zeros = FBigDecimal::ZeroCount(DecimalPart);
	const FBigDecimal Result = FBigDecimal(FBigInteger::BigIntegerFromStringBase(IntegerPart), Decimal, Zeros);
	return bIsNegative ? BigDecimalFlipBigDecimalBase(Result) : Result;
}

FString FBigDecimal::BigDecimalToStringDecBase(const FBigDecimal& A)
{
	FBigDecimal Corrected = FBigDecimal::CorrectSign(A);
	if(Corrected.Content() == FBigInteger::BigIntegerFromInt32Base(0) && Corrected.Decimal < 0)
	{
		const FString IntegerPart = FBigInteger::BigIntegerToStringDecBase(FBigInteger(Corrected.Content()));
		const FString DecimalPart = FString::FromInt(-Corrected.Decimal);
		return "-" + IntegerPart + "." + Corrected.PaddingZero() + DecimalPart;
	}
	const FString IntegerPart = FBigInteger::BigIntegerToStringDecBase(FBigInteger(Corrected.Content()));
	const FString DecimalPart = FString::FromInt(Corrected.Decimal);
	return IntegerPart + "." + Corrected.PaddingZero() + DecimalPart;
}

FString FBigDecimal::BigDecimalToStringABCBase(const FBigDecimal& A)
{
	FBigDecimal Corrected = FBigDecimal::CorrectSign(A);
	if(Corrected.Content() == FBigInteger::BigIntegerFromInt32Base(0) && Corrected.Decimal < 0)
	{
		const FString IntegerPart = FBigInteger::BigIntegerToStringABCBase(FBigInteger(Corrected.Content()));
		const FString DecimalPart = FString::FromInt(-Corrected.Decimal);
		return "-" + IntegerPart + "." + Corrected.PaddingZero() + DecimalPart;
	}
	const FString IntegerPart = FBigInteger::BigIntegerToStringABCBase(FBigInteger(Corrected.Content()));
	const FString DecimalPart = FString::FromInt(Corrected.Decimal);
	return IntegerPart + "." + Corrected.PaddingZero() + DecimalPart;
}

FString FBigDecimal::BigDecimalSerialize() const
{
	//(Bits = (123,321,...,214))
	check(Bits.Num() ==BIG_NUMBER_BITS_COUNT)
	FString Result = "(Decimal = ";
	Result += FString::FromInt(Decimal);
	Result += ", Zero = ";
	Result += FString::FromInt(static_cast<int32>(Zero));
	Result += ", Bits = (";
	for(int32 i=0;i<BIG_NUMBER_BITS_COUNT;i++)
	{
		Result += FString::FromInt(Bits[i]);
		if(i!=BIG_NUMBER_BITS_COUNT-1)
		{
			Result += ",";
		}
	}
	Result += "))";
	return Result;
}

void FBigDecimal::BigDecimalSerializeComponent(FString& DecimalString, FString& ZeroString, FString& BitsString) const
{
	//(Bits = (123,321,...,214))
	check(Bits.Num() ==BIG_NUMBER_BITS_COUNT)
	DecimalString.Reset();
	DecimalString += FString::FromInt(Decimal);
	ZeroString.Reset();
	ZeroString += FString::FromInt(static_cast<int32>(Zero));
	BitsString.Reset();
	BitsString += "(";
	for(int32 i=0;i<BIG_NUMBER_BITS_COUNT;i++)
	{
		BitsString += FString::FromInt(Bits[i]);
		if(i!=BIG_NUMBER_BITS_COUNT-1)
		{
			BitsString += ",";
		}
	}
	BitsString += ")";
}

bool FBigDecimal::Deserialize(const FString& A)
{
	if(A.IsEmpty())
	{
		return false;
	}
	if(Bits.Num()!=BIG_NUMBER_BITS_COUNT)
	{
		Bits.SetNumZeroed(BIG_NUMBER_BITS_COUNT);
	}
	Decimal = 0;
	Zero = 0;//Re-initial
	check(Bits.Num() ==BIG_NUMBER_BITS_COUNT)

	//(Decimal = 1234, Zero = 4, Bits = (123,321,...,))
	TArray<FString> Segments;
	A.ParseIntoArray(Segments,TEXT("="), true);
	for(int32 i=0;i<Segments.Num();i++)
	{
		FString CurrentSegment = Segments[i];
		if(CurrentSegment.Find("Decimal") >=0)
		{
			check(i < Segments.Num() - 1)
			FString NextSegment = Segments[i+1];
			const int32 CommaLocation = NextSegment.Find(",", ESearchCase::IgnoreCase, ESearchDir::FromEnd);
			if(CommaLocation > 0)
			{
				NextSegment = NextSegment.Left(CommaLocation);
			}
			Decimal = FCString::Atoi(*NextSegment);
		}
		else if(CurrentSegment.Find("Zero") >=0)
		{
			check(i < Segments.Num() - 1)
			FString NextSegment = Segments[i+1];
			const int32 CommaLocation = NextSegment.Find(",", ESearchCase::IgnoreCase, ESearchDir::FromEnd);
			if(CommaLocation > 0)
			{
				NextSegment = NextSegment.Left(CommaLocation);
			}
			const int32 TempZero = FCString::Atoi(*NextSegment);
			check(TempZero >= 0 && TempZero < BIG_NUMBER_MAX_DIGIT)
			Zero = static_cast<uint8>(TempZero);
		}
		else if(CurrentSegment.Find("Bits") >=0)
		{
			check(i < Segments.Num() - 1)
			FString NextSegment = Segments[i+1];
			const int32 CommaLocation = NextSegment.Find(",", ESearchCase::IgnoreCase, ESearchDir::FromEnd);
			if(CommaLocation > 0 && i + 1 != Segments.Num() - 1)
			{
				NextSegment = NextSegment.Left(CommaLocation);
			}
			//Deal with Bits
			FString ParenthesizedString = NextSegment;
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
			for(int32 j=0;j<BIG_NUMBER_BITS_COUNT;j++)
			{
				Bits[j] = FCString::Atoi(*Results[j]);
			}
		}
	}
	NormalizeDecimalAndZero();
	return true;
}
