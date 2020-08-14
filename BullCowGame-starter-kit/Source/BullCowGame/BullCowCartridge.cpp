// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
 
//include "Math/UnrealMathUtility.h" // ����� coreminimal.h �ȿ� ����
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
//	const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordtxtFile.txt");
//	FFileHelper::LoadFileToStringArray(Wordtxt, *WordListPath);  //���Ͽ��� �о���̱� ����
	//���� ���� �Ҷ����� Words �� ���Ѵٸ� setupgaem �� ���� ��
	Isograms = GetValidWords(Words);
	SetUpGame();//Setting up Game
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
} 

void UBullCowCartridge::SetUpGame() {
	HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num())];
	lives = HiddenWord.Len();	//typedef �� �����ؼ� int32�� int�� ������
	bGameOver = false;

	//	PrintLine(FW);	//�ܾ� ���� ���
	PrintLine(TEXT("Welcome to BullCow Game"));
	//PrintLine(TEXT("Guess the "+ FW +" letter word! ")); //Magin Number Remove!
	//TEXT �� FString �ۿ� �ȵ�. Magin Number�� �ϵ��ڵ��� ���ڿ� �׷��� ������

	PrintLine(TEXT("Guess the %i letter word! "), HiddenWord.Len());
	//FString::Printf() ���̵� ���� ������ �����. debug line���� ���ٽ���
	//������ FString::Printf �� ���� % ���� �����ڸ� ����� �� �ִµ�
	 //Prompt Player For Guess

	PrintLine(FString::Printf(TEXT("Debug: The HiddenWord is: %s\n and %i long "), *HiddenWord, HiddenWord.Len())); //Debug Line
	DebugFunction();
}

void UBullCowCartridge::DebugFunction() {	
	PrintLine(TEXT("The number of possible words is %i"), Words.Num()); 
	PrintLine(TEXT("The number of valid words is %i"), GetValidWords(Words).Num());
}
void UBullCowCartridge::EndGame() {
	if (lives <= 0)
	{
		++winRate.lose;
	}else {
		++winRate.win;
	}
	bGameOver = true;
}


void UBullCowCartridge::ProcessGuess(const FString& Guess) {
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


	//int32 Bulls, Cows;
	//������ �� �Ű������� �� ������ ���ϴ� �ֿ� ���� �� �ϳ�
	// ������ ���� �� �� �ִ�.
	FBullCowCount score = GetBullCows(Guess);

	PrintLine(TEXT("You %i Bulls %i Cows"), score.bulls, score.cows);
	PrintLine(TEXT("You remaining %i lives, guess again."), lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
	//int32 index = 0;
	//int32 comparison = index + 1;

	//for�������� ���ϱ� ������....
	//index - < Word.Len() �ص� �ȴ�.
	for (int32 index = 0; index < Word.Len(); index++) {
		for (int32 comparison = index + 1; comparison < Word.Len();++comparison) {
			if (Word[index] == Word[comparison])
				return false;
		}
	}
	return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
	TArray<FString> ValidWords;

	//�Ƹ� FString    
	for (auto Word : WordList) {
		if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word)) {
			ValidWords.Emplace(Word);
		}
	}
	return ValidWords;

}
FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
	FBullCowCount count;
	//bull= ���� ��ġ ���� �ܾ�
	//cow = �ٸ� ��ġ ���� �ܾ�
	for (int32 guessIndex = 0; guessIndex < Guess.Len(); ++guessIndex) {
		if (Guess[guessIndex] == HiddenWord[guessIndex]) {
			++count.bulls;
			continue;
		}
		for (int32 hiddenIndex = 0; hiddenIndex < HiddenWord.Len(); ++hiddenIndex) {
			if (Guess[guessIndex] == HiddenWord[hiddenIndex]) {
				++count.cows;
				break;
			}
		}
	}
	return count;
}
