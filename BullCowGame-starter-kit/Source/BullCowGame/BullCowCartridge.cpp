// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
	
void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
	//welcoming player
	SetUpGame();//Setting up Game
	//PrintLine(FString::Printf(TEXT("The HiddenWord is: %s\n and %i long "), *HiddenWord,HiddenWord.Len())); //Debug Line
	//SetUpGame() 에 통합.
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	if (bGameOver) {	//게임오버 라면
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
	// Prompt To Play Again (다시시작을 받아들였음의 표시)
	//check user INput
	//PlayAgain Or Quit
} 

void UBullCowCartridge::SetUpGame() {
	HiddenWord = TEXT("cakes");	
	lives = 4;	//typedef 로 지정해서 int32는 int랑 같은데
	bGameOver = false;

	//	PrintLine(FW);	//단어 숫자 출력
	PrintLine(TEXT("Welcome to BullCow Game"));
	//PrintLine(TEXT("Guess the "+ FW +" letter word! ")); //Magin Number Remove!
	//TEXT 는 FString 밖에 안들어감. Magin Number는 하드코딩된 숫자에 그렇게 쓰더라구

	PrintLine(TEXT("Guess the %i letter word! "), HiddenWord.Len());
	//FString::Printf() 없이도 위의 문장이 실행됨. debug line에서 보다시피
	//원래는 FString::Printf 를 통해 % 형식 지정자를 사용할 수 있는데
	 //Prompt Player For Guess

}
void UBullCowCartridge::EndGame() {
	bGameOver = true;
}


void UBullCowCartridge::ProcessGuess(FString Guess) {
	//Checking PlayerGuess
//if(Input == HiddenWord)// == 도 되는거같음
	IsIsogram(Guess);
	if (Guess.Equals(HiddenWord)) {
		PrintLine(TEXT("You have Won!"));
		EndGame();
		return;
	}
	
	if (!IsIsogram(Guess)) {
		PrintLine(TEXT("No repeating letters, guess again!")); 
		//이 게임은 단어가 중복되지 않음 Magic number?
		return;
	}

	//if (IsIsogram) {
	//	PrintLine(TEXT("아무것도 입력하지 않았다. Guess any word"));
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

	//for문에서만 쓰니까 스코프....
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
//if(Input == HiddenWord)// == 도 되는거같음
	if (Guess.Equals(HiddenWord)) {
		PrintLine(TEXT("You have Won!"));
		EndGame();
		return;
	}
	else if (Guess == "") {
		PrintLine(TEXT("Guess any word"));
	}
	else //틀릴 때
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