/*
 * linked.c
 *
 *  Created on: 17. sep. 2015
 *      Author: larso
 */

#include "linked.h"
#include <string.h>

UnaryNode* CreateUnaryNode(void* data, size_t size)
{
    UnaryNode* node = NULL;
    if(data != NULL && size > 0)
    {
        node = malloc(sizeof(UnaryNode));
        if(node != NULL)
        {
            node->data = malloc(size);
            if(node->data != NULL)
            {
                memcpy(node->data, data, size);
                node->right = NULL;
            }
            else
            {
                free(node);
                node = NULL;
            }
        }
    }
    return node;
}

void DestroyUnaryNode(UnaryNode* node, DataDestructor destructor)
{
    if(node != NULL)
    {
        if(destructor != NULL)
        {
            (*destructor)(node->data);
        }
        else
        {
            free(node->data);
        }
        free(node);
    }
}

BinaryNode* CreateBinaryNode(void* data, size_t size)
{
    BinaryNode* node = NULL;
    if(data != NULL && size > 0)
    {
        node = malloc(sizeof(BinaryNode));
        if(node != NULL)
        {
            node->data = malloc(size);
            if(node->data != NULL)
            {
                memcpy(node->data, data, size);
                node->left = NULL;
                node->right = NULL;
            }
            else
            {
                free(node);
                node = NULL;
            }
        }
    }
    return node;
}

void DestroyBinaryNode(BinaryNode* node, DataDestructor destructor)
{
    if(node != NULL)
    {
        if(destructor != NULL)
        {
            (*destructor)(node->data);
        }
        else
        {
            free(node->data);
        }
        free(node);
    }
}
