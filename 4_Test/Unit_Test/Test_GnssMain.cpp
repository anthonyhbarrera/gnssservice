/************  Copyright 2004-2017 FICOSA CORPORATIVE ELECTRONICS  ********//**
*  @par Language: MISRA C
*  @par Framework: Legato
*  @par Spec: /AC_Repository/25_UNIT_SPEC/FAM_LINUX/ModemMiddleware/MMW051_SIMMng
*  @par Project: Infrastructure Project
*  @brief Unit test for the SIMMng of the MMW051_SIMMng FAM component.
*  @author  F59CGR0
*  @version 2.0.0
*******************************************************************************/

/* -------------------------------- Includes -------------------------------- */
/* Gtest/Gmock */
#include "gmock/gmock.h"
#include "gtest/gtest.h"

/* Mocks includes */  
#include "Mock_Udp.hpp"
#include "Mock_gnssService.hpp" 
#include "Mock_getTimeClock.hpp" 

/* Stubs includes */  
#include "Stub_dbus.hpp"
#include "Stub_udp.hpp"
#include "Stub_gnssParseNmea.hpp"
/* Source includes */ 

/* Test main and other utilities includes */
#include "test_setup.h"
#include "fico_matchers.h"

/* --------------------- TestCocoon Owner Documentation --------------------- */

TEST_SET_HEADER("GNSS Service - Main");

/* -------------------------------- Defines --------------------------------- */

/* --------------------------- Static Declaration --------------------------- */

/* --------------------------- Test Suites & Test --------------------------- */

/* Gtest / Gmock using definitions for easier usage. */
using ::testing::_;
using ::testing::StrEq;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArgPointee;
using ::testing::SaveArg;
using ::testing::SaveArgPointee;

/*
 * Main class where mock instantiation is created and static values of the
 * source file are reset to default values.
 */
 

int main_test(int, char **);
void gnss_signal_handler( int signum );

class TestMainUnit : public ::testing::Test {
   protected:
   ::testing::StrictMock<Mock::Mock_MockBasicGnssService> mockGnssService;
   ::testing::StrictMock<Mock::Mock_MockBasicGetTimeClock> mockGetTime;  
   ::testing::StrictMock<Mock::Mock_MockBasicGnssDbus> mockGnssDbus;  

    

    virtual void SetUp() {
        InitVars();
    }

    virtual void TearDown() {
        /* Do nothing */
    }

    void InitVars( void ) {
    }

}; 
/*
 * Test suites & Test
 */
class TestComponentInit : public TestMainUnit {
};

class TestMain : 
    public TestMainUnit, public ::testing::WithParamInterface<int> {
};
extern int unitTestCnt ;
void setWorkingTrue(void);
TEST_P(TestMain, 
    GivenPositiveSocket_WhenCreatingSocket_ThenServiceShouldBeCreatedCorrectly)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */
    unitTestCnt = 5; 
    setWorkingTrue();
    int inParam = GetParam();  
    /* Expectations */     
    EXPECT_CALL(mockGnssService, createSocket(_,_)) 
    .WillOnce(Return(0));

    EXPECT_CALL(mockGnssService, closeSocket()) 
    .WillOnce(Return(0));


    EXPECT_CALL(mockGetTime, getTime())  
    .WillOnce(Return(0))  
    .WillRepeatedly(Return(1200)); 

    EXPECT_CALL(mockGnssDbus, registerDBusListener(_)) 
    .WillRepeatedly(Return(true));

    EXPECT_CALL(mockGnssDbus, unRegisterDBusListener(_)) 
    .WillRepeatedly(Return(true));
     
    EXPECT_CALL(mockGnssDbus, getVersion()) 
    .WillRepeatedly(Return("Version 0"));
    /* Test */  
    
    /* Checks */  
    EXPECT_EQ(main_test(0, nullptr), 0); 

}
INSTANTIATE_TEST_CASE_P( , TestMain, ::testing::Values(1,-1));
   
class TestMainCloseSockedWrong : 
    public TestMainUnit, public ::testing::WithParamInterface<int> {
};

TEST_P(TestMainCloseSockedWrong, 
    GivenPositiveSocket_WhenCreatingSocket_ThenServiceShouldBeCreatedCorrectly)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */   
 
    /* Expectations */     
    EXPECT_CALL(mockGnssService, createSocket(_,_)) 
    .WillOnce(Return(0));

    EXPECT_CALL(mockGnssService, closeSocket()) 
    .WillOnce(Return(-1));

    EXPECT_CALL(mockGetTime, getTime())  
    .WillOnce(Return(0))  
    .WillRepeatedly(Return(1200)); 

    EXPECT_CALL(mockGnssDbus, registerDBusListener(_)) 
    .WillRepeatedly(Return(true));

    EXPECT_CALL(mockGnssDbus, unRegisterDBusListener(_)) 
    .WillRepeatedly(Return(true));

    EXPECT_CALL(mockGnssDbus, getVersion()) 
    .WillRepeatedly(Return("Version 0"));
    /* Test */  
    
    /* Checks */  
    EXPECT_EQ(main_test(0, nullptr), -1);

}
INSTANTIATE_TEST_CASE_P( , TestMainCloseSockedWrong, ::testing::Values(1,-1));

class TestMainGnssServiceCreateWrong : 
    public TestMainUnit, public ::testing::WithParamInterface<int> {
};

TEST_P(TestMainGnssServiceCreateWrong, 
    GivenNegCreatingSocket_WhenExecutionMain_ThenServiceShouldExit)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */    
 
    /* Expectations */     
    EXPECT_CALL(mockGnssService, createSocket(_,_)) 
    .WillOnce(Return(-1));

    EXPECT_CALL(mockGetTime, getTime())  
    .WillOnce(Return(0))  
    .WillRepeatedly(Return(1200)); 

    EXPECT_CALL(mockGnssDbus, getVersion()) 
    .WillRepeatedly(Return("Version 0"));
    /* Test */  
    
    /* Checks */  
    EXPECT_EQ(main_test(0, nullptr), -1);

}
INSTANTIATE_TEST_CASE_P( , TestMainGnssServiceCreateWrong, ::testing::Values(1,-1));


class TestMainGnssServiceCatchError : 
    public TestMainUnit, public ::testing::WithParamInterface<int> {
};

ACTION(MyThrowException)
{
    throw   sdbus::Error("Throw Error!","message");
}

TEST_P(TestMainGnssServiceCatchError, 
    GivenNegCreatingSocket_WhenExecutionMain_ThenServiceShouldExit)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */    
 
    /* Expectations */     
    EXPECT_CALL(mockGnssService, createSocket(_,_)) 
    .WillOnce(Return(-1));
 
    EXPECT_CALL(mockGetTime, getTime())  
    .WillOnce(Return(0))  
    .WillRepeatedly(Return(1200)); 

    /* Test */  
    EXPECT_CALL(mockGnssDbus, getVersion()) 
    .WillOnce(MyThrowException())
    .WillRepeatedly(Return("Version 0"));
    
    /* Checks */   
    EXPECT_EQ(main_test(0, nullptr), -1);


}
INSTANTIATE_TEST_CASE_P( , TestMainGnssServiceCatchError, ::testing::Values(1));
class TestMainHandleError : 
    public TestMainUnit, public ::testing::WithParamInterface<int> {
};

TEST_P(TestMainHandleError, 
    GivenHandleSignal_WhenExecutionMain_ThenServiceShouldExit)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
 
    /* Expectations */      

    /* Test */  
    
    /* Checks */  
    gnss_signal_handler(5);

}
INSTANTIATE_TEST_CASE_P( , TestMainHandleError, ::testing::Values(1));

