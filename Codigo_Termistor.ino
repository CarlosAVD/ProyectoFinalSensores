   /* PROYECTO FINAL - SENSORES Y ACTUADORES */
 /* Medición de temperatura con termistor NTC */

// LIBRERIA PARA USAR LA LCD
#include <LiquidCrystal.h>
#include <math.h>

//PINES DE LA LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//PIN DEL AnalogIn 
int potPin = 5;

//VALORES DE COMPONENTES DEL CIRCUITO Y MODELO DEL TERMISTOR

float rbias = 1990;
float rp = 9990;
float vcc = 5.0;
float k = 3435;
float t0 = 298.15;
float r0 = 10000.0;
float ganancia = 3.25;
float fuente = ganancia * 3.915;

//Variables del código

float adc = 0; //Valor de tensión leido en el ADC del Arduino
float vo = 0; //Tensión a la salida del divisor de tensión
float resistenciap = 0; //Valor del paralelo de rp con rt
float resistencia = 0; //Valor final de resistencia del termistor
float temperaturaK = 0; //Temperatura calculada en Kelvin
float temperatura = 0; //Temperatura calculada en Celsius

//CARACTERES ESPECIALES PARA LA LCD
//MASMENOS
byte masmenos[] = {
  B00000,
  B00100,
  B00100,
  B11111,
  B00100,
  B00100,
  B11111,
  B00000,
};

void setup() {  
  //TRANSMISION DE DATOS
  Serial.begin(9600);
  
  // INDICAMOS QUE TENEMOS CONECTADA UNA PANTALLA DE 16X2
  lcd.begin(16, 2);
  
  // ENVIAR LOS MAPAS DE BITS AL CONTROLADOR DE PANTALLA
  lcd.createChar(0,masmenos);  
  
  //LCD & SETCURSOR ES FILA, COLUMNA
  lcd.setCursor(2, 0);
  lcd.print("Medicion de"); 
  lcd.setCursor(2, 1);
  lcd.print("Temperatura");
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
  
  //Obtención de la resistencia del termistor a partir de la lectura del ADC
  adc = ((vcc/1024)*(analogRead(potPin))); 
  vo = ((fuente-adc)/ganancia);
  resistenciap = ((rbias)/((vcc/vo)-1));
  resistencia = (resistenciap*rp)/(rp-resistenciap);
  
  //Cálculo de la temperatura a partir del modelo de dos parámetros del termistor NTC
  temperaturaK = (k/(log(resistencia/r0)+(k/t0)));
  temperatura = temperaturaK - 273.15; //Se pasa a grados celsius
  
  //La lectura muestra una incertidumbre fija de ±1°C. Este valor se determinó como la incertidumbre de la medición de temperatura hecha con el 
  //multímetro Steren MUL-605, ya que su mínima división es de 1°C. Recuérdese que el error máximo permisible de la aplicación de medición de temperatura es de 1°C.
  
  //IMPRESIÓN EN PUERTO SERIAL (Para el uso del serial plotter)
  //Serial.print("La temperatura es: (");
  Serial.print(temperatura, 1);
  //Serial.print("±1) °C.");
  Serial.println("");
  
  //IMPRESIÓN EN LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp. Actual");
  lcd.setCursor(0, 1);
  lcd.print("T=(");  
  lcd.print(temperatura,0);
  lcd.write(byte(0));//MASMENOS
  lcd.print("1)");  
  lcd.print((char)223);//Símbolo de grado °
  lcd.print("C");
  delay(1000);//Velocidad de refresco de los datos en la pantalla. Se recomienda que sea lento para mejor visualización.
  
}
