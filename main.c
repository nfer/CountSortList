
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CountSortList.h"

#define TEST_START() \
    CountSortList_init();

#define TEST_RUN(array, result) \
    { \
        int sum = 0; \
        const int arraySize = sizeof(array)/sizeof(array[0]); \
        for (int i=0; i<arraySize; i++) \
            sum++; \
        CountSortList_addArray(array, arraySize); \
        const int resultSize = sizeof(result)/sizeof(result[0]); \
        CountSortData outputArray[resultSize]; \
        int outputSum = 0; \
        CountSortList_output(outputArray, arraySize, &outputSum); \
        if (outputSum != sum) { \
            printf("++++++++++++++++++assert %d, actually %d\n", sum, outputSum); \
            printf("------------------%s sum error, FAILED\n", __FUNCTION__); \
            CountSortList_dump(); \
        } \
        else \
            for (int i=0; i<resultSize; i++) \
                if (result[i].data != outputArray[i].data || result[i].count != outputArray[i].count) { \
                    printf("++++++++++++++++++assert data %d, actually data %d\n", result[i].data, outputArray[i].data); \
                    printf("++++++++++++++++++assert count %d, actually count %d\n", result[i].count, outputArray[i].count); \
                    printf("------------------%s output error, FAILED\n", __FUNCTION__); \
                    CountSortList_dump(); \
                } \
        printf("------------------%s PASS\n", __FUNCTION__); \
    }

#define TEST_END() \
    CountSortList_deinit();

void TestCase_1_0() {
    TEST_START();
    int data[] = {1};
    CountSortData result[] = {{1,1}};
    TEST_RUN(data, result);
    TEST_END();
}

void TestCase_1_1() {
    TEST_START();
    int data[] = {1,1};
    CountSortData result[] = {{1,2}};
    TEST_RUN(data, result);
    TEST_END();
}

void TestCase_reset() {
    TEST_START();
    CountSortList_add(1);
    CountSortList_add(2);
    CountSortList_reset();
    int data[] = {2,2,2};
    CountSortData result[] = {{2,3}};
    TEST_RUN(data, result);
    TEST_END();
}

void TestCase_size() {
    CountSortList_setInitSize(4);
    TEST_START();
    int data[] = {1,2,3,4,5,6,7,8};
    CountSortData result[] = {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
    TEST_RUN(data, result);
    TEST_END();
}

void TestCase_2_0() {
    TEST_START();
    int data[] = {1,3};
    CountSortData result[] = {{1,1}, {3,1}};
    TEST_RUN(data, result);
    TEST_END();
}

void TestCase_2_1() {
    TEST_START();
    int data[] = {1,1,3};
    CountSortData result[] = {{1,2}, {3,1}};
    TEST_RUN(data, result);
    TEST_END();
}

void TestCase_2_2() {
    TEST_START();
    int data[] = {1,3,3};
    CountSortData result[] = {{3,2}, {1,1}};
    TEST_RUN(data, result);
    TEST_END();
}

void TestCase_2_3() {
    TEST_START();
    int data[] = {1,3,1};
    CountSortData result[] = {{1,2}, {3,1}};
    TEST_RUN(data, result);
    TEST_END();
}

void TestCase_3_0() {
    TEST_START();
    int data[] = {1,3,5};
    CountSortData result[] = {{1,1}, {3,1}, {5,1}};
    TEST_RUN(data, result);
    TEST_END();
}

void TestCase_3_1() {
    TEST_START();
    int data[] = {1,1,3,5};
    CountSortData result[] = {{1,2}, {3,1}, {5,1}};
    TEST_RUN(data, result);
    TEST_END();
}

void TestCase_3_2() {
    TEST_START();
    int data[] = {1,3,1,5};
    CountSortData result[] = {{1,2}, {3,1}, {5,1}};
    TEST_RUN(data, result);
    TEST_END();
}

void TestCase_3_3() {
    TEST_START();
    int data[] = {1,3,5,1};
    CountSortData result[] = {{1,2}, {3,1}, {5,1}};
    TEST_RUN(data, result);
    TEST_END();
}

void TestCase_3_4() {
    TEST_START();
    int data[] = {1,3,3,5};
    CountSortData result[] = {{3,2}, {1,1}, {5,1}};
    TEST_RUN(data, result);
    TEST_END();
}

void TestCase_3_5() {
    TEST_START();
    int data[] = {1,3,5,3};
    CountSortData result[] = {{3,2}, {1,1}, {5,1}};
    TEST_RUN(data, result);
    TEST_END();
}

void TestCase_3_6() {
    TEST_START();
    int data[] = {1,3,5,5};
    CountSortData result[] = {{5,2}, {1,1}, {3,1}};
    TEST_RUN(data, result);
    TEST_END();
}

int main(int argc, char * argv[])
{
    TestCase_1_0();
    TestCase_1_1();
    TestCase_reset();
    TestCase_size();
    TestCase_2_0();
    TestCase_2_1();
    TestCase_2_2();
    TestCase_2_3();
    TestCase_3_0();
    TestCase_3_1();
    TestCase_3_2();
    TestCase_3_3();
    TestCase_3_4();
    TestCase_3_5();
    TestCase_3_6();
    // CountSortData array[3] = {{0,0}};
    // int sum = 0;
    // int arraySize = sizeof(array)/sizeof(array[0]);

    // CountSortList_init();
    // CountSortList_add(1);
    // CountSortList_add(3);
    // CountSortList_add(5);
    // CountSortList_add(5);
    // CountSortList_add(5);
    // CountSortList_add(3);
    // CountSortList_add(3);
    // CountSortList_dump();
    // CountSortList_output(array, arraySize, &sum);
    // CountSortList_deinit();

    // printf("sum %d\n", sum);
    // for (int i=0; i<arraySize; i++)
    //     printf("index %d data is %d, count is %d\n", i, array[0].data, array[0].count);
    return 0;
}
