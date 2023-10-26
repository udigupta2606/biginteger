#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct BigInteger{
    struct node *head;
    int length, sign;
};


void display (struct BigInteger A);
struct BigInteger initialize (char *s);
struct BigInteger add ( struct BigInteger A, struct BigInteger B);
struct BigInteger sub ( struct BigInteger A, struct BigInteger B);
struct BigInteger mul (struct BigInteger A, struct BigInteger B);
struct BigInteger div1 (struct BigInteger A, struct BigInteger B);
struct BigInteger mod (struct BigInteger A, struct BigInteger B);