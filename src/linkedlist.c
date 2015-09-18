/*
 * linkedlist.c
 *
 *  Created on: 17. sep. 2015
 *      Author: larso
 */

#include "linked.h"

LinkedList* CreateLinkedList(size_t typeSize, DataDestructor typeDestructor)
{
    LinkedList* list = NULL;
    if(typeSize > 0)
    {
        list = malloc(sizeof(LinkedList));
        if(list != NULL)
        {
            list->typeSize = typeSize;
            list->typeDestructor = typeDestructor;
            list->front = NULL;
            list->back = NULL;
            list->size = 0;
        }
    }
    return list;
}

void DestroyLinkedList(LinkedList* list)
{
    if(list != NULL)
    {
        UnaryNode* iter = list->front;
        while(iter != NULL)
        {
            UnaryNode* tmp = iter;
            iter = iter->right;
            DestroyUnaryNode(tmp, list->typeDestructor);
        }
    }
}

int LinkedListPush(LinkedList* list, void* data)
{
    int error = 0;
    if(list == NULL || data == NULL)
    {
        error = LINKED_ERROR_NULLPOINTER;
    }
    else
    {
        UnaryNode* node = CreateUnaryNode(data, list->typeSize);
        if(node == NULL)
        {
            error = LINKED_ERROR_NODE_CREATION_FAILURE;
        }
        else
        {
            node->right = list->front;
            list->front = node;
            if(list->back == NULL)
            {
                list->back = node;
            }
            list->size++;
        }
    }
    return error;
}

int LinkedListAppend(LinkedList* list, void* data)
{
    int error = 0;
    if(list == NULL || data == NULL)
    {
        error = LINKED_ERROR_NULLPOINTER;
    }
    else
    {
        UnaryNode* node = CreateUnaryNode(data, list->typeSize);
        if(node == NULL)
        {
            error = LINKED_ERROR_NODE_CREATION_FAILURE;
        }
        else
        {
            if(list->back == NULL)
            {
                list->front = list->back = node;
            }
            else
            {
                list->back->right = node;
                list->back = node;
            }
            list->size++;
        }
    }
    return error;
}

int LinkedListInsert(LinkedList* list, size_t index, void* data)
{
    int error = 0;
    if(list == NULL || data == NULL)
    {
        error = LINKED_ERROR_NULLPOINTER;
    }
    else
    {
        if(index > list->size)
        {
            error = LINKED_ERROR_OUT_OF_BOUNDS;
        }
        else
        {
            if(index == list->size)
            {
                error = LinkedListAppend(list, data);
            }
            else if(index == 0)
            {
                error = LinkedListPush(list, data);
            }
            else
            {
                UnaryNode* node = CreateUnaryNode(data, list->typeSize);
                if(node == NULL)
                {
                    error = LINKED_ERROR_NODE_CREATION_FAILURE;
                }
                else
                {
                    UnaryNode* tmp = list->front;
                    size_t i = 0;
                    for(; i < index; i++)
                    {
                        tmp = tmp->right;
                    }
                    node->right = tmp->right->right;
                    tmp->right = node;
                    list->size++;
                }
            }
        }
    }
    return error;
}

void* LinkedListAt(LinkedList* list, size_t index)
{
    void* result = NULL;
    if(list != NULL && index < list->size)
    {
        UnaryNode* tmp = list->front;
        size_t i = 0;
        for(; i <= index; i++)
        {
            tmp = tmp->right;
        }
        result = tmp->data;
    }
    return result;
}

void* LinkedListFirstMatch(LinkedList* list, Predicate predicate, void* predicateData)
{
    void* result = NULL;
    if(list != NULL && predicate != NULL)
    {
        UnaryNode* iter = list->front;
        for(; iter != NULL; iter = iter->right)
        {
            if((*predicate)(iter->data, predicateData))
            {
                result = iter->data;
                break;
            }
        }
    }
    return result;
}

int LinkedListRemove(LinkedList* list, void* toRemove)
{
    int error = 0;
    if(list == NULL || toRemove == NULL)
    {
        error = LINKED_ERROR_NULLPOINTER;
    }
    else if(list->size > 0)
    {
        if(toRemove == list->front->data)
        {
            UnaryNode* tmp = list->front;
            list->front = tmp->right;
            if(list->back == tmp)
            {
                list->back = NULL;
            }
            DestroyUnaryNode(tmp, list->typeDestructor);
            list->size--;
        }
        else if(list->size == 1 && toRemove == list->back->data)
        {
            list->front = NULL;
            DestroyUnaryNode(list->back, list->typeDestructor);
            list->back = NULL;
            list->size--;
        }
        else
        {
            UnaryNode* prev = list->front;
            UnaryNode* tmp = prev->right;
            while(tmp != NULL && tmp->data != toRemove)
            {
                prev = tmp;
                tmp = tmp->right;
            }
            if(tmp == NULL)
            {
                error = LINKED_ERROR_NOT_FOUND;
            }
            else
            {
                prev->right = tmp->right;
                DestroyUnaryNode(tmp, list->typeDestructor);
                list->size--;
            }
        }
    }
    else
    {
        error = LINKED_ERROR_NOT_FOUND;
    }
    return error;
}

int LinkedListRemoveIf(LinkedList* list, Predicate predicate, void* predicateData)
{
    int error = 0;
    if(list == NULL || predicate == NULL)
    {
        error = LINKED_ERROR_NULLPOINTER;
    }
    else if(list->size > 0)
    {
        if((*predicate)(list->front->data, predicateData))
        {
            UnaryNode* tmp = list->front;
            list->front = tmp->right;
            if(list->back == tmp)
            {
                list->back = NULL;
            }
            DestroyUnaryNode(tmp, list->typeDestructor);
            list->size--;
        }
        else if(list->size == 1 && (*predicate)(list->back->data, predicateData))
        {
            list->front = NULL;
            DestroyUnaryNode(list->back, list->typeDestructor);
            list->back = NULL;
            list->size--;
        }
        else
        {
            UnaryNode* prev = list->front;
            UnaryNode* tmp = prev->right;
            while(tmp != NULL && !(*predicate)(tmp->data, predicateData))
            {
                prev = tmp;
                tmp = tmp->right;
            }
            if(tmp == NULL)
            {
                error = LINKED_ERROR_NOT_FOUND;
            }
            else
            {
                prev->right = tmp->right;
                DestroyUnaryNode(tmp, list->typeDestructor);
                list->size--;
            }
        }
    }
    else
    {
        error = LINKED_ERROR_NOT_FOUND;
    }
    return error;
}

int LinkedListForEach(LinkedList* list, Function function, void* functionData)
{
    int error = 0;
    if(list == NULL || function == NULL)
    {
        error = LINKED_ERROR_NULLPOINTER;
    }
    else
    {
        UnaryNode* iter = list->front;
        for(; iter != NULL; iter = iter->right)
        {
            (*function)(iter->data, functionData);
        }
    }
    return error;
}

int LinkedListForEachMatch(LinkedList* list, Predicate predicate,
        void* predicateData, Function function, void* functionData)
{
    int error = 0;
    if(list == NULL || predicate == NULL || function == NULL)
    {
        error = LINKED_ERROR_NULLPOINTER;
    }
    else
    {
        UnaryNode* iter = list->front;
        for(; iter != NULL; iter = iter->right)
        {
            if((*predicate)(iter->data, predicateData))
            {
                (*function)(iter->data, functionData);
            }
        }
    }
    return error;
}
