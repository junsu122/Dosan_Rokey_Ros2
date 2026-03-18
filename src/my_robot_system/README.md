## 전체 실행 구조

이 패키지는 4개의 노드가 다음과 같이 상호작용:

1️⃣ 데이터 흐름
[SensorNode] --(Topic: temperature)--> [ManagerNode]
                                           │
                                           ├─ Service call → [CoolerService]
                                           │
                                           └─ Action goal → [SwitchActionServer]

2️⃣ 동작 시나리오

#### SensorNode

1초마다 랜덤 온도 (25~35도) 생성

temperature 토픽으로 publish

#### ManagerNode

temperature 구독

온도 > 30도이면:

cooler_motor 서비스 호출

switch_control 액션 goal 전송

#### CoolerService

서비스 요청 받으면 "Cooler activated!" 출력

#### SwitchActionServer

액션 goal 받으면:

ON/OFF 상태 로그

feedback 전송

2초 후 성공 처리

### 실행 시 실제 로그 흐름
Temperature: 31.2
→ Cooling ON
→ Service call
→ Action goal sent

Temperature: 32.1
→ (아무것도 안함)

Temperature: 28.5
→ Cooling OFF
→ Action goal sent