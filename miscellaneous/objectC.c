#include <stdio.h>
#include <string.h>

struct person
{
    int age;
    char *name;
    void (*setName)(void *dest, const void * src, size_t n);
} typedef person_t;

person_t *Person()
{
    person_t *person = malloc();

    return person;
}

int main()
{
    printf("Hello world");
}