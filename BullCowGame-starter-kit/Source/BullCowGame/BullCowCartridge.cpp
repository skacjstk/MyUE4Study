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
	bGameOver = true;
}


void UBullCowCartridge::ProcessGuess(FString Guess) {
	//Checking PlayerGuess
//if(Input == HiddenWord)// == �� �Ǵ°Ű���
	IsIsogram(Guess);
	if (Guess.Equals(HiddenWord)) {
		PrintLine(TEXT("You have Won!"));
		EndGame();
		return;
	}
	
	if (!IsIsogram(Guess)) {
		PrintLine(TEXT("No repeating letters, guess again!")); 
		//�� ������ �ܾ �ߺ����� ���� Magic number?
		return;
	}

	//if (IsIsogram) {
	//	PrintLine(TEXT("�ƹ��͵� �Է����� �ʾҴ�. Guess any word"));
	//}

	if (Guess.Len() != HiddenWord.Len()) {
		PrintLine(TEXT("The HiddenWord is %i charactor long"), HiddenWord.Len());
		PrintLine(TEXT("You remaining %i lives, try again."), lives);
		return;
	}

	//Remove Life
	PrintLine(TEXT("Lost a life!"));
	lives--;

	if (lives <= 0)	
	{
	//	PrintLine(TEXT("No more Life!\nYou have Lost!"));
		ClearScreen();
		PrintLine(TEXT("You have Lost!"));
		PrintLine(TEXT("HiddenWord was: %s"), *HiddenWord);
		PrintLine(TEXT("\nPress enter to play again"));
		EndGame();
		return;
	}

	PrintLine(TEXT("You remaining %i lives, guess again."), lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
	//int32 index = 0;
	//int32 comparison = index + 1;

	//for�������� ���ϱ� ������....
	for (int32 index = 0; index < Word.Len(); index++) {
		for (int32 comparison = index + 1; comparison < Word.Len();++comparison) {
			if (Word[index] == Word[comparison])
				return false;
		}
	}

	return true;

}

/*

void UBullCowCartridge::ProcessGuess(FString Guess) {
	//Checking PlayerGuess
//if(Input == HiddenWord)// == �� �Ǵ°Ű���
	if (Guess.Equals(HiddenWord)) {
		PrintLine(TEXT("You have Won!"));
		EndGame();
		return;
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
*/