cmake_minimum_required(VERSION 3.10) # 최소 CMake 버전

project(VEDA_MiniProject1 LANGUAGES CXX) # 프로젝트 이름

# Find SQLite3 library
find_package(SQLite3 REQUIRED)


set(CMAKE_CXX_COMPILER "g++") # 컴파일러 명시
set(CMAKE_CXX_STANDARD 17) # C++ 표준 설정
set(CMAKE_CXX_STANDARD_REQUIRED True)

#헤더파일들이 들어갈 디렉토리 지정
include_directories(include)

#소스파일들 나열
set(SOURCES
    src/main.cpp
    src/customer.cpp
    src/customerManager.cpp
    src/item.cpp
    src/itemManager.cpp
    src/mainMenu.cpp
)

add_executable(VEDA_MiniProject1 ${SOURCES}) # 실행 파일 생성

#링크 SQLite3 to 실행파일
target_link_libraries(VEDA_MiniProject1 PRIVATE SQLite::SQLite3)
