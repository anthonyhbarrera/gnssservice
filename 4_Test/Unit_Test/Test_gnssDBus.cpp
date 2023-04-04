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
#include "Mock_dbusListener.hpp" 

/* Source includes */
#include "gnssDBus.hpp"

/* Test main and other utilities includes */
#include "test_setup.h"
#include "fico_matchers.h"

/* --------------------- TestCocoon Owner Documentation --------------------- */

TEST_SET_HEADER("GNSS Service - DBus Client");

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
 


class TestGnssDbus : public ::testing::Test 
{
    virtual void SetUp() 
    {
        InitVars();
    }

    virtual void TearDown() 
    {
        /* Do nothing */
    }

    void InitVars( void ) 
    {
    }

};
/*
 * Test suites & Test
 */
class TestComponentInit : public TestGnssDbus {
};


class TestRegisteringNullListenerTest : 
    public TestGnssDbus, public ::testing::WithParamInterface<int> {
};

TEST_P(TestRegisteringNullListenerTest, 
    GivenNullPtrForListeners_WhenRegisterListener_ThenServiceShouldDoNothingNever)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */ 
    const char* destinationName = "com.idneo.ublox";
    const char* objectPath = "/com/idneo/ublox";
    Gnss::GnssDBus test_dbus(destinationName, objectPath);
    
    std::shared_ptr<Mock::Mock_MockBasicGnssDbusListener> iDbusListen;
 
    /* Expectations */    
    
    /* Test */ 

    /* Checks */
    EXPECT_EQ(test_dbus.registerDBusListener(iDbusListen),false); 

}
INSTANTIATE_TEST_CASE_P( , TestRegisteringNullListenerTest, ::testing::Values(1));
 
class TestRegisteringListenerTest : 
    public TestGnssDbus, public ::testing::WithParamInterface<int> {
};
TEST_P(TestRegisteringListenerTest, 
    GivenListeners_WhenRegisterListener_ThenServiceShouldRegisterTheListener)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */ 
    const char* destinationName = "com.idneo.ublox";
    const char* objectPath = "/com/idneo/ublox";
    Gnss::GnssDBus test_dbus(destinationName, objectPath);
    
    std::shared_ptr<Mock::Mock_MockBasicGnssDbusListener> iDbusListen;
    iDbusListen = std::make_shared<Mock::Mock_MockBasicGnssDbusListener>();  
    /* Expectations */    
    
    /* Test */ 

    /* Checks */
    EXPECT_EQ(test_dbus.registerDBusListener(iDbusListen),true); 

}
INSTANTIATE_TEST_CASE_P( , TestRegisteringListenerTest, ::testing::Values(1));


class TestUnRegisteringNullListenerTest : 
    public TestGnssDbus, public ::testing::WithParamInterface<int> {
};

TEST_P(TestUnRegisteringNullListenerTest, 
    GivenNullPtrForUnRegisterListeners_WhenUnRegisterListener_ThenServiceShouldDoNothingNever)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */ 
    const char* destinationName = "com.idneo.ublox";
    const char* objectPath = "/com/idneo/ublox";
    Gnss::GnssDBus test_dbus(destinationName, objectPath);
    
    std::shared_ptr<Mock::Mock_MockBasicGnssDbusListener> iDbusListen;
    /* Expectations */    
    
    /* Test */ 

    /* Checks */
    EXPECT_EQ(test_dbus.unRegisterDBusListener(iDbusListen),false); 

}
INSTANTIATE_TEST_CASE_P( , TestUnRegisteringNullListenerTest, ::testing::Values(1));
 
class TestUnRegisteringListenerTest : 
    public TestGnssDbus, public ::testing::WithParamInterface<int> {
};
TEST_P(TestUnRegisteringListenerTest, 
    GivenValidPointerForUnregisterListeners_WhenUnRegisterListener_ThenServiceShouldRUnRegisterTheListener)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */ 
    const char* destinationName = "com.idneo.ublox";
    const char* objectPath = "/com/idneo/ublox";
    Gnss::GnssDBus test_dbus(destinationName, objectPath);
    
    std::shared_ptr<Mock::Mock_MockBasicGnssDbusListener> iDbusListen;
    iDbusListen = std::make_shared<Mock::Mock_MockBasicGnssDbusListener>();  
    
    /* Expectations */     
    EXPECT_TRUE(test_dbus.registerDBusListener(iDbusListen));

    /* Test */ 

    /* Checks */
    EXPECT_EQ(test_dbus.unRegisterDBusListener(iDbusListen),true); 
    EXPECT_EQ(test_dbus.unRegisterDBusListener(iDbusListen),false); 

}
INSTANTIATE_TEST_CASE_P( , TestUnRegisteringListenerTest, ::testing::Values(1));


class TestOnDbusEventUnRegisteredListener : 
    public TestGnssDbus, public ::testing::WithParamInterface<int> {
};
TEST_P(TestOnDbusEventUnRegisteredListener, 
    GivenOnDbusEvents_WhenListenerIsNotRegistered_ThenServiceShouldDoNothing)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */ 
    const char* destinationName = "com.idneo.ublox";
    const char* objectPath = "/com/idneo/ublox";
    Gnss::GnssDBus test_dbus(destinationName, objectPath);
    
    std::shared_ptr<Mock::Mock_MockBasicGnssDbusListener> iDbusListen;
    iDbusListen = std::make_shared<Mock::Mock_MockBasicGnssDbusListener>();  
    std::string state = "Valid";
    std::string NmaFrame = "$GPGLL,5133.81,N,00042.25,W*75";
    
    /* Expectations */     
    EXPECT_TRUE(test_dbus.registerDBusListener(iDbusListen)); 

    
    /* Test */ 
    test_dbus.onUbloxState(state);
    test_dbus.onNmeaNewFrames(NmaFrame);

    /* Checks */
    //EXPECT_EQ(test_dbus.onUbloxState(), );
    //EXPECT_EQ(test_dbus.onNmeaNewFrames(), );  

}
INSTANTIATE_TEST_CASE_P( , TestOnDbusEventUnRegisteredListener, ::testing::Values(1));


class TestOnDbusEventRegisteredListener : 
    public TestGnssDbus, public ::testing::WithParamInterface<int> {
};
TEST_P(TestOnDbusEventRegisteredListener, 
    GivenOnDbusEvents_WhenListenerIsRegistered_ThenServiceShouldCallListener)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */ 
    const char* destinationName = "com.idneo.ublox";
    const char* objectPath = "/com/idneo/ublox";
    Gnss::GnssDBus test_dbus(destinationName, objectPath);
    
    std::shared_ptr<Mock::Mock_MockBasicGnssDbusListener> iDbusListen;
    iDbusListen = std::make_shared<Mock::Mock_MockBasicGnssDbusListener>();  
    std::string state = "Valid";
    std::string NmaFrame = "$GPGLL,5133.81,N,00042.25,W*75";
    
    /* Expectations */     
    EXPECT_TRUE(test_dbus.registerDBusListener(iDbusListen));
    EXPECT_TRUE(test_dbus.unRegisterDBusListener(iDbusListen));  

    
    /* Test */ 
    test_dbus.onUbloxState(state);
    test_dbus.onNmeaNewFrames(NmaFrame);

    /* Checks */
    //EXPECT_EQ(test_dbus.onUbloxState(), );
    //EXPECT_EQ(test_dbus.onNmeaNewFrames(), );  

}
INSTANTIATE_TEST_CASE_P( , TestOnDbusEventRegisteredListener, ::testing::Values(1));

