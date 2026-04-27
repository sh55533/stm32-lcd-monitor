# stm32-lcd-monitor

# 📟 STM32 ADC 전압 모니터 (I2C LCD)

![STM32](https://img.shields.io/badge/STM32-F446RE-blue)
![C](https://img.shields.io/badge/Language-C-lightgrey)
![I2C](https://img.shields.io/badge/Protocol-I2C-green)
![ADC](https://img.shields.io/badge/Peripheral-ADC%20%7C%20UART-orange)

> STM32 NUCLEO-F446RE로 ADC 전압값을 실시간 측정하여 I2C LCD에 출력하는 임베디드 시스템

---

## 📌 프로젝트 개요

| 항목 | 내용 |
|------|------|
| **MCU** | STM32F446RE (NUCLEO-F446RE) |
| **개발 환경** | STM32CubeIDE, HAL 라이브러리 |
| **언어** | C |
| **목적** | ADC, I2C, UART 통합 실습 및 포트폴리오 |

---

## 🛠️ 기술 스택

| 분류 | 내용 |
|------|------|
| **ADC** | PA0 핀 아날로그 전압 측정 (12bit, 0~4095) |
| **I2C** | LCD 1602 연동 (주소 0x27, PB8/PB9) |
| **UART** | 디버그 출력 (115200 baud, PuTTY) |
| **HAL** | STM32 HAL 라이브러리 |

---

## 🔄 시스템 흐름

```
[PA0 아날로그 입력]
        │
        ▼
[ADC 변환 (0~4095)]
        │
        ▼
[전압 계산 (mV = val × 3300 / 4095)]
        │
        ├──▶ [I2C LCD 출력]
        │
        └──▶ [1초 대기 후 반복]
```

---

## 📷 동작 사진

### LCD 출력
![LCD 동작](images/lcd_display.jpg)

### 전체 회로 연결
![회로 연결](images/circuit.jpg)

### UART 디버그 출력
![PuTTY](images/putty.png)

---

## ⚙️ 핀 연결

| LCD 핀 | NUCLEO 핀 |
|--------|----------|
| VCC | 5V |
| GND | GND |
| SDA | PB9 |
| SCL | PB8 |
| ADC 입력 | PA0 |

---

## ✅ 구현 결과

- [x] ADC 12bit 전압 측정 (0~3300mV)
- [x] I2C LCD 실시간 출력 (1초 갱신)
- [x] UART 디버그 출력 확인
- [x] GND/3.3V 연결 시 정확한 값 출력 확인

---

## 💡 배운 점

- STM32 HAL 라이브러리로 **ADC, I2C, UART** 통합 제어
- I2C 주소 스캐너로 디바이스 주소 디버깅 경험
- 여러 주변장치를 하나의 시스템으로 통합하는 설계 역량 향상
