/* 
 * File:   my_usart.h
 * Author: Lenovo
 *
 * Created on September 6, 2024, 6:09 PM
 */

#ifndef MY_USART_H
#define	MY_USART_H

#define asyn 0
#define syn  1

void init_usart(char mode , int baud_rate);
void usart_select_mode(char mode);
void usart_select_baud_rate(int baud_rate);
char usart_receive_data ();
void usart_send_data (char data);

#endif	/* MY_USART_H */

