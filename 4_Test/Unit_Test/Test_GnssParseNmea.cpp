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

/* Source includes */
#include "gnssParseNmea.hpp"
#include <string>

/* Test main and other utilities includes */
#include "test_setup.h"
#include "fico_matchers.h"

/* --------------------- TestCocoon Owner Documentation --------------------- */

TEST_SET_HEADER("GNSS Service - Parse Nmea Frames Service");

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
 


class TestGnssParseNmea : public ::testing::Test 
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
class TestComponentInit : public TestGnssParseNmea {
};


class TestParseNmeaFramesTrue : 
    public TestGnssParseNmea, public ::testing::WithParamInterface< std::string > {
};

TEST_P(TestParseNmeaFramesTrue, 
    GivenPositive_WhenParsingNmea_ThenFramesShouldBeStored)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssParseNmea test_gnssParse;
 
    std::string _MsgFrame = GetParam(); 
    /* Expectations */     

    /* Test */  
    
    /* Checks */ 
    EXPECT_EQ(test_gnssParse.parseNmea(_MsgFrame), true);

}
INSTANTIATE_TEST_CASE_P( , TestParseNmeaFramesTrue, ::testing::Values( 
    "$GNGLL,4133.06529,N,00213.52454,E,101937.00,A,E*71",
    "$GNRMC,101938.00,A,4133.06452,N,00213.52562,E,3.793,131.96,280622,1.26,E,E,V*5A",
    "$GNVTG,131.96,T,130.71,M,3.793,N,7.025,K,E*3F",
    "$GNGGA,101938.00,4133.06452,N,00213.52562,E,6,00,99.99,95.3,M,49.2,M,,*41",
    "$GNGSA,A,2,,,,,,,,,,,,,99.99,99.99,99.99,1*30",
    "$GNGSA,A,2,,,,,,,,,,,,,99.99,99.99,99.99,2*33",
    "$GNGSA,A,2,,,,,,,,,,,,,99.99,99.99,99.99,3*32",
    "$GNGSA,A,2,,,,,,,,,,,,,99.99,99.99,99.99,4*35",
    "$GPGSV,2,1,06,07,09,318,11,10,47,133,20,18,25,051,15,21,14,241,17,1*6D",
    "$GPGSV,2,2,06,23,47,083,17,27,63,320,16,1*6B",
    "$GLGSV,1,1,02,66,24,064,15,73,34,317,21,1*7F",
    "$GLGSV,2,1,07,65,03,012,,67,17,118,,79,18,184,,80,55,246,,0*73",
    "$GLGSV,2,2,07,80,55,246,,81,25,054,,82,60,359,,0*4A",
    "$GLGSV,2,2,07,80,55,246,,81,25,054,,82,60,359,,0"          /* No checksum */
    "$GLGSV,2,2,07,80,55,246,,81,25,054,,82,60,359,,0*4A\r\n",  /* \r\n Ending  */
    "$GLGSV,2,2,07,80,55,246,,81,25,054,,82,60,359,,0*4A\n"     /* \n Ending    */
));
 
class TestParseNmeaFramesFalse : 
    public TestGnssParseNmea, public ::testing::WithParamInterface< std::string > {
};

TEST_P(TestParseNmeaFramesFalse, 
    GivenPositive_WhenParsingNmea_ThenFramesShouldBeStored)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssParseNmea test_gnssParse;
 
    std::string _MsgFrame = GetParam(); 
    /* Expectations */     

    /* Test */  
    
    /* Checks */ 
    EXPECT_EQ(test_gnssParse.parseNmea(_MsgFrame), false);

}
INSTANTIATE_TEST_CASE_P( , TestParseNmeaFramesFalse, ::testing::Values( 
    "$GNGLL,4133.06529,N,00213.52454,E,101937.00,A,E*70",   /* Wrong CRC */
    "", /* Empty string */
    "GNVTG,131.96,T,130.71,M,3.793,N,7.025,K,E*3F", /* No dollar */
    "$,",
    "$GNGSA" 
));


class TestGetGNGGA : 
    public TestGnssParseNmea, public ::testing::WithParamInterface< std::string > {
};

TEST_P(TestGetGNGGA, 
    GivenPositive_WhenParsingNmea_ThenFramesShouldBeStored)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssParseNmea test_gnssParse;
 
    std::string _MsgFrame = GetParam(); 
    /* Expectations */     

    /* Test */  
    
    /* Checks */ 
    EXPECT_EQ(test_gnssParse.parseNmea(_MsgFrame), true);
    //std::string _getString = test_gnssParse.getGNGGAFrame();
    EXPECT_EQ(test_gnssParse.getGNGGAFrame(), _MsgFrame);

}
INSTANTIATE_TEST_CASE_P( , TestGetGNGGA, ::testing::Values( 
    "$GNGGA,101938.00,4133.06452,N,00213.52562,E,6,00,99.99,95.3,M,49.2,M,,*41"
));


class TestGetGNRMC : 
    public TestGnssParseNmea, public ::testing::WithParamInterface< std::string > {
};

TEST_P(TestGetGNRMC, 
    GivenPositive_WhenParsingNmea_ThenFramesShouldBeStored)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssParseNmea test_gnssParse;
 
    std::string _MsgFrame = GetParam(); 
    /* Expectations */     

    /* Test */  
    
    /* Checks */ 
    EXPECT_EQ(test_gnssParse.parseNmea(_MsgFrame), true);
    //std::string _getString = test_gnssParse.getGNGGAFrame();
    EXPECT_EQ(test_gnssParse.getGNRMCFrame(), _MsgFrame);

}
INSTANTIATE_TEST_CASE_P( , TestGetGNRMC, ::testing::Values( 
    "$GNRMC,101938.00,A,4133.06452,N,00213.52562,E,3.793,131.96,280622,1.26,E,E,V*5A"
));



class TestPublishNmea : 
    public TestGnssParseNmea, public ::testing::WithParamInterface< std::string > {
};

TEST_P(TestPublishNmea, 
    GivenPositive_WhenParsingNmea_ThenFramesShouldBeStored)
{
    /* Info */
    //TEST_SET_DESCRIPTION("GivenSimOk_WhenInitializing_ComponentInitShouldDoNothing");
    TEST_SET_REQUIREMENTS("");
    //TEST_SET_CONDITIONS("Given Sim Ok");
    //TEST_SET_ACTIONS("When initializing the component.");
    //TEST_SET_EXPECTED("Then should do nothing.");

    /* Preconditions */  
    Gnss::GnssParseNmea test_gnssParse;
 
    std::string _MsgFrame = GetParam(); 
    /* Expectations */     

    /* Test */  
    
    /* Checks */ 
    if(_MsgFrame.size() > 0)
    {
        EXPECT_EQ(test_gnssParse.parseNmea(_MsgFrame), true);
    }
    else
    {
        EXPECT_EQ(test_gnssParse.parseNmea(_MsgFrame), false);

    }
    //std::string _getString = test_gnssParse.getGNGGAFrame();
    test_gnssParse.publishSyslogNmea();

}
INSTANTIATE_TEST_CASE_P( , TestPublishNmea, ::testing::Values( 
    "$GNRMC,101938.00,A,4133.06452,N,00213.52562,E,3.793,131.96,280622,1.26,E,E,V*5A",
    "$GNGGA,101938.00,4133.06452,N,00213.52562,E,6,00,99.99,95.3,M,49.2,M,,*41",
    ""
));