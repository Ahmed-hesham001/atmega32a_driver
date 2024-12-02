/*
 * File:   newavr-main.c
 * Author: Lenovo
 *
 * Created on August 22, 2024, 5:55 PM
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DIO.h"
#include "buttons.h"
#include "leds.h"
#include "my_lcd.h"
#include "my_lcd4.h"
#include "keypad.h"
#include "adc.h"
#include "my_interrupt.h"
#include "my_timer.h"
#include "my_functions.h"
#include "my_usart.h"
#include "spi.h"
#include "eeprom.h"

#include "freertos/include/FreeRTOS.h"
#include "freertos/include/FreeRTOSConfig.h"
#include "freertos/include/task.h"
#include "freertos/include/queue.h"
#include "freertos/include/semphr.h"

//password code
//int main(void) {
//    /* Replace with your application code */
//    init_keypad();
//    init_lcd4();
//    char password [] = "5555";
//    int tries = 3;
//    char input [17];
//
//    while (1) {
//        if (tries) {
//            lcd4_cmd(clear);
//            lcd4_print_str("password :");
//            lcd4_set_cur(1, 0);
//            for (int i = 0; i < 16; ++i) {
//                if (read_key() == '=') {
//                    _delay_ms(200);
//                    break;
//                } else {
//                    input[i] = read_key();
//                    _delay_ms(200);
//                    lcd4_print_char(input[i]);
//                }
//            }
//            if (!strcmp(input, password)) {
//                lcd4_cmd(clear);
//                lcd4_print_str("access granted");
//                _delay_ms(1000);
//                break;
//            } else {
//                lcd4_cmd(clear);
//                lcd4_print_str("access denied");
//                _delay_ms(1000);
//                --tries;
//            }
//        } else {
//            lcd4_cmd(clear);
//            lcd4_print_str("device blocked");
//            _delay_ms(1000);
//            break;
//        }
//    }
//}
//char input;
//
//ISR(INT0_vect) {
//    lcd4_cmd(clear);
//    lcd4_print_str("enter pot num: ");
//    input = read_key();
//}
//
//int main(void) {
//    init_adc(AVCC, div_factor128, ch0);
//    init_lcd4();
//    init_keypad();
//    init_INT0(INT_FALLING_EDGE);
//    _delay_ms(100);
//    lcd4_cmd(clear);
//    lcd4_print_str("enter pot num: ");
//    input = read_key();
//    
//    while (1) {
//        switch (input) {
//            case '1':
//                adc_select_channel(ch0);
//                adc_sc();
//                check_flag;
//                lcd4_cmd(clear);
//                lcd4_print_str("pot 1 : ");
//                lcd4_ptint_int(ADCW * step);
//                lcd4_print_str("mV");
//                _delay_ms(500);
//                break;
//            case '2':
//                adc_select_channel(ch1);
//                adc_sc();
//                check_flag;
//                lcd4_cmd(clear);
//                lcd4_print_str("pot 2 : ");
//                lcd4_ptint_int(ADCW * step);
//                lcd4_print_str("mV");
//                _delay_ms(500);
//                break;
//            case '3':
//                adc_select_channel(ch2);
//                adc_sc();
//                check_flag;
//                lcd4_cmd(clear);
//                lcd4_print_str("pot 3 : ");
//                lcd4_ptint_int(ADCW * step);
//                lcd4_print_str("mV");
//                _delay_ms(500);
//                break;
//            default:
//                lcd4_cmd(clear);
//                lcd4_print_str("invalid input>:(");
//                _delay_ms(1500);
//                lcd4_cmd(clear);
//                lcd4_print_str("enter pot num: ");
//                input = read_key();
//                break;
//
//        }
//    }
//}
//ISR(TIMER1_CAPT_vect){
//    lcd4_cmd(clear);
//    lcd4_ptint_int(timer1_ICP_getValue());
//}
//int main(void) {
//    init_lcd4();
//    init_timer1(TIMER_NORMAL,clockSelect_Clk_io_1024);
//    timer1_ICP_select_Edge(FALLING_EDGE);
//    timer1_ICP_init();
//    timer1_ICP_noise_filter();
//    timer1_ICP_int_en();
//    sei();
//    while (1) {
//    
//    }
//}

////////////////////////////////usart///////////////////////////////
//#define buzzer PA3
//
//int main() {
//    DDRA |= (1 << buzzer);
//    init_buttons();
//    init_lcd4();
//    init_usart(asyn, 1200);
//    char message[16];
//    char state = -1;
//    while (1) {
//
//        if (is_pressed(BTN1)) {
//            _delay_ms(100);
//            state = 1;
//
//        }
//        if (is_pressed(BTN2)) {
//            _delay_ms(100);
//            state = 2;
//        }
//        switch (state) {
//            case 1:
//                lcd4_cmd(clear);
//                strcpy(message, "RECEIVER");
//                lcd4_print_str(message);
//                lcd4_set_cur(1, 0);
////                for (int i = 0; i < 16; ++i) {
////                    lcd4_print_char(usart_receive_data());
////                }
////                _delay_ms(2000);
//                lcd4_print_char(usart_receive_data());
//                _delay_ms(2000);
////                if(usart_receive_data()){
////                    set_pin('A', buzzer, HIGH);
////                _delay_ms(250);
////                set_pin('A', buzzer, LOW);
////                }
//                state = -1;
//                break;
//            case 2:
//                lcd4_cmd(clear);
//                strcpy(message, "TRANSMITTER");
//                lcd4_print_str(message);
//                lcd4_set_cur(1, 0);
////                strcpy(message, "test yasta");
////                for (int i = 0; i < 16; ++i) {
////                    usart_send_data(message[i]);
////                    _delay_ms(500);
////                    }
//                usart_send_data('7');
//                _delay_ms(500);
//                state = -1;
//                break;
//            default:
//                state = -1;
//                lcd4_cmd(clear);
//                strcpy(message, "pick mode :");
//                lcd4_print_str(message);
//                break;
//        }
//
//    }
//    return 0;
//}

//int main() {
//    init_spi(master, SPI_CLK_128);
//    init_leds();

//    init_buttons();
//
//    init_lcd4();
//    _delay_ms(100);
//    while (1) {
//                if (is_pressed(BTN0)){
//                    _delay_ms(150);
//                    spi_send_data(1);
//                    lcd4_cmd(clear);
//                    lcd4_print_char('1');
//                }
//                if (is_pressed(BTN1)){
//                    _delay_ms(150);
//                    spi_send_data(2);
//                    lcd4_cmd(clear);
//                    lcd4_print_char('2');
//                }

//        char input = spi_get_data();
//
//        switch (input) {
//            case 1:
//                set_led(LED0, HIGH);
//                lcd4_cmd(clear);
//                lcd4_print_char('1');
//                break;
//            case 2:
//                set_led(LED0, LOW);
//                lcd4_cmd(clear);
//                lcd4_print_char('2');
//                break;
//        }

//    }

//int main() {
//
//    init_buttons();
//    init_lcd4();
//    spi_clk_select(SPI_CLK_128);
//    init_spi(MASTER);
//
//    char data = 'A';
//
//    eeprom_write_char(data, 0x10);
//
//    lcd4_print_char(eeprom_read_char(0x10));
//    _delay_ms(50);
//
//    int i = 0;
//    while (1) {
//
//        if (is_pressed(BTN0)) {
//            if(i>=15 && i<31){
//                lcd4_set_cur(1,0+i-15);
//            }else if (i>=31){
//                lcd4_cmd(clear);
//                lcd4_set_cur(0,0);
//                i=0;
//            }
//            eeprom_write_char(++data, 0x10);
//            _delay_ms(200);
//            lcd4_print_char(eeprom_read_char(0x10));
//            ++i;
//        }
//
//    }
//    return 0;
//}

//int main() {
//
//    init_buttons();
//
//    init_timer2_syn(TIMER2_CTC_MODE, clockSelect_Clk_io_1024);
//    char val = 150;
//    timer2_select_comp_val(val);
//    init_OC2();
//    OC2_select_mode(OC2_TOGGLE_NON_PWM_MODE);
//
//    DDRC = 0xFF;
//    while (1) {
//        if (is_pressed(BTN0)) {
//            _delay_ms(250);
//            val += 10;
//            timer2_select_comp_val(val);
//        }
//        if (is_pressed(BTN2)) {
//            _delay_ms(250);
//            val -= 10;
//            timer2_select_comp_val(val);
//        }
//        PORTC = OCR2;
//    }
//    return 0;
//}

//void task_fun1(void *pParameter) {
//    while (1) {
//        toggle_led(LED0);
//        vTaskDelay(500);
//    }
//    vTaskDelete(NULL);
//}
//
//void task_fun2(void *pParameter) {
//    while (1) {
//        toggle_led(LED1);
//        vTaskDelay(100);
//    }
//    vTaskDelete(NULL);
//}
//
//void task_fun3(void *pParameter) {
//    while (1) {
//        toggle_led(LED2);
//        vTaskDelay(250);
//    }
//    vTaskDelete(NULL);
//}
//
//int main() {
//
//    init_leds();
//
//    TaskHandle_t Handeler1 = NULL;
//
//    xTaskCreate(task_fun1,
//            "TASK1",
//            100,
//            NULL,
//            1,
//            &Handeler1);
//
//
//    TaskHandle_t Handeler2 = NULL;
//
//    xTaskCreate(task_fun2,
//            "TASK2",
//            100,
//            NULL,
//            1,
//            &Handeler2);
//
//    TaskHandle_t Handeler3 = NULL;
//
//    xTaskCreate(task_fun3,
//            "TASK3",
//            100,
//            NULL,
//            1,
//            &Handeler3);
//
//    vTaskStartScheduler();
//
//    while (1) {
//
//    }
//    return 0;
//}
//void TaskFUNC1(void* para);
//void TaskFUNC2(void* para);
//void TaskFUNC3(void* para);
//
//TaskHandle_t TaskHandler3 = NULL;
//TaskHandle_t TaskHandler2 = NULL;
//TaskHandle_t TaskHandler1 = NULL;
//
//int main() {
//    init_leds();
//    init_lcd4();
//
//    char* state1 = "   TASK  A   ";
//    char* state2 = "   TASK  B   ";
//
//    init_uart(ASYN, 9600);
//
//    //handler to delete task (it acts as task pointer)
//    //A task handle, used later to delete or control the task.
//
//    //create a TASK
//    xTaskCreate(//task function
//            TaskFUNC1,
//
//            //task name 
//            "Task1",
//
//            //allowed stack size
//            100,
//
//            //POINTER to parameter 
//            NULL,
//
//            //priority (where higher numbers indicate higher priority).
//            1,
//
//            //ADDRESS to handler to delete/control task
//            &TaskHandler1);
//
//    xTaskCreate(
//            //task function
//            TaskFUNC2,
//
//            //task name 
//            "Task2",
//
//            //allowed stack size
//            100,
//
//            //address of parameter casted as (void*)
//            //if it is already a pointer we don't need to send it address
//            //if state1 wasn't a pointer: (void*) &state1
//            (void *) state1,
//
//            //priority
//            1,
//
//            //address to handler to delete task
//            &TaskHandler2);
//
//
//    /*In FreeRTOS (and many other RTOSs), task functions always take a (void*) as their parameter for flexibility. 
//     * This allows the same task function to receive ANY type of data when the task is created.
//     */
//
//
//    xTaskCreate(TaskFUNC2, //task function
//            "Task3", //task name 
//            100, //allowed stack size
//            (void *) state2, //pointer to parameter (&(char*) state2 == state2)
//            1, //priority
//            &TaskHandler3); //address to handler to delete task
//
//
//    //Starts the FreeRTOS scheduler, allowing tasks to run according to their priorities.
//    vTaskStartScheduler();
//
//    while (1) {
//
//    }
//    return 0;
//}
//
//void TaskFUNC1(void* para) {
//    while (1) {
//        toggle_led(LED0);
//        vTaskDelay(500);
//    }
//    vTaskDelete(NULL); //to delete task if we break from the loop
//    /*if it is given NULL it deletes the task it is in, 
//    else give it the handler of the task you want to delete */
//}
//
//void TaskFUNC2(void* para) {
//
//    TaskStatus_t *pxTask1Status;
//    TaskStatus_t *pxTask2Status;
//    TaskStatus_t *pxTask3Status;
//
//    vTaskGetInfo(TaskHandler1,
//            pxTask1Status,
//            pdTRUE,
//            eInvalid);
//    vTaskGetInfo(TaskHandler2,
//            pxTask2Status,
//            pdTRUE,
//            eInvalid);
//    vTaskGetInfo(TaskHandler3,
//            pxTask3Status,
//            pdTRUE,
//            eInvalid);
//
//    while (1) {
//        if ((char*) para == "   TASK  A   ") {
//            uart_send_str((char*) para);
//            vTaskDelay(500);
//        } else if ((char*) para == "   TASK  B   ") {
//            uart_send_str((char*) para);
//            vTaskDelay(500);
//        }
//    }
//    vTaskDelete(NULL);
//
//}
//
//void TaskFUNC3(void* para) {
//    while (1) {
//        //cast para to be char pointer then DE-REFFRENCE (*) to get the data in this pointer
//        char data = *((char *) para);
//        /* casting steps:
//         * 1) you have para as void pointer (void* )
//         * 2) make para a char pointer instead (or any data type you want) (type* )
//         * 3) then dereference it using (*) to get data inside the pointer
//         */
//    }
//    vTaskDelete(NULL);
//}
//

///////////////////////////////////////////////////////////////////


//QueueHandle_t queue_handler;
//
//void task1_fun() {
//    while (1) {
//        uart_send_str("hello task 1");
//        uart_send_char('\r');
//        vTaskDelay(500);
//    }
//    vTaskDelete(NULL);
//}
//
//TaskHandle_t handler1;
//
//void task2_fun() {
//    while (1) {
//        uart_send_str("hello task 2");
//        uart_send_char('\r');
//        vTaskDelay(1000);
//    }
//    vTaskDelete(NULL);
//}
//
//TaskHandle_t handler2;
//
//int main() {
//    init_uart(ASYN, 9600);
//
//
//    xTaskCreate(task1_fun, "task1", 100, NULL, 1, &handler1);
//    xTaskCreate(task2_fun, "task1", 100, NULL, 1, &handler2);
//
//
//    vTaskStartScheduler();
//
//    while (1) {
//    }
//}

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////


//QueueHandle_t queue_handler = NULL;
//
//void task1_fun() {
//
//    int data = 0;
//    while (1) {
//        vTaskDelay(2);
//        uart_send_str("in task 1 :");
//        uart_send_char('\r');
//        adc_sc();
//        while (!(ADCSRA & (1 << ADIF)));
//        data = adc_get_data();
//        xQueueSendToFront(queue_handler, (void*) &data, 2);
//        taskYIELD();
//
//    }
//    vTaskDelete(NULL);
//}
//
//TaskHandle_t handler1;
//
//void task2_fun() {
//    int rec_data = 0;
//    while (1) {
//        vTaskDelay(2);
//        xQueueReceive(queue_handler, (void*) &rec_data, 2);
//
//        uart_send_str("in task 2 :");
//        uart_send_num(rec_data);
//        uart_send_char('\r');
//        taskYIELD();
//    }
//    vTaskDelete(NULL);
//}
//
//TaskHandle_t handler2;
//
//int main() {
//    init_uart(ASYN, 9600);
//    init_adc(AVCC, div_factor128, ch0);
//    _delay_ms(50);
//
//    queue_handler = xQueueCreate(3, sizeof (int));
//
//    xTaskCreate(task1_fun, "task1", 200, NULL, 1, &handler1);
//    xTaskCreate(task2_fun, "task2", 200, NULL, 1, &handler2);
//
//
//    vTaskStartScheduler();
//
//    while (1) {
//    }
//}

///////////////////////////////////////////////////////////////////////////////

//int main(){
//    init_uart(ASYN,9600);
//    init_adc(AVCC , div_factor128 , ch0);
//    init_lcd4();
//    while(1){
//        adc_select_channel(ch0);
//        adc_sc();
//        check_flag;
//        int data = adc_get_data();
//        lcd4_cmd(clear);
//        lcd4_ptint_int(data);
//        uart_send_num(data);
//        uart_send_char('\r');
//        _delay_ms(500);
//    }
//    return 0;
//}
//////////////////////////////////////////////////////////////////////////
//
//QueueHandle_t queue_handler = NULL;
//
//typedef struct {
//    int data;
//    int channel;
//} zData;
//
//void task1_fun(void *parameter) {
//    vTaskDelay(4);
//    zData my_data;
//    my_data.channel = ((int *) parameter);
//    adc_select_channel(my_data.channel);
//    adc_sc();
//    check_flag;
//    my_data.data = adc_get_data();
//    xQueueSendToFront(queue_handler, (void *) &my_data, 2);
//}
//
//void task2_fun() {
//    zData rec_data;
//    while (1) {
//        vTaskDelay(4);
//        xQueueReceive(queue_handler, (void*) &rec_data, 2);
//
//        switch (rec_data.channel) {
//            case 0:
//                uart_send_str("CHO :");
//                uart_send_num(rec_data.data);
//                uart_send_char('\r');
//                taskYIELD();
//                break;
//            case 1:
//                uart_send_str("CH1 :");
//                uart_send_num(rec_data.data);
//                uart_send_char('\r');
//                taskYIELD();
//                break;
//        }
//
//    }
//    vTaskDelete(NULL);
//}
//
//
//TaskHandle_t handler1;
//TaskHandle_t handler2;
//TaskHandle_t handler3;
//
//int main() {
//    init_uart(ASYN, 9600);
//    init_adc(AVCC, div_factor128, ch0);
//    _delay_ms(50);
//
//    queue_handler = xQueueCreate(4, sizeof (zData));
//
//    int channel0 = ch0;
//    int channel1 = ch1;
//
//    xTaskCreate(task1_fun, "task1", 100, (void *) &channel0, 1, &handler1);
//    xTaskCreate(task2_fun, "task2", 200, NULL, 2, &handler2);
//    xTaskCreate(task1_fun, "task3", 100, (void *) &channel1, 1, &handler3);
//
//
//    vTaskStartScheduler();
//
//    while (1) {
//    }
//}

//////////////////////////////////////////////////////////////////////////////

//QueueHandle_t queue_handler = NULL;
//
//typedef struct {
//    int data;
//    int channel;
//} zData;
//
//void task1_fun(void *parameter) {
//    vTaskDelay(pdMS_TO_TICKS(10));  // Delay by 10ms
//    zData my_data;
//    my_data.channel = *((int *) parameter);  // Dereferencing the pointer correctly
//    adc_select_channel(my_data.channel);
//    adc_sc();
//    check_flag;  // Assuming it's a function
//    my_data.data = adc_get_data();
//    xQueueSendToFront(queue_handler, (void *) &my_data, portMAX_DELAY);  // Ensure queue success
//}
//
//void task2_fun() {
//    zData rec_data;
//    while (1) {
//        vTaskDelay(pdMS_TO_TICKS(10));  // Delay by 10ms
//        if (xQueueReceive(queue_handler, (void*) &rec_data, portMAX_DELAY)) {  // Updated queue receive
//            switch (rec_data.channel) {
//                case 0:
//                    uart_send_str("CH0 :");
//                    uart_send_num(rec_data.data);
//                    uart_send_char('\r');
//                    taskYIELD();
//                    break;
//                case 1:
//                    uart_send_str("CH1 :");
//                    uart_send_num(rec_data.data);
//                    uart_send_char('\r');
//                    taskYIELD();
//                    break;
//            }
//        }
//    }
//    vTaskDelete(NULL);  // Ensure this task deletion is handled properly
//}
//
//TaskHandle_t handler1;
//TaskHandle_t handler2;
//TaskHandle_t handler3;
//
//int main() {
//    init_uart(ASYN, 9600);
//    init_adc(AVCC, div_factor128, ch0);
//    vTaskDelay(pdMS_TO_TICKS(50));  // Replacing _delay_ms with FreeRTOS delay
//
//    queue_handler = xQueueCreate(4, sizeof(zData));
//    if (queue_handler == NULL) {
//        uart_send_str("Queue creation failed");
//        while (1);  // Handle error
//    }
//
//    int channel0 = ch0;
//    int channel1 = ch1;
//
//    xTaskCreate(task1_fun, "task1", 200, (void *) &channel0, 1, &handler1);  // Increased stack size
//    xTaskCreate(task2_fun, "task2", 200, NULL, 2, &handler2);
//    xTaskCreate(task1_fun, "task3", 200, (void *) &channel1, 1, &handler3);
//
//    vTaskStartScheduler();
//
//    while (1) {
//    }
//}


///////////////////////////////////////////////////////////////////////////////
//
//
//SemaphoreHandle_t semaphore = NULL;
//
//TaskHandle_t handler1;
//TaskHandle_t handler2;
//
//
//int count = 0;
//
//void function1() {
//
//
//    vTaskDelay(10);
//    while (1) {
//        if (xSemaphoreTake(semaphore, 4) == pdTRUE) {
//            uart_send_num(++count);
//            uart_send_str("done1\r");
//            xSemaphoreGive(semaphore);
//            taskYIELD();
//        } else {
//            uart_send_str("busy1\r");
//        }
////        vTaskDelay(30);
//    }
//}
//
//void function2() {
//
//    vTaskDelay(10);
//    while (1) {
//        if (xSemaphoreTake(semaphore, 4) == pdTRUE) {
//            uart_send_num(++count);
//            uart_send_str("done2\r");
//            xSemaphoreGive(semaphore);
//            taskYIELD();
//        } else {
//            uart_send_str("busy2\r");
//        }
////        vTaskDelay(30);
//    }
//}
//
//int main() {
//
//    init_uart(ASYN, 9600);
//    uart_send_str("hello world\r");
//
//    xTaskCreate(function1, "task1", 200, NULL, 1, &handler1);
//    xTaskCreate(function2, "task2", 200, NULL, 1, &handler2);
//
//    semaphore = xSemaphoreCreateBinary();
//    xSemaphoreGive(semaphore);
//
//    vTaskStartScheduler();
//    while (1) {
//
//    }
//    return 0;
//}

///////////////////////////////////////////////////////////////////////////////


//SemaphoreHandle_t semaphore = NULL;
//
//TaskHandle_t handler1;
//TaskHandle_t handler2;
//
//
//int count = 0;
//
//void function1() {
//
//
//    vTaskDelay(1);
//    while (1) {
//        if (xSemaphoreTake(semaphore, 1) == pdTRUE) {
//            uart_send_num(++count);
//            uart_send_str("done1\r");
//            xSemaphoreGive(semaphore);
//            taskYIELD();
//        } else {
//            uart_send_str("busy1\r");
//        }
//    }
//}
//
//void function2() {
//
//    vTaskDelay(1);
//    while (1) {
//        if (xSemaphoreTake(semaphore, 1) == pdTRUE) {
//            uart_send_num(++count);
//            uart_send_str("done2\r");
//            xSemaphoreGive(semaphore);
//            taskYIELD();
//        } else {
//            uart_send_str("busy2\r");
//        }
//    }
//}
//
//int main() {
//
//    init_uart(ASYN, 9600);
//    uart_send_str("hello world\r");
//
//    xTaskCreate(function1, "task1", 200, NULL, 1, &handler1);
//    xTaskCreate(function2, "task2", 200, NULL, 1, &handler2);
//
//    semaphore = xSemaphoreCreateCounting(2,2);
//    xSemaphoreGive(semaphore);
//
//    vTaskStartScheduler();
//    while (1) {
//
//    }
//    return 0;
//}
///////////////////////////////////////////////////////////////////////////////


SemaphoreHandle_t semaphore = NULL;

TaskHandle_t handler1;
TaskHandle_t handler2;


int count = 0;

void function1() {


    vTaskDelay(1);
    while (1) {
        if (xSemaphoreTake(semaphore, 1) == pdTRUE) {
            uart_send_num(++count);
            uart_send_str("done1\r");
            xSemaphoreGive(semaphore);
            taskYIELD();
        } else {
            uart_send_str("busy1\r");
        }
    }
}

void function2() {

    vTaskDelay(1);
    while (1) {
        if (xSemaphoreTake(semaphore, 1) == pdTRUE) {
            uart_send_num(++count);
            uart_send_str("done2\r");
            xSemaphoreGive(semaphore);
            taskYIELD();
        } else {
            uart_send_str("busy2\r");
        }
    }
}

int main() {

    init_uart(ASYN, 9600);
    uart_send_str("hello world\r");

    xTaskCreate(function1, "task1", 200, NULL, 1, &handler1);
    xTaskCreate(function2, "task2", 200, NULL, 1, &handler2);

    semaphore = xSemaphoreCreateMutex();
    //    xSemaphoreGive(semaphore);

    vTaskStartScheduler();
    while (1) {

    }
    return 0;
}