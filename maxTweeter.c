#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// Part 1. Get Command Line Argument
//    1.1 Check get exactly ONE command line argument
//    1.2 Check if we can open the file

// Part 2. Get Header
//      2.1 Check line length <= 1024 characters
//      2.2 Check no duplicate names
//      2.3 Check either name or "name" appear
//      2.4 Record the index of field that's surrounded by ""
//      2.5 Record the number of fields separated by comma

// Part 3. Get line by line (after Header)
//      3.1 Check line length <= 1024 characters
//      3.2 Check the number of items after stripped by comma == the number of fields in 2.5
//      3.3 Check the item that supposed to be surrounded by "" (2.4) indeed is surrounded by ""
//      3.4 Update the name count (if "name" instead name (2.3), strip away the outmost "" when recording)

// Part 4. Check the length of the file <= 20,000 lines.

// Part 5. Get the top 10 Tweeters


void print_error(){
    fprintf(stderr, "Invalid Input Format\n");
}


void process_header(char *lineBuf){

}


void process_body(char *lineBuf){

}


void get_top_ten(){

}


void process_file(const char *filePathname){
    FILE *fp;
    size_t lineSize = 0;
    ssize_t byte_read;
    char *lineBuf = NULL;
    int rowCount = 0;
    fp = fopen(filePathname, "r");

    // CHECK 1.2
    if (fp == NULL){
        print_error();
        exit(EXIT_FAILURE);
    }else{
        errno = 0;
        while ((byte_read = getline(&lineBuf, &lineSize, fp)) != (-1)){
            // CHECK 2.1 AND 3.1
            if (byte_read > 1024){
                print_error();
                free (lineBuf);
                exit(EXIT_FAILURE);
            }
            rowCount++;
            if (rowCount ==1){
                // CHECK Part 2
                process_header(lineBuf);
            }else{
                // CHECK Part 3
                process_body(lineBuf);
            }
            free (lineBuf);
            lineBuf = NULL;
            lineSize = 0;
            errno = 0;
        }

        // In case if getline() returns -1 NOT because of EOF
        if (errno != 0){
            if (lineBuf != NULL){
                free (lineBuf);
            }
            print_error();
            exit(EXIT_FAILURE);
        }

        // CHECK Part 4
        if (rowCount > 20000){
            print_error();
            exit(EXIT_FAILURE);
        }else{
            // DO Part 5
            get_top_ten();
        }
    }

}




int main(int argc, const char** argv) {
    // CHECK 1.1
    if (argc != 2){
        print_error();
        exit(EXIT_FAILURE);
    }

    process_file(argv[1]);
    exit(EXIT_SUCCESS);

}