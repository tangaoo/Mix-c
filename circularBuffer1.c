/* This approach adds one bit to end and start pointers */
#include "circularBuffer1.h"
#include <stdlib.h>

void cbInit(CircularBuffer *cb, int size) 
{
	cb->size = size;
	cb->start = 0;
	cb->end = 0;
	cb->elems = (ElemType *)calloc(cb->size, sizeof(ElemType));
}

void cbPrint(CircularBuffer *cb) 
{
	printf("size=0x%x, start=%d, end=%d\n", cb->size, cb->start, cb->end);
}

int cbIsFull(CircularBuffer *cb) 
{
	return cb->end == (cb->start ^ cb->size); /* This inverts the most significant bit of start before comparison */
}

int cbIsEmpty(CircularBuffer *cb) 
{
	return cb->end == cb->start;
}

static int cbIncr(CircularBuffer *cb, int p) 
{
	return (p + 1)&(2 * cb->size - 1); /* start and end pointers incrementation is done modulo 2*size */
}

void cbWrite(CircularBuffer *cb, ElemType *elem) 
{
	cb->elems[cb->end&(cb->size - 1)] = *elem;
	if (cbIsFull(cb)) /* full, overwrite moves start pointer */
		cb->start = cbIncr(cb, cb->start);
	cb->end = cbIncr(cb, cb->end);
}

void cbRead(CircularBuffer *cb, ElemType *elem) 
{
	*elem = cb->elems[cb->start&(cb->size - 1)];
	cb->start = cbIncr(cb, cb->start);
}

void hello(void)
{}