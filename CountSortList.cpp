
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CountSortList.h"

#define LIST_INCREASE_SIZE  (1024)

typedef struct SortLinkList {
    int index;
    struct SortLinkList *prev;
    struct SortLinkList *next;
}SortLinkList;

CountSortData * g_dataList = NULL;
SortLinkList  * g_linkList = NULL;
SortLinkList  * g_linkHead = NULL;
SortLinkList  * g_linkTail = NULL;
int g_listSize = LIST_INCREASE_SIZE;
int g_dataSize = 0;
int g_dataSum = 0;

void CountSortList_init() {
    g_dataList = (CountSortData *)calloc(g_listSize, sizeof(CountSortData));
    g_linkList = (SortLinkList *)calloc(g_listSize, sizeof(SortLinkList));

    g_linkHead = g_linkTail = NULL;
}
void CountSortList_deinit() {
    free(g_dataList);
    free(g_linkList);
    g_dataList = NULL;
    g_linkList = NULL;
    g_linkHead = NULL;
    g_linkTail = NULL;
    g_dataSize = 0;
    g_dataSum = 0;
}
void CountSortList_reset() {
    memset(g_dataList, 0x00, g_dataSize * sizeof(CountSortData));
    memset(g_linkList, 0x00, g_dataSize * sizeof(SortLinkList));
    g_linkHead = NULL;
    g_linkTail = NULL;
    g_listSize = LIST_INCREASE_SIZE;
    g_dataSize = 0;
    g_dataSum = 0;
}

void CountSortList_setInitSize(int size) {
    if (NULL == g_dataList && NULL == g_linkList)
        g_listSize = size;
    else
        printf("Please invoke this function before CountSortList_init.\n");
}

void CountSortList_add(int data) {
    g_dataSum++;
    int i = 0;
    for (i=0; i<g_dataSize; i++) {
        if (g_dataList[i].data == data)
            break;
    }

    if (i == g_dataSize) { // not found this data in current list
        g_dataList[i].data = data;
        g_dataList[i].count = 1;

        if (g_linkTail == NULL) {
            g_linkHead = g_linkTail = g_linkList;
            g_linkTail->index = 0;
            g_linkTail->prev = NULL;
            g_linkTail->next = NULL;
        }
        else {
            // last tail
            g_linkTail->next = g_linkList + g_dataSize;

            // current tail
            g_linkTail->next->prev = g_linkTail;
            g_linkTail = g_linkTail->next;
            g_linkTail->index = g_dataSize;
            g_linkTail->next = NULL;
        }

        g_dataSize++;
        if (g_dataSize > g_listSize*8/10) { // need increase list size
            g_listSize *= 2;

            CountSortData * dataList = (CountSortData *)realloc (g_dataList, g_listSize*sizeof(CountSortData));
            if (dataList == NULL)
                printf("realloc %ld memory, but failed.", g_listSize * sizeof(CountSortData));
            else
                g_dataList = dataList;

            SortLinkList * linkList = (SortLinkList *)realloc (g_linkList, g_listSize*sizeof(SortLinkList));
            if (linkList == NULL)
                printf("realloc %ld memory, but failed.", g_listSize * sizeof(SortLinkList));
            else
                g_linkList = linkList;
            // printf("increase list size to %d.\n", g_listSize);
        }
        return ;
    }
    else {
        g_dataList[i].count++;
        // printf("[%d]new Count is %d\n", i, g_dataList[i].count);

        SortLinkList  * link = g_linkTail;
        SortLinkList  * curData = NULL;
        // printf("g_linkHead is %p, g_linkTail is %p\n", g_linkHead, g_linkTail);

        while (link && link->prev) {
            // printf("check link->index %d, count %d\n", link->index, g_dataList[link->index].count);
            if (g_dataList[link->index].data == data) { // has found the data
                // printf("found it with link->index %d\n", link->index);
                curData = link;
                link->prev->next = link->next;
                if (link->next)
                    link->next->prev = link->prev;
                if (link == g_linkTail) {
                    g_linkTail = link->prev;
                    // printf("new g_linkTail is %p\n", g_linkTail);
                }
                link = link->prev;
                continue;
            }

            if (g_dataList[link->index].count == g_dataList[i].count) {
                link->next->prev = curData;
                curData->next = link->next;
                link->next = curData;
                curData->prev = link;
                break;
            }
            link = link->prev;
        }

        if ((curData == NULL) && (link == g_linkHead || link == g_linkTail)) {
            return;
        }

        if (link || link->prev == NULL) { //means curData is the max data
            g_linkHead->prev = curData;
            curData->next = g_linkHead;
            curData->prev = NULL;
            g_linkHead = curData;
            // printf("new g_linkHead is %p\n", g_linkHead);
        }
    }
}

void CountSortList_addArray(int * data, int size) {
    for (int i=0; i<size; i++)
        CountSortList_add(data[i]);
}

void CountSortList_raw(CountSortData * dataList, int size, int * sum) {
    int i = 0;
    while (i < size && i < g_dataSize) {
        dataList[i].data = g_dataList[i].data;
        dataList[i].count = g_dataList[i].count;
        i++;
    }
    *sum = g_dataSum;
}

void CountSortList_output(CountSortData * dataList, int size, int * sum) {
    SortLinkList  * link = g_linkHead;
    int i = 0;
    while (link && i < size) {
        dataList[i].data = g_dataList[link->index].data;
        dataList[i].count = g_dataList[link->index].count;
        link = link->next;
        i++;
    }
    *sum = g_dataSum;
}

void CountSortList_dump() {
    for (int i=0; i<g_dataSize; i++) {
        printf("[%d] data %d, count %d\n", i, g_dataList[i].data, g_dataList[i].count);
    }

    int index = 0;
    SortLinkList  * link = g_linkHead;
    while(link) {
        printf("[%d] link index %d, data %d, count %d\n", index, link->index,
            g_dataList[link->index].data, g_dataList[link->index].count);
        index++;
        link = link->next;
    }
}