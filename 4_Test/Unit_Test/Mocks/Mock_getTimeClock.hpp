
#include "gmock/gmock.h"
#include <assert.h>  
#include "gmock/gmock.h" 
   
   
#include <string>

#ifndef MOCK_GETTIMECLOCK_H
#define MOCK_GETTIMECLOCK_H

namespace Mock 
{
    class Mock_MockBasicGetTimeClock  
    {
        public:
        static Mock::Mock_MockBasicGetTimeClock *instance;
        Mock_MockBasicGetTimeClock(void)
        {
            assert((( Mock::Mock_MockBasicGetTimeClock::instance == NULL ) && "You have several mock objects of the type Mock_MockBasicGetTimeClock. Please remove the duplicated object."));
            instance = this;

        }
        ~Mock_MockBasicGetTimeClock(void)
        {
            instance = NULL;
        }
        MOCK_METHOD0( getTime, std::time_t ( void ));  
    };
}  
#define MOCK_ASSERT_TIME_CLOCK assert((( Mock::Mock_MockBasicGetTimeClock::instance != NULL ) && "UT error: You have to add a mock object of type Mock_MockBasicGetTimeClock to your test class."));

Mock::Mock_MockBasicGetTimeClock *Mock::Mock_MockBasicGetTimeClock::instance = NULL;


std::time_t getTime (void)
{
    MOCK_ASSERT_TIME_CLOCK
    return Mock::Mock_MockBasicGetTimeClock::instance->getTime();
}
 
  
#endif