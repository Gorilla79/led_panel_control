// 초음파 센서 핀 설정
const int trigPin1 = 7;  // 첫 번째 초음파 센서 트리거 핀
const int echoPin1 = 6;  // 첫 번째 초음파 센서 에코 핀
const int trigPin2 = 9;  // 두 번째 초음파 센서 트리거 핀
const int echoPin2 = 10; // 두 번째 초음파 센서 에코 핀
const int ledPin = 8;    // LED가 연결된 핀

void setup() {
    Serial.begin(9600);  // 시리얼 통신 시작
    pinMode(trigPin1, OUTPUT);  // 첫 번째 트리거 핀을 출력 모드로 설정
    pinMode(echoPin1, INPUT);   // 첫 번째 에코 핀을 입력 모드로 설정
    pinMode(trigPin2, OUTPUT);  // 두 번째 트리거 핀을 출력 모드로 설정
    pinMode(echoPin2, INPUT);   // 두 번째 에코 핀을 입력 모드로 설정
    pinMode(ledPin, OUTPUT);    // 핀 8을 출력 모드로 설정 (LED 제어)
}

float getDistance(int trigPin, int echoPin) {
    // 초음파 신호 전송
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // 초음파 신호 수신 시간 측정
    long duration = pulseIn(echoPin, HIGH);

    // 거리 계산 (단위: cm)
    float distance = (duration * 0.0343) / 2;
    return distance;
}

void loop() {
    // 첫 번째 센서로부터 거리 측정
    float distance1 = getDistance(trigPin1, echoPin1);

    // 두 번째 센서로부터 거리 측정
    float distance2 = getDistance(trigPin2, echoPin2);

    // 결과를 Serial 모니터에 출력
    Serial.print("Distance1: ");
    Serial.print(distance1);
    Serial.print(" cm, ");
    Serial.print("Distance2: ");
    Serial.print(distance2);
    Serial.println(" cm");

    // 거리 조건에 따라 핀 8 제어
    if (distance1 < 100 && distance2 < 100) {  // 어느 하나라도 100cm 미만일 때
        digitalWrite(ledPin, HIGH);  // 핀 8에 전원 공급 (LED ON)
        Serial.println("LED ON");
    } else {  // 두 센서 모두 100cm 이상일 때
        digitalWrite(ledPin, LOW);   // 핀 8의 전원 차단 (LED OFF)
        Serial.println("LED OFF");
    }

    delay(500);  // 0.5초 대기 후 다음 측정
}
