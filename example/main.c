
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CountSortList.h"
#define COLOR_OK
#define CTEST_MAIN
#include "ctest.h"

#define TEST_START() \
    CountSortList_init();

#define TEST_RUN(array, result) \
    { \
        const int arraySize = sizeof(array)/sizeof(array[0]); \
        const int resultSize = sizeof(result)/sizeof(result[0]); \
        CountSortList_addArray(array, arraySize); \
        int sum = 0; \
        CountSortData outputArray[resultSize]; \
        CountSortList_output(outputArray, resultSize, &sum); \
        ASSERT_EQUAL(arraySize, sum); \
        for (int i=0; i<resultSize; i++) { \
            ASSERT_EQUAL(result[i].data, outputArray[i].data); \
            ASSERT_EQUAL(result[i].count, outputArray[i].count); \
        } \
    }

#define TEST_END() \
    CountSortList_deinit();

CTEST(Base, add) {
    TEST_START();
    CountSortList_add(1);
    int sum = 0;
    CountSortData result[1];
    CountSortList_output(result, 1, &sum);
    ASSERT_EQUAL(1, sum);
    ASSERT_EQUAL(1, result[0].data);
    ASSERT_EQUAL(1, result[0].count);
    TEST_END();
}

CTEST(Base, addArray) {
    TEST_START();
    int data[] = {1};
    CountSortData result[] = {{1,1}};
    TEST_RUN(data, result);
    TEST_END();
}

CTEST(Base, addMore) {
    TEST_START();
    int data[] = {1,2};
    CountSortData result[] = {{1,1},{2,1}};
    TEST_RUN(data, result);
    TEST_END();
}

CTEST(Base, reset) {
    TEST_START();
    CountSortList_add(1);
    CountSortList_reset();
    int data[] = {1};
    CountSortData result[] = {{1,1}};
    TEST_RUN(data, result);
    TEST_END();
}

CTEST(Base, size) {
    CountSortList_setInitSize(4);
    TEST_START();
    int data[] = {1,2,3,4,5,6,7,8};
    CountSortData result[] = {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
    TEST_RUN(data, result);
    TEST_END();
}

CTEST(SortData, NoNeedReSort) {
    TEST_START();
    {
        // add at head, no need re-sort
        int data[] = {1,1};
        CountSortData result[] = {{1,2}};
        TEST_RUN(data, result);
    }
    CountSortList_reset();
    {
        // prev's count is no-less than cur's new count, no need re-sort
        int data[] = {1,2,1,2};
        CountSortData result[] = {{1,2},{2,2}};
        TEST_RUN(data, result);
    }
    TEST_END();
}

CTEST(SortData, NeedReSort) {
    TEST_START();
    {
        // sort effect no head, no tail {a,b,c,d} => {a,c,b,d}
        int data[] = {1,1,1,2,2,3,3,4,3};
        CountSortData result[] = {{1,3},{3,3},{2,2},{4,1}};
        TEST_RUN(data, result);
    }
    CountSortList_reset();
    {
        // sort effect head {a,b,c} => {b,a,c}
        int data[] = {1,2,3,2};
        CountSortData result[] = {{2,2},{1,1},{3,1}};
        TEST_RUN(data, result);
    }
    CountSortList_reset();
    {
        // sort effect tail {a,b,c} => {a,c,b}
        int data[] = {1,1,2,3,3};
        CountSortData result[] = {{1,2},{3,2},{2,1}};
        TEST_RUN(data, result);
    }
    CountSortList_reset();
    {
        // sort effect head, tail {a,b} => {b,a}
        int data[] = {1,2,2};
        CountSortData result[] = {{2,2},{1,1}};
        TEST_RUN(data, result);
    }
    TEST_END();
}

int main(int argc, const char * argv[])
{
    return ctest_main(argc, argv);
}
