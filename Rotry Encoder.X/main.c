//  File name: Rotary Encorder
//  Description:
//  ���[�^���[�G���R�[�̉�]�ɑΉ�����
//  �l��4����LED�ŕ\������B
//  Notes: 4MHz�����N���b�N
//        LED  RC0-3
//        Rotary Encorder
//             RB4,RB5
//    Language: MPLAB xc8
//    Target: PIC18F14K50

#include <xc.h>
#define _XTAL_FREQ 4000000      //�@delay_ms(x) �̂��߂̒�`

#define  LED         LATC
#define  A_pin       PORTBbits.RB5
#define  B_pin       PORTBbits.RB4

//-- �R���t�B�O���[�V���� --------
#pragma config MCLRE  = OFF, PWRTEN = OFF, BOREN  = OFF, BORV  = 30
#pragma config WDTEN  = OFF, WDTPS  = 32768, STVREN = ON, FOSC = IRC
#pragma config PLLEN  = ON,  CPUDIV = NOCLKDIV, USBDIV = OFF
#pragma config FCMEN  = OFF, IESO   = OFF, HFOFST = OFF, LVP   = OFF
#pragma config XINST  = OFF, BBSIZ  = OFF, CP0    = OFF
#pragma config CP1    = OFF, CPB    = OFF, WRT0   = OFF
#pragma config WRT1   = OFF, WRTB   = OFF, WRTC   = OFF
#pragma config EBTR0  = OFF, EBTR1  = OFF, EBTRB  = OFF

//-------�v���g�^�C�v--------------------------------------------------
char readRE(void);

#pragma code

void main(void){
    char count = 0;
    OSCCON = 0b01010010;      // �����N���b�N4Mhz
    PORTC = 0;
    TRISB = 0xF0;             // PortB ����
    TRISC = 0xF0;             // PortC RC0-3�o��
    ANSEL  = 0;               // �f�W�^������
    ANSELH = 0;
    INTCON2bits.RABPU = 0;    // RA/RB WeekPullUp��ON�ɐݒ�
    while(1){                 // �J��Ԃ����[�v
        count += readRE();    // �ω��������Z����
//      LED = count >> 2;     // 1�m�b�`��4�J�E���g�i�ރ^�C�v
        LED = count;          // �m�b�`�̂Ȃ��^�C�v
    }                         // �����܂ŌJ��Ԃ�
    
    //LED �`�J
    while(1){
    RA1 = 1;            //RA1�̃s����HIGH
    __delay_ms(200);    //200ms�x��
    RA1 = 0;
    __delay_ms(200);
  }
    
}

//------------------ readRE ------------------------------
// ���O�̏󋵂ƍ���̏󋵂����킹��16�ʂ�̑g��������
// ���E�ǂ���ɉ�]�������̂����肷�邱�Ƃ��ł���
// �߂�l�� (-1,0,1) �̂R�ʂ�
//--------------------------------------------------------
char readRE(void){
  static char RE_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
  static char RE_old = 0;               // ���ʕϐ��i�l�͕ۑ��j
  char RE_now;
  RE_now = B_pin * 2 + A_pin;           // ������̓ǎ�
  RE_old <<= 2;                         // �O��̓ǎ�l��
  RE_old |= ( RE_now & 0x03 );          // ����̓ǎ�l��g���킹��
  return (RE_states[(RE_old & 0x0F)]);  // �ω�����߂�l������
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
  ANSEL = 0b00000000;//�A�i���O���͂̐ݒ�iANSEL)
  ANSELH = 0b00000000;
  TRISA  = 0b00000000;
  TRISB  = 0b00000000;
  TRISC  = 0b00000000;
  PORTA  = 0b00000000;    //2�i���ŏ������ꍇ
  PORTB  = 0x00;          //16�i���ŏ������ꍇ
  PORTC  = 0;            //10�i���ŏ������ꍇ
}

int main(void){
  PICinit();      //PIC��������
  while(1){
    RA1 = 1;            //RA1�̃s����HIGH
    __delay_ms(200);    //200ms�x��
    RA1 = 0;
    __delay_ms(200);
  }


  return 0;
}
 */