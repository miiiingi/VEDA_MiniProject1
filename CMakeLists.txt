cmake_minimum_required(VERSION 3.10) # 최소 CMake 버전

project(VEDA_MiniProject1 LANGUAGES CXX) # 프로젝트 이름

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# SQLite3 라이브러리와의 연결을 위한 설정
if(WIN32)
    # Windows 환경에서만 SQLite3 경로 설정
    set(SQLite3_INCLUDE_DIR "C:/Users/snd03/Desktop/VEDA/02. VEDA_Class/02. 2week_C++/04. PATH")
    set(SQLite3_LIBRARY "C:/Users/snd03/Desktop/VEDA/02. VEDA_Class/02. 2week_C++/04. PATH/sqlite3.lib")
else()
    # Unix-like 시스템 (Linux, macOS 등)
    find_package(SQLite3 REQUIRED)
    set(SQLite3_INCLUDE_DIR ${SQLite3_INCLUDE_DIRS})
    set(SQLite3_LIBRARY ${SQLite3_LIBRARIES})
endif()

# 헤더파일들이 들어갈 디렉토리 지정
include_directories(include)

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

# SQLite3 라이브러리와 테스트 타겟 연결
target_link_libraries(VEDA_MiniProject1 PRIVATE ${SQLite3_LIBRARY})

# GTest 라이브러리와의 연결을 위한 설정
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 테스트 실행 파일 생성
add_executable(RunTests test/test.cpp)

# GTest와 테스트 타겟 연결
target_link_libraries(RunTests PRIVATE GTest::gtest_main)

# 테스트 자동 검색 및 실행 설정
enable_testing()
include(GoogleTest)
gtest_discover_tests(RunTests)
