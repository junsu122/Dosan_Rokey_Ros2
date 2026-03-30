# 🤖 ROS 2 실습 코드 모음 (Doosan ROKEY 7기)

본 저장소는 **Doosan ROKEY 7기** 과정 중 학습한 ROS 2의 핵심 통신 메커니즘인 **Topic, Service, Action**의 Python 구현 및 실습 내용을 정리한 공간입니다.

---

## 📋 ROS 2 통신 메커니즘 요약

| 구분 | 통신 방식 | 특징 | 주요 용도 |
| :--- | :--- | :--- | :--- |
| **Topic** | 단방향 / 비동기 | 연속적인 데이터 스트림 | 센서 데이터, 로봇 상태 보고 |
| **Service** | 양방향 / 동기 | Request-Response 구조 | 일시적인 명령, 상태 변경 |
| **Action** | 양방향 / 비동기 | Goal-Feedback-Result | 장시간 작업, 피드백 필요 시 |

---

## 📂 주요 실습 내용

### 1. Topic (Publisher & Subscriber)
- **개념**: 데이터를 발행(Publish)하고 구독(Subscribe)하는 가장 기본적인 통신 방식
- **실습 항목**:
  - `std_msgs/String` 메시지를 활용한 문자열 송수신
  - 주기적(Timer) 데이터 발행 및 콜백 함수를 통한 데이터 처리

### 2. Service (Service & Client)
- **개념**: 클라이언트의 요청이 있을 때만 서버가 응답하는 일대일 통신 방식
- **실습 항목**:
  - `example_interfaces/AddTwoInts` 서비스를 이용한 숫자 합산 서버 구현
  - 비동기 클라이언트를 활용한 요청 및 응답 대기 로직

### 3. Action (Action Server & Client)
- **개념**: 서비스와 유사하나 중간 피드백(Feedback)을 제공하고 취소가 가능한 통신 방식
- **실습 항목**:
  - `example_interfaces/Fibonacci` 액션을 이용한 수열 계산 서버 구현
  - 목표 송신, 중간 상태 피드백 수신, 최종 결과 확인 프로세스 구현

---

## 🛠 실행 방법 (Build & Run)

### 1. 환경 설정 및 빌드
```bash
# 워크스페이스 이동 및 빌드
cd ~/ros2_ws
colcon build --packages-select [your_package_name]

# 환경 변수 반영
source install/setup.bash

---
## 노트북에 맞는 드라이버 사용중인지 확인
glxinfo | grep "OpenGL renderer"
