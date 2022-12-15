// Copyright 2022 Suika Studio. All Rights Reserved.
#pragma once
#include <array>

#include "BigInteger.h"
#include "BigDecimal.h"
#include "BigNumberBPLibrary.generated.h"

UCLASS()
class UBigNumberBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	static constexpr int32 Digits[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
	static constexpr uint32 UZero32 = 0x00000000; 
	static constexpr uint32 UMax32 = 0xffffffff; 
	static constexpr int64 U32Mask = 0x00000000ffffffff; 
	UFUNCTION(BlueprintPure, meta = (DisplayName = "NumDigitOf(I32)", Keywords = "Num, Digit, Int32", CompactNodeTitle = "Digit", BlueprintAutocast), Category = "BigNumber|Integer")
	static int32 NumDigitOfInt32(int32 A);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "NumDigitOf(I64)", Keywords = "Num, Digit, Int64", CompactNodeTitle = "Digit", BlueprintAutocast), Category = "BigNumber|Integer")
	static int32 NumDigitOfInt64(int64 A);

	template<int32 Bits, bool bSigned>
	static int32 NumDigitOfAny(TBigInt<Bits, bSigned> A);
	
	template<int32 Bits, bool bSigned>
	static TBigInt<Bits, bSigned> RemoveTailZeroOfAny(TBigInt<Bits, bSigned> A);
	/*Big Int Conversion*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From(I32)", Keywords = "Conversion, From, Make, Create, Int32, Big, Int", CompactNodeTitle = "I32->BI", BlueprintAutocast), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerFromInt32(int32 A);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "From(I64)", Keywords = "Conversion, From, Make, Create, Int64, Big, Int", CompactNodeTitle = "I64->BI", BlueprintAutocast), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerFromInt64(int64 A);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From(StrDec,Pure)", Keywords = "Conversion, From, Make, Create, Int32, Big, Int", CompactNodeTitle = "Dec->BI", BlueprintAutocast), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerFromStringPure(FString A);//Pass, can accept negative number
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From(StrDec,ABC)", Keywords = "Conversion, From, Make, Create, Int32, Big, Int", CompactNodeTitle = "ABC->BI"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerFromString(FString A);//Todo, free form
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From(DigitMark)", Keywords = "Conversion, From, Make, Create, Int32, Big, Int"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerFromSingleString(FString A);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To(I32)", Keywords = "Conversion, To, Int32, Big, Int", CompactNodeTitle = "BI->I32", BlueprintAutocast), Category = "BigNumber|Integer")
	static int32 BigIntegerToInt32(FBigInteger A);//Pass but better not use this
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To(I64)", Keywords = "Conversion, To, Int64, Big, Int", CompactNodeTitle = "BI->I64", BlueprintAutocast), Category = "BigNumber|Integer")
	static int64 BigIntegerToInt64(FBigInteger A);//Pass but better not use this
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To(StrHex)", Keywords = "Conversion, To, String, Big, Int", CompactNodeTitle = "BI->Hex"), Category = "BigNumber|Integer")
	static FString BigIntegerToStringHex(FBigInteger A);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To(StrDec)", Keywords = "Conversion, To, String, Big, Int", CompactNodeTitle = "BI->Dec", BlueprintAutocast), Category = "BigNumber|Integer")
	static FString BigIntegerToStringDec(FBigInteger A);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To(S-ABC)", Keywords = "Conversion, To, String, Big, Int", CompactNodeTitle = "BI->ABC"), Category = "BigNumber|Integer")
	static FString BigIntegerToStringABC(FBigInteger A);//Pass
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "To(S-FA)", Keywords = "Conversion, To, String, Big, Int"), Category = "BigNumber|Integer")
	static FString BigIntegerToStringFA(FBigInteger A, int Digit = 8);//Todo

	/*Big Int operation*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add(BI)", Keywords = "Add, Big, Int, +", CompactNodeTitle = "+", CommutativeAssociativeBinaryOperator = "true"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerAddBigInteger(FBigInteger A, FBigInteger B);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Sub(BI)", Keywords = "Subtract, Big, Int, -", CompactNodeTitle = "-"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerSubtractBigInteger(FBigInteger A, FBigInteger B);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Mul(BI)", Keywords = "Mul, Big, Int, *", CompactNodeTitle = "×", CommutativeAssociativeBinaryOperator = "true"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerMultiplyBigInteger(FBigInteger A, FBigInteger B);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Div(BI)", Keywords = "Div, Big, Int, /", CompactNodeTitle = "÷"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerDivideBigInteger(FBigInteger A, FBigInteger B);//Pass
	//Compare
	UFUNCTION(BlueprintPure, meta = (DisplayName = "==(BI)", Keywords = "Equal, Big, Int, =, ==", CompactNodeTitle = "=="), Category = "BigNumber|Integer")
	static bool BigIntegerEqualBigInteger(FBigInteger A, FBigInteger B);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "!=(BI)", Keywords = "Not Equal, Big, Int, =, !=", CompactNodeTitle = "!="), Category = "BigNumber|Integer")
	static bool BigIntegerNotEqualBigInteger(FBigInteger A, FBigInteger B);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = ">(BI)", Keywords = "Bigger, Big, Int, >, Larger, Greater", CompactNodeTitle = ">"), Category = "BigNumber|Integer")
	static bool BigIntegerLargerBigInteger(FBigInteger A, FBigInteger B);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = ">=(BI)", Keywords = "Bigger, Big, Int, >, =, >=, Larger, Greater, Or, Equal", CompactNodeTitle = ">="), Category = "BigNumber|Integer")
	static bool BigIntegerLargerOrEqualBigInteger(FBigInteger A, FBigInteger B);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "<(BI)", Keywords = "Less, Big, Int, <", CompactNodeTitle = "<"), Category = "BigNumber|Integer")
	static bool BigIntegerLessBigInteger(FBigInteger A, FBigInteger B);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "<=(BI)", Keywords = "Less, Big, Int, <, =, <=, Or, Equal", CompactNodeTitle = "<="), Category = "BigNumber|Integer")
	static bool BigIntegerLessOrEqualBigInteger(FBigInteger A, FBigInteger B);//Pass
	//Flip
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Flip(BI)", Keywords = "Flip, Big, Int, -", CompactNodeTitle = "Flip"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerFlipBigInteger(FBigInteger A);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "bIsNegative(BI)", Keywords = "Negative, Big, Int", CompactNodeTitle = "IsNeg?"), Category = "BigNumber|Integer")
	static bool bBigIntegerIsNegativeBigInteger(FBigInteger A);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Abs(BI)", Keywords = "Abs, Big, Int, |", CompactNodeTitle = "Abs"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerAbsBigInteger(FBigInteger A);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Pow(BI)", Keywords = "Pow, Big, Int", CompactNodeTitle = "Pow"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerPowerBigInteger(FBigInteger A, FBigInteger B);//Pass
	/*Big Int , int32 operation*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add(BI,I32)", Keywords = "Add, Big, Int, Int32, +", CompactNodeTitle = "+"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerAddBigIntegerBy32(FBigInteger A, int32 B);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Sub(BI,I32)", Keywords = "Subtract, Big, Int, Int32, -", CompactNodeTitle = "-"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerSubtractBigIntegerBy32(FBigInteger A, int32 B);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Mul(BI,I32)", Keywords = "Mul, Big, Int, Int32, *", CompactNodeTitle = "×"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerMultiplyBigIntegerBy32(FBigInteger A, int32 B);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Div(BI,I32)", Keywords = "Div, Big, Int, Int32, /", CompactNodeTitle = "÷"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerDivideBigIntegerBy32(FBigInteger A, int32 B);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Pow(BI,I32)", Keywords = "Pow, Big, Int", CompactNodeTitle = "Pow"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerPowerBigIntegerBy32(FBigInteger A, int32 B);//Pass
	/*Big Int , int64 operation*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add(BI,I64)", Keywords = "Add, Big, Int, Int64, +", CompactNodeTitle = "+"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerAddBigIntegerBy64(FBigInteger A, int64 B);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Sub(BI,I64)", Keywords = "Subtract, Big, Int, Int64, -", CompactNodeTitle = "-"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerSubtractBigIntegerBy64(FBigInteger  A, int64 B);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Mul(BI,I64)", Keywords = "Mul, Big, Int, Int64, *", CompactNodeTitle = "×"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerMultiplyBigIntegerBy64(FBigInteger A, int64 B);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Div(BI,I64)", Keywords = "Div, Big, Int, Int64, /", CompactNodeTitle = "÷"), Category = "BigNumber|Integer")
	static FBigInteger BigIntegerDivideBigIntegerBy64(FBigInteger A, int64 B);//Pass

	//Todo BI +-*/ Float
	//Todo Mod
	
	///
	/*Big Decimal Conversion*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From(I32)", Keywords = "Conversion, From, Make, Create, Int32, Big, Decimal, Float, Double", CompactNodeTitle = "I32->BD", BlueprintAutocast), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalFromInt32(int32 A);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From(I64)", Keywords = "Conversion, From, Make, Create, Int64, Big, Decimal, Float, Double", CompactNodeTitle = "I64->BD", BlueprintAutocast), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalFromInt64(int64 A);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "From(BI)", Keywords = "Conversion, From, Make, Create, Integer, BI, Big, Decimal, Float, Double", CompactNodeTitle = "BI->BD", BlueprintAutocast), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalFromBigInteger(FBigInteger A);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From(F)", Keywords = "Conversion, From, Make, Create, Float, Big, Decimal, Float, Double", CompactNodeTitle = "F->BD", BlueprintAutocast), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalFromFloat(float A);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "From(StrDec,Pure)", Keywords = "Conversion, From, Make, Create, String, Dec, Big, Decimal, Float, Double", CompactNodeTitle = "Dec->BD", BlueprintAutocast), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalFromStringPure(FString A);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "From(StrDec,ABC)", Keywords = "Conversion, From, Make, Create, Int32, Big, Decimal, Float, Double", CompactNodeTitle = "ABC->BD"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalFromString(FString A);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To(I32)", Keywords = "Conversion, To, Int32, Big, Decimal, Float, Double", CompactNodeTitle = "BD->I32", BlueprintAutocast), Category = "BigNumber|Decimal")
	static int32 BigDecimalToInt32(FBigDecimal A);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To(I64)", Keywords = "Conversion, To, Int64, Big, Decimal, Float, Double", CompactNodeTitle = "BD->I64", BlueprintAutocast), Category = "BigNumber|Decimal")
	static int64 BigDecimalToInt64(FBigDecimal A);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To(F)", Keywords = "Conversion, To, Float, Big, Decimal, Float, Double", CompactNodeTitle = "BD->F", BlueprintAutocast), Category = "BigNumber|Decimal")
	static float BigDecimalToFloat(FBigDecimal A);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To(BI)", Keywords = "Conversion, To, Integer, BI, Big, Decimal, Float, Double", CompactNodeTitle = "BD->BI", BlueprintAutocast), Category = "BigNumber|Decimal")
	static FBigInteger BigDecimalToBigInteger(FBigDecimal A);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To(StrHex)", Keywords = "Conversion, To, String, Big, Decimal, Float, Double", CompactNodeTitle = "BD->Hex"), Category = "BigNumber|Decimal")
	static FString BigDecimalToStringHex(FBigDecimal A);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To(StrDec)", Keywords = "Conversion, To, String, Big, Decimal, Float, Double", CompactNodeTitle = "BD->Dec", BlueprintAutocast), Category = "BigNumber|Decimal")
	static FString BigDecimalToStringDec(FBigDecimal A);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To(S-ABC)", Keywords = "Conversion, To, String, Big, Decimal, Float, Double", CompactNodeTitle = "BD->ABC"), Category = "BigNumber|Decimal")
	static FString BigDecimalToStringABC(FBigDecimal A);//Pass
	//Todo
	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "To(S-FA)", Keywords = "Conversion, To, String, Big, Decimal"), Category = "BigNumber|Decimal")
	//static FString BigDecimalToStringFA(const FBigDecimal& A, int Digit = 8);

	//Flip
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Flip(BD)", Keywords = "Flip, Big, Decimal, -, Float, Double", CompactNodeTitle = "Flip"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalFlipBigDecimal(FBigDecimal A);//Pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "bIsNegative(BD)", Keywords = "Negative, Big, Decimal, Float, Double", CompactNodeTitle = "IsNeg?"), Category = "BigNumber|Decimal")
	static bool bBigDecimalIsNegativeBigDecimal(FBigDecimal A);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "bIsZero(BD)", Keywords = "Zero, Big, Decimal, Float, Double", CompactNodeTitle = "Is0?"), Category = "BigNumber|Decimal")
	static bool bBigDecimalIsZeroBigDecimal(FBigDecimal A);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Abs(BD)", Keywords = "Abs, Big, Decimal, |, Float, Double", CompactNodeTitle = "Abs"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalAbsBigDecimal(FBigDecimal A);
	
	static void DecimalAdd(int32 A, int32 B, uint8 AZeros, uint8 BZeros, int32& Result, uint8& ZeroResult, int32& CarryResult);//Pass? Maybe, 1.000234 Not Pass Cuz int cant store 000234
	static int32 DecimalInverse(int32 Decimal, uint8 Zeros);//Pass? Maybe
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add(BD)", Keywords = "Add, Big, Decimal, +, Float, Double", CompactNodeTitle = "+", CommutativeAssociativeBinaryOperator = "true"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalAddBigDecimal(FBigDecimal A, FBigDecimal B);//Pass? Maybe

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Sub(BD)", Keywords = "Subtract, Big, Decimal, -, Float, Double", CompactNodeTitle = "-"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalSubtractBigDecimal(FBigDecimal A, FBigDecimal B);//If add pass then this pass

	template<int32 AugBits = 64>//Positive Number only
	static TBigInt<BIG_NUMBER_BITS + AugBits, false> AugmentBigInteger(const BigInt& A);
	
	template<int32 SourceAugBits = 64>//Positive Number only
	static BigInt ReduceBigInteger(const TBigInt<BIG_NUMBER_BITS + SourceAugBits, false>& A);
	
	static BigInt AugmentDecimalPart(int32 A, uint8 AZeros, int32 AugTo = 10);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Mul(BD)", Keywords = "Mul, Big, Decimal, *, Float, Double", CompactNodeTitle = "×", CommutativeAssociativeBinaryOperator = "true"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalMultiplyBigDecimal(FBigDecimal A, FBigDecimal B);//Hard

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Div(BD)", Keywords = "Div, Big, Decimal, /, Float, Double", CompactNodeTitle = "÷"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalDivideBigDecimal(FBigDecimal A, FBigDecimal B);
	//Todo BD +-*/ BI
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add(BD,BI)", Keywords = "Add, Big, Decimal, Integer, +, Float, Double", CompactNodeTitle = "+"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalAddBigInteger(FBigDecimal A, FBigInteger B);//If BD +-*/ pass then this pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Sub(BD,BI)", Keywords = "Subtract, Big, Decimal, Integer, -, Float, Double", CompactNodeTitle = "-"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalSubtractBigInteger(FBigDecimal A, FBigInteger B);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Mul(BD,BI)", Keywords = "Mul, Big, Decimal, Integer, *, Float, Double", CompactNodeTitle = "×"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalMultiplyBigInteger(FBigDecimal A, FBigInteger B);//If BD +-*/ pass then this pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Div(BD,BI)", Keywords = "Div, Big, Decimal, Integer, /, Float, Double", CompactNodeTitle = "÷"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalDivideBigInteger(FBigDecimal A, FBigInteger B);
	//Todo BD +-*/ I32
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add(BD,I32)", Keywords = "Add, Big, Decimal, Integer, int32, +, Float, Double", CompactNodeTitle = "+"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalAddInt32(FBigDecimal A, int32 B);//If BD +-*/ pass then this pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Sub(BD,I32)", Keywords = "Subtract, Big, Decimal, Integer, int32, -, Float, Double", CompactNodeTitle = "-"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalSubtractInt32(FBigDecimal A, int32 B);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Mul(BD,I32)", Keywords = "Mul, Big, Decimal, Integer, int32, *, Float, Double", CompactNodeTitle = "×"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalMultiplyInt32(FBigDecimal A, int32 B);//If BD +-*/ pass then this pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Div(BD,I32)", Keywords = "Div, Big, Decimal, Integer, int32, /, Float, Double", CompactNodeTitle = "÷"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalDivideInt32(FBigDecimal A, int32 B);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Div(I32,BD)", Keywords = "Div, Big, Decimal, Integer, int32, /, Float, Double", CompactNodeTitle = "÷"), Category = "BigNumber|Decimal")
	static FBigDecimal Int32DivideBigDecimal(int32 A, FBigDecimal B);
	//Todo BD +-*/ I64
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add(BD,I64)", Keywords = "Add, Big, Decimal, Integer, int64, +, Float, Double", CompactNodeTitle = "+"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalAddInt64(FBigDecimal A, int64 B);//If BD +-*/ pass then this pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Sub(BD,I64)", Keywords = "Subtract, Big, Decimal, Integer, int64, -, Float, Double", CompactNodeTitle = "-"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalSubtractInt64(FBigDecimal A, int64 B);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Mul(BD,I64)", Keywords = "Mul, Big, Decimal, Integer, int64, *, Float, Double", CompactNodeTitle = "×"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalMultiplyInt64(FBigDecimal A, int64 B);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Div(BD,I64)", Keywords = "Div, Big, Decimal, Integer, int64, /, Float, Double", CompactNodeTitle = "÷"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalDivideInt64(FBigDecimal A, int64 B);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Div(I64, BD)", Keywords = "Div, Big, Decimal, Integer, int64, /, Float, Double", CompactNodeTitle = "÷"), Category = "BigNumber|Decimal")
	static FBigDecimal Int64DivideBigDecimal(int64 A, FBigDecimal B);

	//Todo BD +-*/ Float
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add(BD,F)", Keywords = "Add, Big, Decimal, +, Float, Double", CompactNodeTitle = "+"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalAddFloat(FBigDecimal A, float B);//If BD +-*/ pass then this pass

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Sub(BD,F)", Keywords = "Subtract, Big, Decimal, -, Float, Double", CompactNodeTitle = "-"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalSubtractFloat(FBigDecimal A, float B);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Mul(BD,F)", Keywords = "Mul, Big, Decimal, *, Float, Double", CompactNodeTitle = "×"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalMultiplyFloat(FBigDecimal A, float B);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Div(BD,F)", Keywords = "Div, Big, Decimal, /, Float, Double", CompactNodeTitle = "÷"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalDivideFloat(FBigDecimal A, float B);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Div(F,BD)", Keywords = "Div, Big, Decimal, /, Float, Double", CompactNodeTitle = "÷"), Category = "BigNumber|Decimal")
	static FBigDecimal FloatDivideBigDecimal(float A, FBigDecimal B);
	//Todo: Comparison
	UFUNCTION(BlueprintPure, meta = (DisplayName = "==(BD)", Keywords = "Equal, Big, Decimal, =, ==, Float, Double", CompactNodeTitle = "=="), Category = "BigNumber|Decimal")
	static bool BigDecimalEqualBigDecimal(FBigDecimal A, FBigDecimal B);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "!=(BD)", Keywords = "Not Equal, Big, Decimal, =, !=, Float, Double", CompactNodeTitle = "!="), Category = "BigNumber|Decimal")
	static bool BigDecimalNotEqualBigDecimal(FBigDecimal A, FBigDecimal B);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = ">(BD)", Keywords = "Bigger, Big, Decimal, >, Larger, Greater, Float, Double", CompactNodeTitle = ">"), Category = "BigNumber|Decimal")
	static bool BigDecimalLargerBigDecimal(FBigDecimal A, FBigDecimal B);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = ">=(BD)", Keywords = "Bigger, Big, Decimal, >, =, >=, Larger, Greater, Or, Equal, Float, Double", CompactNodeTitle = ">="), Category = "BigNumber|Decimal")
	static bool BigDecimalLargerOrEqualBigDecimal(FBigDecimal A, FBigDecimal B);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "<(BD)", Keywords = "Less, Big, Decimal, <, Float, Double", CompactNodeTitle = "<"), Category = "BigNumber|Decimal")
	static bool BigDecimalLessBigDecimal(FBigDecimal A, FBigDecimal B);//Pass
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "<=(BD)", Keywords = "Less, Big, Decimal, <, =, <=, Or, Equal, Float, Double", CompactNodeTitle = "<="), Category = "BigNumber|Decimal")
	static bool BigDecimalLessOrEqualBigDecimal(FBigDecimal A, FBigDecimal B);//Pass
	//Others
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Sqrt(BD)", Keywords = "Sqaure Root, Big, Decimal, Float, Double", CompactNodeTitle = "Sqrt"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalSquareRoot(FBigDecimal A);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Rec(BD)", Keywords = "Rec, Reciprocal, F1, Big, Decimal, /, Float, Double", CompactNodeTitle = "F1"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalReciprocal(FBigDecimal A);
	UFUNCTION(BlueprintPure, meta = (DisplayName = "RecF2(BD)", Keywords = "RecF2, Reciprocal, F2, Big, Decimal, /, Float, Double", CompactNodeTitle = "F2"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalReciprocalF2(FBigDecimal A);

	/*
	static FBigDecimal BigDecimalSimpson(FBigDecimal A, FBigDecimal B, int32 Flag);
	static FBigDecimal BigDecimalASR(FBigDecimal A, FBigDecimal B, FBigDecimal Eps, FBigDecimal AA, int32 Flag);
	static FBigDecimal BigDecimalASR(FBigDecimal A, FBigDecimal B, FBigDecimal Eps, int32 Flag);
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Pow(BD,I32)", Keywords = "Pow, Big, Decimal, Integer, int32, Float, Double", CompactNodeTitle = "Pow"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalPowInt32(FBigDecimal A, int32 B);

	//Todo Ln,exp,log10,log2..
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Ln(BD)", Keywords = "Ln, Big, Decimal, Log, LogE, Float, Double", CompactNodeTitle = "Ln"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalLn(FBigDecimal A);

	/*
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Exp(BD)", Keywords = "Exp, Big, Decimal, E, Pow, Float, Double", CompactNodeTitle = "Exp"), Category = "BigNumber|Decimal")
	static FBigDecimal BigDecimalExp(FBigDecimal A);
	*/
	//Todo FMod
};
