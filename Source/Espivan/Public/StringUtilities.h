// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StringUtilities.generated.h"

/**
 * 
 */
UCLASS()
class ESPIVAN_API UStringUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "String Utilities", meta = (CompactNodeTitle = "->"))
	static FString ConvertAsciiToChar(int32 AsciiValue);
	
	UFUNCTION(BlueprintPure, Category = "String Utilities")
    static FString FindAndReplace(const FString& Source, const FString& Content, 
    		const FString& Pattern = TEXT("1,2"));

	UFUNCTION(BlueprintPure, Category = "String Utilities")
	static FString GetCleanAnswer(const FString& InputString);

	UFUNCTION(BlueprintCallable, Category = "String Utilities")
	static void ExtractHintsAndEnglTran(const FString& InputString);
	
	UFUNCTION(BlueprintPure, Category = "String Utilities")
	static FString GetHints();

	UFUNCTION(BlueprintPure, Category = "String Utilities")
	static FString GetGermTran();

	UFUNCTION(BlueprintPure, Category = "String Utilities")
	static void GetFromGermToEngl(TMap<FString, FString>& OutMap);

private:
	static FString Hints;
	static FString EnglTran;
	static FString GermTran;
};
