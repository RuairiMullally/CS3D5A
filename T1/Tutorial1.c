#include <stdio.h>

void main1(){
    printf("Hello Geek!");
    char name[99];
    int age;

    printf("Name >> ");
    scanf("%s", &name);
    printf("Age >> ");
    scanf("%d", &age);
    printf("Hello %s (%d)", name, age);
}