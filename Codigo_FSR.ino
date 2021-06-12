   /* PROYECTO FINAL - SENSORES Y ACTUADORES */
      /* Determinación de fuerza con FSR */

// LIBRERIA PARA USAR LA LCD
#include <LiquidCrystal.h>

//PINES DE LA LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//PIN DEL AnalogIn 
int potPin = 0;

//VALORES DE COMPONENTES DEL CIRCUITO Y MODELO DEL FSR

int fsrADC; //Corresponde al valor leido del ADC del Arduino
float fsrVo; //El valor del ADC convertido a voltaje
float fsrRes; //La resistencia del FSR.
float fsrCond; //La conductancia del FSR, útil para la aproximación de la fuerza
float Fuerza; //La fuerza que actúa sobre el área activa del FSR

const float R = 3300.0; //La Rm del circuito
int vcc = 5.0; //Los 5V de la alimentación

void setup() {  
  //TRANSMISION DE DATOS
  Serial.begin(9600);
  pinMode(potPin, INPUT);
  
  // INDICAMOS QUE TENEMOS CONECTADA UNA PANTALLA DE 16X2
  lcd.begin(16, 2);
  
  //LCD & SETCURSOR ES FILA, COLUMNA
  lcd.setCursor(2, 0);
  lcd.print("Medicion de"); 
  lcd.setCursor(5, 1);
  lcd.print("Fuerza");
  delay(1500);
  lcd.clear();
  
  //GRUPOS
  lcd.setCursor(4, 0);
  lcd.print("Grupo 1");
  lcd.setCursor(3, 1);
  lcd.print("Subgrupo 5");
  delay(1500);
  lcd.clear();
  
  //INTEGRANTE 1
  lcd.setCursor(4, 0);
  lcd.print("Fernanda");
  lcd.setCursor(5, 1);
  lcd.print("Araya");
  delay(1500);
  lcd.clear();
  
  //INTEGRANTE 2
  lcd.setCursor(5, 0);
  lcd.print("Marco");
  lcd.setCursor(3, 1);
  lcd.print("Rodriguez");
  delay(1500);
  lcd.clear();
  
  //INTEGRANTE 3
  lcd.setCursor(5, 0);
  lcd.print("Carlos");
  lcd.setCursor(4, 1);
  lcd.print("Valverde");
  delay(1500);
  lcd.clear();
}

void loop() {
  //LIMPIAR LCD
  lcd.clear();

  analogReference(DEFAULT);
  
  fsrADC = analogRead(potPin);  
   
  if (fsrADC != 0) {
    fsrVo = (fsrADC * vcc) / 1023.0; //Se calcula el valor de tensión correspondiente a la lectura del ADC
    
    fsrRes = R * ((vcc/fsrVo)-1); //La resistencia se despeja de la ecuación del divisor de tensión
    fsrCond = (1/fsrRes); //Conductancia expresada en siemens.
    
    // La aproximación de la fuerza se aplica según las Figuras 3 y 4 de la guía de uso del FSR de Interlink y de la información en la página del distribuidor, Adafruit Electronics.
    //Para más información, puede consultar el link: https://learn.sparkfun.com/tutorials/force-sensitive-resistor-hookup-guide?_ga=2.84003161.1509577838.1623319749-1598400594.1622957393
    if (fsrRes <= 600) 
      Fuerza = (fsrCond - 0.00075) / 0.00032639;
    else
      Fuerza =  fsrCond / 0.000642857;

    Serial.println(Fuerza);
    //Serial.println();
                
    //IMPRESIÓN EN LCD
    lcd.setCursor(0, 0);
    lcd.print("Hay presion!");
    lcd.setCursor(0, 1);
    lcd.print("Aprox. ");
    lcd.print(Fuerza,3); 
    lcd.print("kg");
    delay(200);//Velocidad de refresco de los datos en la pantalla. Se recomienda que sea lento para mejor visualización. 
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("NO hay presion!");
    delay(200);//Velocidad de refresco de los datos en la pantalla.
  }
}
