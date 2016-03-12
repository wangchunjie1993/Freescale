/******************** (C) COPYRIGHT 2012-2013 �Ĭ�Ƽ� DEMOK*********
 * �ļ���         ��uart.h
 * ����           ��������غ�����ͷ�ļ�

 * ʵ��ƽ̨       �� �Ĭ�Ƽ�DEMOK Kinetis������
 * ����           �� �Ĭ�Ƽ�DEMOK Kinetis����С��

 * �Ա�����       �� http://shop60443799.taobao.com/
 * ������������   �� 1030923155@qq.com 
 * ��������QQȺ   �� 103360642

 * ����޶�ʱ��    ��2012-10-29
 * �޶�����        ����
**********************************************************************************/

#ifndef __UART_H__
#define __UART_H__

typedef enum  UARTn
{
    //��ʼ��Ĭ������       --TXD--      --RXD--     ���Ը�������ͨ�����������޸� uart_init
    UART0,    //           PTD7         PTD6
    UART1,    //           PTC4         PTC3
    UART2,    //           PTD3         PTD2
    UART3,    //           PTC17        PTC16
    UART4,    //           PTE24        PTE25
    UART5     //           PTE8         PTE9
} UARTn;

extern volatile struct UART_MemMap *UARTx[6];
/********************************************************************/



void uart_init (UARTn, u32 baud);                     //��ʼ��uartxģ��

char uart_getchar   (UARTn);                          //���޵ȴ�����1���ֽ�
char uart_pendchar  (UARTn, char *ch);                //����ʱ��ȴ�����һ���ַ�
char uart_pendstr   (UARTn, char *str);               //����ʱ��ȴ������ַ���

int uart_query      (UARTn);                          //��ѯ�Ƿ���յ�һ���ֽ�

void uart_putchar   (UARTn, char ch);                 //����1���ֽ�
void uart_sendN     (UARTn , uint8 *buff, uint16 len); //����n���ֽ�
void uart_sendStr   (UARTn , const u8 *str);          //�����ַ���


void uart_irq_EN    (UARTn);                          //�����ڽ����ж�
void uart_irq_DIS   (UARTn);                          //�ش��ڽ����ж�



#define UART_IRQ_EN(UARTn)   UART_C2_REG(UARTx[UARTn])|=UART_C2_RIE_MASK; enable_irq((UARTn<<1)+45)     //�궨�忪���ڽ����ж�
#define UART_IRQ_DIS(UARTn)  UART_C2_REG(UARTx[UARTn])&=~UART_C2_RIE_MASK; disable_irq((UARTn<<1)+45)   //�궨��ؽ������ŵ�IRQ�ж�




/********************************************************************/

#endif /* __UART_H__ */