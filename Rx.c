
void main()
{

      PORTA = 0;          // PINES DEL PORTA EN 0
      PORTB = 0;          // PINES DEL PORTB EN 0
      ANSEL = 0;          // PORTA COMO E/S DIGITAL
      ANSELH = 0;         // PORTB COMO E/S DIGITAL
      TRISA = 0b10000011; // RA7 COMO ENTRADA (BTN CONFIRMACION)
                          // RA1 COMO ENTRADA (ACTIVACION RETARDADA)
                          // RA0 COMO ENTRADA (RECEPCION SERIAL DE DATOS)
      TRISB = 0b00000000; // PORTB COMO SALIDA DIGITAL

      while (1)
      {

            if (PORTA.RA7 == 1)    //LECTURA DEL BOTON DE ACTIVACION
            {
                  if (PORTA.RA1 == 1)
                  { // RETARDO ADICIONAL PARA RX Y TX 2
                        delay_ms(3500);
                  }
                  // C1
                  delay_ms(1000);
                  PORTB.RB0 = PORTA.RA0;
                  delay_ms(500);

                  // C2
                  PORTB.RB1 = PORTA.RA0;
                  delay_ms(500);

                  // C3
                  PORTB.RB2 = PORTA.RA0;
                  delay_ms(500);

                  // C4
                  PORTB.RB3 = PORTA.RA0;
                  delay_ms(500);

                  // C5
                  PORTB.RB4 = PORTA.RA0;
                  delay_ms(500);

                  // C6
                  PORTB.RB5 = PORTA.RA0;
                  delay_ms(500);

                  PORTA.RA0 = 0;
            }
      }
}