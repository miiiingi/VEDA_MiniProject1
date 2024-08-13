
//고객 매니저를 잘 만들면, 이 헤더를 여기서 include 안해도 되겠죠?
#include <iostream>

#include "customer.h"
#include "customerManager.h"

using namespace std;

//생성자는 id,이름,전번 순입니다.

CustomerManager Manager;

int main(void){
    
    //다섯명 넣고 다섯명 빼 봅시다.
    //이 예제가 성공하면, 인터페이스 함수가 그냥 두 메소드를 가져다 쓰면
    //customer 에 대한 입출력은 이제 종료에요.

    //추후 작업은, 각종 입력에 대한 방어코드 입력 입니다 
    for(int i = 0;i<5;i++){
	Manager.insertCustomer();
    }

    for(int i = 0;i<5;i++){
	Manager.printCustomer();
    }


    return 0;
}

