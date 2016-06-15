#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userBase.h"

int main(int argc, char ** argv)
{
    UserBase * list;
    char input[1000];
    int opt;
    list = NULL;

    printf("Welcome\nThis is a practice user base written by James McLennan\n\n");
    list = loadUserBase();
    if(list == NULL)
    {
        printf("Error: File has been corrupted or destroyed. Please contact your system admin\n");
        return EXIT_FAILURE;
    }
    else
    {
        do
        {
            printf("Menu\n");
            printf("- Login\n");
            printf("- Join\n");
            printf("- Quit\n");
            printf("Please type in your selection: ");
            fgets(input, 1000, stdin);

            if(strncmp(input, LOGIN, 5) == 0)
            {
               userLogin(list); 
            }
            else if(strcmp(input, QUIT) == 0)
            {
                opt = 0;
            }
        }while(opt != 0);
    }
    printf("Thank you\n");
    return EXIT_SUCCESS;
}

UserNode * createUserNode()
{
    UserNode * newUser = malloc(sizeof(UserNode));

    if(newUser != NULL)
    {
        newUser->nextNode = NULL;
        newUser->previousNode = NULL;
        return newUser;
    }
    else
    {
        return NULL;
    }
}

UserBase * createUserBase()
{
    UserBase * list = malloc(sizeof(UserBase));

    if(list != NULL)
    {
        list->head = NULL;
        list->tail = NULL;
        list->current = NULL;
        list->size = 0;
        return list;
    }
    else
    {
        return NULL;
    }
}

UserBase * loadUserBase()
{
    UserBase * list = createUserBase();
    UserNode * node;

    FILE *fp = fopen("UserBase.txt", "r");
    char text[1000];
    char *token;
    
    if(fp != NULL)
    {
        while(fgets(text, 1000, fp))
        {
            text[strlen(text) - CLEARONECHAR] = '\0'; 
            token = strtok(text, ", ");

            while(token != NULL)
            {
                printf("Admin: Loading user...\n");
                node = createUserNode();

                strcpy(node->userName, token);
                token = strtok(NULL, ", ");

                strcpy(node->passWord, token);
                token = strtok(NULL, ", ");
            
                insert(list, node);
            }
        }
        fclose(fp);
    }
    else
    {
        printf("Error: File could not be found.\n");
    }
    return list;
}

Boolean insert(UserBase * list, UserNode * node)
{
    UserNode * lastNode, * curNode;
    
    lastNode = NULL;
    curNode = list->head;

    while(curNode != NULL)
    {
        lastNode = curNode;
        curNode = curNode->nextNode;
    }

    if(list->head == NULL)
    {
        printf("Admin: Inserting user as head...\n");
        node->previousNode = list->head;
        node->nextNode = NULL;
        list->current = node;
        list->head = node;
        list->tail = node;
    }
    else if(list->head != NULL)
    {
        printf("Admin: Inserting user in body...\n");
        lastNode->nextNode = node;
        node->previousNode = lastNode;
        node->nextNode = NULL;
        list->current = node;
        list->tail = node;
        lastNode = node;
    }
    return TRUE;
}

void userLogin(UserBase * list)
{
    UserNode * node = list->head;
    char text[1000];

    printf("Please enter your username: ");
    fgets(text, 1000, stdin);
    text[strlen(text) - 1] = '\0';

    while(node != NULL)
    {
        if(strcmp(text, node->userName) == 0)
        {
            printf("Please enter your password %s: ", node->userName);
            fgets(text, 1000, stdin);
            text[strlen(text) - 1] = '\0';

            if(strcmp(text, node->passWord) == 0)
            {
                printf("Welcome back %s\n", node->userName);
                break;
            }
        }
        node = node->nextNode;
    }
}
