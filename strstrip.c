//
// strstrip() - strip unwanted characters from a string
// Copyright (c) 2004-2017 by Antoni Sawicki
//
// it's beyond me why this is not part of libc
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

//  referemce:
//  deny all by default
//  allow a=alpha n=numeric u=convert spaces to underscore
//  use allow="an.-@" for email
//  use allow="anu.-_/" for filenames
//  ! is a cmd termination char
//  use !! to allow only ! char
//  use !a to allow only letter a
//  use n!abcdef to allow hex numbers
//
int strstrip(char *str, int len, char *allow) {
    int n,a;
    int alpha=0, number=0, spctou=0;
    char *dst;

    if(!str || !strlen(str) || !allow || !strlen(allow))
        return -1;

    if(*allow == 'a') {
        alpha=1;
        allow++;
    }
    if(*allow == 'n') {
        number=1;
        allow++;
    }
    if(*allow == 'u') {
        spctou=1;
        allow++;
    }
    if(*allow == '!') {
        allow++;
    }

    dst=str;

    for(n=0; n<len && *str!='\0'; n++, str++) {
        if(alpha && isalpha(*str))
            *(dst++)=*str;
        else if(number && isdigit(*str))
            *(dst++)=*str;
        else if(spctou && *str==' ')
            *(dst++)='_';
        else if(strlen(allow))
            for(a=0; a<strlen(allow); a++) 
                if(*str==allow[a])
                    *(dst++)=*str;
    }

    *dst='\0';

    return 0; /* strlen(dst); */
}


// 
// examples how to use strstrip() function
// 
int main(void) {
    char mystring[128]={'\0'};
    int n;

    // fill with garbage
    for(n=0; n<sizeof(mystring)-1; n++) 
        mystring[n]=(char)n+1;

    // example: allow only letters 
    //strstrip(mystring, sizeof(mystring), "a");

    // example: allow only numbers 
    //strstrip(mystring, sizeof(mystring), "n");

    // example: allow letters and numbers 
    //strstrip(mystring, sizeof(mystring), "an");

    // example: allow letters, numbers and some other chars 
    //strstrip(mystring, sizeof(mystring), "an_./[]");

    // example: allow letters, numbers and some other chars plus convert spaces to underscore
    strstrip(mystring, sizeof(mystring), "anu_./[]");

    // example: allow only letters a, b, c and numbers 1, 2, 3
    //strstrip(mystring, sizeof(mystring), "!abc123");

    // example: allow hex numbers
    //strstrip(mystring, sizeof(mystring), "n!abcdef");

    puts(mystring);

    return 0;
}
