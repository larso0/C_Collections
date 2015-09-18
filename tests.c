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

bool ContainsZero(void* element, void* data)
{
    Point* point = (Point*)element;
    return point->x == 0 || point->y == 0;
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

    printf("List:\n");
    LinkedListForEach(list, &ShowPoint, NULL);
    printf("List size = %d\n", (int)list->size);

    printf("Inserting into index 1\nList:\n");
    p.x = 12;
    p.y = -90;
    LinkedListInsert(list, 1, &p);
    LinkedListForEach(list, &ShowPoint, NULL);
    printf("List size = %d\n", (int)list->size);

    printf("Pushing a value\nList:\n");
    p.y = p.x;
    p.x = -2;
    LinkedListPush(list, &p);
    LinkedListForEach(list, &ShowPoint, NULL);
    printf("List size = %d\n", (int)list->size);

    printf("Removing points that contain zero\nList:\n");
    LinkedListRemoveIf(list, &ContainsZero, NULL);
    LinkedListForEach(list, &ShowPoint, NULL);
    printf("List size = %d\n", (int)list->size);

    DestroyLinkedList(list);
    return 0;
}
