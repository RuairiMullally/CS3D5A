#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int get_middle(int left, int right){
    return(left + right) / 2;
}


int search_prefix(char* prefix, char** search_terms, int m, int n){
    int left = 0;
    int right = m - 1;
    int middle;

    int answer = -1;
    

    //printf("%s\n", prefix);
    //printf("%s", comparison_prefix);

    while(left <= right){
        middle = get_middle(left, right);
        char* comparison_prefix = malloc((strlen(prefix) + 1) * sizeof(char));    
        //get prefix of comparison string
        strncpy(comparison_prefix, search_terms[middle], strlen(prefix) );
        comparison_prefix[strlen(prefix)] = '\0';
        if(!(strcmp(prefix, comparison_prefix))){
            answer = middle;
            right = middle -1;
        }else if( strcmp(prefix, comparison_prefix) < 0){
            right = middle - 1;
            
        }else if(strcmp(prefix, comparison_prefix) > 0){
            left = middle - 1;
            
        }
    }
    return answer;

}




int main(){

    char* inputs[3] = {"Ann\0",
                         "Apple\0",
                         "Boy\0"};

    printf("%i", search_prefix("An", inputs, 3, 6));

    return 0;
}