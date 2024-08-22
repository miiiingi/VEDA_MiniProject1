cmake_minimum_required(VERSION 3.10) # 최소 CMake 버전

project(VEDA_MiniProject1 LANGUAGES CXX) # 프로젝트 이름

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Windows 환경에서만 SQLite3 경로 설정
if(WIN32)
    set(SQLite3_INCLUDE_DIR "C:/Users/snd03/Desktop/VEDA/02. VEDA_Class/02. 2week_C++/04. PATH")
    set(SQLite3_LIBRARY "C:/Users/snd03/Desktop/VEDA/02. VEDA_Class/02. 2week_C++/04. PATH/sqlite3.lib")
endif()

# 헤더파일들이 들어갈 디렉토리 지정
include_directories(${SQLite3_INCLUDE_DIR})
include_directories(include)  # 헤더 파일이 위치한 디렉토리

# 소스파일들 나열
set(SOURCES
    src/main.cpp
    src/customer.cpp
    src/customerManager.cpp
    src/item.cpp
    src/itemManager.cpp
    src/mainMenu.cpp
)

# 실행 파일 생성
add_executable(VEDA_MiniProject1 ${SOURCES})

# SQLite3 라이브러리와의 연결
target_link_libraries(VEDA_MiniProject1 PRIVATE ${SQLite3_LIBRARY})
