cmake_minimum_required(VERSION 3.10) # 최소 CMake 버전

project(VEDA_MiniProject1 LANGUAGES CXX) # 프로젝트 이름

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17) # C++17 표준
set(CMAKE_CXX_STANDARD_REQUIRED True)

# SQLite3 라이브러리와 헤더 파일 경로 설정
set(SQLite3_INCLUDE_DIR "C:/Users/snd03/Desktop/VEDA/02. VEDA_Class/02. 2week_C++/04. PATH")
set(SQLite3_LIBRARY "C:/Users/snd03/Desktop/VEDA/02. VEDA_Class/02. 2week_C++/04. PATH/sqlite3.lib")

# 헤더 파일 경로 추가
include_directories(${SQLite3_INCLUDE_DIR})

# 헤더파일들이 들어갈 디렉토리 지정
include_directories(${CMAKE_SOURCE_DIR}/include)

# 라이브러리 경로 추가
#link_directories(${CMAKE_SOURCE_DIR}/04. PATH)

# 소스파일들 나열
set(SOURCES
    src/main.cpp
    src/customer.cpp
    src/customerManager.cpp
    src/item.cpp
    src/itemManager.cpp
    src/mainMenu.cpp
)    

add_executable(VEDA_MiniProject1 ${SOURCES}) # 실행 파일 생성

# SQLite3 라이브러리 링크
target_link_libraries(VEDA_MiniProject1 PRIVATE ${SQLite3_LIBRARY})