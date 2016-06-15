#ifndef USER_BASE_H
#define USER_BASE_H

#define USERNAME_LENGTH 20
#define PWD_LENGTH 15
#define CLEARONECHAR 1
#define LOGIN "Login"
#define JOIN "Join"
#define QUIT "Quit"

typedef enum boolean
{
    FALSE = 0,
    TRUE
} Boolean;

typedef struct userNode
{
    char userName[USERNAME_LENGTH];
    char passWord[PWD_LENGTH];
    struct userNode * nextNode;
    struct userNode * previousNode;
} UserNode;

typedef struct userBase
{
    UserNode * head;
    UserNode * tail;
    UserNode * current;
    unsigned size;
} UserBase;

UserBase * createUserBase();
void freeUserBase(UserBase * list);

UserNode * createUserNode();
void freeUserNode(UserNode * node);

UserBase * loadUserBase();
Boolean insert(UserBase * list, UserNode * node);

void userLogin();
#endif
