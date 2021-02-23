# Lock-free-Stack
3학년 1학기 운영체제 과목에서 출제되었던 과제 수행물입니다.

## Lock-free Stack 구현하기
- 구현 환경
  - MS Visual Studio Community 2017
  - C++17
- 컴파일 환경
  - MSVC++ 14.16, x64
- 주의사항
  - 반드시 **64bit**로 컴파일해야 정상작동한다.
  
## Lock-Free Data Stucture
운영체제의 주요 역할 중 하나는 resource를 관리하는 일입니다. 한 시스템 안에는 여러 공유 자원이 있는데, 하나의 공유 자원에 여러 개의 스레드(혹은 프로세스)가 동시에 접근하려고 시도하면 *race condition*이 발생할 수 있습니다. 운영체제는 이런 상황을 막기 위해 적절한 resource 관리 알고리즘을 수행해야 합니다. race condition을 방지하기 위한 resource 관리 방법엔 다음과 같은 것들이 있습니다.
- busy waiting
- Semaphore
- Monitor
- **Lock-free data structure**
Lock-free data structure는 여러 방법 중 하나입니다. Semaphore나 Monitor는 자원을 Lock함으로써 특정 프로세스가 자원을 이용하고 있을 때 다른 프로세스가 해당 자원에 접근하지 못하게 하는 원리지만 lock-free data structure는 lock에 의존하지 않습니다. 대신 **CAS(Compare And Swap)**라는 operation을 이용하여 자원의 취득을 atomic하게 처리합니다.

## ABA problem
lock-free data structure를 구현할 때 주의해야할 점이 있습니다. 바로 ABA problem입니다. ABA problem은 특수한 입출력이 발생했을 때 개발자가 의도하지 않은 형태로 동작할 수 있는 문제입니다. 제가 구현한 스택의 경우 push와 pop을 반복하면서 ABA problem이 발생할 수 있습니다.
이 문제를 해결하는 방법은 각 element에 tag를 붙이는 것입니다. 제 경우 각 element를 push 혹은 pop할 때 `cnt` tag를 붙여서 몇 번째 operation인지 기록해두었습니다. 이렇게 하면 CAS연산을 할 때 참조하는 두 element가 정말 같은 element인지 확인할 수 있습니다.
구체적으로는 64bit 시스템에서는 하위 52bit를 주소로 사용하고 상위 12bit를 사용하지 않는다는 점을 이용해, 상위 12bit를 counter로 사용했습니다.

## 테스트 방법
이 코드는 Visual Studio Community 2017로 작성되었으므로 코드 다운로드 후 Visual Studio에서 실행하여 테스트할 수 있습니다.
