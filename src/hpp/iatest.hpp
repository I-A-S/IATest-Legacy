/*
   Copyright 2021 I-A-S

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef _IA_TEST_HPP_
#define _IA_TEST_HPP_

/* Standard Includes */
#include <iostream>

/* Internal Constant Definitions */
#define __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_RED     "\033[31m"
#define __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_GREEN   "\033[32m"
#define __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_YELLOW  "\033[33m"
#define __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_MAGENTA "\033[35m"
#define __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_DEFAULT "\033[39m"

/* Internal Global Variables */
size_t __ia_test_internal_g_method_set_pass_count = SIZE_MAX;
size_t __ia_test_internal_g_method_set_fail_count = SIZE_MAX;

#define IA_TEST_RUN() __ia_test_internal_main()
#define IA_TEST_MAIN() void __ia_test_internal_main()

#define IA_TEST_START_METHOD_SET(method_set_name)\
{\
    if(__ia_test_internal_g_method_set_pass_count != SIZE_MAX)\
    {\
        std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_RED "Error : IA_TEST_START_METHOD_SET : IATest is in an invalid state. Did you forget to call IA_TEST_END_METHOD_SET()?\n" __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_DEFAULT;\
        return;\
    }\
    std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_MAGENTA "Started  Testing Method Set : " << #method_set_name << "\n";\
    __ia_test_internal_g_method_set_pass_count = 0;\
    __ia_test_internal_g_method_set_fail_count = 0;\
}

#define IA_TEST_END_METHOD_SET(method_set_name)\
{\
    if(__ia_test_internal_g_method_set_pass_count == SIZE_MAX)\
    {\
        std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_RED "Error : IA_TEST_END_METHOD_SET : IATest is in an invalid state. Did you forget to call IA_TEST_START_METHOD_SET()?\n" __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_DEFAULT;\
        return;\
    }\
    std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_MAGENTA "Finished Testing Method Set : " << #method_set_name;\
    size_t _total_test_count = __ia_test_internal_g_method_set_pass_count + __ia_test_internal_g_method_set_fail_count;\
    if(__ia_test_internal_g_method_set_fail_count == 0) std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_GREEN "  ALL " << _total_test_count << " TEST(S) PASSED!";\
    else std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_RED " " << __ia_test_internal_g_method_set_fail_count << " OUT OF " << _total_test_count << " TEST(S) FAILED!";\
    std::cout << "\n" __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_DEFAULT;\
    __ia_test_internal_g_method_set_pass_count = SIZE_MAX;\
    __ia_test_internal_g_method_set_fail_count = SIZE_MAX;\
}

#define IA_TEST_METHOD_EQ(method, expected_result)\
{\
    auto result = method;\
    std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_YELLOW "\t\tTesting Method : " << #method << "... ";\
    if(result == expected_result)\
    {\
        std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_GREEN "PASS\n";\
        __ia_test_internal_g_method_set_pass_count += 1;\
    }\
    else\
    {\
        std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_RED "FAIL. Expected: \'" << #expected_result << "\', but got : \'" << result << "\'\n";\
        __ia_test_internal_g_method_set_fail_count += 1;\
    }\
}

#define IA_TEST_METHOD_NE(method, expected_result)\
{\
    auto result = method;\
    std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_YELLOW "\t\tTesting Method : " << #method << "... ";\
    if(result != expected_result)\
    {\
        std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_GREEN "PASS\n";\
        __ia_test_internal_g_method_set_pass_count += 1;\
    }\
    else\
    {\
        std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_RED "FAIL. Expected : not \'" << #expected_result << "\', but got \'" << result << "\'\n";\
        __ia_test_internal_g_method_set_fail_count += 1;\
    }\
}

#endif