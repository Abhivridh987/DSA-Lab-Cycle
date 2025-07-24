#include <stdio.h>
#include <stdlib.h>
char st[100];
int top = -1;

char op_st[100];
int op_top = -1;

void push_st(char ch)
{
    st[++top] = ch;
}
void pop_st()
{
    if(top == -1)
        printf("\nStack Underflow\n");
    else{
        st[top] = '\0';
        top--;
    }
}
char peek_st(){
    return st[top];
}


void push_op_st(char ch)
{
    op_st[++op_top] = ch;
}
void pop_op_st()
{
    if(op_top == -1)
        printf("\nStack Underflow\n");
    else{
        op_st[op_top] = '\0';
        op_top--;
    }
}
char peek_op_st(){
    return op_st[op_top];
}

int preference(char ch)
{
    if(ch == '+' || ch == '-')
        return 0;
    else if(ch == '*' || ch == '/')
        return 1;
    else
        return -1;
}
int main()
{
    char eqn[30];
    printf("Enter a equation : ");
    scanf("%[^\n]",eqn);

    for(int i =0; eqn[i] != '\0'; i++){
        if(eqn[i] >= '0' && eqn[i] <= '9')
        {
            push_st(eqn[i]);
        }
        else if(eqn[i] == '(')
        {
            push_op_st(eqn[i]);
        }
        else if(eqn[i] == ')'){
            while(peek_op_st() != '(')
            {
                push_st(' ');
                push_st(peek_op_st());
                pop_op_st();
            }
            pop_op_st();
        }
        else if(op_top == -1){
            push_st(' ');
            push_op_st(eqn[i]);
        }
        else if(preference(eqn[i]) > preference(peek_op_st()))
        {
            push_st(' ');
            push_op_st(eqn[i]);
        }
        else if(preference(eqn[i]) <= preference(peek_op_st()))
        {
            push_st(' ');
            push_st(peek_op_st());
            pop_op_st();
            push_op_st(eqn[i]);
            push_st(' ');
        }

    }
    printf("\n");

    while(op_top != -1){
        push_st(' ');
        char op = peek_op_st();
        push_st(op);
        pop_op_st();


    }
    for(int k = 0 ;k <= top; k++){
        printf("%c",st[k]);
    }
    return 0;
}
