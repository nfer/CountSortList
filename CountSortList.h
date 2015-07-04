#ifndef COUNT_SORTLIST_H_INCLUDED
#define COUNT_SORTLIST_H_INCLUDED

typedef struct CountSortData{
    int data;
    int count;
}CountSortData;

void CountSortList_init();
void CountSortList_deinit();
void CountSortList_reset();
void CountSortList_setInitSize(int size);

void CountSortList_add(int data);
void CountSortList_addArray(int * data, int size);
void CountSortList_raw(CountSortData * dataList, int size, int * sum);
void CountSortList_output(CountSortData * dataList, int size, int * sum);
void CountSortList_dump();

#endif /*COUNT_SORTLIST_H_INCLUDED */
