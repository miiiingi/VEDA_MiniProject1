# VEDA_MiniProject1

## 조원 소개

- 김민기
- 장준호
- 이준영

## 개요
- customer & item 클래스의 데이터들을 sqlite3 를 통해 관리
- mainMenu 클래스를 통한 각 클래스 조작과 UI 동작
- CMake 를 활용한 빌드
- gtest 를 활용한 테스트
- 스마트 포인터, STL 자료구조 등을 활용한 효율적인 C++ 프로그래밍
- git & github 를 활용한 협업


## 프로젝트 차별점

### CMake 를 활용한 빌드
- CMakeLists.txt 파일은 Windows와 Unix-like 시스템에서 모두 SQLite3 라이브러리와 GoogleTest를 사용하여 프로젝트를 빌드하고 테스트할 수 있도록 구성되어 있습니다. 
- OS별 경로 처리, 종속성 관리, 빌드 대상 설정 등을 포함하여, 플랫폼 간 호환성을 유지하면서도 빌드를 간소화하였습니다.

- 프로젝트에서 사용한 도구인 gtest 및 sqlite3 역시 CMake 를 통해 간편하게 사용이 가능했습니다.

### gtest 를 활용한 테스트와 특히 DB 정합성 보장을 위한 노력
1. 각 Manager 클래스의 생성자를 통해, 일반적인 사용 시 useInMemory 값이 디폴트로 false 로 들어가면서 파일 db 를 사용하도록 하고, 
2. 테스트 시에는 인메모리 db 를 활용할 수 있도록 각 manager 의 생성자에 true 값 전달, db 를 테스트마다 백업 및 롤백해 주어야 하는 상황을 예방

### git & github 를 활용한 협업
- 각 멤버마다 클래스를 나누어 작업 수요를 분담하였음. 이때, 작업 내용과 목표를 명확히 하고자 github 를 통해 issue 내용을 공유 및 기록하였으며, 각 작업마다 branch 를 생성하여 작업하였음.
- 작업 branch 를 main 에 merge 할 땐 팀원들의 리뷰를 필수로 설정한 pull request 를 생성하여 모든 팀원이 프로젝트에 추가된 내용을 인지할 수 있도록 하였음.

### sqlite3 를 활용한 데이터 관리
- DB 를 통한 데이터 관리를 위해, 별도의 서버 없이 단일 파일에 저장해 간편하고 특히 C++ 에서 사용하기 적절한 sqlite3 를 사용하였습니다.

- 프로젝트 내 item 및 customer 클래스의 모든 데이터는 sqlite3 를 통해 저장 및 관리됩니다.

- 각 클래스의 구현에 있어서, 프로그램이 새로 실행되면서 기존에 db 저장되어 있는 데이터와 중복되는 경우의 처리도 고려하였습니다.

### 효율적인 C++ 프로그래밍 
- 프로젝트의 특성상, 고객 및 상품을 특정 key 값으로 검색하는 일이 잦을 것이라고 판단하여, 해시를 사용해 검색이 빠른 C++ STL map 자료구조인 unordered_map 을 선택하였습니다.
    - item 은 barcode 를 key 값으로, customer 는 phone 을 key 값으로 활용하였으며 value 는 각 클래스의 유니크 포인터를 활용하였음.
	    - 각 자료를 보관하는 데 유니크 포인터를 활용한 덕분에, 프로그램의 시작과 종료 시 map 자료구조가 소멸하면서 별도의 처리 없이 간편하게 동적할당된 객체들이 heap 메모리에서 해제됨.

### 세부 구현 디테일
- 상품 자료구조의 경우 실제 데이터와 유사하게 barcode 멤버를 활용하였음. 이는 상품 이름에 비해 각 상품을 구분하는 역할을 더 정확히 수행할 수 있음.
- 고객 자료구조의 경우 전화번호(phone)멤버를 통해 고객들을 서로 구분하였는데, 전화번호는 이름에 비해 중복(동명이인)이 없고 int 값인 덕분에 적은 오버헤드로 각 고객을 구분하는 역할을 더 정확히 수행할 수 있음.

- UI 기능을 각 클래스가 직접 수행하지 않고, mainMenu 클래스가 전담하여 처리하여, 모든 클래스가 하나의 역할만 맡는 책임 중심 설계 기법을 실현하고자 노력하였음. 
- 또한 item/customer 클래스는 데이터의 저장만을 맡았으며, 실질적으로 각 클래스들의 Manager 역할을 하는 클래스들이 데이터의 CRUD 를 포함한 여타 동작을 담당하도록 분리하였음.

- 모든 데이터 관련 동작은, map, .csv, sqlite3 db 모두에 대해 동작하도록 하였음.
