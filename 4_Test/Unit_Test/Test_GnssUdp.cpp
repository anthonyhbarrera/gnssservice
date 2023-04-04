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
#include "Mock_socket.hpp" 

/* Source includes */
#include "GnssUdp.hpp"

/* Test main and other utilities includes */
#include "test_setup.h"
#include "fico_matchers.h"

/* --------------------- TestCocoon Owner Documentation --------------------- */

TEST_SET_HEADER("GNSS Service - Udp Service");

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
 


class TestGnssUdp : public ::testing::Test {
    protected: 
    ::testing::StrictMock<Mock::Mock_MockSocket> mock_MockSocket; 

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
class TestComponentInit : public TestGnssUdp {
};


class TestCreateSocket : 
    public TestGnssUdp, public ::testing::WithParamInterface<int> {
};

TEST_P(TestCreateSocket, 
    GivenPositiveSocket_WhenCreatingSocket_ThenServiceShouldBeCreatedCorrectly)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssUdp test_upd;
 
    /* Expectations */    
    EXPECT_CALL(mock_MockSocket,socket(_, _, _))
        .WillOnce(Return(200));

    EXPECT_CALL(mock_MockSocket,setsockopt(_, _, _, _, _))
        .Times(2)
        .WillOnce(Return(200))
        .WillOnce(Return(200));
    /* Test */  
    
    /* Checks */
    EXPECT_EQ(test_upd.createSocket(), 0);

}
INSTANTIATE_TEST_CASE_P( , TestCreateSocket, ::testing::Values(1));
 
class TestCreateSocketEq0 : 
    public TestGnssUdp, public ::testing::WithParamInterface<int> {
};

TEST_P(TestCreateSocketEq0, 
    GivenNegativeSocket_WhenCreatingSocket_ThenServiceShouldBeCreatedCorrectly)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssUdp test_upd;
 
    /* Expectations */    
    EXPECT_CALL(mock_MockSocket,socket(_, _, _))
        .WillOnce(Return(0));

    EXPECT_CALL(mock_MockSocket,setsockopt(_, _, _, _, _))
        .Times(2)
        .WillOnce(Return(0))
        .WillOnce(Return(0));
    /* Test */  
    
    /* Checks */
    EXPECT_EQ(test_upd.createSocket(), 0);

}
INSTANTIATE_TEST_CASE_P( , TestCreateSocketEq0, ::testing::Values(1));


class TestCreateWrongSocket : 
    public TestGnssUdp, public ::testing::WithParamInterface<int> {
};

TEST_P(TestCreateWrongSocket, 
    GivenNegativeSocket_WhenCreatingSocket_ThenServiceShouldBeCreatedCorrectly)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssUdp test_upd;
 
    /* Expectations */    
    EXPECT_CALL(mock_MockSocket,socket(_, _, _))
        .WillOnce(Return(-200));

    EXPECT_CALL(mock_MockSocket,setsockopt(_, _, _, _, _))
        .Times(0);
        
    /* Test */  
    
    /* Checks */
    EXPECT_EQ(test_upd.createSocket(), 1);

}
INSTANTIATE_TEST_CASE_P( , TestCreateWrongSocket, ::testing::Values(1));

class TestCloseSocket : 
    public TestGnssUdp, public ::testing::WithParamInterface<int> {
};

TEST_P(TestCloseSocket, 
    GivenSocket_WhenClosingSocket_ThenServiceCloseSocket)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssUdp test_upd;
    int retVal = 2000;

    /* Expectations */    
    EXPECT_CALL(mock_MockSocket,close(_))
        .WillOnce(Return(retVal));
 
    /* Test */  
    
    /* Checks */
    EXPECT_EQ(test_upd.closeSocket(), retVal);

}
INSTANTIATE_TEST_CASE_P( , TestCloseSocket, ::testing::Values(1));

class TestCloseWrongSocket : 
    public TestGnssUdp, public ::testing::WithParamInterface<int> {
};

TEST_P(TestCloseWrongSocket, 
    GivenNegativeSocket_WhenClosingSocket_ThenServiceShouldDontCloseSocket)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssUdp test_upd;
    int retVal = -200;

    /* Expectations */    
    EXPECT_CALL(mock_MockSocket,close(_))
        .WillOnce(Return(retVal));
 
    /* Test */  
    
    /* Checks */
    EXPECT_EQ(test_upd.closeSocket(), retVal);

}
INSTANTIATE_TEST_CASE_P( , TestCloseWrongSocket, ::testing::Values(1));



class TestUdpSendBytesNegSend : 
    public TestGnssUdp, public ::testing::WithParamInterface<int> {
};

TEST_P(TestUdpSendBytesNegSend, 
    GivenNegativeSendAnswer_WhenSendingByte_ThenServiceDontSendUdpFrames)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssUdp test_upd;
    int retVal = -200;
    std::string testString = "TEST STRING";

    /* Expectations */    
    EXPECT_CALL(mock_MockSocket,sendto(_,_,_,_,_,_))
        .WillOnce(Return(retVal));
 
    /* Test */  
    
    /* Checks */
    EXPECT_FALSE(test_upd.send(testString));

}
INSTANTIATE_TEST_CASE_P( , TestUdpSendBytesNegSend, ::testing::Values(1));

class TestUdpSendBytes : 
    public TestGnssUdp, public ::testing::WithParamInterface<int> {
};

TEST_P(TestUdpSendBytes, 
    GivenPosSendAnswer_WhenSendingByte_ThenServiceSendUdpFrames)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssUdp test_upd;
    int retVal = 200;
    std::string testString = "TEST STRING";

    /* Expectations */    
    EXPECT_CALL(mock_MockSocket,sendto(_,_,_,_,_,_))
        .WillOnce(Return(retVal));
 
    /* Test */  
    
    /* Checks */
    EXPECT_TRUE(test_upd.send(testString));

}
INSTANTIATE_TEST_CASE_P( , TestUdpSendBytes, ::testing::Values(1));
