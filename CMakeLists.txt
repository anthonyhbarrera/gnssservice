cmake_minimum_required(VERSION 2.8.9)

# provides install directory variables CMAKE_INSTALL_<dir>
include(GNUInstallDirs)
# pkg-config module
include(FindPkgConfig)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(TARGET_GNSSSERVICE_APP gnssservice)

set(GNSS_SOURCES
    3_Implementation/main.cpp 
    3_Implementation/GnssUdp.cpp 
    3_Implementation/gnssService.cpp 
    3_Implementation/gnssDBus.cpp
    3_Implementation/gnssParseNmea.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/3_Implementation  
    ${CMAKE_CURRENT_BINARY_DIR}
)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)

# set global variables
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror")

# add custom command to generate the gnssConfigService-glue.h from the xml file
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gnnsConfigservice-glue.h
    COMMAND bash -c "sdbus-c++-xml2cpp ${CMAKE_CURRENT_SOURCE_DIR}/3_Implementation/gnns_configservice.xml --proxy=${CMAKE_CURRENT_BINARY_DIR}/gnnsConfigservice-glue.h"
)


add_executable (
    ${TARGET_GNSSSERVICE_APP} ${GNSS_SOURCES}
    ${CMAKE_CURRENT_BINARY_DIR}/gnnsConfigservice-glue.h
)

pkg_check_modules(SD_BUS REQUIRED IMPORTED_TARGET sdbus-c++)

target_link_libraries(${TARGET_GNSSSERVICE_APP}  sdbus-c++)

# install to target
install ( TARGETS ${TARGET_GNSSSERVICE_APP}
          RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
          ARCHIVE DESTINATION ${CMAKE_INSTALL_BINDIR} )
