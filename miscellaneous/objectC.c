#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct person
{
    int age;
    char *name;
} typedef person_t;

void setName(person_t *this, const char *p_name)
{
    // free the space for name if name was already allocated and 
    if (this->name != NULL)
    {
        free(this->name);
    }

    this->name = (char *)malloc(strlen(p_name)*(sizeof(char*)));
    memcpy(this->name, p_name, strlen(p_name));
}

void printName(person_t *this)
{
    printf("Name: %s\n", this->name);
}

void printAge(person_t *this)
{
    printf("%s's age: %d\n", this->name, this->age);
}

void destroyPerson(person_t *this)
{
    free(this->name);
    free(this);
}

person_t *Person(int age, const char*name)
{
    person_t *person = (person_t *)malloc(sizeof(person_t)); 
    person->name = (char *)malloc(strlen(name)*(sizeof(char*)));
    setName(person, name);
    person->age = age;
    return person;
}

int main()
{
    printf("Hello world\n");
    person_t *person = Person(22, "Tim");
    printName(person);
    printAge(person);
    destroyPerson(person);
}