/*
 * @Author:	Jeff Berube
 * @Title:	Dictionary v2 (Assignment 2 - CS2010)
 *
 * @Description:	Reads words from a file, adds them to a dictionary, counts
 * 			and sorts them and outputs the results.
 *
 * @Usage		./dictionaryv2 < INPUTFILE
 *
 */

#include "dictionary.h"

/* Global variables */
DICT dictionary;
WORD word;
int count[MAX];
int row = 0;

/* 
 * InsertWord
 *
 * Adds a word to the dictionary.
 *
 * Returns 1 on success, otherwise 0.
 *
 */

BOOL InsertWord(DICT dict, WORD word) {

	if (row < MAX) {

		dict[row] = word;
		count[row++]++;

		return 1;

	} else 
		return 0;	

}

/* 
 * DumpDictionary
 *
 * Sorts dictionary then displays contents 
 *
 */

void DumpDictionary(DICT dict, int count[]) {

	int i = 0, tmp = 0, word_len = 0, count_tmp;
	WORD word_tmp;

	/* Sort dictionary (Simple bubble sort) */
	while (i < row) {
	
		tmp = i + 1;
		
		while (tmp < row) {
		
			if (strncmp(lowercase(dict[i]).c_str(), 
						lowercase(dict[tmp]).c_str(), 132) > 0) {
			
				word_tmp = dict[i];
				dict[i] = dict[tmp];
				dict[tmp] = word_tmp;

				count_tmp = count[i];
				count[i] = count[tmp];
				count[tmp] = count_tmp;

			}

			tmp++;

		}

		i++;


	}

	/* Print table header */
	cout << endl << "Freq\tWord" << endl;
	cout << "----------------------------------" << endl;

	i = 0;

	while (i < row) {

		word_len = dict[i].length();
		word_tmp = word_len > 22 ? dict[i].substr(0, 22) : dict[i];

		cout << count[i] << "\t" << word_tmp;

		if (word_len > 22) cout << "...";

		cout << endl;

		i++;

	}


	cout << endl;

}

/* 
 * GetNextWord
 *
 * Retrieves next word in input stream. 
 *
 * Returns WORD or 0 if stream is empty. 
 *
 */

WORD GetNextWord(void) {

	char *ch = (char *)malloc(2);
	memset(ch, 0, 2);	

	WORD next = "";

	/* Test for EOF, return 0 if reached */
	if (cin.eof()) return "";
	
	while (next == "") {

		while (cin.good() && isalpha((*ch = cin.get()))) next.append(ch);
		
		if (cin.eof()) break;

	}

	return next;

}

/* 
 * FullDictionary
 *
 * Determines if dictionary is full. 
 *
 * Returns 1 if full, 0 otherwise. 
 *
 */

BOOL FullDictionary(DICT dict) {

	return row == MAX ? 1 : 0;

}

/*
 * lowercase
 *
 * Transforms a word from mixed cased to lower case
 *
 * Returns a lowercase WORD.
 *
 */

WORD lowercase(WORD mixedcase) {

	WORD modified, s;

	for (char c : mixedcase) {	
		s = tolower(c);
		modified.append(s);
	}

	return modified;

}

/*
 * LocateWord
 *
 * Tries to find a word in a dictionary.
 *
 * Returns word position if found, -1 otherwise.
 *
 */

int LocateWord(DICT dict, WORD word) {

	int i = 0, index = -1;

	while (i < row) {
	
		if (lowercase(dict[i]) == lowercase(word)) {
			
			index = i;
			break;

		}

		i++;

	}
		
	return index;

}

