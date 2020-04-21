// Copyright 2020 Myshkin Andrey
#include <numeric>
#include <utility>
#include <algorithm>
#include <gtest/gtest.h>
#include "./ops_omp.h"
#include "../../../modules/task_1/myshkin_a_radix_sort_double/radix_sort_double.h"


TEST(Senquential, Test_Numder_First) {
    const int length = 10;
    int sts = 0;
    int sts2 = 0;
    double *buffer = nullptr;
    double *buffer2 = nullptr;
    int num_threads = 2;

    if (length > 0) {
        buffer = reinterpret_cast<double*>(malloc(sizeof(double) * length));
        buffer2 = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    } else {
        sts = -1;
        ASSERT_EQ(sts, 0);
    }

    sts2 = getRandomArray(buffer, length, -1000.0, 1000.0);
    memcpy(buffer2, buffer, sizeof(double) * length);

    sts = RadixSort(buffer, length);
    sts2 = SortingCheck(buffer, length);

    sts = RadixSortOmp(buffer2, length, num_threads);
    sts2 = SortingCheck(buffer, length);

    sts = ArrayComparison(buffer, buffer2, length);

    if (sts2 == -1) sts = -1;

    if (buffer) { free(buffer); buffer = nullptr; }
    if (buffer2) { free(buffer); buffer = nullptr; }

    ASSERT_EQ(sts, 0);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

