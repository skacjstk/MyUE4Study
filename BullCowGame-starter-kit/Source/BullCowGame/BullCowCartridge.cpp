// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
	PrintLine(TEXT("Hello PrintLine\n"));
	PrintLine(TEXT("Guess the N letter word! ")); //Magin Number Remove!
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	ClearScreen();
	FString HiddenWord = TEXT("cake");	//Move outside this function 
	//PrintLine(Input);

	int32 HwLen = HiddenWord.Len();
	FString FW = FString::FromInt(HwLen);
	//PrintLine(FW);	//�ܾ� ���� ���
	if (Input.Equals(HiddenWord)) { // == �� �Ǵ°Ű���
		PrintLine(TEXT("You have Won!"));	
	}
	else
	{
		PrintLine(TEXT("You have Lost!"));
	}
	

} 