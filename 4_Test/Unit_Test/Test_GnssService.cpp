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
#include "Mock_gnssParseNmea.hpp"

/* Source includes */
#include "gnssService.hpp"   

/* Test main and other utilities includes */
#include "test_setup.h"
#include "fico_matchers.h"

/* --------------------- TestCocoon Owner Documentation --------------------- */

TEST_SET_HEADER("Gnss Service");

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
 
 

class TestGnssService : public ::testing::Test 
{ 

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
class TestComponentInit : public TestGnssService {
};
 
  
class TestcreateSocketNullPtr : 
    public TestGnssService, public ::testing::WithParamInterface<int> {
};
 
TEST_P(TestcreateSocketNullPtr, 
    GivenUdpNullPointer_WhenCreatingSocket_ThenServiceShouldDoNothingNever)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssService test_gnssServ;
    
    std::shared_ptr<Mock::Mock_MockBasicGnssUdp>  gnssUdp;
    std::shared_ptr<Mock::Mock_MockBasicGnssParseNmea>  _gnssParseNmea;
    /* Expectations */  
    //test_udp.createSocket();
    
    /* Test */ 
    //EXPECT_CALL(mock_MockGnssUdp, createSocket())
    //.Times(0) 
    //.WillOnce(Return(-1));
    
  
    
    /* Checks */ 
    EXPECT_EQ(test_gnssServ.createSocket(gnssUdp,_gnssParseNmea), -1);
    
}
INSTANTIATE_TEST_CASE_P(ReturnGnssStatus, TestcreateSocketNullPtr, ::testing::Values(1));
 



class TestcreateSocketWrongUdp : 
    public TestGnssService, public ::testing::WithParamInterface<int> {
};
  

TEST_P(TestcreateSocketWrongUdp, 
    GivenUdpPointer_WhenCreatingWrongUdpSocket_ThenServiceShouldDoNothingNever)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssService test_gnssServ; 
    std::shared_ptr<Mock::Mock_MockBasicGnssUdp>   gnssUdp = std::make_shared<Mock::Mock_MockBasicGnssUdp>() ; 

    std::shared_ptr<Mock::Mock_MockBasicGnssParseNmea>  _gnssParseNmea = std::make_shared<Mock::Mock_MockBasicGnssParseNmea>() ;
    /* Expectations */  
    //test_udp.createSocket();
    
    /* Test */ 
    EXPECT_CALL(*gnssUdp, createSocket()) 
    .WillOnce(Return(-1));
     
    
    /* Checks */ 
    EXPECT_EQ(test_gnssServ.createSocket(gnssUdp, _gnssParseNmea), -1);
    
}
INSTANTIATE_TEST_CASE_P(ReturnGnssStatus, TestcreateSocketWrongUdp, ::testing::Values(1)); 

  
 class TestcreateSocket : 
    public TestGnssService, public ::testing::WithParamInterface<int> {
};
 
TEST_P(TestcreateSocket, 
    GivenUdpPointer_WhenCreatingGoodUdpSocket_ThenServiceShouldReturn0)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssService test_gnssServ;
    
    std::shared_ptr<Mock::Mock_MockBasicGnssUdp> gnssUdp; 
    gnssUdp = std::make_shared<Mock::Mock_MockBasicGnssUdp>();
    std::shared_ptr<Mock::Mock_MockBasicGnssParseNmea> _gnssParseNmea;  
    _gnssParseNmea = std::make_shared<Mock::Mock_MockBasicGnssParseNmea>() ;
    
    /* Expectations */  
    
    /* Test */ 
    EXPECT_CALL(*gnssUdp, createSocket()) 
    .WillOnce(Return(0)); 
    
    /* Checks */ 
    EXPECT_EQ(test_gnssServ.createSocket(gnssUdp, _gnssParseNmea), 0);
    
}
INSTANTIATE_TEST_CASE_P(ReturnGnssStatus, TestcreateSocket, ::testing::Values(1));
 
 class TestcreateSocketWrongParseNmea : 
    public TestGnssService, public ::testing::WithParamInterface<int> {
};
 
TEST_P(TestcreateSocketWrongParseNmea, 
    GivenUdpPointer_WhenCreatingGoodUdpSocket_ThenServiceShouldReturn0)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssService test_gnssServ;
    
    std::shared_ptr<Mock::Mock_MockBasicGnssUdp> gnssUdp; 
    gnssUdp = std::make_shared<Mock::Mock_MockBasicGnssUdp>();
    std::shared_ptr<Mock::Mock_MockBasicGnssParseNmea> _gnssParseNmea;   ;
    
    /* Expectations */  
    
    /* Test */ 
    EXPECT_CALL(*gnssUdp, createSocket()) 
    .WillOnce(Return(0)); 
    
    /* Checks */ 
    EXPECT_EQ(test_gnssServ.createSocket(gnssUdp, _gnssParseNmea), -1);
    
}
INSTANTIATE_TEST_CASE_P(ReturnGnssStatus, TestcreateSocketWrongParseNmea, ::testing::Values(1));
 

class TestCloseSocketUdpPtrNull : 
    public TestGnssService, public ::testing::WithParamInterface<int> {
};
 
TEST_P(TestCloseSocketUdpPtrNull, 
    GivenUdpNullPointer_WhenCloseSocket_ThenServiceShouldDoNothingNever)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssService test_gnssServ;
    
    std::shared_ptr<Mock::Mock_MockBasicGnssUdp>   gnssUdp  ; 

    std::shared_ptr<Mock::Mock_MockBasicGnssParseNmea> _gnssParseNmea;   
    /* Expectations */  
    //test_udp.createSocket();
    
    /* Test */  
     
    /* Checks */ 
    EXPECT_EQ(test_gnssServ.createSocket(gnssUdp, _gnssParseNmea), -1);
    EXPECT_EQ(test_gnssServ.closeSocket(), -1);
    
}
INSTANTIATE_TEST_CASE_P(ReturnGnssStatus, TestCloseSocketUdpPtrNull, ::testing::Values(1));
 
class TestCloseSocket : 
    public TestGnssService, public ::testing::WithParamInterface<int> {
};
 
TEST_P(TestCloseSocket, 
    GivenUdpPointer_WhenCloseSocket_ThenServiceShouldBeClosed)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssService test_gnssServ;
     
    std::shared_ptr<Mock::Mock_MockBasicGnssUdp>   gnssUdp = std::make_shared<Mock::Mock_MockBasicGnssUdp>() ; 

    std::shared_ptr<Mock::Mock_MockBasicGnssParseNmea> _gnssParseNmea;  
    _gnssParseNmea = std::make_shared<Mock::Mock_MockBasicGnssParseNmea>() ;
    /* Expectations */  
    EXPECT_CALL(*gnssUdp, createSocket()) 
    .WillOnce(Return(0));
    EXPECT_CALL(*gnssUdp, closeSocket()) 
    .WillOnce(Return(0));
      
    /* Test */  
     
    /* Checks */ 
    EXPECT_EQ(test_gnssServ.createSocket(gnssUdp, _gnssParseNmea), 0);
    EXPECT_EQ(test_gnssServ.closeSocket(), 0);
    
}
INSTANTIATE_TEST_CASE_P(ReturnGnssStatus, TestCloseSocket, ::testing::Values(1));


class TestCloseSocketCanNotClose : 
    public TestGnssService, public ::testing::WithParamInterface<int> {
};
 
TEST_P(TestCloseSocketCanNotClose, 
    GivenCannotCloseUdp_WhenCloseSocket_ThenServiceShouldReturnError)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssService test_gnssServ;
    
    std::shared_ptr<Mock::Mock_MockBasicGnssUdp>   gnssUdp = std::make_shared<Mock::Mock_MockBasicGnssUdp>() ; 

    std::shared_ptr<Mock::Mock_MockBasicGnssParseNmea> _gnssParseNmea;  
    _gnssParseNmea = std::make_shared<Mock::Mock_MockBasicGnssParseNmea>() ;
    /* Expectations */  
    EXPECT_CALL(*gnssUdp, createSocket()) 
    .WillOnce(Return(0));
    EXPECT_CALL(*gnssUdp, closeSocket()) 
    .WillOnce(Return(-1));
      
    /* Test */  
     
    /* Checks */ 
    EXPECT_EQ(test_gnssServ.createSocket(gnssUdp,_gnssParseNmea), 0);
    EXPECT_EQ(test_gnssServ.closeSocket(), -1);
    
}
INSTANTIATE_TEST_CASE_P(ReturnGnssStatus, TestCloseSocketCanNotClose, ::testing::Values(1));


class TestOnNmeaFrameUdpNotCreated : 
    public TestGnssService, public ::testing::WithParamInterface<int> {
};
 
TEST_P(TestOnNmeaFrameUdpNotCreated, 
    GivenNmeaFrame_WhenUdpSocketNotCreated_ThenServiceShouldNeverWork)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssService test_gnssServ;
    std::string testString = "TEST STRING";
    
    std::shared_ptr<Mock::Mock_MockBasicGnssUdp>   gnssUdp = std::make_shared<Mock::Mock_MockBasicGnssUdp>() ; 

    /* Expectations */    
      
    /* Test */  
     
    /* Checks */  
    //test_gnssServ.createSocket(gnssUdp);
    test_gnssServ.onDbusNmeaFrames(testString);
    EXPECT_EQ(test_gnssServ.closeSocket(), -1);
    
}
INSTANTIATE_TEST_CASE_P(ReturnGnssStatus, TestOnNmeaFrameUdpNotCreated, ::testing::Values(1));


class TestOnNmeaFrameUdpSockedCreated : 
    public TestGnssService, public ::testing::WithParamInterface<int> {
};
 
TEST_P(TestOnNmeaFrameUdpSockedCreated, 
    GivenNmeaFrame_WhenUdpSocketNotCreated_ThenServiceShouldNeverWork)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssService test_gnssServ;
    std::string testString = "TEST STRING";
    
    std::shared_ptr<Mock::Mock_MockBasicGnssUdp>   gnssUdp = std::make_shared<Mock::Mock_MockBasicGnssUdp>() ; 

    std::shared_ptr<Mock::Mock_MockBasicGnssParseNmea> _gnssParseNmea;  
    _gnssParseNmea = std::make_shared<Mock::Mock_MockBasicGnssParseNmea>() ;
    /* Expectations */  
    EXPECT_CALL(*gnssUdp, createSocket()) 
    .WillOnce(Return(0));
    
    EXPECT_CALL(*gnssUdp, send(_)) 
    .WillOnce(Return(false));
     
    EXPECT_CALL(*gnssUdp, closeSocket()) 
    .WillOnce(Return(0));
      
    /* Test */  
     
    /* Checks */  
    test_gnssServ.createSocket(gnssUdp,_gnssParseNmea);
    test_gnssServ.onDbusNmeaFrames(testString);
    EXPECT_EQ(test_gnssServ.closeSocket(), 0);
    
}
INSTANTIATE_TEST_CASE_P(ReturnGnssStatus, TestOnNmeaFrameUdpSockedCreated, ::testing::Values(1));

class TestOnUbloxState : 
    public TestGnssService, public ::testing::WithParamInterface<int> {
};
 
TEST_P(TestOnUbloxState, 
    GivenNmeaFrame_WhenUdpSocketNotCreated_ThenServiceShouldNeverWork)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssService test_gnssServ;
    std::string testString = "TEST STRING";
     

    /* Expectations */   
      
    /* Test */  
     
    /* Checks */   
    test_gnssServ.onDbusUbloxState(testString); 
    
}
INSTANTIATE_TEST_CASE_P(ReturnGnssStatus, TestOnUbloxState, ::testing::Values(1));
