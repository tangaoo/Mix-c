/* note: user's buffer size must be set 2 power, A detailed reference Wikipedia*/

#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <stdio.h>
#include <malloc.h>

typedef int ElemType;  //define for user, such as char,int,struct...

					   /* Circular buffer object */
typedef struct {
	int         size;   /* maximum number of elements           */
	int         start;  /* index of oldest element              */
	int         end;    /* index at which to write new element  */
	ElemType   *elems;  /* vector of elements                   */
} CircularBuffer;

extern void cbInit(CircularBuffer *cb, int size);
extern void cbPrint(CircularBuffer *cb);
extern int cbIsFull(CircularBuffer *cb);
extern int cbIsEmpty(CircularBuffer *cb);
extern void cbWrite(CircularBuffer *cb, ElemType *elem);
extern void cbRead(CircularBuffer *cb, ElemType *elem);


#endif // !__CIRCULAR_BUFFER_H__

