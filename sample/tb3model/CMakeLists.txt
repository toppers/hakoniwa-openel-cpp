set(HAKO_CMAKE_VERSION 3.5.1)
cmake_minimum_required(VERSION ${HAKO_CMAKE_VERSION})

project(hakoniwa-openel
    VERSION 1.0.0
    DESCRIPTION "hakoniwa-openel-cpp project"
    LANGUAGES C CXX
)

set(OPENEL_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../../openel-cpp/lib/surface")
set(OPENEL_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../../openel-cpp/include/surface")
set(SAMPLE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(HAKO_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../../hakoniwa-core-cpp-client")
set(HAKO_PDU_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../../hakoniwa-ros2pdu/pdu/types")
set(TB3MODEL_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../../openel-device/tb3model/src")

if (DEFINED HAKO_OPTION_FILEPATH)
    include(${HAKO_OPTION_FILEPATH})
else()
    include(default-cmake-options.cmake)
endif()

message(STATUS "BUILD_TYPE " ${BUILD_TYPE})

add_executable(
    hako-openel
    ${OPENEL_SOURCE_DIR}/Actuator.cpp
    ${OPENEL_SOURCE_DIR}/Sensor.cpp
    ${OPENEL_SOURCE_DIR}/HALComponent.cpp
    ${OPENEL_SOURCE_DIR}/EventTimer.cpp
    ${OPENEL_SOURCE_DIR}/openEL_linkedList.cpp
    ${OPENEL_SOURCE_DIR}/openEL.cpp
    ${OPENEL_SOURCE_DIR}/HALObserver.cpp
    ${OPENEL_SOURCE_DIR}/Property.cpp
    ${OPENEL_SOURCE_DIR}/HALId.cpp
    ${SAMPLE_SOURCE_DIR}/main.cpp
    ${TB3MODEL_SOURCE_DIR}/hako_openEL_registryConfig.cpp
    ${TB3MODEL_SOURCE_DIR}/openEL_ActuatorHako.cpp
    ${TB3MODEL_SOURCE_DIR}/openEL_SensorHako.cpp
    ${TB3MODEL_SOURCE_DIR}/openel_impl.cpp
)
message(STATUS "hako lib path: " ${HAKO_SOURCE_DIR}/cmake-build/core/src)
target_link_directories(hako-openel
  PRIVATE
  ${HAKO_SOURCE_DIR}/cmake-build/core/src
  /usr/local/lib/hakoniwa
)

target_link_libraries(hako-openel 
  hako
  rt
  pthread
)

target_include_directories(
    hako-openel
    PRIVATE /usr/local/include
    PRIVATE ${OPENEL_INCLUDE_DIR}
    PRIVATE ${OPENEL_SOURCE_DIR}
    PRIVATE ${STUBS_SOURCE_DIR}/include
    PRIVATE ${SAMPLE_SOURCE_DIR}
    PRIVATE ${HAKO_SOURCE_DIR}/core/src/include
    PRIVATE ${HAKO_PDU_SOURCE_DIR}
)
