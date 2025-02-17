#include <string.h>
// self-referential structure
struct Node {
   int id; // each listNode contains a character
   char name[20];
   struct Node *nextPtr; // pointer to next node
   struct Node *pPtr;
}; // end structure listNode

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*

// prototypes

int deletes( LLPtr *sPtr, int value );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int value, char name[] );
void printList( LLPtr currentPtr );
void instructions( void );


// display program instructions to user
void instructions( void )
{
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert( LLPtr *sPtr, int value , char name[])
{
   LLPtr newPtr; // pointer to new node
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list

   newPtr =(LLPtr) malloc( sizeof( LLnode ) ); // create node

   if ( newPtr != NULL ) { // is space available
      newPtr->id = value; // place value in node
      newPtr->nextPtr = NULL; // node does not link to another node
      strcpy(newPtr->name, name);
      previousPtr = NULL;
      currentPtr = *sPtr;

      // loop to find the correct location in the list
      while ( currentPtr != NULL && value > currentPtr->id ) {
         previousPtr = currentPtr; // walk to ...
         currentPtr = currentPtr->nextPtr; // ... next node
      } // end while

      // insert new node at beginning of list
      if ( previousPtr == NULL ) {
         newPtr->nextPtr = *sPtr;
         if(*sPtr) (*sPtr)->pPtr=newPtr;
         *sPtr = newPtr;
        
      } // end if
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->pPtr=previousPtr;
   
          
         newPtr->nextPtr = currentPtr;
         if(currentPtr) currentPtr->pPtr=newPtr;
 
         
      } // end else
   } // end if
   else {
      printf( "%d not inserted. No memory available.\n", value );
   } // end else
} // end function insert

// delete a list element
int deletes( LLPtr *sPtr, int value )
{
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer

   // delete first node
   if ( value == ( *sPtr )->id ) {
      tempPtr = *sPtr; // hold onto node being removed
      *sPtr = ( *sPtr )->nextPtr; // de-thread the node
      if(*sPtr) (*sPtr)->pPtr=NULL;
      free( tempPtr ); // free the de-threaded node
      return value;
   } // end if
   else {
      previousPtr = *sPtr;
      currentPtr = ( *sPtr )->nextPtr;

      // loop to find the correct location in the list
      while ( currentPtr != NULL && currentPtr->id != value ) {
         previousPtr = currentPtr; // walk to ...
         currentPtr = currentPtr->nextPtr; // ... next node
      } // end while

      // delete node at currentPtr
      if ( currentPtr != NULL ) {
         tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
         if(currentPtr)
            currentPtr=currentPtr->nextPtr;
         free(tempPtr);
         return value;
      } // end if
   } // end else

   return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( LLPtr currentPtr )
{
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else {
      puts( "The list is:" );

      // while not the end of the list
      while ( currentPtr->nextPtr!= NULL ) {
         printf( "%d %s -->", currentPtr->id , currentPtr->name);
         currentPtr = currentPtr->nextPtr;
      } // end while

      printf( "%d %s -->NULL\n",currentPtr->id, currentPtr->name);
       

     
       
   } // end else
} // end function printList


void printListR ( LLPtr currentPtr )
{
   if( isEmpty(currentPtr))
   {
      puts( "List is empty.\n");
   }
   else
   {

      while( currentPtr->nextPtr!=NULL)
         currentPtr=currentPtr->nextPtr;

         while( currentPtr->pPtr!=NULL)
         {
            printf( "%d %s -->", currentPtr->id, currentPtr->name );
            currentPtr=currentPtr->pPtr;
         }

      
      printf("%d %s -->NULL\n", currentPtr->id, currentPtr->name );
   }
}


void clearList(LLPtr *sPtr) {
   LLPtr tempPtr;
   while (*sPtr != NULL) {
      tempPtr = *sPtr;
      *sPtr = (*sPtr)->nextPtr;
      free(tempPtr);
   }
   puts("All nodes cleared.");
}
