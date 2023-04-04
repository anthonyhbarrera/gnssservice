/************  Copyright 2004-2017 FICOSA CORPORATIVE ELECTRONICS  ********//**
* Generic header that serves as main for the GoogleTest and GoogleMock
* Framework integrated in Ficosa for Unit testing.
*******************************************************************************/

#ifndef TEST_SETUP_H
#define TEST_SETUP_H

/* -------------------------------- Includes -------------------------------- */

#include <gtest/gtest.h>
#include "coverageEnable.h"

/* --------------------------------- Defines -------------------------------- */

/**
 * @brief
 * Define to add the sw component name as a property for the report generation.
 */
#define TEST_SET_HEADER(swcomponent)                    void Environment::TestStart(void){::testing::Test::RecordProperty("swcomp", swcomponent);}

/**
 * @brief
 * Define to add a custom description for the test.
 */
#define TEST_SET_DESCRIPTION(text)                      RecordProperty("description", text)

/**
 * @brief
 * Define to add the sw component requirements into the report. Not required.
 */
#define TEST_SET_REQUIREMENTS(text)                     RecordProperty("requirements", text)

/**
 * @brief
 * Define to add the sw component conditions into the report. If not present it will try to retrieve it from the testname.
 */
#define TEST_SET_CONDITIONS(text)                       RecordProperty("conditions", text)

/**
 * @brief
 * Define to add the sw component actions into the report. If not present it will try to retrieve it from the testname.
 */
#define TEST_SET_ACTIONS(text)                          RecordProperty("action", text)

/**
 * @brief
 * Define to add the sw component expectations into the report. If not present it will try to retrieve it from the testname.
 */
#define TEST_SET_EXPECTED(text)                         RecordProperty("expected", text)

/**
 * @brief
 * Define to justify the remaining func coverage.
 */
#define TEST_JUSTIFY_MISSING_COVERAGE(src, func, text)  RecordProperty("justified_src", src);RecordProperty("justified_func", func);RecordProperty("justified_text", text)


/* ------------------------------- Data types ------------------------------- */
/* ---------------------------- Global Variables ---------------------------- */
/* -------------------------------- Routines -------------------------------- */

/**
 * @brief The Environment class
 */
class Environment : public ::testing::Environment{
    public:
    virtual ~Environment() {}
    // Override this to define how to set up the environment.
    virtual void SetUp() {
#ifdef COVERAGE_ENABLED
    #if defined(COVERAGE_MCDC)
        ::testing::Test::RecordProperty("coveragemetric", "Condition/Decision");
    #elif defined(COVERAGE_BRANCH)
        ::testing::Test::RecordProperty("coveragemetric", "Branch");
    #else
        ::testing::Test::RecordProperty("coveragemetric", "Undefined");
    #endif
#else
        ::testing::Test::RecordProperty("coveragemetric", "Coverage disabled");
#endif
        TestStart();
    }
    // Override this to define how to tear down the environment.
    virtual void TearDown() {}
    void TestStart(void);
};

class CodeCoverageListener : public ::testing::TestEventListener
{
    public:
    // Fired before any test activity starts.
    virtual void OnTestProgramStart(const ::testing::UnitTest& unit_test){}
    // one iteration if GTEST_FLAG(repeat) is set. iteration is the iteration
    // index, starting from 0.
    virtual void OnTestIterationStart(const ::testing::UnitTest& unit_test, int iteration){}
    // Fired before environment set-up for each iteration of tests starts.
    virtual void OnEnvironmentsSetUpStart(const ::testing::UnitTest& unit_test){}
    // Fired after environment set-up for each iteration of tests ends.
    virtual void OnEnvironmentsSetUpEnd(const ::testing::UnitTest& unit_test){}
    // Fired before the test case starts.
    virtual void OnTestCaseStart(const ::testing::TestCase& test_case){}
    // Fired before the test starts.
    virtual void OnTestStart(const ::testing::TestInfo& test_info)
    {
#ifdef __COVERAGESCANNER__
        __coveragescanner_clear();
        std::string test_name=
            std::string(test_info.test_case_name())
            + '/'
            + std::string(test_info.name());
        __coveragescanner_testname(test_name.c_str());
#endif
    }
    // Fired after a failed assertion or a SUCCESS().
    virtual void OnTestPartResult(const ::testing::TestPartResult& test_part_result){}
    // Fired after the test ends.
    virtual void OnTestEnd(const ::testing::TestInfo& test_info)
    {
#ifdef __COVERAGESCANNER__
        __coveragescanner_teststate("UNKNOWN");
        if (test_info.result())
        {
            if (test_info.result()->Passed())
                __coveragescanner_teststate("PASSED");
            if (test_info.result()->Failed())
                __coveragescanner_teststate("FAILED");
        }
        __coveragescanner_save();
#endif
    }
    // Fired after the test case ends.
    virtual void OnTestCaseEnd(const ::testing::TestCase& test_case){}
    // Fired before environment tear-down for each iteration of tests starts.
    virtual void OnEnvironmentsTearDownStart(const ::testing::UnitTest& unit_test){}
    // Fired after environment tear-down for each iteration of tests ends.
    virtual void OnEnvironmentsTearDownEnd(const ::testing::UnitTest& unit_test){}
    // Fired after each iteration of tests finishes.
    virtual void OnTestIterationEnd(const ::testing::UnitTest& unit_test, int iteration){}
    // Fired after all test activities have ended.
    virtual void OnTestProgramEnd(const ::testing::UnitTest& unit_test){}
} ;

extern "C" {
static void * __fopenread(const char *name) { return (void *)fopen(name,"r"); }
static void * __fopenappend(const char *name) { return (void *)fopen(name,"a+"); }
static void * __fopenwrite(const char *name) { return (void *)fopen(name,"w"); }
}

int main(int argc, char **argv) {
    ::testing::AddGlobalTestEnvironment(new Environment);
    ::testing::FLAGS_gtest_output = "xml";
#ifndef DISABLE_SHUFFLE
    ::testing::FLAGS_gtest_shuffle = true;
#endif
#ifdef COVERAGE_ENABLED
    ::testing::UnitTest::GetInstance()->listeners().Append(new CodeCoverageListener);
#endif
    ::testing::InitGoogleTest(&argc, argv);
#ifdef COVERAGE_ENABLED
    if (NULL != __coveragescanner_filename) {
        __coveragescanner_filename("coverage");
        /* __coveragescanner_set_custom_io(
         *     (char *(*)(char *s, int size, void *stream)) fgets, 
         *     (int (*)(const char *s, void *stream))fputs, 
         *     __fopenappend, __fopenread, __fopenwrite, 
         *     (int (*)(void *fp))fclose,
         *     NULL); */
        atexit(ShowCoverageSummary);
    }
#endif /* COVERAGE_ENABLED */
    return RUN_ALL_TESTS();
}

#endif /* TEST_SETUP_H */
