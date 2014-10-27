#ifndef __dictionary_h__
	#define __dictionary_h__

/*
 * @Author:	Jeff Berube
 * @Title:	dictionary.h	
 *
 * @Description:	Contains function prototypes and type definition for
 * 			dictionary.
 *
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;
using std::string;

#define MAX 100

/* Custom types */
typedef int BOOL;
typedef string WORD;
typedef WORD DICT[MAX];

/* Function prototypes */
int LocateWord(DICT, WORD);
BOOL FullDictionary(DICT);
BOOL InsertWord(DICT, WORD);
WORD GetNextWord(void);
WORD lowercase(WORD);
void DumpDictionary(DICT, int[]);

/* Global variables */
extern DICT dictionary;
extern WORD word;
extern int count[MAX];
extern int row;

#endif

