// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
	
void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
	//welcoming player
	SetUpGame();//Setting up Game
	//PrintLine(FString::Printf(TEXT("The HiddenWord is: %s\n and %i long "), *HiddenWord,HiddenWord.Len())); //Debug Line
	//SetUpGame() �� ����.
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	if (bGameOver) {	//���ӿ��� ���
		ClearScreen();
		SetUpGame();
	}
	else {
		ProcessGuess(Input);
	}

	//rest 0724

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
	HiddenWord = TEXT("cakes");	
	lives = 4;	//typedef �� �����ؼ� int32�� int�� ������
	bGameOver = false;

	//	PrintLine(FW);	//�ܾ� ���� ���
	PrintLine(TEXT("Welcome to BullCow Game"));
	//PrintLine(TEXT("Guess the "+ FW +" letter word! ")); //Magin Number Remove!
	//TEXT �� FString �ۿ� �ȵ�. Magin Number�� �ϵ��ڵ��� ���ڿ� �׷��� ������

	PrintLine(TEXT("Guess the %i letter word! "), HiddenWord.Len());
	//FString::Printf() ���̵� ���� ������ �����. debug line���� ���ٽ���
	//������ FString::Printf �� ���� % ���� �����ڸ� ����� �� �ִµ�
	 //Prompt Player For Guess
}
void UBullCowCartridge::EndGame() {
	PrintLine(TEXT("Press enter to play again"));	
	bGameOver = true;
}

void UBullCowCartridge::ProcessGuess(FString Guess) {
	//Checking PlayerGuess
//if(Input == HiddenWord)// == �� �Ǵ°Ű���
	if (Guess.Equals(HiddenWord)) {
		PrintLine(TEXT("You have Won!"));
		EndGame();
	}
	else if (Guess == "") {
		PrintLine(TEXT("Guess any word"));
	}
	else //Ʋ�� ��
	{
		lives--;
		PrintLine(TEXT("Lost a life!"));
		if (lives > 0)
		{
			if (Guess.Len() != HiddenWord.Len()) {
				PrintLine(TEXT("The HiddenWord is %i charactor long"), HiddenWord.Len());
			}
			PrintLine(TEXT("You remaining %i lives, try again."), lives);

		}
		else {
			PrintLine(TEXT("You have Lost!"));
			EndGame();
		}
	}
}