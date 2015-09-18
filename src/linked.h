/*
 * linked.h
 *
 *  Created on: 17. sep. 2015
 *      Author: larso
 */

#ifndef SRC_LINKED_H_
#define SRC_LINKED_H_

#include <stdlib.h>
#include <stdbool.h>

enum
{
    LINKED_ERROR_NULLPOINTER,
    LINKED_ERROR_NODE_CREATION_FAILURE,
    LINKED_ERROR_OUT_OF_BOUNDS,
    LINKED_ERROR_NOT_FOUND
};

typedef struct UnaryNode
{
    void* data;
    struct UnaryNode* right;
} UnaryNode;

typedef struct BinaryNode
{
    void* data;
    struct BinaryNode* left, *right;
} BinaryNode;

typedef bool (*Predicate)(void*, void*);
typedef void (*Function)(void*, void*);
typedef void (*DataDestructor)(void*);

UnaryNode* CreateUnaryNode(void* data, size_t size);
void DestroyUnaryNode(UnaryNode* node, DataDestructor* destructor);

BinaryNode* CreateBinaryNode(void* data, size_t size);
void DestroyBinaryNode(BinaryNode* node, DataDestructor* destructor);

typedef struct
{
    size_t typeSize;
    DataDestructor* typeDestructor;
    UnaryNode* front, *back;
    size_t size;
} LinkedList;

LinkedList* CreateLinkedList(size_t typeSize, DataDestructor* typeDestructor);
void DestroyLinkedList(LinkedList* list);

int LinkedListPush(LinkedList* list, void* data);
int LinkedListAppend(LinkedList* list, void* data);
int LinkedListInsert(LinkedList* list, size_t index, void* data);

void* LinkedListAt(LinkedList* list, size_t index);
void* LinkedListFirstMatch(LinkedList* list, Predicate* predicate,
        void* predicateData);

int LinkedListRemove(LinkedList* list, void* toRemove);
int LinkedListRemoveIf(LinkedList* list, Predicate* predicate,
        void* predicateData);

int LinkedListForEach(LinkedList* list, Function* function, void* functionData);
int LinkedListForEachMatch(LinkedList* list, Predicate* predicate,
        void* predicateData, Function* function, void* functionData);

#endif /* SRC_LINKED_H_ */
