// assg1_Q_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<string>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<iostream>
#include <algorithm>

using namespace std;

// function for reading the text file
 #include<fstream>
 void fread(string fname, string words[], const int & nwords)
 // returns the read string of words
 // make sure that you give full path of file to be read
 // nwords will contain total number of read words
 // words will contain array of read words
 {
	ifstream ifile(fname.c_str(), ios::in);
	 if (!ifile)
		 {
		 cout << " Couldn’t read the file " << fname;
		 exit(-1);
		 }
	
		 int count = 0;
	 while (ifile && count < nwords)
		 ifile >> words[count++];
	 ifile.close();
	 }

 // ASCII art for Hangman as an array of strings
  char *hangman[19] = { 
	  " ___________.._______",
	  "| .__________))______|",
	  "| | / /      ||",
	  "| |/ /       ||",
	  "| | /        ||.-’’.",
	  "| |/         |/  _  \\",
	  "| |          ||  `/,|",
	  "| |          (\\\\`_.’",
	  "| |         .-`--’.",
	  "| |        /Y . . Y\\",
	  "| |       // |   | \\\\",
	  "| |      //  | . |  \\\\",
	  "| |     ’)   |   |   (`",
	  "| |	     ||’||",
	  "| |	     || ||",
	  "| |	     || ||",
	  "| |	     || ||",
	  "| |	    / | | \\",
	  "	 |_`-’  `-’ | |" };


int main()
{
	
	const  int nwords = 4000;
	string words[nwords];
	int randNum;
	srand(time(NULL));
	fread("1-4000.txt", words, nwords);
	
	int WordToGuessLength = 0;
	char * WordToGuess = NULL;
	char * WordToGuessForUser = NULL;

	randNum = rand() % 4000;
	WordToGuess = _strdup(words[randNum].c_str());
	WordToGuessForUser = _strdup(words[randNum].c_str());

	cout << WordToGuess <<endl;
	
	WordToGuessLength = strlen(WordToGuess);

	int * MissingLettersIndexArray = new int[WordToGuessLength];
	int RandNumForMissing = 0;	
	//For Shuffling Array
	for (int i = 0; i<WordToGuessLength; i++)
	{
		MissingLettersIndexArray[i] = i;
	}
	
	std::random_shuffle(MissingLettersIndexArray, MissingLettersIndexArray + WordToGuessLength);

	int HideCharLength = 2 * (WordToGuessLength / 3);

	/*for (int i = 0; i<WordToGuessLength; i++)
	{
		cout << MissingLettersIndexArray[i] << endl;
	}*/

	//cout << "==========" << endl;

	for (int i = 0; i<HideCharLength; i++)
	{
		WordToGuessForUser[MissingLettersIndexArray[i]] = '_';
		//cout << MissingLettersIndexArray[i] << endl;
	}
		
	cout << "Guess It =";

	for (int i =0;i<WordToGuessLength;i++)
	{
		cout << WordToGuessForUser[i] << " ";
	}
	
	char CharGuessByUser = '\0';
	int NumOfGuessedCharByUser = 0;

	int indexFound = -1;
	int NumOfTurn = HideCharLength * 2;
	
	//////////////////////
	int current_index = 0;
	int wrong_jump = 0;
	int remaining_jump = 0;
	int jump_result_divide = 0;
	int hangman_lenght = 19;
	int HangmanHeightToShow = HideCharLength * 2;
	int MissedTurnLoopLength = 0;

	//if lenght of the word is less then hangman lenght
	if (HangmanHeightToShow	<	hangman_lenght)
	{
		jump_result_divide = hangman_lenght / HangmanHeightToShow;
	}
	//if lenght of the word is greater then hangman lenght
	else
	{
		jump_result_divide = HangmanHeightToShow / hangman_lenght;
	}
	
	for (int i = 0;i < HideCharLength * 2;i++)
	{ 
		indexFound = -1;
		cout << "\nGuess Any Character =";
		cin >> CharGuessByUser;

		for (int j = 0;j < HideCharLength;j++)
		{
			if (CharGuessByUser == WordToGuess[MissingLettersIndexArray[j]])
			{
				indexFound = MissingLettersIndexArray[j];
				break;
			}
		}

		if (indexFound >= 0)	//Found
		{
			i--;
			NumOfGuessedCharByUser++;
			WordToGuessForUser[indexFound] = WordToGuess[indexFound];  
			cout << "Hurrah You Guessed it !!!!!!!!!!!!!" << endl;
		}
		else
		{
			NumOfTurn--;
			cout << "Alas You Missed it !!!!!!!!!!!!!" << endl;
			cout << endl << endl ;
			
			MissedTurnLoopLength += jump_result_divide;

			for (int current_index = 0; current_index < MissedTurnLoopLength; current_index++)
			{
				cout <<"\t\t\t"<< hangman[current_index] << endl;
			}

			cout << endl << endl ;
		}

		
		cout << "Remaining Turns are =" << NumOfTurn << endl;

		for (int k = 0;k < WordToGuessLength;k++)
		{
			cout << WordToGuessForUser[k] << " ";
		}

		if (NumOfGuessedCharByUser == HideCharLength)
		{
			cout << " \nHurrah You Guessed the WORD \n You are Genious !!!!!!!!!!!!!" << endl;
			break;
		}
		else if (i == HangmanHeightToShow-1)
		{
			for (int current_index = 0; current_index < hangman_lenght; current_index++)
			{
				cout << "\t\t\t" << hangman[current_index] << endl;
			}
		}


	}
	
	_getch();
	return 0;
}