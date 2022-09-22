//  File name: Rotary Encorder
//  Description:
//  ロータリーエンコーの回転に対応した
//  値を4ヶのLEDで表示する。
//  Notes: 4MHz内部クロック
//        LED  RC0-3
//        Rotary Encorder
//             RB4,RB5
//    Language: MPLAB xc8
//    Target: PIC18F14K50

#include <xc.h>
#define _XTAL_FREQ 4000000      //　delay_ms(x) のための定義

#define  LED         LATC
#define  A_pin       PORTBbits.RB5
#define  B_pin       PORTBbits.RB4

//-- コンフィグレーション --------
#pragma config MCLRE  = OFF, PWRTEN = OFF, BOREN  = OFF, BORV  = 30
#pragma config WDTEN  = OFF, WDTPS  = 32768, STVREN = ON, FOSC = IRC
#pragma config PLLEN  = ON,  CPUDIV = NOCLKDIV, USBDIV = OFF
#pragma config FCMEN  = OFF, IESO   = OFF, HFOFST = OFF, LVP   = OFF
#pragma config XINST  = OFF, BBSIZ  = OFF, CP0    = OFF
#pragma config CP1    = OFF, CPB    = OFF, WRT0   = OFF
#pragma config WRT1   = OFF, WRTB   = OFF, WRTC   = OFF
#pragma config EBTR0  = OFF, EBTR1  = OFF, EBTRB  = OFF

//-------プロトタイプ--------------------------------------------------
char readRE(void);

#pragma code

void main(void){
    char count = 0;
    OSCCON = 0b01010010;      // 内部クロック4Mhz
    PORTC = 0;
    TRISB = 0xF0;             // PortB 入力
    TRISC = 0xF0;             // PortC RC0-3出力
    ANSEL  = 0;               // デジタル入力
    ANSELH = 0;
    INTCON2bits.RABPU = 0;    // RA/RB WeekPullUpをONに設定
    while(1){                 // 繰り返しループ
        count += readRE();    // 変化分を加算する
//      LED = count >> 2;     // 1ノッチで4カウント進むタイプ
        LED = count;          // ノッチのないタイプ
    }                         // ここまで繰り返し
    
    //LED チカ
    while(1){
    RA1 = 1;            //RA1のピンをHIGH
    __delay_ms(200);    //200ms遅延
    RA1 = 0;
    __delay_ms(200);
  }
    
}

//------------------ readRE ------------------------------
// 直前の状況と今回の状況を合わせた16通りの組合せから
// 左右どちらに回転をしたのか判定することができる
// 戻り値は (-1,0,1) の３通り
//--------------------------------------------------------
char readRE(void){
  static char RE_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
  static char RE_old = 0;               // 共通変数（値は保存）
  char RE_now;
  RE_now = B_pin * 2 + A_pin;           // 今回情報の読取
  RE_old <<= 2;                         // 前回の読取値と
  RE_old |= ( RE_now & 0x03 );          // 今回の読取値を組合わせる
  return (RE_states[(RE_old & 0x0F)]);  // 変化分を戻り値をする
}






/*

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 8000000

void PICinit(){
  OSCCON = 0b01110000;
  ANSEL = 0b00000000;//アナログ入力の設定（ANSEL)
  ANSELH = 0b00000000;
  TRISA  = 0b00000000;
  TRISB  = 0b00000000;
  TRISC  = 0b00000000;
  PORTA  = 0b00000000;    //2進数で書いた場合
  PORTB  = 0x00;          //16進数で書いた場合
  PORTC  = 0;            //10進数で書いた場合
}

int main(void){
  PICinit();      //PICを初期化
  while(1){
    RA1 = 1;            //RA1のピンをHIGH
    __delay_ms(200);    //200ms遅延
    RA1 = 0;
    __delay_ms(200);
  }


  return 0;
}
 */