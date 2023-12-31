cmake_minimum_required(VERSION 3.14)

project(ToolBox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

#======================= INCLUSION OF Qt =======================#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})


find_package(Qt5 COMPONENTS 
    Core
    Gui 
    Widgets
    Sql
    QUIET)

#=========================== use folders ===========================#
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#=================== INCLUSION OF Project Files ====================#
if (WIN32)
add_definitions(-DHAVE_STRUCT_TIMESPEC -DWIN32_LEAN_AND_MEAN )
endif()

set (FORMS_DIR          "${CMAKE_SOURCE_DIR}/forms")
set (RES_DIR            "${CMAKE_SOURCE_DIR}/res")
set (SOURCE_DIR         "${CMAKE_SOURCE_DIR}/src") 
set (INCLUDE_DIR        "${CMAKE_SOURCE_DIR}/src")



include_directories(
    ${FORMS_DIR}
    ${INCLUDE_DIR}
    ${INCLUDE_DIR}/ui
    ${INCLUDE_DIR}/manager
)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_autogen/include_Debug)

link_directories(
)

file(GLOB_RECURSE SRC_FILES
    "${SOURCE_DIR}/*.c*"
)

file (GLOB_RECURSE INC_FILES
    "${INCLUDE_DIR}/*.h"
)

file (GLOB_RECURSE FORMS_FILES
    "${FORMS_DIR}/*.ui"
)

file (GLOB_RECURSE RES_FILES
    "${RES_DIR}/Qss/*.qss"
    "${RES_DIR}/*.qrc"
    "${RES_DIR}/*.rc"
)

if (WIN32)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${SRC_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${INC_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${FORMS_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${RES_FILES})
endif()

#=================== SETUP EXECTUABLE ====================#
# Enable debug logging on RELWITHDEBINFO configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
)

# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS  ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})
# Add the forms directory to the AUTORCC search paths
set(CMAKE_AUTORCC_SEARCH_PATHS ${CMAKE_AUROECC_SEARCH_PATHS} ${RES_DIR})


if (WIN32)
    list(APPEND EXTRA_LIBS
)
else (UNIX)
    list(APPEND EXTRA_LIBS
    )
endif()


if (WIN32) 
    add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES} ${INC_FILES} ${FORMS_FILES} ${RES_FILES})
elseif(UNIX)
    add_executable(${PROJECT_NAME} ${SRC_FILES} ${INC_FILES} ${FORMS_FILES} ${RES_FILES})
endif()


# Add the target includes for MY_PROJECT 
target_include_directories(${PROJECT_NAME} PRIVATE ${RES_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${FORMS_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${QT_INC})


#===================== LINKING LIBRARIES =======================#
target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::Sql
    ${EXTRA_LIBS}
    ${QT_QTSQL_LIBRARIES}
)

# out set
set (OUT_BIN ${CMAKE_BINARY_DIR})

file(COPY config/config.ini DESTINATION config)
file(COPY db/components.db DESTINATION db)
