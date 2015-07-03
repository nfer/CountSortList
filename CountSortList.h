#ifndef COUNT_SORTLIST_H_INCLUDED
#define COUNT_SORTLIST_H_INCLUDED

typedef struct CountSortList_Data{
    int data;
    int count;
}CountSortList_Data;

void CountSortList_init();
void CountSortList_deinit();
void CountSortList_reset();

void CountSortList_add(int data);
void CountSortList_output(CountSortList_Data * dataList, int size, int * sum);

#endif /*COUNT_SORTLIST_H_INCLUDED */
