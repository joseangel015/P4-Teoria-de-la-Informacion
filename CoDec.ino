
// Bits de entrada para la palabra dato
int palabraDato[3] = {13, 12, 11};

// Bits de salida para la palabra código
int palabraCodigo[6] = {10, 9, 8, 7, 6, 5};

// Boton de confirmacion
int confirmar = 4;

// Puertos de envío y recepción serial
int serialTx1 = 22;
int serialRx1 = 23;
int bitPrueba1 = 26;

int serialTx2 = 24;
int serialRx2 = 25;
int bitPrueba2 = 27;

// Palabra código recibida
int palabraCodigoRx[6];

// Bits de entrada para error
int palabraError[6] = {28, 29, 30, 31, 32, 33};

// Bits de salida para la palabra R
int palabraR[6] = {34, 35, 36, 37, 38, 39};

// Palabra R recibida
int palabraRRx[6];

// Bits para el síndrome
int sindrome[3] = {40, 41, 42};
int sindromeV[3];

// Error reconstruido mediante el síndrome
int palabraErrorR[6];

// Bits de salida para la palabra Código reconstruida
int palabraCodigoReconstruida[6] = {43, 44, 45, 46, 47, 48};

void setup()
{

  pinMode(palabraDato[0], INPUT); // d1
  pinMode(palabraDato[1], INPUT); // d2
  pinMode(palabraDato[2], INPUT); // d3

  pinMode(palabraCodigo[0], OUTPUT); // c1
  pinMode(palabraCodigo[1], OUTPUT); // c2
  pinMode(palabraCodigo[2], OUTPUT); // c3
  pinMode(palabraCodigo[3], OUTPUT); // c4
  pinMode(palabraCodigo[4], OUTPUT); // c5
  pinMode(palabraCodigo[5], OUTPUT); // c6

  pinMode(confirmar, INPUT);

  pinMode(serialTx1, OUTPUT);
  pinMode(serialRx1, INPUT);
  pinMode(bitPrueba1, OUTPUT);
  pinMode(serialTx2, OUTPUT);
  pinMode(serialRx2, INPUT);
  pinMode(bitPrueba2, OUTPUT);

  pinMode(palabraError[0], INPUT); // e1
  pinMode(palabraError[1], INPUT); // e2
  pinMode(palabraError[2], INPUT); // e3
  pinMode(palabraError[3], INPUT); // e4
  pinMode(palabraError[4], INPUT); // e5
  pinMode(palabraError[5], INPUT); // e6

  pinMode(palabraR[0], OUTPUT); // r1
  pinMode(palabraR[1], OUTPUT); // r2
  pinMode(palabraR[2], OUTPUT); // r3
  pinMode(palabraR[3], OUTPUT); // r4
  pinMode(palabraR[4], OUTPUT); // r5
  pinMode(palabraR[5], OUTPUT); // r6

  pinMode(sindrome[0], OUTPUT); // s1
  pinMode(sindrome[1], OUTPUT); // s2
  pinMode(sindrome[2], OUTPUT); // s3

  pinMode(palabraCodigoReconstruida[0], OUTPUT); // c1r
  pinMode(palabraCodigoReconstruida[1], OUTPUT); // c2r
  pinMode(palabraCodigoReconstruida[2], OUTPUT); // c3r
  pinMode(palabraCodigoReconstruida[3], OUTPUT); // c4r
  pinMode(palabraCodigoReconstruida[4], OUTPUT); // c5r
  pinMode(palabraCodigoReconstruida[5], OUTPUT); // c6r
}

void loop()
{

  if (digitalRead(confirmar) == 1)
  {

    // Limpieza de variables
    int j;
    for (j = 0; j < 6; j++)
    {
      digitalWrite(palabraCodigo[j], 0);
      digitalWrite(palabraR[j], 0);
      digitalWrite(palabraCodigoReconstruida[j], 0);
      if (j < 3)
      {
        digitalWrite(sindrome[j], 0);
      }
    }

    // Creación de la palabra código

    digitalWrite(palabraCodigo[0], digitalRead(palabraDato[0])); // c1
    digitalWrite(palabraCodigo[1], digitalRead(palabraDato[1])); // c2
    digitalWrite(palabraCodigo[2], digitalRead(palabraDato[2])); // c3

    digitalWrite(palabraCodigo[3], digitalRead(palabraDato[0]) ^ digitalRead(palabraDato[2])); // c4
    digitalWrite(palabraCodigo[4], digitalRead(palabraDato[1]) ^ digitalRead(palabraDato[2])); // c5
    digitalWrite(palabraCodigo[5], digitalRead(palabraDato[0]) ^ digitalRead(palabraDato[1])); // c6

    // Transmisión serial de la palabra Código

    int i;
    for (i = 0; i < 6; i++)
    {
      digitalWrite(serialTx1, digitalRead(palabraCodigo[i]));
      palabraCodigoRx[i] = digitalRead(serialRx1);
      digitalWrite(bitPrueba1, digitalRead(serialRx1));
      delay(500);
      digitalWrite(bitPrueba1, LOW);
      delay(250);
    }
    digitalWrite(serialTx1, LOW);
    digitalWrite(bitPrueba1, LOW);

    // Creación de la palabra R

    for (i = 0; i < 6; i++)
    {
      digitalWrite(palabraR[i], digitalRead(palabraError[i]) ^ palabraCodigoRx[i]);
    }

    // Transmisión serial de la palabra R

    for (i = 0; i < 6; i++)
    {
      digitalWrite(serialTx2, digitalRead(palabraR[i]));
      palabraRRx[i] = digitalRead(serialRx2);
      digitalWrite(bitPrueba2, digitalRead(serialRx2));
      delay(500);
      digitalWrite(bitPrueba2, LOW);
      delay(250);
    }
    digitalWrite(serialTx2, LOW);
    digitalWrite(bitPrueba2, LOW);

    // Cálculo del síndrome

    digitalWrite(sindrome[0], palabraRRx[0] ^ palabraRRx[2] ^ palabraRRx[3]); // s1 = r1+r3+r4
    digitalWrite(sindrome[1], palabraRRx[1] ^ palabraRRx[2] ^ palabraRRx[4]); // s2 = r2+r3+r5
    digitalWrite(sindrome[2], palabraRRx[0] ^ palabraRRx[1] ^ palabraRRx[5]); // s3 = r1+r2+r6

    sindromeV[0] = digitalRead(sindrome[0]);
    sindromeV[1] = digitalRead(sindrome[1]);
    sindromeV[2] = digitalRead(sindrome[2]);

    // Reconstrucción del error a partir del síndrome

    palabraErrorR[0] = (sindromeV[0] && !sindromeV[1] && sindromeV[2]) || (sindromeV[0] && sindromeV[1] && sindromeV[2]);  // e1
    palabraErrorR[1] = (!sindromeV[0] && sindromeV[1] && sindromeV[2]);                                                    // e2
    palabraErrorR[2] = (sindromeV[0] && sindromeV[1] && !sindromeV[2]);                                                    // e3
    palabraErrorR[3] = (sindromeV[0] && !sindromeV[1] && !sindromeV[2]);                                                   // e4
    palabraErrorR[4] = (!sindromeV[0] && sindromeV[1] && !sindromeV[2]) || (sindromeV[0] && sindromeV[1] && sindromeV[2]); // e5
    palabraErrorR[5] = (!sindromeV[0] && !sindromeV[1] && sindromeV[2]);                                                   // e6

    // Reconstrucción de la palabra código

    for (i = 0; i < 6; i++)
    {
      digitalWrite(palabraCodigoReconstruida[i], palabraRRx[i] ^ palabraErrorR[i]);
    }
  }
}
