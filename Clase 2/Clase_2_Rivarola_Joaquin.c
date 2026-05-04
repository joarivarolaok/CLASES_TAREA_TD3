#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

//==================== CONFIG ====================
#define APARTADO 'a'   // 'a', 'b', 'c', 'd', 'e'

//==================== DEFINICIONES ====================
#define PULSADOR   GPIO_NUM_18
#define SALIDA1    GPIO_NUM_25
#define SALIDA2    GPIO_NUM_26

#define DELAY_US   10000
#define DELAY_MS   10

//==================== HANDLES ====================
TaskHandle_t xHandleA = NULL;
TaskHandle_t xHandleB = NULL;
TaskHandle_t xHandleMonitor = NULL;

//==================== PROTOTIPOS ====================
void TaskA(void *pvParameters);
void TaskB(void *pvParameters);
void TaskMonitor(void *pvParameters);

//==================== APP_MAIN ====================

//APARTADO A
#if APARTADO == 'a'    
void app_main()
{
    xTaskCreatePinnedToCore(TaskA,                                  //Funcion que implementa la tarea 
                            "Tarea A",                              //Nombre de la tarea
                            configMINIMAL_STACK_SIZE * 2,           //Tamaño de la pila en bytes
                            NULL,                                   //Puntero a los parametros de la tarea
                            tskIDLE_PRIORITY + 1,                   //Prioridad de la tarea (0 es la mas baja)
                            &xHandleA,                              //Puntero a la tarea
                            0);                                     //Procesador donde se ejecuta la tarea

    configASSERT( xHandleA );                                       //Entra si no se pudieron crear las tareas

    xTaskCreatePinnedToCore(TaskB,                                  //Funcion que implementa la tarea 
                            "Tarea B",                              //Nombre de la tarea
                            configMINIMAL_STACK_SIZE * 2,           //Tamaño de la pila en bytes
                            NULL,                                   //Puntero a los parametros de la tarea
                            tskIDLE_PRIORITY + 1,                   //Prioridad de la tarea (0 es la mas baja)
                            &xHandleB,                              //Puntero a la tarea
                            0);                                     //Procesador donde se ejecuta la tarea

    configASSERT( xHandleB );                                       //Entra si no se pudieron crear las tareas

}

//==================== TAREA A - A ====================
void TaskA(void *pvParameters)
{
    gpio_set_direction(SALIDA1, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(SALIDA1, 1);
        ets_delay_us(DELAY_US);         //Delay en microsegundos que bloquea el procesador
        gpio_set_level(SALIDA1, 0);
        ets_delay_us(DELAY_US);
    }
}

//==================== TAREA B - A ====================

void TaskB(void *pvParameters)
{
    gpio_set_direction(SALIDA2, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(SALIDA2, 1);
        ets_delay_us(DELAY_US);         //Delay en microsegundos que bloquea el procesador
        gpio_set_level(SALIDA2, 0);
        ets_delay_us(DELAY_US);
    }
}

/*//APARTADO B

#elif APARTADO == 'b'    
void app_main()
{
    xTaskCreatePinnedToCore(TaskA,                                  //Funcion que implementa la tarea 
                            "Tarea A",                              //Nombre de la tarea
                            configMINIMAL_STACK_SIZE * 2,           //Tamaño de la pila en bytes
                            NULL,                                   //Puntero a los parametros de la tarea
                            tskIDLE_PRIORITY + 1,                   //Prioridad de la tarea (0 es la mas baja)
                            &xHandleA,                              //Puntero a la tarea
                            0);                                     //Procesador donde se ejecuta la tarea

    configASSERT( xHandleA );                                       //Entra si no se pudieron crear las tareas

    xTaskCreatePinnedToCore(TaskB,                                  //Funcion que implementa la tarea 
                            "Tarea B",                              //Nombre de la tarea
                            configMINIMAL_STACK_SIZE * 2,           //Tamaño de la pila en bytes
                            NULL,                                   //Puntero a los parametros de la tarea
                            tskIDLE_PRIORITY + 2,                   //Prioridad de la tarea (0 es la mas baja)
                            &xHandleB,                              //Puntero a la tarea
                            0);                                     //Procesador donde se ejecuta la tarea

    configASSERT( xHandleB );                                       //Entra si no se pudieron crear las tareas

}

//==================== TAREA A - B ====================
void TaskA(void *pvParameters)
{
    gpio_set_direction(SALIDA1, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(SALIDA1, 1);
        ets_delay_us(DELAY_US);         //Delay en microsegundos que bloquea el procesador
        gpio_set_level(SALIDA1, 0);
        ets_delay_us(DELAY_US);
    }
}

//==================== TAREA B - B ====================

void TaskB(void *pvParameters)
{
    gpio_set_direction(SALIDA2, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(SALIDA2, 1);
        ets_delay_us(DELAY_US);         //Delay en microsegundos que bloquea el procesador
        gpio_set_level(SALIDA2, 0);
        ets_delay_us(DELAY_US);
    }
}

//APARTADO C

#elif APARTADO == 'c'    
void app_main()
{
    xTaskCreatePinnedToCore(TaskA,                                  //Funcion que implementa la tarea 
                            "Tarea A",                              //Nombre de la tarea
                            configMINIMAL_STACK_SIZE * 2,           //Tamaño de la pila en bytes
                            NULL,                                   //Puntero a los parametros de la tarea
                            tskIDLE_PRIORITY + 2,                   //Prioridad de la tarea (0 es la mas baja)
                            &xHandleA,                              //Puntero a la tarea
                            0);                                     //Procesador donde se ejecuta la tarea

    configASSERT( xHandleA );                                       //Entra si no se pudieron crear las tareas

    xTaskCreatePinnedToCore(TaskB,                                  //Funcion que implementa la tarea 
                            "Tarea B",                              //Nombre de la tarea
                            configMINIMAL_STACK_SIZE * 2,           //Tamaño de la pila en bytes
                            NULL,                                   //Puntero a los parametros de la tarea
                            tskIDLE_PRIORITY + 2,                   //Prioridad de la tarea (0 es la mas baja)
                            &xHandleB,                              //Puntero a la tarea
                            0);                                     //Procesador donde se ejecuta la tarea

    configASSERT( xHandleB );                                       //Entra si no se pudieron crear las tareas

}

//==================== TAREA A - C ====================
void TaskA(void *pvParameters)
{
    gpio_set_direction(SALIDA1, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(SALIDA1, 1);
        vTaskDelay(DELAY_MS);         //Delay en milisegundos no bloqueante
        gpio_set_level(SALIDA1, 0);
        vTaskDelay(DELAY_MS);
    }
}

//==================== TAREA B - C ====================

void TaskB(void *pvParameters)
{
    gpio_set_direction(SALIDA2, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(SALIDA2, 1);
        vTaskDelay(DELAY_MS);         //Delay en milisegundos que bloquea el procesador
        gpio_set_level(SALIDA2, 0);
        vTaskDelay(DELAY_MS);
    }
}

#elif APARTADO == 'd'
void app_main()
{
    UBaseType_t prioridad = uxTaskGetPriority(NULL);    //Para obtener la prioridad de la tarea actual
    printf("Prioridad de app_main: %u\n", prioridad);   //Deberia ser 1

    xTaskCreatePinnedToCore(TaskA,                                  //Funcion que implementa la tarea 
                            "Tarea A",                              //Nombre de la tarea
                            configMINIMAL_STACK_SIZE,           //Tamaño de la pila en bytes
                            NULL,                                   //Puntero a los parametros de la tarea
                            tskIDLE_PRIORITY + 1,                   //Prioridad de la tarea (0 es la mas baja)
                            &xHandleA,                              //Puntero a la tarea
                            0);
    configASSERT( xHandleA );
    
    xTaskCreatePinnedToCore(TaskB,                                  //Funcion que implementa la tarea 
                            "Tarea B",                              //Nombre de la tarea
                            configMINIMAL_STACK_SIZE,           //Tamaño de la pila en bytes
                            NULL,                                   //Puntero a los parametros de la tarea
                            tskIDLE_PRIORITY + 2,                   //Prioridad de la tarea (0 es la mas baja)
                            &xHandleB,                              //Puntero a la tarea
                            0);
    configASSERT( xHandleB );
    
    xTaskCreatePinnedToCore(TaskMonitor,                                  //Funcion que implementa la tarea 
                            "Tarea Monitor",                              //Nombre de la tarea
                            configMINIMAL_STACK_SIZE * 3,           //Tamaño de la pila en bytes
                            NULL,                                   //Puntero a los parametros de la tarea
                            tskIDLE_PRIORITY + 1,                   //Prioridad de la tarea (0 es la mas baja)
                            &xHandleMonitor,                              //Puntero a la tarea
                            0);
    configASSERT( xHandleMonitor );//Entra si no se pudieron crear las tareas
}

//==================== TAREA A - D ====================
void TaskA(void *pvParameters)
{
    gpio_set_direction(SALIDA1, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(SALIDA1, 1);
        vTaskDelay(DELAY_MS*10);         //Delay en milisegundos no bloqueante
        gpio_set_level(SALIDA1, 0);
        vTaskDelay(DELAY_MS*10);
    }
}

//==================== TAREA B - D ====================

void TaskB(void *pvParameters)
{
    gpio_set_direction(SALIDA2, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(SALIDA2, 1);
        vTaskDelay(DELAY_MS*10);         //Delay en milisegundos que bloquea el procesador
        gpio_set_level(SALIDA2, 0);
        vTaskDelay(DELAY_MS*10);
    }
}


void TaskMonitor(void *pvParameters)
{
    while (true)
    {
        //Muestra el espacio minimo que ha en el stack desde que se creo la tarea
        //Cuanto menor sea el numero, mas cerca esta la tarea de quedarse sin stack
        printf( "Task %u min %u bytes \r\n", 2, uxTaskGetStackHighWaterMark( xHandleB));
        printf( "Task %u min %u bytes \r\n", 1, uxTaskGetStackHighWaterMark( xHandleA));
        vTaskDelay(DELAY_MS*10);
    }
}

#elif APARTADO == 'e'
void app_main()
{
    UBaseType_t prioridad = uxTaskGetPriority(NULL);    //Para obtener la prioridad de la tarea actual
    printf("Prioridad de app_main: %d\n", prioridad);   //Deberia ser 1

    xTaskCreatePinnedToCore(TaskA,                                  //Funcion que implementa la tarea 
                            "Tarea A",                              //Nombre de la tarea
                            configMINIMAL_STACK_SIZE*2,           //Tamaño de la pila en bytes
                            NULL,                                   //Puntero a los parametros de la tarea
                            tskIDLE_PRIORITY + 3,                   //Prioridad de la tarea (0 es la mas baja)
                            &xHandleA,                              //Puntero a la tarea
                            0);
    configASSERT( xHandleA );
    
    xTaskCreatePinnedToCore(TaskB,                                  //Funcion que implementa la tarea 
                            "Tarea B",                              //Nombre de la tarea
                            configMINIMAL_STACK_SIZE*2,           //Tamaño de la pila en bytes
                            NULL,                                   //Puntero a los parametros de la tarea
                            tskIDLE_PRIORITY + 3,                   //Prioridad de la tarea (0 es la mas baja)
                            &xHandleB,                              //Puntero a la tarea
                            0);
    configASSERT( xHandleB );
    
    xTaskCreatePinnedToCore(TaskMonitor,                                  //Funcion que implementa la tarea 
                            "Tarea Monitor",                              //Nombre de la tarea
                            configMINIMAL_STACK_SIZE * 3,           //Tamaño de la pila en bytes
                            NULL,                                   //Puntero a los parametros de la tarea
                            tskIDLE_PRIORITY + 1,                   //Prioridad de la tarea (0 es la mas baja)
                            &xHandleMonitor,                              //Puntero a la tarea
                            0);
    configASSERT( xHandleMonitor );//Entra si no se pudieron crear las tareas
}

//==================== TAREA A - D ====================
void TaskA(void *pvParameters)
{
    gpio_set_direction(SALIDA1, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(SALIDA1, 1);
        vTaskDelay(DELAY_MS*10);         //Delay en milisegundos no bloqueante
        gpio_set_level(SALIDA1, 0);
        vTaskDelay(DELAY_MS*10);
    }
}


//==================== TAREA B - D ====================

void TaskB(void *pvParameters)
{
    gpio_set_direction(SALIDA2, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(SALIDA2, 1);
        vTaskDelay(DELAY_MS*10);         //Delay en milisegundos que bloquea el procesador
        gpio_set_level(SALIDA2, 0);
        vTaskDelay(DELAY_MS*10);
    }
}


void TaskMonitor(void *pvParameters)
{
    while (true)
    {
        //Muestra el espacio minimo que ha en el stack desde que se creo la tarea
        //Cuanto menor sea el numero, mas cerca esta la tarea de quedarse sin stack
        printf( "Task %u min %u bytes \r\n", 2, uxTaskGetStackHighWaterMark( xHandleB));
        printf( "Task %u min %u bytes \r\n", 1, uxTaskGetStackHighWaterMark( xHandleA));
        vTaskDelay(DELAY_MS*10);
    }
}
*/
#endif