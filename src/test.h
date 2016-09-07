/* JPEG GPU project
Copyright (c) 2014-2016 JPEG GPU project contributors.  All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License"); you may not
 use this file except in compliance with the License.
You may obtain a copy of the License at:

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed
 under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and limitations
 under the License. */

#if !defined(_test_H)
# define _test_H

#include <math.h>
#include <string.h>
#include "logging.h"

typedef void (*glj_test_suite_before_func)(void *ctx);
typedef void (*glj_test_suite_after_func)(void *ctx);
typedef void (*glj_test_func)(void *ctx);

typedef struct glj_test glj_test;

struct glj_test {
  const char *name;
  glj_test_func func;
  int checks;
  int errors;
};

void glj_test_reset(glj_test *test);

typedef struct glj_test_suite glj_test_suite;

struct glj_test_suite {
  glj_test_suite_before_func before;
  glj_test_suite_after_func after;
  glj_test *tests;
  int ntests;
};

int glj_test_suite_run(glj_test_suite *ts, void *ctx);

extern glj_test *glj_active_test;

#define GLJ_TEST(cond) \
  do { \
    glj_active_test->checks++; \
    if (!(cond)) { \
      GLJ_LOG((GLJ_LOG_TEST, GLJ_LOG_INFO, "%s, line %d: %s Failed!", \
       __FILE__, __LINE__, #cond)); \
      glj_active_test->errors++; \
    } \
  } \
  while(0)

#define GLJ_TEST_EQ(x, y, delta) \
 GLJ_TEST(fabs((x) - (y)) < delta)

#define GLJ_TEST_STRCMP(x, y) \
 GLJ_TEST(strcmp(x, y) == 0)

#define GLJ_TEST_STRICMP(x, y) \
 GLJ_TEST(strcasecmp(x, y) == 0)

#endif
