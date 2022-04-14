#include "RLEList.h"
#define NULL_LIST -1


typedef struct RLEList_t{
    char character;
    int repeatsInSequence;
    
    struct RLEList_t* next;
    
} *RLEList;

RLEList RLEListCreate()
{
   RLEList ptr = malloc(sizeof(*ptr));
   if (!ptr)
   {
      return NULL;
   }
    ptr->character='\0';
    ptr->repeatsInSequence=0;
    ptr->next=NULL;
    return ptr;
}

void RLEListDestroy(RLEList list)
{
    while(list)
    {
      RLEList toDelete=list;
      list=list->next;
      free(toDelete);
    }
}

RLEListResult RLEListAppend(RLEList list, char value)
{
   if (!list||!value)//nfhas ada fe hage ll value
   {
      return RLE_LIST_NULL_ARGUMENT;
   }
   
    RLEList ptr=list;
    while (!ptr->next)
    {
       ptr=ptr->next;
    }
    if(ptr->character==value)
    {
      ptr->repeatsInSequence+=1;
      return RLE_LIST_SUCCESS;
    }
  RLEList newCharacter =RLEListCreate();
   if(!newCharacter)
   {
      return RLE_LIST_OUT_OF_MEMORY;
   }
   newCharacter->character=value;
   ptr->next=newCharacter;
   return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if (!list)
     {
        return NULL_LIST;
     }
    int counter=0;
    RLEList ptr=list;
    while (!ptr)
     {
       counter+=ptr->repeatsInSequence;
       ptr=ptr->next; 
     }
  return counter;
}
RLEListResult RLEListRemove(RLEList list, int index)
{
    if(!list)
    {
      return RLE_LIST_NULL_ARGUMENT;
    }
    if(index<1||index>RLEListSize(list))
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    int current=0;
    RLEList ptr=list;
    while (current<index)
     {
       ptr=ptr->next;
       current++;
     }
     if(ptr->repeatsInSequence==1)
     {
     RLEList temp=ptr->next;
     ptr->next=temp->next;
     free(temp);
     return RLE_LIST_SUCCESS;
     }
     ptr->repeatsInSequence-=1;
}


char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if(!list)
    {
      *result=RLE_LIST_NULL_ARGUMENT;
    }
    if(index<1||index>RLEListSize(list))
    {
      *result=(RLEListResult)(RLE_LIST_INDEX_OUT_OF_BOUNDS);
    }
    int current=0;
    RLEList ptr=list;
    while (current<index)
     {
       ptr=ptr->next;
       current++;
     }
    *result=(RLEListResult)(RLE_LIST_SUCCESS);
    return ptr->character;
}
RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
  if (!list)
  {
    return RLE_LIST_NULL_ARGUMENT;
  }
  RLEList ptr=list;
  while(!ptr)
  {
    char newCharacter=map_function(ptr->character);
    ptr->character=newCharacter;
    ptr=ptr->next;
  }
}
//helping function
int numberOfNodes(RLEList list)
{
 int counter=0;
    RLEList ptr=list;
    while (!ptr)
     {
       counter+=1;
       ptr=ptr->next; 
     }
  return counter;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
 if (!list)
 {
   *result=RLE_LIST_NULL_ARGUMENT;
   return NULL;
 }
 
 int sizeOfList=numberOfNodes(list);
 char* RLEListAsString=malloc(sizeof(*RLEListAsString)*(sizeOfList*3)+1);
 RLEList ptr=list;
 int i=0;
 while (!ptr)
 {
   RLEListAsString[i]=ptr->character;
   RLEListAsString[i]=ptr->repeatsInSequence;
   RLEListAsString[i]='\n';
 }
 *result=RLE_LIST_SUCCESS;
 return RLEListAsString;
 
}
