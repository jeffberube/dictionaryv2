/*
 * @Author: Jeff Berube
 * @Title: Dictionary (Assigment #1)
 *
 * @Description: Takes a stream of characters as input and outputs every unique word with its frequency.
 *
 */


#include <cstdio>
#include <cctype>
#include <iostream>
#include <cstring>
using namespace std;

#define MAX_WORD_LEN 132
#define MAX_ROWS 10

char dictionary[MAX_ROWS + 1][MAX_WORD_LEN + 1] = {0};
int freq[MAX_ROWS] = {0};

int dict_col = 0, ptr = 0, biggest_word = 0;
bool flag_truncated = false, flag_maxrows = false;

/*
 * str_len
 *
 * Returns lenght of string. Takes a pointer to the string.
 *
 */

int str_len(char *string) {
	
	int i = 0;

	while (*string++) i++;

	return i;

}

/*
 * str_cmp
 * 
 * Compares two strings. Takes 2 char pointers. Returns 1 if found, 0 otherwise.
 *
 */

int str_cmp(char *string1, char *string2) {

	int i = 0;
	char ch1, ch2;

	if (str_len(string1) != str_len(string2)) return 0;
	else {

		/* While we haven't reached end of string */
		while (*(string1 + i) != 0) { 
			
			ch1 = *(string1 + i);
			ch2 = *(string2 + i);

			/* Convert character to lower case */
			if (ch1 > 64 && ch1 < 91) ch1 += 32;
			if (ch2 > 64 && ch2 < 91) ch2 += 32;

			/* If characters are the same, increment pointer */
			if (ch1 == ch2) i++;
			else break;

		}

		return i == str_len(string1) ? 1 : 0;
	
	}

}

/*
 * str_search
 * 
 * Search for string in table
 *
 */

int str_search(char *string) {
	
	/* Create temporary pointer */
	int tmp_ptr = 0, ret_val;

	/* Iterate through dictionary */
	while (tmp_ptr < ptr) {
		
		/* If strings are the same, break out */
		if (str_cmp(dictionary[tmp_ptr], string)) break;

		/* Otherwise, increase pointer */
		tmp_ptr++;

	}

	/* Return index if found, -1 if not */
	return tmp_ptr != ptr ? tmp_ptr : -1;	

}

/*
 * str_pad
 *
 * Pads output with character for specified interval. Takes an int for the
 * number of times to reproduce the character and a char pointer to the
 * character to use to pad the string.
 *
 */

void str_pad(int width, char pad_char) {

	int tmp_col = 0;

	while (tmp_col < width) {
		
		cout << pad_char;
		tmp_col++;

	}

}

/*
 * print_word
 *
 * Prints string character by character. Takes a char pointer to start of the
 * string. Ends when it encounters a null byte.
 *
 */

void print_word(char *string) {

	int tmp_col = 0;

	/* Print word character by character up to 22 char then ... */
	while (tmp_col < str_len(string) && tmp_col < 22) {
		
		cout << *(string + tmp_col);
		tmp_col++;
	
	}

	if (tmp_col == 22) cout << "...";

}

/*
 * dump
 *
 * Dumps dictionary
 *
 */

void dump() {

	/* Display warning message if one of the words exceeds MAX_WORD_LEN */
	if (flag_truncated)
		cout << endl << "WARNING: One or more words exceeded the " 
			<< MAX_WORD_LEN << " character limit and were truncated."
			<< endl;

	/* Display warning message if number of unique words exceeds MAX_ROWS */
	if (flag_maxrows)
		cout << endl 
			<< "WARNING: Dictionary exceeded capacity. "
			<< "One or more words have been omitted." << endl;	

	/* RENDER TABLE LAYOUT */
	/* Print table header */
	cout << endl << "Freq\tWord" << endl;
	cout << "----------------------------------"  << endl;

	int tmp_row = 0, tmp_col = 0;

	/* Print table rows */
	while (tmp_row < ptr) {

		/* Print frequency */
		cout <<  freq[tmp_row] << "\t\t";
		
		print_word(dictionary[tmp_row]);

		tmp_row++;

		cout << endl;

	}

	cout << endl << endl;

	/* RENDER HORIZONTAL HISTOGRAM LAYOUT */
	const int margin = 6;
	const int max = 25;
	int pad = biggest_word - 4 > 4 ? biggest_word - 4 : 4;
	int word_len = 0;
	int i = 0, word_freq = 0;

	tmp_row = 0;
	
	/* Print horizontal histogram header */
	str_pad(pad + margin, ' ');
	cout << "Word | Freq " << endl << endl;

	/* Print histogram rows */
	while (tmp_row < ptr) {
	
		/* Left pad the word to center */
		word_len = str_len(dictionary[tmp_row]);
		pad = biggest_word - (word_len < 22 ? word_len : 25);
		str_pad(pad + margin, ' ');

		/* Print word and separator */
		print_word(dictionary[tmp_row]);
		cout << " | ";	

		/* Print asterisks */
		i = 0;
		word_freq = freq[tmp_row] < max ? freq[tmp_row] : max;

		while (i++ < word_freq) cout << "=";
		
		/* If the frequency is greater than max,
		 * truncate histogram and print out freq in brackets
		 */
		if (word_freq == max) cout << "/(" << freq[tmp_row] << ")";

		cout << endl;

		tmp_row++;

	}

	cout << endl << endl << endl;

	/* RENDER VERTICAL HISTOGRAM LAYOUT */
	/* Find out max frequency */
	int height = 0;

	tmp_row = 0;

	while (tmp_row < ptr) {
	
		height = height > freq[tmp_row] ? height : freq[tmp_row];
		tmp_row++;
	
	}

	/* Set max height and truncate if necessary */
	if (height > 10) height = 10;

	/* Draw vertical histogram */
	while (height > 0) {
	
		str_pad(margin, ' ');		
		tmp_row = 0;

		while (tmp_row < ptr) {
	
			if (freq[tmp_row] >= height) cout << "#";
			else cout << " ";

			cout << "    ";
			tmp_row++;
		
		}
	
		cout << endl;
		height--;

	}

	/* Draw horizontal line under histogram */
	str_pad(margin, ' ');
	
	i = 0;
	
	while (i++ < ((ptr - 1) * 5) + 1) cout << "=";

	cout << endl;

	/* Print words vertically */
	height = 0;

	while (height < biggest_word) {
	
		str_pad(margin, ' ');
		tmp_row = 0;

		while (tmp_row < ptr) {
		
			if (height < str_len(dictionary[tmp_row]))
					cout << dictionary[tmp_row][height];
			else cout << " ";

			cout << "    ";

			tmp_row++;

		}

		cout << endl;
		height++;
	
	}

	cout << endl << endl;


}



int main() {

	/* Define variables */
	char ch;
	int newline = 0;
	int index, word_len;

	/* Read input */
	while (cin.good()) {
	
		ch = cin.get();

		if(isalpha(ch)) {

			if (dict_col == MAX_WORD_LEN) flag_truncated = true;

			/* If current word is less than MAX_WORD_LEN*/	
			if (dict_col < MAX_WORD_LEN && ptr < MAX_ROWS + 1)
				dictionary[ptr][dict_col++] = ch;	

		/* Make sure we're not adding an empty string */
		} else if (str_len(dictionary[ptr])) {

			index = str_search(dictionary[ptr]);
			word_len = str_len(dictionary[ptr]);

			if (ptr == MAX_ROWS) flag_maxrows = true;

			/* If string is not in dictionary, add word */
			if (ptr == 0 || (index == -1 && ptr < MAX_ROWS)) {
				
				freq[ptr++] = 1;

				/* Keep track of biggest word in dictionary */
				if (biggest_word < word_len)	
					biggest_word = word_len > 21 ? 25 : word_len;

			/* Else increase frequency of word */
			} else 
				freq[index]++; 

			/* Reset column pointer and clear buffer */
			dict_col = 0;
			memset(dictionary[ptr], 0, MAX_WORD_LEN);


		}
	}

	dump();
	return 0;

}
