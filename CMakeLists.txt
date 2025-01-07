cmake_minimum_required(VERSION 3.25)
project(Poker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#if(WIN32)
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/mingw_64/lib/cmake/Qt6")
#elseif(APPLE)
#    set(CMAKE_PREFIX_PATH "PATH TO APPLE QT COMPILER"
# set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Gui Quick Qml)
qt_add_resources(RESOURCES resources.qrc)

qt_wrap_cpp(MOC_SOURCES include/gameState.h)

# Select which files to compile here, comment out files not needed instead of deleting
add_executable(poker src/main.cpp
                     src/gameState.cpp
                     src/CardDeck.cpp
                     src/Game.cpp
                     src/Player.cpp
                     src/Pot.cpp
                     src/Table.cpp
                     ${RESOURCES}
                     ${MOC_SOURCES})

target_include_directories(poker PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(poker PRIVATE Qt6::Core Qt6::Gui Qt6::Quick Qt6::Qml)
