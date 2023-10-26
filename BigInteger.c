#include "BigInteger.h"



struct node* reverse (struct node *head)
{
    struct node *current = head, *prev = NULL, *next = NULL;
    while (current) 
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}

void displayR (struct node *head)
{
    if(!head)
        return;
    displayR (head->next);
    printf("%d",head->data);
}

void display (struct BigInteger A)
{
    if(A.sign==1  && !(A.head->next==NULL && A.head->data==0))
        printf("-");
    displayR(A.head);
    printf("\n");
}

struct node* freed(struct node *head)
{
    head = reverse(head);
    while(head->next!=NULL)
    {
        if(head->data==0)
        {
            struct node *temp = head;
            head = head->next;
            free(temp);
        }
        else
            break;
    }
    head = reverse(head);
    return head;
}

struct node* newNode (int data)
{
    struct node *temp = (struct node *) malloc (sizeof(struct node));
    if(!temp)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    temp->next = NULL;
    temp->data = data;
    return temp;
}

struct node* convertList (char *str)
{
    struct node *head = NULL;
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i]>='0' && str[i]<='9')
        {
            struct node *temp = newNode(str[i] - '0');
            temp->next = head;
            head = temp;
            continue;
        }
        printf("Invalid input.\n");
        return NULL;
    }
    return head;
}

struct BigInteger initialize (char *s)
{
    struct BigInteger A;
    if(s[0]=='-')
    {
        A.sign = 1;
        A.length = strlen(s)-1;
        A.head = convertList(&s[1]);
        return A;
    }
    A.head = convertList(s);
    A.length = strlen(s);
    A.sign = 0;
    return A;
}

void result (struct node **head, int data)
{
    struct node *temp = newNode(data);
    if((*head)==NULL) 
    {
        *head = temp;
        return;
    }
    temp->next = *head;
    *head = temp;
}

int length (struct node *head)
{
    int i = 0;
    while(head)
    {
        i++;
        head = head->next;
    }
    return i;
}

struct node* summ (struct node *list1, struct node *list2)
{
    struct node *head = NULL;
    int c = 0, sum = 0;
        while(list1 && list2)
        {
            sum = list1->data + list2->data + c;
            c = sum/10;
            result(&head, sum%10);
            list1 = list1->next;
            list2 = list2->next;
        }
        while(list1)
        {
            sum = list1->data + c;
            c = sum/10;
            result(&head, sum%10);
            list1 = list1->next;
        }
        while(list2)
        {
            sum = list2->data + c;
            c = sum/10;
            result(&head, sum%10);
            list2 = list2->next;
        }
        if(c > 0)
            result(&head, c);
        head = reverse(head);   
        return head;
}

struct node* diff (struct node *itr1, struct node *itr2)
{
    struct node *head=NULL,*list2=itr2, *list1=NULL;
    while(itr1)
    {
        struct node *n = newNode(itr1->data);
        n->next = list1;
        list1 = n;
        itr1 = itr1->next;
    }
    list1 = reverse(list1);
    int diff = 0;
    while(list1 && list2)
    {
        if((list1->data)<(list2->data))
        {
            if(list1->next)
            {
                list1->data += 10;
                list1->next->data--;
            }
            else
            {
                return NULL;
            }
        }
        diff = list1->data - list2->data;
        result(&head, diff);
        list1 = list1 -> next;
        list2 = list2 -> next;
    }
    while(list1)
    {
        if(list1->data<0)
        {
            if(list1->next)
            {
                list1->data += 10;
                list1->next->data--;
            }
            else
            {
                return  NULL;
            }
        }
        result(&head, list1->data);
        list1 = list1 -> next;
    }
    head= reverse(head);
    return head;
}

struct BigInteger add ( struct BigInteger A, struct BigInteger B)
{
    struct BigInteger C;
    struct node *list1 = A.head, *list2 = B.head;
    if((A.sign==0 && B.sign==0) || (A.sign==1 && B.sign==1))
    {
        C.head = summ(list1,list2);
        C.head = freed(C.head);
        C.length = length (C.head);
        C.sign = A.sign;
        return C;
    }
    if(A.sign == 0 && B.sign== 1)
    {
        if(A.length>B.length)
        {
            C.head = diff(list1,list2);
            C.head = freed(C.head);
            C.length = length(C.head);
            C.sign = A.sign;
            return C;
        }
        if(B.length>A.length)
        {
            C.head = diff(list2,list1);
            C.head = freed(C.head);
            C.length = length(C.head);
            C.sign = B.sign;
            return C;
        }
        C.head = diff(list1,list2);
        if(C.head==NULL)
        {
            C.head = diff(list2,list1);
            C.head = freed(C.head);
            C.length = length(C.head);
            C.sign = 1;
            return C;
        }
        C.head = freed(C.head);
        C.length = length(C.head);
        C.sign = 0;
        return C;
    }
    if(A.sign == 1 && B.sign== 0)
    {
        if(A.length>B.length)
        {
            C.head = diff(list1,list2);
            C.head = freed(C.head);
            C.length = length(C.head);
            C.sign= A.sign;
            return C;
        }
        if(B.length>A.length)
        {
            C.head = diff(list2,list1);
            C.head = freed(C.head);
            C.length = length(C.head);
            C.sign = B.sign;
            return C;
        }
        C.head= diff(list1,list2);
        if(C.head==NULL)
        {
            C.head= diff(list2,list1);
            C.head = freed(C.head);
            C.length = length(C.head);
            C.sign= 0;
            return C;
        }
        C.head = freed(C.head);
        C.length = length(C.head);
        C.sign = 1;
        return C;
    }
}

struct BigInteger sub ( struct BigInteger A, struct BigInteger B)
{
    struct BigInteger C;
    struct node *list1 = A.head, *list2 = B.head;
    if((A.sign == 1 && B.sign == 0) || (A.sign==0 && B.sign ==1))
    {
        C.head = summ (list1,list2);
        C.head = freed(C.head);
        C.length = length(C.head);
        C.sign = A.sign;
        return C;
    }
    if(A.sign==0 && B.sign==0)
    {
        if(A.length>B.length)
        {
            C.head = diff(list1,list2);
            C.head = freed(C.head);
            C.length = length(C.head);
            C.sign = 0;
            return C;
        }
        if(B.length>A.length)
        {
            C.head = diff(list2,list1);
            C.head = freed(C.head);
            C.length = length(C.head);
            C.sign = 1;
            return C;
        }
        C.head = diff(list1,list2);
        if(!(C.head))
        {
            C.head = diff(list2,list1);
            C.head = freed(C.head);
            C.length = length(C.head);
            C.sign = 1;
            return C;
        }
        C.head = freed(C.head);
        C.length = length(C.head);
        C.sign = 0;
        return C;
    }
    if(A.sign == 1 && B.sign== 1)
    {
        if(A.length>B.length)
        {
            C.head = diff(list1,list2);
            C.head = freed(C.head);
            C.length = length(C.head);
            C.sign = 1;
            return C;
        }
        if(B.length>A.length)
        {
            C.head = diff(list2,list1);
            C.head = freed(C.head);
            C.length = length(C.head);
            C.sign = 0;
            return C;
        }
        C.head = diff(list1,list2);
        if(C.head==NULL)
        {
            C.head = diff(list2,list1);
            C.head = freed(C.head);
            C.length = length(C.head);
            C.sign = 0;
            return C;
        }
        C.head = freed(C.head);
        C.length = length(C.head);
        C.sign = 1;
        return C;
    }
}

struct BigInteger mul (struct BigInteger A, struct BigInteger B)
{
    struct BigInteger C;
    struct node *head = NULL, *list1 = A.head, *list2 = B.head;
    struct node *mul1 = NULL, *mul2 = NULL;
    int pro, i = 0;
    while (list1)
    { 
        list2 = B.head;
        mul1 = NULL;
        int c = 0;
        for(int j=0; j<i; j++)
        {
            struct node *temp = newNode(0);
            temp->next = mul1;
            mul1 = temp;
        }
        while(list2)
        {
            pro = (list1->data)*(list2->data) + c;
            struct node *temp = newNode(pro%10);
            c = pro/10;
            temp->next = mul1;
            mul1 = temp;
            list2 = list2->next;
        
        }
        if(c>0)
        {
            struct node *temp = newNode(c);
            c = 0;
            temp->next = mul1;
            mul1 = temp;
        }
        mul1 = reverse(mul1);
        head = summ(mul1,mul2);
        i++;
        mul2 = head;
        list1 = list1->next;
    }
    C.head = mul2;
    C.head = freed(C.head);
    C.length = length(mul2);
    if(A.sign != B.sign)
        C.sign = 1;
    else
        C.sign = 0;
    return C;
}

struct BigInteger div1 (struct BigInteger A, struct BigInteger B)
{
    struct BigInteger C;
    struct node *head = newNode(-1);
    struct node *list1 = A.head, *list2 = B.head;
    struct node* temp = newNode(1);
    if(list2->next == NULL && list2->data == 0)
    {
        C.head = NULL;
        C.length = C.sign = 0;
        return C;
    }
    if(A.length < B.length)
        C.head = newNode(0);
    else
    {    
        while(list1)
        {
            list1 = diff(list1,list2);
            head = summ(head,temp);
        }
        C.head = head;
        C.head = freed(head);
    }
    free (temp);
    C.length = length(C.head);
    if(A.sign == B.sign)
        C.sign = 0;
    else
        C.sign = 1;
    return C;
}

struct BigInteger mod (struct BigInteger A, struct BigInteger B)
{
    struct BigInteger C;
    struct node *list1 = A.head, *list2 = B.head;
    C.head = A.head;
    if(A.length >= B.length)
    {
        while(list1)
        {
            list1 = diff(list1,list2);
            if(list1)
                C.head = list1;
        }
        C.head = freed(C.head);
    }
    C.length = length(C.head);
    C.sign = A.sign;
    return C;
}