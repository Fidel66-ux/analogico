#include <LiquidCrystal.h> // libreria
LiquidCrystal lcd(13,12,11,10,9,8); // pines conectados
#include <Keypad.h>
 
const byte rowsCount = 4;
const byte columsCount = 4;
 
char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '#','0','*', 'D' }
};
 
const byte rowPins[rowsCount] = { 9, 8, 7, 6 };
const byte columnPins[columsCount] = { 5, 4, 3, 2 };
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

  int   Pin_de_medicion = 5; // Pin analogico 5
  int   R1 = 15; // Cambiar por el valor de la resistencia conocida (Resistencia de clibracion)
  long  lectura; // Lectura en el pin analogico 5
  float Tension_de_trabajo = 5.0; // VCC 
  float Voltaje_R2; // Valor que calculamos
  float Resistencia; // Valor que calculamos
  float diametro = 0.00032;
  float area;
  float longitud;
  int variable = 0;

  void setup(){
  lcd.begin(16, 2);  // Fijamos el numero de caracteres y filas
  Serial.begin(9600);
  Serial.println("Medición de resistencia:");
  Serial.println();
}

  void loop(){
  char key = keypad.getKey();
  // Leemos el valor en el pin A5
  lectura=0;
  for(int i=0;i<5;i++){
  lectura+=analogRead(Pin_de_medicion);
  }
  lectura=trunc(lectura/5);
  
  if (key == '1'&& variable == 0) {
  Serial.println(key);
  //Colculamos el voltaje en la resistencia desconocida y area
  //Calculamos la resistencia desconocida con las fórmulas
  //(V1/R1=V2/R2) y (V1=+5V-V2)
  Voltaje_R2 = (Tension_de_trabajo/1023.0)*lectura;
  area = (3.14*(diametro*diametro))/4;
  Resistencia = ((R1*Voltaje_R2)/(Tension_de_trabajo-Voltaje_R2));
  longitud = (Resistencia*area)/(0.0000000172);
  variable == 1;
  }

  if (key == 'A'&& (variable == 0 || variable == 1)) {
  Serial.println(key);
  variable = 0;
  }
  // Lo imprimimos en el Monitor Serie
  Serial.print("Diametro: ");
  Serial.print(diametro,10);
  Serial.println(" m");

  Serial.print("Area: ");
  Serial.print(area,10);
  Serial.println(" m2");
  
  Serial.print("Voltaje en R2: ");
  Serial.print(Voltaje_R2,2);
  Serial.println(" Voltios");
  
  Serial.print("La resistencia tiene ");
  Serial.print(Resistencia,2);
  Serial.println(" Ohm.");

  Serial.print("La longitud es ");
  Serial.print(longitud,2);
  Serial.println(" cm.");
  Serial.println();
  delay(5000);

    //LCD
  lcd.setCursor(0,0);
  lcd.print("Resistencia de ");
  lcd.setCursor(1,1);
  lcd.print(Resistencia,2);
  lcd.setCursor(6,1);
  lcd.print(" Ohm");

}
