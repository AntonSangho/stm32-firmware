# STM32 펌웨어 실습

임베디드 펌웨어 엔지니어 취업을 목표로 STM32F446RE(Nucleo-64) 보드에서 진행하는 실습 저장소입니다.

## 개발 환경

| 항목 | 내용 |
|------|------|
| MCU | STM32F446RE (ARM Cortex-M4, 최대 180MHz) |
| 보드 | Nucleo-64 (온보드 ST-Link) |
| 툴체인 | arm-none-eabi-gcc 10.3.1 |
| 라이브러리 | libopencm3 |
| RTOS | FreeRTOS |
| 플래싱 | st-flash |
| 참고 교재 | *Beginning STM32* (Warren Gay, Apress) |

## 실습 로드맵

| 미션 | 주제 | 핵심 개념 | 상태 |
|------|------|---------|------|
| M01 | 개발 환경 구축 + LED Blink | 툴체인, libopencm3, st-flash | ✅ 완료 |
| M02 | GPIO 입출력 (버튼 + LED) | GPIO 입력, Pull-up/down, 폴링 | ✅ 완료 |
| M03 | FreeRTOS 멀티태스킹 Blink | Task, Scheduler, vTaskDelay | ✅ 완료 |
| M04 | USART 시리얼 통신 | UART, printf 리다이렉션, FreeRTOS 브릿지 | ✅ 완료 |
| M05 | RTC + 인터럽트 | EXTI, ISR, Mutex | 🔲 예정 |
| M06 | I2C 센서 연동 | I2C 프로토콜, 슬레이브 주소 | 🔲 예정 |
| M07 | SPI Flash 읽기/쓰기 | SPI, 칩셀렉트 | 🔲 예정 |
| M08 | ADC 아날로그 입력 | ADC, 전압 변환 | 🔲 예정 |
| M09 | 클럭 트리 + PWM 서보 제어 | PLL, Timer, PWM | 🔲 예정 |
| M10 | CAN Bus 통신 | 차동 신호, 메시지 프레임 | 🔲 예정 |

## 프로젝트 구조

```
stm32-firmware/
├── libopencm3/          # libopencm3 서브모듈
├── FreeRTOS/            # FreeRTOS-Kernel 서브모듈
├── .vscode/             # VSCode IntelliSense 설정
├── m01-blink/           # M01: LED Blink
├── m02-button/          # M02: 버튼 + LED
├── m03-freertos/        # M03: FreeRTOS Blink
├── m04-usart/           # M04: USART 시리얼 통신
└── ...
```

## 빌드 및 플래싱

각 미션 디렉토리에서 실행합니다.

```bash
make          # 빌드
make flash    # 플래싱 (st-flash --reset)
make clean    # 빌드 산출물 삭제
```

## 주요 트러블슈팅 기록

### libopencm3 + FreeRTOS 핸들러 브릿지
libopencm3와 FreeRTOS는 인터럽트 핸들러 이름이 달라 브릿지 함수가 필요합니다.

```c
extern void xPortSysTickHandler(void);
extern void xPortPendSVHandler(void);
extern void vPortSVCHandler(void);

void sys_tick_handler(void) { xPortSysTickHandler(); }
void __attribute__((naked)) pend_sv_handler(void) { __asm volatile("b xPortPendSVHandler"); }
void __attribute__((naked)) sv_call_handler(void) { __asm volatile("b vPortSVCHandler"); }
```
