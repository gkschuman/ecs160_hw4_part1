#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

// Part 1. Get Command Line Argument
//    1.1 Check get exactly ONE command line argument
//    1.2 Check if we can open the file

// Part 2. Get Header
//      2.1 Check line length <= 1024 characters
//      2.2 Check no duplicate names
//      2.3 Check quotation validation
//      2.4 Record the index of field that's surrounded by ""
//      2.5 Remove the outermost quotation marks if there are any
//      2.6 Check name appear
//      2.7 Record the number of fields separated by comma

// Part 3. Get line by line (after Header)
//      3.1 Check line length <= 1024 characters
//      3.2 Check the number of items after stripped by comma == the number of fields in 2.7
//      3.3 Check quotation validation
//      3.4 Record the index of field that's surrounded by ""
//      3.5 Make sure the fields that are supposed to be surrounded by "" are indeed surrounded by "" (Compare 3.4 and 2.4)
//      3.6 Remove the outermost quotation marks if there are any
//      3.4 Update the name count

// Part 4. Check the length of the file <= 20,000 lines.

// Part 5. Get the top 10 Tweeters


typedef  struct CSV_row_Struct{
    int name_col;
    bool *quotation_index;
    char **col;
    int num_col;
} csv_row;



void print_error(){
    fprintf(stderr, "Invalid Input Format\n");
}


void remove_newline(csv_row *head){
    char* last_field = head->col[(head->num_col)-1];
    int last_field_len = strlen(last_field);
    if (last_field[last_field_len-1] == '\n'){
        last_field[last_field_len-1] = '\0';
        if (last_field[last_field_len-2] == '\r'){
            last_field[last_field_len-2] = '\0';
        }
    }
}


void parse_header(char *lineBuf, csv_row *head){
    // parse header into tokens and record 2.7
    head->col = NULL;
    char *token = NULL;
    head->num_col = 0;
    token = strtok(lineBuf, ",");

    while( token != NULL ) {
        head->num_col++;
        head->col  = realloc(head->col , head->num_col*sizeof(*head->col));
        head->col[head->num_col-1] = malloc((strlen(token)+1)* sizeof(char));
        strcpy(head->col[head->num_col-1], token);
        token = strtok(NULL, lineBuf);
    }

    remove_newline(&head);
}


bool check_quotation_validatoin(char** string_list, int num_string){
    bool quotation_val = false;
    for (int i = 0; i < num_string; i++){
        if (string_list[i][0] =='"'){
            if (string_list[i][strlen(string_list[i])-1] !='"') {
                return quotation_val;
            }
        }
        if (string_list[i][strlen(string_list[i])-1] =='"'){
            if (string_list[i][0] !='"'){
                return quotation_val;
            }
        }
    }
    quotation_val = true;
    return quotation_val;
}




bool check_duplicate_names(csv_row *head){
    // check if header has duplicate names (2.2)
    bool no_duplicate = false;
    for (int i = 0; i < head->num_col; i++){
        for (int j = i+1; j < head->num_col; j++){
            if (strcmp(head->col[i], head->col[j]) == 0){
                return no_duplicate;
            }
        }
    }
    no_duplicate = true;
    return no_duplicate;
}



bool check_name_exist(csv_row *head){
    // check if name appears in the header (2.6)
    bool name_exist = false;
    for (int i = 0; i < head->num_col; i++){
        if ((strcmp(head->col[i]), "name") == 0){
            name_exist = true;
        }
    }
    return name_exist;
}


csv_row process_header(char *lineBuf){
    csv_row head;
    parse_header(lineBuf, &head);
    if (!check_quotation_validatoin(head.col, head.num_col)){

    }
    // CHECK 2.2 AND 2.6
    if (check_duplicate_names(&head) && check_name_exist(&head)){

    }
    return head;
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
                csv_row head = process_header(lineBuf);
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