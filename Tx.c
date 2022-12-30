
void main()
{

     PORTA = 0;          // PINES DEL PORTA EN 0
     PORTB = 0;          // PINES DEL PORTB EN 0
     ANSEL = 0;          // PORTA COMO E/S DIGITAL
     ANSELH = 0;         // PORTB COMO E/S DIGITAL
     TRISA = 0b10000010; // RA7 COMO ENTRADA (BTN CONFIRMACION)
                         // RA1 COMO ENTRADA (ACTIVACION RETARDADA)
                         // RA0 COMO SALIDA (ENVIO SERIAL DE DATOS)
     TRISB = 0b11111111; // PORTB COMO ENTRADA DIGITAL

     while (1)
     {

          if (PORTA.RA7 == 1)     //LECTURA DEL BOTON DE ACTIVACION
          {
               if (PORTA.RA1 == 1)
               { // RETARDO ADICIONAL PARA RX Y TX 2

                    delay_ms(3500);
               }
               delay_ms(500);
               // C1
               PORTA.RA0 = PORTB.RB0;
               delay_ms(500);

               // C2
               PORTA.RA0 = PORTB.RB1;
               delay_ms(500);

               // C3
               PORTA.RA0 = PORTB.RB2;
               delay_ms(500);

               // C4
               PORTA.RA0 = PORTB.RB3;
               delay_ms(500);

               // C5
               PORTA.RA0 = PORTB.RB4;
               delay_ms(500);

               // C6
               PORTA.RA0 = PORTB.RB5;
               delay_ms(500);

               PORTA.RA0 = 0;
          }
     }
}