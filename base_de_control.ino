//programacion para arduino mega, que funciona como la base
//de control de el alimentador

#include <Wire.h>//libreria para conexion i2c
#include <LiquidCrystal.h>//libreria para uso de pantalla lcd
#include <Servo.h>//libreria para el uso de servomotores
#include <TimerOne.h>
#include <Keypad.h>
#include <DS1307RTC.h>
#include <Time.h>

const byte ROWS = 4;
const byte COLS = 3;

char hexaKeys[ROWS][COLS] = {
  {
    '1', '2', '3'                      }
  ,
  {
    '4', '5', '6'                      }
  ,
  {
    '7', '8', '9'                      }
  ,
  {
    '*', '0', '#'                      }
};

byte rowPins[ROWS] = {
  29, 31, 33, 35}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  37, 39, 41};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

Servo servoA;
Servo servoC;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int buttonPin1 = 22;
const int buttonPin2 = 23;
const int buttonPin3 = 24;
const int buttonPin4 = 25;
const int led1 = 4;
const int led2 = 3;

int buttonState1 = 0;
int buttonState2 = 0;  
int buttonState3 = 0;
int buttonState4 = 0;

int FSR_Pin = A0;

int tipo = 0;
int raza = 0;
int edad = 0;
int peso = 0;
int cont = 0;
int nComidas = 5;
int sum = 0;
double horaComida;
int cantComida = 0 ;
double contH;

void setup() {

  Timer1.initialize(250000);

  Wire.begin();

  setSyncProvider(RTC.get); 
  setTime(10,6,0,1,7,2016);
  if (timeStatus() != timeSet)
    Serial.println("Unable to sync with the RTC");
  else
    Serial.println("RTC has set the system time");

  servoA.attach(26);
  servoC.attach(27);

  servoA.write(90);
  servoC.write(90);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);

  Serial.begin(9600);

  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.write("INICIALIZANDO...");
  delay(1000);
  lcd.begin(20, 4);
  lcd.setCursor(8, 0);
  lcd.write("UDLA");
  delay(1000);
  // put your setup code here, to run once:
}

void loop() {

  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);

  int temp1 = 0;
  int temp2 = 0;

  int FSRReading = analogRead(FSR_Pin);
  char customKey = customKeypad.getKey();
  //char customKey = customKeypad.waitForKey();

  if(cont == 0){
    lcd.setCursor(0, 0);
    lcd.write("Seleccione el tipo:");
    lcd.setCursor(0, 1);
    lcd.write("1.- Perro");
    lcd.setCursor(0, 2);
    lcd.write("2.- Gato");

    //ciclo para perros
    if (customKey == '1') {
      //perro
      //lcd.clear();
      tipo = 1;
      cont++; 
      //delay(3000);
      //lcd.begin(20, 4);
      lcd.setCursor(0, 0);
      lcd.write("Seleccione la raza: ");
      lcd.setCursor(0, 1);
      lcd.write("1.- Grande");
      lcd.setCursor(0, 2);
      lcd.write("2.- Mediado");
      lcd.setCursor(0, 3);
      lcd.write("3.- Pequenio");
      Serial.println(customKey);
      customKey='0';
      delay(1000);
      char customKey = customKeypad.waitForKey();

      //if perro grande
      if (customKey == '1') {
        //perro grande
        raza = 1;
        cont++;
        //delay(3000);
        //lcd.begin(20, 4);
        lcd.setCursor(0, 0);
        lcd.write("Seleccione la edad: ");
        lcd.setCursor(0, 1);
        lcd.write("1.- Mas de 5 anios");
        lcd.setCursor(0, 2);
        lcd.write("2.- 1 anio a 5 anios");
        lcd.setCursor(0, 3);
        lcd.write("3.- Menos de un anio");
        customKey='0';
        delay(1000);
        char customKey = customKeypad.waitForKey();

        if (customKey == '1') {
          //perro grande menos 1
          edad = 1;
          cont++;
          //delay(3000);
          lcd.begin(20, 4);
          lcd.setCursor(0, 0);
          lcd.write("Seleccione el peso: ");
          lcd.setCursor(0, 1);
          lcd.write("1.- Alto");
          lcd.setCursor(0, 2);
          lcd.write("2.- Medio");
          lcd.setCursor(0, 3);
          lcd.write("3.- Bajo");
          customKey='0';
          delay(1000);
          char customKey = customKeypad.waitForKey();
          if (customKey == '1') {
            peso = 1;
            cont++;
            Serial.println(cont);
          }
          if (customKey == '2') {
            peso = 2;
            cont++;
          }
          if (customKey == '3') {
            peso = 3;
            cont++;
          }
        }
        if (customKey == '2') {
          //perro grande medio
          edad = 2;
          cont++;
          lcd.begin(20, 4);
          lcd.setCursor(0, 0);
          lcd.write("Seleccione el peso: ");
          lcd.setCursor(0, 1);
          lcd.write("1.- Alto");
          lcd.setCursor(0, 2);
          lcd.write("2.- Medio");
          lcd.setCursor(0, 3);
          lcd.write("3.- Bajo");
          customKey='0';
          delay(1000);
          char customKey = customKeypad.waitForKey();

          if (customKey == '1') {
            peso = 1;
            cont++;
          }
          if (customKey == '2') {
            peso = 2;
            cont++;
          }
          if (customKey == '3') {
            peso = 3;
            cont++;
          }
        }
        if (customKey == '3') {
          //perro grande mas 5
          edad = 3;
          cont++;
          lcd.begin(20, 4);
          lcd.setCursor(0, 0);
          lcd.write("Seleccione el peso: ");
          lcd.setCursor(0, 1);
          lcd.write("1.- Alto");
          lcd.setCursor(0, 2);
          lcd.write("2.- Medio");
          lcd.setCursor(0, 3);
          lcd.write("3.- Bajo");
          customKey='0';
          delay(1000);
          char customKey = customKeypad.waitForKey();
          if (customKey == '1') {
            peso = 1;
            cont++;
          }
          if (customKey == '2') {
            peso = 2;
            cont++;
          }
          if (customKey == '3') {
            peso = 3;
            cont++;
          }
        }
      }

      //if perro mediado
      if (customKey == '2') {
        //perro mediano
        raza = 2;
        cont++;
        lcd.begin(20, 4);
        lcd.setCursor(0, 0);
        lcd.write("Seleccione la edad: ");
        lcd.setCursor(0, 1);
        lcd.write("1.- Mas de 5 anios");
        lcd.setCursor(0, 2);
        lcd.write("2.- 1 anio a 5 anios");
        lcd.setCursor(0, 3);
        lcd.write("3.- Menos de un anio");
        customKey='0';
        delay(1000);
        char customKey = customKeypad.waitForKey();
        if (customKey == '1') {
          edad = 1;
          cont++;
          lcd.begin(20, 4);
          lcd.setCursor(0, 0);
          lcd.write("Seleccione el peso: ");
          lcd.setCursor(0, 1);
          lcd.write("1.- Alto");
          lcd.setCursor(0, 2);
          lcd.write("2.- Medio");
          lcd.setCursor(0, 3);
          lcd.write("3.- Bajo");
          customKey='0';
          delay(1000);
          char customKey = customKeypad.waitForKey();
          if (customKey == '1') {
            peso = 1;
            cont++;
          }
          if (customKey == '2') {
            peso = 2;
            cont++;
          }
          if (customKey == '3') {
            peso = 3;
            cont++;
          }
        }
        if (customKey == '2') {
          edad = 2;
          cont++;
          lcd.begin(20, 4);
          lcd.setCursor(0, 0);
          lcd.write("Seleccione el peso: ");
          lcd.setCursor(0, 1);
          lcd.write("1.- Alto");
          lcd.setCursor(0, 2);
          lcd.write("2.- Medio");
          lcd.setCursor(0, 3);
          lcd.write("3.- Bajo");
          customKey='0';
          delay(1000);
          char customKey = customKeypad.waitForKey();
          if (customKey == '1') {
            peso = 1;
            cont++;
          }
          if (customKey == '2') {
            peso = 2;
            cont++;
          }
          if (customKey == '3') {
            peso = 3;
            cont++;
          }
        }
        if (customKey == '3') {
          edad = 3;
          cont++;
          lcd.begin(20, 4);
          lcd.setCursor(0, 0);
          lcd.write("Seleccione el peso: ");
          lcd.setCursor(0, 1);
          lcd.write("1.- Alto");
          lcd.setCursor(0, 2);
          lcd.write("2.- Medio");
          lcd.setCursor(0, 3);
          lcd.write("3.- Bajo");
          customKey='0';
          delay(1000);
          char customKey = customKeypad.waitForKey();
          if (customKey == '1') {
            peso = 1;
            cont++;
          }
          if (customKey == '2') {
            peso = 2;
            cont++;
          }
          if (customKey == '3') {
            peso = 3;
            cont++;
          }
        }
      }

      //if perro pequeño
      if (customKey == '3') {
        //perro pequeño
        raza = 3;
        cont++;
        lcd.begin(20, 4);
        lcd.setCursor(0, 0);
        lcd.write("Seleccione la edad: ");
        lcd.setCursor(0, 1);
        lcd.write("1.- Mas de 5 anios");
        lcd.setCursor(0, 2);
        lcd.write("2.- 1 anio a 5 anios");
        lcd.setCursor(0, 3);
        lcd.write("3.- Menos de un anio");
        customKey='0';
        delay(1000);
        char customKey = customKeypad.waitForKey();
        if (customKey == '1') {
          edad = 1;
          cont++;
          lcd.begin(20, 4);
          lcd.setCursor(0, 0);
          lcd.write("Seleccione el peso: ");
          lcd.setCursor(0, 1);
          lcd.write("1.- Alto");
          lcd.setCursor(0, 2);
          lcd.write("2.- Medio");
          lcd.setCursor(0, 3);
          lcd.write("3.- Bajo");
          customKey='0';
          delay(1000);
          char customKey = customKeypad.waitForKey();
          if (customKey == '1') {
            peso = 1;
            cont++;
          }
          if (customKey == '2') {
            peso = 2;
            cont++;
          }
          if (customKey == '3') {
            peso = 3;
            cont++;
          }
        }
        if (customKey == '2') {
          edad = 2;
          cont++;
          lcd.begin(20, 4);
          lcd.setCursor(0, 0);
          lcd.write("Seleccione el peso: ");
          lcd.setCursor(0, 1);
          lcd.write("1.- Alto");
          lcd.setCursor(0, 2);
          lcd.write("2.- Medio");
          lcd.setCursor(0, 3);
          lcd.write("3.- Bajo");
          customKey='0';
          delay(1000);
          char customKey = customKeypad.waitForKey();
          if (customKey == '1') {
            peso = 1;
            cont++;
          }
          if (customKey == '2') {
            peso = 2;
            cont++;
          }
          if (customKey == '3') {
            peso = 3;
            cont++;
          }
        }
        if (customKey == '3') {
          edad = 3;
          cont++;
          lcd.begin(20, 4);
          lcd.setCursor(0, 0);
          lcd.write("Seleccione el peso: ");
          lcd.setCursor(0, 1);
          lcd.write("1.- Alto");
          lcd.setCursor(0, 2);
          lcd.write("2.- Medio");
          lcd.setCursor(0, 3);
          lcd.write("3.- Bajo");
          customKey='0';
          delay(1000);
          char customKey = customKeypad.waitForKey();
          if (customKey == '1') {
            peso = 1;
            cont++;
          }
          if (customKey == '2') {
            peso = 2;
            cont++;
          }
          if (customKey == '3') {
            peso = 3;
            cont++;
          }
        }
      }
    }

    //ciclo para gatos
    if (customKey == '2') {
      //gato
      tipo = 2;
      cont++;
      lcd.begin(20, 4);
      lcd.setCursor(0, 0);
      lcd.write("Seleccione la edad: ");
      lcd.setCursor(0, 1);
      lcd.write("1.- Mas de 5 anios");
      lcd.setCursor(0, 2);
      lcd.write("2.- 1 anio a 5 anios");
      lcd.setCursor(0, 3);
      lcd.write("3.- Menos de un anio");
      customKey='0';
      delay(1000);
      char customKey = customKeypad.waitForKey();
      if (customKey == '1') {
        //gato menos 1
        edad = 1;
        cont+2;
        lcd.begin(20, 4);
        lcd.setCursor(0, 0);
        lcd.write("Seleccione el peso: ");
        lcd.setCursor(0, 1);
        lcd.write("1.- Alto");
        lcd.setCursor(0, 2);
        lcd.write("2.- Medio");
        lcd.setCursor(0, 3);
        lcd.write("3.- Bajo");
        customKey='0';
        delay(1000);
        char customKey = customKeypad.waitForKey();
        if (customKey == '1') {
          peso = 1;
          cont++;
        }
        if (customKey == '2') {
          peso = 2;
          cont++;
        }
        if (customKey == '3') {
          peso = 3;
          cont++;
        }
      }
      if (customKey == '2') {
        //gato medio
        edad = 2;
        cont+2;
        lcd.begin(20, 4);
        lcd.setCursor(0, 0);
        lcd.write("Seleccione el peso: ");
        lcd.setCursor(0, 1);
        lcd.write("1.- Alto");
        lcd.setCursor(0, 2);
        lcd.write("2.- Medio");
        lcd.setCursor(0, 3);
        lcd.write("3.- Bajo");
        customKey='0';
        delay(1000);
        char customKey = customKeypad.waitForKey();
        if (customKey == '1') {
          peso = 1;
          cont++;
        }
        if (customKey == '2') {
          peso = 2;
          cont++;
        }
        if (customKey == '3') {
          peso = 3;
          cont++;
        }
      }
      if (customKey == '3') {
        //gato mas 5
        edad = 3;
        cont+2;
        lcd.begin(20, 4);
        lcd.setCursor(0, 0);
        lcd.write("Seleccione el peso: ");
        lcd.setCursor(0, 1);
        lcd.write("1.- Alto");
        lcd.setCursor(0, 2);
        lcd.write("2.- Medio");
        lcd.setCursor(0, 3);
        lcd.write("3.- Bajo");
        customKey='0';
        delay(1000);
        char customKey = customKeypad.waitForKey();
        if (customKey == '1') {
          peso = 1;
          cont++;
        }
        if (customKey == '2') {
          peso = 2;
          cont++;
        }
        if (customKey == '3') {
          peso = 3;
          cont++;
        }
      }
    }
  }


  if(cont == 4){
    //perro
    if(tipo==1){
      sum= tipo+raza+edad+peso;
      if(sum==4 || sum==5){
        cantComida=500;
        nComidas=5;
      }
      else{
        if(sum==9 || sum==10){
          nComidas=3;
          cantComida=300;
        }
        else{
          nComidas=4; 
          cantComida=400;
        }
      }
    }

    //gato
    if(tipo==2){
      sum= tipo+edad+peso;
      if(sum==3 || sum==4){
        cantComida=300;
        nComidas=5;
      }
      else{
        if(sum==5 || sum==6){
          cantComida=200;
          nComidas=4;
        }
        else{
          nComidas=3; 
          cantComida=150;
        }
      }
    }

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write("Configuracion");
    lcd.setCursor(0,1);
    lcd.write("Completa");
    Serial.println("configuracion completa");
    delay(5000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write("Numero de comidas:");
    lcd.setCursor(0,1);
    lcd.print(nComidas);
    Serial.println("Numero de comidas");
    //Serial.println(nComidas);
    delay(5000);
    lcd.clear();
    //mostrar reloj
    contH=(18/nComidas);
    buttonState1 = HIGH;
    buttonState2 = HIGH;
    temp1 = 1;
    servoC.write(90);
    servoA.write(0);
    cont++;
  }



  if(cont == 5){
    //MOTOR 1
    //activar apertura de compuerta
    if (buttonState1 == HIGH) {
      temp1 = 1;
      if (temp1 == 1) {
        //lcd.begin(20,4);
        servoC.write(90);
        lcd.setCursor(0, 0);
        Serial.write("comida act");
        lcd.write("Comida Activada ");
        digitalWrite(led1, HIGH);
      }
    }
    //desactivar apertura de compuerta
    if (buttonState2 == HIGH) {
      temp1 = 2;
      if (temp1 == 2) {
        servoC.write(90);
        //lcd.begin(20,4);
        lcd.setCursor(0, 0);
        Serial.write("comida bloq");
        lcd.write("Comida Bloqueada");
        digitalWrite(led1, LOW);
      }
    }


    //MOTOR 2
    //activar apertura de compuerta
    if (buttonState3 == HIGH) {
      temp2 = 1;
      if (temp2 == 1) {
        servoA.write(0);
        //  lcd.begin(20,4);
        lcd.setCursor(0, 2);
        Serial.write("agua act");
        lcd.write("Agua Activada ");
        digitalWrite(led2, HIGH);
      }
    }
    //desactivar apertura de compuerta
    if (buttonState4 == HIGH) {
      temp2 = 2;
      if (temp2 == 2) {
        servoA.write(90);
        //lcd.begin(20,4);
        lcd.setCursor(0, 2);
        Serial.write("agua bloq");
        lcd.write("Agua Bloqueada");
        digitalWrite(led2, LOW);
      }
    }

    if((temp1==1) && ((hour()==6)+contH) && (hour()>6) && (hour()<0)){
      if(FSRReading>100){
        while(FSRReading<=(cantComida + 100)){
          servoC.write(0);
        }
        servoC.write(90);
      }
    }


    Wire.requestFrom(8, 6);

    while (Wire.available()) {
      char c = Wire.read();
      Serial.print(c);
    }
  }
}






