// Fill out your copyright notice in the Description page of Project Settings.


#include "StringUtilities.h"

FString UStringUtilities::Hints = TEXT("");
FString UStringUtilities::EnglTran = TEXT("");
FString UStringUtilities::GermTran = TEXT("");

FString UStringUtilities::ConvertAsciiToChar(int32 AsciiValue)
{
	return FString::Chr(AsciiValue);
}

FString UStringUtilities::FindAndReplace(const FString& Source, const FString& Content, const FString& Pattern)
{
	// Check if the pattern is correct
	if (Pattern.Len() < 3 || !Pattern.Contains(TEXT(",")))
	{
		return Source;
	}

	FString PatternX = Pattern.Left(1);
	FString PatternY = Pattern.Right(1);

	// 1. Step: Try to find with Pattern X
	int32 IndexX = Source.Find(PatternX);

	// Pattern X found nothing, try to find with Pattern Y
	if (IndexX == INDEX_NONE) 
	{
		// 2. Step: Try to find with Pattern Y
		int32 IndexY = Source.Find(PatternY);

		// If nothing found, just return Source, possible it has been already replaced
		if (IndexY == INDEX_NONE)
		{
			return Source;
		}
		else // It has been found via Pattern Y
		{
			// Replace Pattern Y for Content and return
			return Source.Replace(*PatternY, *Content);
		}
	}
	else // It has been found via Pattern X
	{
		// Replace Pattern X for Content and return
		return Source.Replace(*PatternX, *Content);		
	}
}

FString UStringUtilities::GetCleanAnswer(const FString& InputString)
{
	// I've got 3 types of strings
	// A: "This is my sentence" [Answer]
	// B: "I go to the forest, Cat, Dog, Lamp" [Answer, Hint01, Hint02...]
	// C: "Sun, after, shines; Table, Pen; OtherStuff" [Answer; Hint01, Hint02; Other]
	FString Result;

	bool isVarC = InputString.Contains(TEXT(";"));
	bool isVarB =  !isVarC;

	// VarB
	if (isVarB && InputString.Split(TEXT(","), &Result, nullptr))
	{
		return Result;
	}

	// VarC
	if (InputString.Split(TEXT(";"), &Result, nullptr))
	{
		return Result.Replace(TEXT(","), TEXT(""));
	}

	// VarA
	return InputString;
}

void UStringUtilities::ExtractHintsAndEnglTran(const FString& InputString)
{
	// I've got 3 types of strings
	// A: "This is my sentence" [Answer]
	// B: "I go to the forest, Cat, Dog, Lamp" [Answer, Hint01, Hint02...]
	// C: "Sun, after, shines; Table, Pen; OtherStuff" [Answer; Hint01, Hint02; Other]

	bool isVarC = InputString.Contains(TEXT(";"));
	bool isVarB = !isVarC && InputString.Contains(TEXT(","));
	bool isVarA = !isVarB && !isVarC;

	if (isVarA)
	{
		return;
	}

	if (isVarB)
	{
		InputString.Split(TEXT(","), nullptr, &Hints, 
			ESearchCase::IgnoreCase, ESearchDir::FromStart);
		return;
	}

	FString HintsAndOtherText;
	InputString.Split(TEXT(";"), &EnglTran, &HintsAndOtherText,
		ESearchCase::IgnoreCase, ESearchDir::FromStart);
	HintsAndOtherText.Split(TEXT(";"), &GermTran, &HintsAndOtherText,
		ESearchCase::IgnoreCase, ESearchDir::FromStart);
	HintsAndOtherText.Split(TEXT(";"), nullptr, &Hints,
		ESearchCase::IgnoreCase, ESearchDir::FromStart);
}

FString UStringUtilities::GetHints()
{
	return Hints;
}

FString UStringUtilities::GetGermTran()
{
	return GermTran;
}

void UStringUtilities::GetFromGermToEngl(TMap<FString, FString>& OutMap)
{
	FString Hint;
	FString EnglWord;
	FString LocGermTran = GermTran;
	while (LocGermTran.Split(TEXT(","), &Hint, &LocGermTran,
		ESearchCase::IgnoreCase, ESearchDir::FromStart))
	{
		EnglTran.Split(TEXT(","), &EnglWord, &EnglTran, 
		ESearchCase::IgnoreCase, ESearchDir::FromStart);
		OutMap.Add(Hint.TrimStartAndEnd(), EnglWord.TrimStartAndEnd());
	}

	OutMap.Add(LocGermTran.TrimStartAndEnd(), EnglTran.TrimStartAndEnd());
}
