/*
   Copyright 2022 I-A-S

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

// -----------------------------------------------------------------------
//                               Includes
// -----------------------------------------------------------------------
#include <stdint.h>
#include <iostream>

// -----------------------------------------------------------------------
//                         IATest Public Interface
// -----------------------------------------------------------------------
#define IATEST_EXECUTE_TEST_SET(TestSet) IATest::__Internal_ExecuteTestSet(#TestSet, TestSet)

#define IA_TEST_SET(SetName) void SetName(IATest::TestSetContext& context)

#define IA_TEST_EQ(Value, ExpectedValue) IATest::__Internal_TestEQ(context, #Value, Value, ExpectedValue)
#define IA_TEST_NE(Value, ExpectedValue) IATest::__Internal_TestNE(context, #Value, Value, ExpectedValue)

// -----------------------------------------------------------------------
//                       Internal Constant Definitions
// -----------------------------------------------------------------------
#define __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_RED     "\033[31m"
#define __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_GREEN   "\033[32m"
#define __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_YELLOW  "\033[33m"
#define __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_MAGENTA "\033[35m"
#define __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_DEFAULT "\033[39m"

// -----------------------------------------------------------------------
//                          IATest Implementation
// -----------------------------------------------------------------------
namespace IATest
{
    struct TestSetContext
    {
        TestSetContext(): m_passCount(0), m_failCount(0) {}
        ~TestSetContext() {}
    
        uint64_t m_passCount;
        uint64_t m_failCount;
    };

    typedef void (*TestSet_t)(TestSetContext& context);

    static void __Internal_ExecuteTestSet(const char* testSetName, TestSet_t testSet)
    {
        std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_MAGENTA "Started  Testing Set " << testSetName << "\n";
        TestSetContext context; testSet(context);
        std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_MAGENTA "Finished Testing Set " << testSetName;
        if(context.m_failCount == 0) std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_GREEN " ALL " << context.m_passCount << " TEST(S) PASSED!\n\n" __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_DEFAULT;
        else std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_RED " " << context.m_failCount << " OUT OF " << (context.m_passCount + context.m_failCount) << " TEST(S) FAILED!\n\n" __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_DEFAULT;
    }

    template<typename T_V, typename T_EV>
    static bool __Internal_TestEQ(TestSetContext& context, const char* description, T_V value, T_EV expectedValue)
    {
        std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_YELLOW "\tTesting " << description << "... ";
        bool passed = (value == expectedValue);
        if(passed)
        {
            std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_GREEN "PASS\n";
            context.m_passCount += 1;
        }
        else
        {
            std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_RED "FAIL. Expected '" << expectedValue << "', but got '" << value << "'\n";
            context.m_failCount += 1;
        }
        return passed;
    }

    template<typename T_V, typename T_EV>
    static bool __Internal_TestNE(TestSetContext& context, const char* description, T_V value, T_EV expectedValue)
    {
        std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_YELLOW "\tTesting " << description << "... ";
        bool passed = (value != expectedValue);
        if(passed)
        {
            std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_GREEN "PASS\n";
            context.m_passCount += 1;
        }
        else
        {
            std::cout << __IA_TEST_INTERNAL_ANSI_FG_COLOR_CODE_RED "FAIL. Expected not '" << expectedValue << "', but got '" << value << "'\n";
            context.m_failCount += 1;
        }
        return passed;
    }
};

#endif