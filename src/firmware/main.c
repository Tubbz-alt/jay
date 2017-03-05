#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include "uart.h"

#include "gyro.h"
#include "mag.h"
#include "temperature.h"
#include "accel.h"
#include "nmea.h"
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

char buffer[256];

int main (void) {
	InitializeUART(9600);
    _delay_ms(500);
    GPS_DATA data;
    while (1) {
        memset(buffer, '\0', 180);
            GPS_UpdateData();
           if(GPS_IsDataReady()) {
                data = GPS_GetData();
                sprintf(buffer, "time: %02d:%02d:%02d \nstatus: %c \nlat: %.4f \nlong: %.4f \nspeed: %.2f \nAlt: %.2f \n", data.time.tm_hour, data.time.tm_min, data.time.tm_sec, data.status, data.Lat, data.Long, data.speed, data.altitude);
                int i = 0;
                while (buffer[i] != '\0') {
                    _uart_driver_SendByte(buffer[i]);
                    i++;
                }
            }
       
       // check if missing many packets, data may be close in time 

    }
    /*
	UART_SendString("RESET\n");
	InitializeMag();
	InitializeGyro();
	InitializeTemperature();
    InitializeAccel();
    
	memset(buffer, '\0', 128);
  	DDRB |= (1<<DDB5);  //Set the 6th bit on PORTB (i.e. PB5) to 1 => output
  	while(1){
    	PORTB |= (1<<PORTB5);     //Turn 6th bit on PORTB (i.e. PB5) to 1 => on
    	//_delay_ms(200);          //Delay for 1000ms => 1 sec

    	PORTB &= ~(1<<PORTB5);    //Turn 6th bit on PORTB (i.e. PB5) to 0 => off
         
		sprintf(buffer, "M = %f\n", Mag_Get());
		UART_SendString(buffer);
		memset(buffer, '\0', 128);

		Gyro_Update();
    	sprintf(buffer, "G(x,y,z) = %f,%f,%f\ntemp=%f\n", Gyro_GetX(), Gyro_GetY(), Gyro_GetZ(), Temperature_Get());

		UART_SendString(buffer);
		memset(buffer, '\0', 128);
	    
        Accel_Update();
        _delay_ms(2);
    	sprintf(buffer, "A(x,y,z) = %f,%f,%f\n", Accel_GetX(), Accel_GetY(), Accel_GetZ());
       

		UART_SendString(buffer);
		memset(buffer, '\0', 128);
        UART_SendString("\nHI_THERE\n");

    	_delay_ms(1000);          //Delay for 1000ms => 1 sec
		
        i=0;
        while (!UART_IsEmpty()){
            buffer[i] = UART_GetByte();
            i++;
           
        }
         if(i ){

               UART_SendString(buffer);
            }
           
        
    }*/
}


