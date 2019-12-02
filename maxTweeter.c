#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

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
//      3.2 Check the number of items after stripped by comma == the number of fields in 2.7 or if it is an empty line
//      3.3 Check quotation validation
//      3.4 Record the index of field that's surrounded by ""
//      3.5 Remove the outermost quotation marks if there are any
//      3.6 Make sure the fields that are supposed to be surrounded by "" are indeed surrounded by "" (Compare 3.4 and 2.4)
//      3.7 Update the name count


// Part 4. Check the length of the file <= 20,000 lines.

// Part 5. Get the top 10 Tweeters


typedef  struct CSV_row_Struct{
    int name_col;
    bool *quotation_index;
    char **col;
    int num_col;
} csv_row;


typedef struct Tweeter{
    char* name;
    int num_occur;
} tweeter;


typedef struct Name_list{
    tweeter *tweeter_array;
    int list_size;
} name_list;


void print_error(){
    fprintf(stderr, "Invalid Input Format\n");
}



void free_csv_row(csv_row *row){
    if (row->quotation_index != NULL){
        free(row->quotation_index);
        row->quotation_index = NULL;
    }
    if (row->col != NULL){
        for (int i=0; i < row->num_col; i++){
            free(row->col[i]);
        }
        free(row->col);
        row->col = NULL;
    }
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


void parse_row(char *lineBuf, csv_row *row){
    // parse header into tokens, and record number of fields separated by ","
    row->col = NULL;
    char *token = NULL;
    row->num_col = 0;
    token = strtok(lineBuf, ",");
    while( token != NULL ) {
        row->num_col++;
        row->col  = realloc(row->col , row->num_col*sizeof(*row->col));
        row->col[row->num_col-1] = malloc((strlen(token)+1)* sizeof(char));
        strcpy(row->col[row->num_col-1], token);
        token = strtok(NULL, ",");
    }
    remove_newline(row);
}


bool check_quotation_validation(char** string_list, int num_string){
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
    // check if name appears in the header and record its index (2.6)
    bool name_exist = false;
    for (int i = 0; i < head->num_col; i++){
        if (strcmp(head->col[i], "name") == 0){
            name_exist = true;
            head->name_col =i;
        }
    }
    return name_exist;
}


void shuffle_string(char* string){
    // shuffle every character in the string to the left by 1 and remove the first and last characters of the string
    int str_len = strlen(string);
    for (int i = 0; i < str_len-1; i++){
        int j = i+1;
        string[i] = string[j];
    }
    string[str_len-1] = '\0';
    string[str_len-2] = '\0';
}


void remove_and_record_quotation(csv_row *row){
    row->quotation_index = malloc(row->num_col*sizeof(bool));
    for (int i = 0; i < row->num_col; i++){
        if (row->col[i][0] =='"'){
            row->quotation_index[i] = true;
            shuffle_string(row->col[i]);
        }else{
            row->quotation_index[i] = false;
        }
    }
}



void process_header(char *lineBuf, csv_row *head){
    // DO 2.7
    parse_row(lineBuf, head);
    // CHECK 2.3
    if (check_quotation_validation(head->col, head->num_col)){
        // DO 2.4 AND 2.5
        remove_and_record_quotation(head);
        // CHECK 2.2 AND 2.6
        if (check_duplicate_names(head) && check_name_exist(head)){
            return;
        }
    }
    // some checking didn't pass, free everything we have so far and terminate the program
    free_csv_row(head);
    free(lineBuf);
    print_error();
    exit(EXIT_FAILURE);
}


bool compare_quotation_index(const bool *head_bool, const bool *body_bool, int size){
    bool same_bool_array = false;
    for (int i = 0; i < size; i++){
        if (head_bool[i] != body_bool[i]){
            return same_bool_array;
        }
    }
    same_bool_array = true;
    return same_bool_array;
}


void first_time_update(name_list *nameList, char* name){
    char *name_cpy = malloc((strlen(name)+1)* sizeof(char));
    int list_size = nameList->list_size;
    strcpy(name_cpy,name);
    nameList->tweeter_array = realloc(nameList->tweeter_array, (list_size+1)*sizeof(*nameList->tweeter_array));
    nameList->tweeter_array[list_size].name = name_cpy;
    nameList->tweeter_array[list_size].num_occur = 1;
    nameList->list_size++;
}


void not_first_time_update(name_list *nameList, int index){
    nameList->tweeter_array[index].num_occur ++;
}


void update_name_list(name_list *nameList, csv_row *body){
    char* name = body->col[body->name_col];
    if (nameList->list_size == 0){
        first_time_update(nameList, name);
    }else{
        for (int i = 0; i < nameList->list_size; i++){
            if (strcmp(name, nameList->tweeter_array[i].name) == 0){
                not_first_time_update(nameList, i);
                return;
            }
        }
        first_time_update(nameList, name);
    }
    return;
}


bool check_empty_string(char *string){
    bool is_empty = false;
    for (unsigned long i = 0; i < strlen(string); i++){
        if (isspace(string[i]) == 0){
            return is_empty;
        }
    }
    is_empty = true;
    return is_empty;
}


void process_body(char *lineBuf, csv_row *body, csv_row *head, name_list *nameList){
    parse_row(lineBuf, body);
    // CHECK 3.2 (first half)
    if (body->num_col == head->num_col){
        // CHECK 3.3
        if (check_quotation_validation(body->col, body->num_col)){
            // DO 3.4 AND 3.5
            remove_and_record_quotation(body);
            // CHECK 3.6
            if (compare_quotation_index(head->quotation_index, body->quotation_index, head->num_col)){
                // DO 3.7
                update_name_list(nameList, body);
                return;
            }
        }
    }

    // CHECK 3.2 (second half)
    if (body->num_col == 1){
        if(check_empty_string(body->col[0])){
            return;
        }
    }

    // some checking didn't pass, free everything we have so far and terminate the program
    free_csv_row(head);
    free_csv_row(body);
    free(lineBuf);
    print_error();
    exit(EXIT_FAILURE);
}


int compare_tweeter (const void * a, const void * b){
    const tweeter* lhs = (const tweeter*)a;
    const tweeter* rhs = (const tweeter*)b;
    return (rhs->num_occur - lhs->num_occur);
}


void print_top_tweeters(name_list *nameList, int range){
    for (int i = 0; i < range; i++){
        printf("%s: %d\n",nameList->tweeter_array[i].name, nameList->tweeter_array[i].num_occur);
    }
}

void get_top_ten(name_list *nameList){
    qsort(nameList->tweeter_array, nameList->list_size, sizeof(tweeter), compare_tweeter);
    if(nameList->list_size > 10){
        print_top_tweeters(nameList, 10);
    }
    if((nameList->list_size < 10) && (nameList->list_size != 0)){
        print_top_tweeters(nameList, nameList->list_size);
    }
    if (nameList->list_size == 0){
        return;
    }
}


void check_line_length(ssize_t byte_read, char* lineBuf){
    if (byte_read > 1024){
        print_error();
        free (lineBuf);
        exit(EXIT_FAILURE);
    }
}


void initialize_for_get_line(char** lineBuf, size_t* lineSize){
    if (*lineBuf != NULL){
        free (*lineBuf);
    }
    *lineBuf = NULL;
    *lineSize = 0;
    errno = 0;
}


void free_name_list(name_list *nameList){
    for(int i = 0; i < nameList->list_size; i++){
        free(nameList->tweeter_array[i].name);
    }
}

void process_file(const char *filePathname){
    FILE *fp;
    size_t lineSize = 0;
    ssize_t byte_read;
    char *lineBuf = NULL;
    int rowCount = 0;
    fp = fopen(filePathname, "r");
    csv_row head = {-1, NULL, NULL, -1};
    name_list nameList ={NULL, 0};

    // CHECK 1.2
    if (fp == NULL){
        print_error();
        exit(EXIT_FAILURE);
    }else{
        errno = 0;
        // CHECK Part 2 (Header Part)
        if ((byte_read = getline(&lineBuf, &lineSize, fp)) != (-1)){
            // CHECK 2.1
            check_line_length(byte_read, lineBuf);
            rowCount++;
            process_header(lineBuf, &head);
            initialize_for_get_line(&lineBuf, &lineSize);
        }
        // CHECK Part 3 (Body Part)
        while ((byte_read = getline(&lineBuf, &lineSize, fp)) != (-1)){
            // CHECK 3.1
            check_line_length(byte_read, lineBuf);
            rowCount++;
            csv_row body = {head.name_col, NULL, NULL, 0};
            process_body(lineBuf, &body, &head, &nameList);
            initialize_for_get_line(&lineBuf, &lineSize);
            free_csv_row(&body);
        }
        // In case if getline() returns -1 NOT because of EOF
        if (errno != 0){
            if (lineBuf != NULL){
                free_csv_row(&head);
            }
            print_error();
            exit(EXIT_FAILURE);
        }
        // CHECK Part 4
        if (rowCount > 20000){
            free_csv_row(&head);
            print_error();
            exit(EXIT_FAILURE);
        }else{
            // DO Part 5
            free_csv_row(&head);
            get_top_ten(&nameList);
            free_name_list(&nameList);
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