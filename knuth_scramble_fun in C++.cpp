// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

// Scramble the letters of this string randomly
void permute(char items[], int len);

// Define an array of strings (an array of char pointers, like argv)
char** wordBank; // in wordbank, store the pointer to the respective addresses 




int main(int argc, char *argv[]) {

int numWords;

cout << "argc: is" << argc << endl; 
if (argc != 2){
  cerr << "The file is unable to be accessed :(" << endl;
  return 1;
} 


ifstream readfilein (argv[1]); // get word will begin a C-string with representation of an integer

readfilein >> numWords;


if( readfilein.fail() ){ // able to open file?
cout << "Couldn't open file" << endl;
return 1;
}


wordBank = new char* [numWords] ;
 // using a similar file-finder to memleak


char buffer[41];

 // part 6, maybe include buffer

for(int i=0; i < numWords; i++){ //part 8 fix this!
  readfilein >> buffer;
  char* readwords = new char [strlen(buffer)+1];
  readwords[strlen (buffer)] = '\0';
  //w = readwords;
  strcpy(readwords, buffer);
  wordBank[i] = readwords;


}
readfilein.close();


//---------------------------------------------------------------
  srand(time(0));
  char guess[80];

  bool wordGuessed = false;
  int numTurns = 10;


  int target = rand() % numWords;
  int targetLen = strlen(wordBank[target]);

  char* word = new char[targetLen + 1];
  strcpy(word, wordBank[target]);
  permute(word, targetLen);
  

  while (!wordGuessed && numTurns > 0) {
    cout << "Scrambled word: " << word << endl;
    cout << "What do you guess the original word is? ";
    cin >> guess;
    wordGuessed = (strcmp(guess, wordBank[target]) == 0);
    numTurns--;
  }
  if (wordGuessed) {
    cout << "You win!" << endl;
  }
  else {
    cout << "Too many turns...You lose!" << endl;
  }

  for (int i = 0; i < numWords; i++){
      delete [] wordBank[i];
  }
  
  delete [] wordBank;
  delete [] word;
  return 0;

}

// Scramble the letters. See "Knuth shuffle" on Wikipedia.
void permute(char items[], int len) {
  for (int i = len-1; i > 0; --i) {
    int r = rand() % i;
    char temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }
}