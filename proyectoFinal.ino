#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial 


LiquidCrystal_I2C lcd(0x3F,16,2) ;
SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth
Servo servoMotor1;
Servo servoMotor2;
char dato = 0;

void setup()
{
  Serial.begin(9600);   // Inicializamos  el puerto serie  
  BT.begin(38400);
  servoMotor1.attach(3);
  servoMotor2.attach(5);

  lcd.init();

  lcd.backlight();

  lcd.print("Ruiz marica");
}
 
void loop()
{

     // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)

  
  if(BT.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
    dato = BT.read();
    Serial.println("Leido BT");
    Serial.println(dato);
    if(dato == '1'){
      servoMotor1.write(180);
      servoMotor2.write(0);
        lcd.setCursor(0, 1);
        lcd.backlight();
   // Escribimos el número de segundos trascurridos
  lcd.print(millis()/1000);
  lcd.print(" Segundos");
  delay(100);
    }
    if(dato == '0'){
      servoMotor1.write(0);
      servoMotor2.write(39); 
      lcd.noBacklight();
    }
  }
 
  if(Serial.available())  // Si llega un dato por el monitor serial se envía al puerto BT
  {
     BT.write(Serial.read());
  }
}

//Nombre = SMRT_BULB
//Password = 1209

// -5 el de abajo
// -3 el de arriba
