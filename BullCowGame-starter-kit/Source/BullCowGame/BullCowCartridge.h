// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 bulls = 0;
	int32 cows = 0;
};

struct PerOfVictory
{
	int32 win = 0;
	int32 lose = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetUpGame();
	void EndGame();
	void ProcessGuess(const FString& Guess);
	bool IsIsogram(const FString& Word) const;
	TArray<FString> GetValidWords(const TArray<FString>& WordList) const;
	FBullCowCount GetBullCows(const FString& Guess) const;
	void DebugFunction();

	// Your declarations go below!
	private:
	FString HiddenWord;
	TArray<FString> Wordtxt;
	int32 lives;
	bool bGameOver;
	TArray<FString> Isograms;
	PerOfVictory winRate;
};
