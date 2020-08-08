cmake_minimum_required(VERSION 3.5)

project(qrun LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES src/*.cpp)

find_package(Qt5 COMPONENTS Core Quick Positioning REQUIRED)

add_executable(qrun
	${SRC_FILES}
	qml.qrc
	)

target_compile_definitions(qrun PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(qrun PRIVATE Qt5::Core Qt5::Quick Qt5::Positioning)
