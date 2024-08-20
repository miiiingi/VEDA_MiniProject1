# VEDA_MiniProject1




## 유저플로우

정의해야 되는 동작..

- 좋은 후보 : customerManager 클래스가, 구매라는 메소드를 통해서 ItemManager 클래스를 콜해서 요런저런 동작을 수행한다.
    - customer 에 Point 추가

- customerManager 클래스에서 CR 말고 UD 도 추가해야 함
- 각 customer 에 point 추가하고 이에대한 게터세터 추가하셔야 함
- 이거랑 더해서 기존 동작들 sqlite implementation
- 구매동작 구현(itemManager 를 멤버로 지니도록 수정)
    - 위에서 추가된 Point 연산이, item 의 price 기반으로 이뤄져야 함

    - 무엇보다 itemManager 를 customerManager 가 콜해서, 구매동작을 해야 해요...
        1. 바코드가지고 itemManager 에다가 검색하면 바로 구매 & Point 적립 되는걸로 yes or no 정도 물어보던지..
    


- itemManager 클래스에서, 상품목록을 마치 ls -a 명령어처럼 쭉 띄워주는 함수 만들고 => 이거 mainMenu 간접적으로 호출하도록..

1. main Menu 클래스에, 멤버변수로 current customer(customer 원시포인터)
2. customerManager 의 searchCustomer 함수를 통해, 로그인 시도 시 전화번호 기반으로 검색해서 얻은 유니크포인터에다가.get() 으로 원시포인터 얻어서 current customer 멤버에 대입


- mainMenu 클래스가 current customer 를 포인터의 형태로 가지고 있어야 함
    - 전화번호 베이스로 로그인하는 동작을 통해 currnet customer 의 유니크포인터참조자를 customerManager 안에 searchCustomer 메소드 통해서 가져와야함 

- mainMenu 는   
1. 매니저로그인하면 현재의 일반적인 모든 CRUD 옵션 뜨도록
2. 전화번호기반으로 customer 로그인하면 그제서야 구매(customerManager 가 콜하도록)및 item 목록조회(itemManager 콜하겟죠)가 뜨도록
    - 여기에 더해서 customer 로그아웃 까지 ?



