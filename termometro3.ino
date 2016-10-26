#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Hasta aquí hemos declarado la librería para la LCD y los pines por donde le va a entrar la información.

//arreglo que guarda los ultimos 5 datos 
floar arregloUltimos[5] = {0.0,0.0,0.0,0.0,0.0};


float centi()
{// Funcion para leer el dato analogico y convertirlo a digital:

  int dato;
  float c;
  dato=analogRead(A0);
  
  c = (500.0 * dato)/1023;

  //Esta fórmula sale de la relación del sensor con los grados. Ésta es fácilmente rastreable por la web pero vamos a intentar explicarla un poco: El sensor de temperatura LM35 responde a variaciones de 10 mV por cada grado centígrado. Si el sensor detecta 1 grado centígrado a la salida del sensor obtendríamos 10 mV. Ejemplo: 26,4ºC = 264 mV = 0.264 V.Tenemos que el convertidor de analógico a digital es de 10 bits de resolución, los valores variarán entre 0 y 1023, entonces Vout= (5V*Dato)/1023 siendo  ( 0 < Dato < 1023 ) y para ajustar la escala a grados centígrados: Vout = ((5V*Dato)*100)/1023
  return (c);
}

float kelvin(float cent)
{
  float k;
  k=cent+273.15;
  return(k);
  
}

float fahren(float cent)
{
  float f;
  f=cent*1.8+32;
  return (f);
  

}

float rankin(float cent)
{
  float r;
  r=(cent + 273.15)*1.8;
  return (r);
}

//Hasta aquí hemos declarado las funciones de conversión del dato analógico de entrada del sensor en grados celsius en sus respectivas equivalencias.

//funcion que retorna si va subiendo la temperatura o no, recibe el ultimo float del que se use
String subeTemperatura(float dato){
  for(int i=0;i<4;i++){
    arregloUltimos[i] =arregloUltimos[i+1]; 
  }
  for(int i=0;i<4;i++){
    if(arregloUltimos[i] == 0.0){
      return "INICIANDO"; 
    }
  }
  arreglo[4] = dato;
  if(arregloUltimos[0]<arregloUltimos[1] && arregloUltimos[1]<arregloUltimos[2] && arregloUltimos[2]<arregloUltimos[3] && arregloUltimos[3]<arregloUltimos[4]){
    return "SUBE";
  }else if(arregloUltimos[0]>arregloUltimos[1] && arregloUltimos[1]>arregloUltimos[2] && arregloUltimos[2]>arregloUltimos[3] && arregloUltimos[3]>arregloUltimos[4]){
    return "BAJA";
  }else{
    return "INDETERMINADO";
  }
}


void setup() {
  // Definimos la LCD con dimension 2x16 y definimos los caracteres que deben salir en las filas:
lcd.begin(16,2);
lcd.print("C=      F=");
lcd.setCursor(0,1);
lcd.print("Temperatura");
}

//Hasta aquí hemos definido qué queremos que salga impreso por la pantalla y el tamaño de ésta.
void loop() {
  // put your main code here, to run repeatedly: 
  float Centigrados = centi();
  float Fahrenheit = fahren (Centigrados);
  float Rankin = rankin (Centigrados);
  float Kelvin = kelvin (Centigrados);
  
  lcd.setCursor(2,0);
  lcd.print(Centigrados);
  
  lcd.setCursor(10,0);
  lcd.print(Fahrenheit);

  ///se llama si sube o baja el sensor, retorna una string
  String respuesta = subeTemperatura(Centigrados);

  
  delay(200);
  //Por último, hemos usado la parte activa del programa o bucle para que constantemente para cada variación recalcule los datos. 
  
}
