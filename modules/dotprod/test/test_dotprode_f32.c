// Copyright 2018-2019 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string.h>
#include "unity.h"
#include "freertos/FreeRTOS.h"
#include "freertos/portable.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_clk.h"
#include "soc/cpu.h"

#include "dsps_dotprod.h"
#include "dsp_tests.h"

TEST_CASE("dsps_dotprode_f32_ae32 functionality", "[dsps]")
{
    float check_value = 1235;
    int max_N = 1024;
    float *x = (float *)malloc(max_N * sizeof(float));
    float *y = (float *)malloc(max_N * sizeof(float));
    float *z = (float *)malloc(max_N * sizeof(float));

    for (int i = 0 ; i < max_N ; i++) {
        x[i] = 0;
        y[i] = 1000;
    }

    z[0] = check_value;
    z[2] = check_value + 1;

    for (int i = 1 ; i < 1024 ; i++) {
        esp_err_t status = dsps_dotprode_f32_ae32(x, y, &z[1], i, 1, 1);
        TEST_ASSERT_EQUAL(status, ESP_OK);
        TEST_ASSERT_EQUAL(check_value, z[0]);
        TEST_ASSERT_EQUAL(check_value + 1, z[2]);
        TEST_ASSERT_EQUAL(0, z[1]);
    }
    for (int i = 0 ; i < max_N ; i++) {
        x[i] = 1;
        y[i] = 3;
    }
    for (int i = 1 ; i < 1024 ; i++) {
        esp_err_t status = dsps_dotprode_f32_ae32(x, y, &z[1], i, 1, 1);
        TEST_ASSERT_EQUAL(status, ESP_OK);
        TEST_ASSERT_EQUAL(check_value, z[0]);
        TEST_ASSERT_EQUAL(check_value + 1, z[2]);
        TEST_ASSERT_EQUAL(i * 3, z[1]);
    }

    free(x);
    free(y);
    free(z);
}

TEST_CASE("dsps_dotprode_f32_ae32 benchmark", "[dsps]")
{
    int max_N = 1024;
    float *x = (float *)malloc(max_N * sizeof(float));
    float *y = (float *)malloc(max_N * sizeof(float));
    float *z = (float *)malloc(max_N * sizeof(float));

    for (int i = 0 ; i < max_N ; i++) {
        x[i] = 0;
        y[i] = 1000;
    }

    unsigned int start_b = xthal_get_ccount();
    int repeat_count = 1024;
    for (int i = 0 ; i < repeat_count ; i++) {
        dsps_dotprode_f32_ae32(x, y, &z[1], 1024, 1, 1);
    }
    unsigned int end_b = xthal_get_ccount();

    float total_b = end_b - start_b;
    float cycles = total_b / (1024 * repeat_count);
    printf("Benchmark dsps_dotprode_f32_ae32 - %f per sample + overhead.\n", cycles);
    float min_exec = 3;
    float max_exec = 6;
    TEST_ASSERT_EXEC_IN_RANGE(min_exec, max_exec, cycles);

    free(x);
    free(y);
    free(z);
}


TEST_CASE("dsps_dotprode_f32_ansi functionality", "[dsps]")
{
    float check_value = 1235;
    int max_N = 1024;
    float *x = (float *)malloc(max_N * sizeof(float));
    float *y = (float *)malloc(max_N * sizeof(float));
    float *z = (float *)malloc(max_N * sizeof(float));

    for (int i = 0 ; i < max_N ; i++) {
        x[i] = 0;
        y[i] = 1000;
    }

    z[0] = check_value;
    z[2] = check_value + 1;

    for (int i = 1 ; i < 1024 ; i++) {
        esp_err_t status = dsps_dotprode_f32_ansi(x, y, &z[1], i, 1, 1);
        TEST_ASSERT_EQUAL(status, ESP_OK);
        TEST_ASSERT_EQUAL(check_value, z[0]);
        TEST_ASSERT_EQUAL(check_value + 1, z[2]);
        TEST_ASSERT_EQUAL(0, z[1]);
    }
    for (int i = 0 ; i < max_N ; i++) {
        x[i] = 1;
        y[i] = 3;
    }
    for (int i = 1 ; i < 1024 ; i++) {
        esp_err_t status = dsps_dotprode_f32_ansi(x, y, &z[1], i, 1, 1);
        TEST_ASSERT_EQUAL(status, ESP_OK);
        TEST_ASSERT_EQUAL(check_value, z[0]);
        TEST_ASSERT_EQUAL(check_value + 1, z[2]);
        TEST_ASSERT_EQUAL(i * 3, z[1]);
    }

    free(x);
    free(y);
    free(z);
}

TEST_CASE("dsps_dotprode_f32_ansi benchmark", "[dsps]")
{
    int max_N = 1024;
    float *x = (float *)malloc(max_N * sizeof(float));
    float *y = (float *)malloc(max_N * sizeof(float));
    float *z = (float *)malloc(max_N * sizeof(float));

    for (int i = 0 ; i < max_N ; i++) {
        x[i] = 0;
        y[i] = 1000;
    }

    unsigned int start_b = xthal_get_ccount();
    int repeat_count = 1024;
    for (int i = 0 ; i < repeat_count ; i++) {
        dsps_dotprode_f32_ansi(x, y, &z[1], 1024, 1, 1);
    }
    unsigned int end_b = xthal_get_ccount();

    float total_b = end_b - start_b;
    float cycles = total_b / (1024 * repeat_count);
    printf("Benchmark dsps_dotprode_f32_ansi - %f per sample + overhead.\n", cycles);
    float min_exec = 10;
    float max_exec = 20;
    TEST_ASSERT_EXEC_IN_RANGE(min_exec, max_exec, cycles);

    free(x);
    free(y);
    free(z);
}