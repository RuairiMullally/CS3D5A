#include <stdio.h>
#include <stdlib.h>

void readCSV();
int next_field( FILE *csv , char *buffer , int max_len );

void main()
{
    const int max_len = 150;
    char buffer[150]; //buffer for storing fields
    int field_return; //return value of field storer, checks for new lines
    

    FILE *csv = fopen("pokemon.csv", "r"); //open csv
    if(csv == NULL) {printf("error opening file");}



    do{
        field_return = next_field(csv, &buffer[0], max_len);
        printf("%s", buffer);
        if(field_return == 0) {printf("\n");
        }else if(field_return == 1) {printf("\n\n");
        }

    }while( field_return != -1);
    
    }

int next_field( FILE *csv , char *buffer , int max_len ){

    for(int n=0; n<max_len; n++){
        buffer[n] = '-';
    }
    buffer[max_len - 1] = '\0';

    int i = 0;
    static int inside = 0;
    if(csv == NULL) return -1;//check

    while(i < max_len){
        char buff = fgetc(csv);
        if(buff == EOF) return -1;

        if((buff =='"') && inside == 0){
            inside = 1;
            //buff = fgetc(csv);
        }else if((buff == '"') && inside == 1 ){
            inside = 0;
        }

        if(buff == '\n'){
            return 1;
        }else if(buff == ',' && inside == 0){
            return 0;
        }else if(buff != '"'){
            buffer[i] = buff;
            i++;
        }
    }
}

void readCSV(){

}