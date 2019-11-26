/*
 * maxTweet.c
 *
*/


#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>




/*
 * Store tweet info into this struct
 */
//struct tweet{
//	int rowNum;
//	int tweet_id;
//	char *name;
//	char *text;
//	//do we need retweet count?
//
//};

struct Node{
	char *name;
	Node *next;
};

struct List{
	struct Node *node;
	struct Node *head;
};


/*
 * Process the csv file and get the tweets
 *
 *
*/
void printTopTweeters(){

}

void printInvalid(){
	printf("Invalid Input Format\n");
}

int getNameColNum(char *lineBuf){
	// 1. no two names are the same
	// 2. one of the names be "name" (with OR without "")
	// if 1 and 2 are true, return the col number of "name", otherwise return -1

	//assuming that csv file won't have a ton of columns so use simple search
	int colCount = -1;
	char *filed = strtok(lineBuf, ",");
	while (filed){
		for ()
	}


//	for (int i  = 0, i < sizeof(line)), i++){
//
//	}
	//printf("%lu\n", sizeof(line));



	return colCount; //if can't find name in column names
}
/*
 * Process the csv file and get the tweets
 *
 *
*/
void getCSVData(const char *filePathname){
	// first check if filePathname is null
	// check first row is correct name row (new function)
	// store (names, count) in a data structure (new function) [better be hash table we think, we know max rows are 20,000]
	// sort (names, count) by count, take the top 10 (new function)

	FILE *fp;
	fp = fopen(filePathname, "r");
	//char buf[1024]; //not sure this is correct buffer size
	char *lineBuf;
	int rowCount = 0, colCount = 0;
	char *field;
	size_t lineSize = 0, lineBufSize = 0;

	// if error reading file print error
	if (fp == NULL){
		printInvalid();
		//int errnum = errno;
		// fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
	} else{
		//process the data in the csv
		while ((lineSize = getline(&lineBuf, &lineSize, fp)) != (-1)){
			colCount = 0;
			rowCount++;

			//if on first row, ignore it
			if (rowCount == 1){
				//Search first line of file for "name"
				//lineSize = getline(&lineBuf, &lineSize, fp);
				int nameColNum = getNameColNum(lineBuf);
				if (nameColNum == -1){
					printInvalid();
					break;
				}
				continue;
			}

//			char *line = strtok(lineBuf, ","); //delimite on comma
//
//			while (field){
//
//				//find the
//		}
		fclose(fp);
		}
	}
}

int main(int argc, const char * argv[]){

	getCSVData(argv[1]);
	exit(EXIT_SUCCESS);
}

/*
 * Resources Used to Complete Assignment
 * https://codingboost.com/parsing-csv-files-in-c
 * 	Used to help process CSV file in C
 *
*/
