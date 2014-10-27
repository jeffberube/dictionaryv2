/*
 * @Author:	Jeff Berube
 * @Title:	main.cpp	
 *
 * @Description:	Main dictionary routine.
 *
 * @Usage		./dic < INPUTFILE
 *
 */

#include "dictionary.h"

using namespace std;
using std::string;

#define MAX 100

/* Global variables */
extern DICT dictionary;
extern WORD word;
extern int count[MAX];
extern int row;


int main(void) {

	int pos;

	while (1) {
	
		word = GetNextWord();

		if (0 == word.length()) {
		
			DumpDictionary(dictionary, count);
			break;

		}
	
		if ((pos = LocateWord(dictionary, word)) >= 0)
			count[pos]++;
		
		else if (!InsertWord(dictionary,word))
			cout << "Dictionary full. " << word << " could not be added.\n";
	
	}

	return 0;

}
