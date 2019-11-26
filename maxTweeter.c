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
struct tweet{
	int rowNum;
	int tweet_id;
	char *name;
	char *text;
	//do we need retweet count?

};
/*
 * Process the csv file and get the tweets
 *
 *
*/
void printTopTweeters(){

}

int getNameColNum(char *lineBuf){
	//assuming that csv file won't have a ton of columns so use simple search
	int colCount = -1;

	return colCount; //if can't find name in column names
}
/*
 * Process the csv file and get the tweets
 *
 *
*/
void getCSVData(const char *filePathname){
	FILE *fp;
	fp = fopen(filePathname, "r");
	//char buf[1024]; //not sure this is correct buffer size
	char *lineBuf;
	int rowCount = 0, colCount = 0;
	char *field;
	size_t lineSize = 0, lineBufSize = 0;

	// if error reading file print error
	if (fp = NULL){
		int errnum = errno;
		// fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
	} else{
		//process the data in the csv
		while (fgets(lineBuf, 1024, fp)){
			colCount = 0;
			rowCount++;

			//if on first row, ignore it
			if (rowCount == 1){
				//Search first line of file for "name"
				lineSize = getline(&lineBuf, &lineSize, fp);
				int nameColNum = getNameColNum(lineBuf);
				continue;
			}

			char *line = strtok(lineBuf, ","); //delimite on comma

			while (field){

				//find the 
		}
		fclose(fp);
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