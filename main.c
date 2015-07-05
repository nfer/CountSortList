
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CountSortList.h"
#define CTEST_MAIN
#include "ctest.h"

#define TEST_START() \
    CountSortList_init();

#define TEST_RUN(array, result) \
    { \
        const int arraySize = sizeof(array)/sizeof(array[0]); \
        CountSortList_addArray(array, arraySize); \
        int sum = 0, i; \
        for (i=0; i<arraySize; i++) \
            sum++; \
        int outputSum = 0; \
        const int resultSize = sizeof(result)/sizeof(result[0]); \
        CountSortData outputArray[resultSize]; \
        CountSortList_output(outputArray, resultSize, &outputSum); \
        ASSERT_EQUAL(sum, outputSum); \
        for (i=0; i<resultSize; i++) { \
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

int main(int argc, const char * argv[])
{
    return ctest_main(argc, argv);
}
