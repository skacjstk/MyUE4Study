// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
	
void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

	//welcoming player
	SetUpGame();//Setting up Game
	FString FW = FString::FromInt(HiddenWord.Len());

	//	PrintLine(FW);	//단어 숫자 출력
	PrintLine(TEXT("Hello PrintLine"));
	PrintLine(TEXT("Guess the "+ FW +" letter word! ")); //Magin Number Remove!
	//TEXT 는 FString 밖에 안들어감. Magin Number는 하드코딩된 숫자에 그렇게 쓰더라구
	
	//Prompt Player For Guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	ClearScreen();

	HiddenWord.Len();
	//Checking PlayerGuess

	if (Input.Equals(HiddenWord)) { // == 도 되는거같음
		PrintLine(TEXT("You have Won!"));	
	}
	else
	{
		PrintLine(TEXT("You have Lost!"));

	}

	//Check If Isogram
	//Prompt To guess again	
	//Check Right number of characters
	//prompt to guess again

	//remove Life

	//Check If Lives > 0
	//If Yes PlayAgain
	//show Lives left
	//If No Show GameOver and HiddenWord?
	// Prompt To Play Again (다시시작을 받아들였음의 표시)
	//check user INput
	//PlayAgain Or Quit
} 

void UBullCowCartridge::SetUpGame() {
	HiddenWord = TEXT("cake");	
	lives = 4;	//typedef 로 지정해서 int32는 int랑 같은데
	
}