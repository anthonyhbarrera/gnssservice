 #include "gmock/gmock.h"
// #include "gmock-c-generated-function-mockers.h"
 //#include <assert.h>

// extern "C"{
 #include <sys/socket.h>
// }

 

namespace Mock {
    class Mock_MockSocket{
    public:
        static Mock::Mock_MockSocket *instance;

        Mock_MockSocket(void) {
            assert((( Mock::Mock_MockSocket::instance == NULL ) && "You have several mock objects of the type Mock_MockSocket. Please remove the duplicated object."));
            instance = this;
        }

        ~Mock_MockSocket(void) {
            instance = NULL;
        }

        MOCK_METHOD3( socket, int ( int __domain, int __type, int __protocol ));
        MOCK_METHOD3( bind, int ( int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len ));
        MOCK_METHOD6( recvfrom, ssize_t (int __fd, void *__restrict __buf, size_t __n,int __flags, __SOCKADDR_ARG __addr,socklen_t *__restrict __addr_len));
        MOCK_METHOD1( close, int ( int __fd));
        MOCK_METHOD5( setsockopt, int (int __fd, int __level, int __optname,const void *__optval, socklen_t __optlen));
        MOCK_METHOD6( sendto, ssize_t ( int __fd, 
                                        const void *__buf,
                                        size_t __n,
                                        int __flags,
                                        __CONST_SOCKADDR_ARG __addr,
                                        socklen_t __addr_len));
    };
}
#define MOCK_ASSERT_SOCKET assert((( Mock::Mock_MockSocket::instance != NULL ) && "UT error: You have to add a mock object of type Mock_MockSocket to your test class."));

Mock::Mock_MockSocket *Mock::Mock_MockSocket::instance = NULL;


int socket(int __domain, int __type, int __protocol)throw()
{
    MOCK_ASSERT_SOCKET
    return Mock::Mock_MockSocket::instance->socket(__domain,__type,__protocol);
}

int bind (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len)throw()
{
    MOCK_ASSERT_SOCKET
    return Mock::Mock_MockSocket::instance->bind(__fd,__addr,__len);
}

ssize_t recvfrom (int __fd, void *__restrict __buf, size_t __n,int __flags, __SOCKADDR_ARG __addr,socklen_t *__restrict __addr_len)
{
    MOCK_ASSERT_SOCKET
    return Mock::Mock_MockSocket::instance->recvfrom(__fd,__buf,__n,__flags,__addr,__addr_len);
}

int close(int __fd)
{
    MOCK_ASSERT_SOCKET
    return Mock::Mock_MockSocket::instance->close(__fd);
}

int setsockopt(int __fd, int __level, int __optname,const void *__optval, socklen_t __optlen)throw()
{
    MOCK_ASSERT_SOCKET
    return Mock::Mock_MockSocket::instance->setsockopt(__fd,__level,__optname,__optval,__optlen);
}

 
ssize_t sendto (int __fd, 
            const void *__buf,
            size_t __n,
            int __flags,
            __CONST_SOCKADDR_ARG __addr,
            socklen_t __addr_len)
{
    MOCK_ASSERT_SOCKET
    return Mock::Mock_MockSocket::instance->sendto( __fd, 
                                                    __buf,
                                                    __n,
                                                    __flags,
                                                    __addr,
                                                    __addr_len);
}
 


