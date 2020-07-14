// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
	HiddenWord = TEXT("cake");
	int32 HwLen = HiddenWord.Len();
	FString FW = FString::FromInt(HwLen);
	//	PrintLine(FW);	//�ܾ� ���� ���
	PrintLine(TEXT("Hello PrintLine"));
	PrintLine(TEXT("Guess the "+ FW +" letter word! ")); //Magin Number Remove!
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	ClearScreen();


	if (Input.Equals(HiddenWord)) { // == �� �Ǵ°Ű���
		PrintLine(TEXT("You have Won!"));	
	}
	else
	{
		PrintLine(TEXT("You have Lost!"));
	}
	

} 