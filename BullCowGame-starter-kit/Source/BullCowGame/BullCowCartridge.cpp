// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
	
void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

	//welcoming player
	SetUpGame();//Setting up Game
	FString FW = FString::FromInt(HiddenWord.Len());

	//	PrintLine(FW);	//�ܾ� ���� ���
	PrintLine(TEXT("Hello PrintLine"));
	PrintLine(TEXT("Guess the "+ FW +" letter word! ")); //Magin Number Remove!
	//TEXT �� FString �ۿ� �ȵ�. Magin Number�� �ϵ��ڵ��� ���ڿ� �׷��� ������
	
	//Prompt Player For Guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	ClearScreen();

	HiddenWord.Len();
	//Checking PlayerGuess

	if (Input.Equals(HiddenWord)) { // == �� �Ǵ°Ű���
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
	// Prompt To Play Again (�ٽý����� �޾Ƶ鿴���� ǥ��)
	//check user INput
	//PlayAgain Or Quit
} 

void UBullCowCartridge::SetUpGame() {
	HiddenWord = TEXT("cake");	
	lives = 4;	//typedef �� �����ؼ� int32�� int�� ������
	
}