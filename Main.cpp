#include <MEGA328P.h>
#include <stdio.h>
#include <stdlib.h>
#include <delay.h>
#include "display.h"

/**
  * @desc En esta seccion se declaran las variables para la deteccion de pet,
  * como el pin al que se conectara la fotoresistencia, el tipo de ADC que se va
  * a utilizar y el rango de valores ADC que se usaran para determinar si es PET
**/

// Especifica el tipo de conversion de ADC
#define ADC_VREF_TYPE 0x40

// variable para el rango del ADC para detectar PET
#define PET_MIN
#define PET_MAX

// Variables del pin al que se conecta la entrada analogica

#define PIN_ADC_PET 7
#define PORT_ADC_PET PORTF.7

/**
  * @desc Funcion que lee el valor de ADC del pin seleccionado
  * @return bool - regresa un unsigned int de 0 a 1024 dependiendo del valor
  * analogico (0 a 5 volts)
**/
unsigned int read_adc(unsigned char adc_input){
  ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
  // Delay needed for the stabilization of the ADC input voltage
  delay_us(10);
  // Start the AD conversion
  ADCSRA|=0x40;
  // Wait for the AD conversion to complete
  while ((ADCSRA & 0x10)==0);
  ADCSRA|=0x10;
  return ADCW;
}

/**
  * @desc Funcion que inicializa comunicacion serial, timers y puertos del
  * microcontrolador
**/
void init(){
  //Esta seccion inicializa el ADC del microcontrolador
  DIDR0=0x01;
  ADMUX=ADC_VREF_TYPE & 0xff;
  ADCSRA=0x83;

  //Establece los pullups del microcontrolador
  PIN_ADC_PET = 1;
}

/**
  * @desc Funcion encargada de verificar que el material a detectar es tetrapack
  * @return int - regresa 0 si no es tetrepack o regresa mayor que cero si es
  * tetrapack
**/
int esTetraPack(){
  //Insertar codigo de deteccion de tetrapack
  return 0;
}

/**
  * @desc Funcion encargada de verificar que el material a detectar es una lata
  * @return int - regresa 0 si el material no es una lata o regresa mayor que
  * cero si es lata
**/
int esLata(){
  //Insertar codigo de deteccion de latas de aluminio
  return 0;
}

/**
  * @desc Funcion encargada de verificar que el material a detectar es vidrio
  * @return int - regresa 0 si el material no es vidrio o regresa mayor que cero
  * si es vidrio
**/
int esVidrio(){
  //Insertar codigo de deteccion de latas de aluminio
  return 0;
}


/**
  * @desc Funcion encargada de verificar que el material a detectar es PET
  * @return int - regresa 0 si el material no es PET o regresa mayor que cero
  * si es PET
**/
int esPet(){
  int valor =  read_adc(PIN_ADC_PET);
  if(valor > min && valor < min){
    return 1;
  }
  return 0;
}

/**
  * @desc FUNCION PRINCIPAL aqui se ejecuta el codigo que estara en el micro,
  * se encarga de verificar que tipo de material esta detectando y mandar por
  * el puerto serial al modulo bluetooth valores de "D1" a "D4" dependiendo del
  * material.
**/
void main(){
  init();
  while(1){
    if(esPet() > 0){
      printf("D1");
    }else if(esTetraPack()){
      printf("D2");
    }else if(esLata()){
      printf("D3");
    }else if(esVidrio()){
      printf("D4");
    }
  }
}
