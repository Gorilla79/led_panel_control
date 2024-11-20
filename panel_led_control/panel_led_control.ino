#include <Adafruit_GFX.h>   // Core graphics library
#include <P3RGB64x32MatrixPanel.h>

P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 0, 15, 32, 33, 12, 5, 23, 4);

const char* messages[] = { "Searching", "Warnning", "Campus Guardians", "RECS" };
int messageIndex = 0;          // 현재 표시할 메시지의 인덱스
int16_t textX = matrix.width(); // 텍스트의 초기 X 좌표
int16_t textMin;                // 텍스트가 왼쪽으로 나가는 최소 좌표
int16_t hue = 0;                // 텍스트 색상 변화 속도

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);    // 텍스트가 화면의 오른쪽 끝을 넘어가도록 설정
  matrix.setTextSize(2);        // 텍스트 크기 설정
  textMin = -strlen(messages[messageIndex]) * 12; // 텍스트 길이에 따라 왼쪽 끝 좌표 설정
}

void loop() {
  // 화면 지우기
  matrix.fillScreen(0);

  // 텍스트 색상 설정 및 위치 설정
  matrix.setTextColor(matrix.colorHSV(hue, 255, 255));
  matrix.setCursor(textX, 9); // 텍스트 Y 좌표를 4칸 아래로 설정 (기존 5 -> 9로 변경)

  // 현재 메시지 출력
  matrix.print(messages[messageIndex]);

  // 텍스트 왼쪽 이동 (왼쪽으로 모두 이동하면 초기 위치로 리셋하고 다음 메시지로 전환)
  if (--textX < textMin) {
    textX = matrix.width();
    messageIndex = (messageIndex + 1) % 4; // 다음 메시지로 전환
    textMin = -strlen(messages[messageIndex]) * 12; // 새로운 메시지의 길이에 맞게 좌표 조정
  }

  // 색상 변화
  hue += 7;
  if (hue >= 1536) hue -= 1536;

#if !defined(__AVR__)
  // AVR 보드가 아닌 경우 화면 업데이트 속도를 맞추기 위한 딜레이
  delay(20);
#endif
}
