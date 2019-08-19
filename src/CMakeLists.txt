#  Copyright (c) 2014-2017 Andrey Upadyshev <oliora@gmail.com>
#
#  Use, modification and distribution are subject to the
#  Boost Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

project(ppconsul LANGUAGES CXX)

set(HEADERS
    agent.h
    catalog.h
    consul.h
    error.h
    health.h
    helpers.h
    http_client.h
    http_status.h
    kv.h
    kwargs.h
    parameters.h
    ppconsul.h
    response.h
    sessions.h
    types.h
)

set(SOURCES
    http_helpers.h
    s11n.h
    s11n_types.h
    all_clients.h
    agent.cpp
    catalog.cpp
    consul.cpp
    helpers.cpp
    health.cpp
    kv.cpp
    sessions.cpp
    status.cpp
    curl/http_client.h
    curl/http_client.cpp
)

foreach(SRC ${HEADERS})
    list(APPEND SOURCES "${HEADERS_DIR}/${SRC}")
endforeach()

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

if (NOT BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} STATIC
        ${SOURCES}
    )
else()
    add_library(${PROJECT_NAME} SHARED
        ${SOURCES}
    )
endif()

target_compile_features(${PROJECT_NAME} PUBLIC cxx_auto_type cxx_decltype cxx_static_assert cxx_rvalue_references)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Boost_INCLUDE_DIRS}
        ${CURL_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/ext
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        json11
        ${Boost_LIBRARIES}
        ${CURL_LIBRARIES}
)

source_group(${PROJECT_NAME} FILES ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${Ppconsul_VERSION}
    SOVERSION ${Ppconsul_VERSION}
    FOLDER ${PROJECT_NAME}
)

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${CMAKE_PROJECT_NAME}
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

