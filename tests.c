/*
 * tests.c
 *
 *  Created on: 17. sep. 2015
 *      Author: larso
 */

#include <stdio.h>
#include "src/linked.h"

typedef struct
{
    int x, y;
} Point;

void ShowPoint(void* element, void* data)
{
    Point* point = (Point*)element;
    printf("(%d, %d)\n", point->x, point->y);
}

int main(int argc, char** argv)
{
    LinkedList* list = CreateLinkedList(sizeof(Point), NULL);

    Point p;

    p.x = p.y = 0;
    LinkedListAppend(list, &p);
    p.x = 5;
    LinkedListAppend(list, &p);
    p.y = -5;
    LinkedListAppend(list, &p);
    p.x += p.y;
    LinkedListAppend(list, &p);

    printf("Data in list: \n");
    LinkedListForEach(list, &ShowPoint, NULL);

    DestroyLinkedList(list);
    return 0;
}
