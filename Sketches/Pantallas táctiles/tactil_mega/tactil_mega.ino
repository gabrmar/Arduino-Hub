// Modified TFT_paint sketch from Adafruit_TFTLCD Library for

#include <Adafruit_GFX.h>    // Libreria de graficos
#include <Adafruit_TFTLCD.h> // Libreria de LCD 
#include <TouchScreen.h>     // Libreria del panel tactil

 // Pines necesarios para los 4 pines del panel tactil
//#define YP A1 // Pin analogico A1 para ADC
//#define XM A2 // Pin analogico A2 para ADC
//#define YM 7 
//#define XP 6 
////////////////////otra configuracion de pines
#define YP A2 // Pin analogico A2 para ADC
#define XM A1 // Pin analogico A1 para ADC
#define YM 6
#define XP 7
//////////////////

// Definimos la presion máxima y minima que podemos realizar sobre el panel
#define MINPRESSURE 1
#define MAXPRESSURE 1000

// Para mejor precision de la presion realizada, es necesario 
// medir la resistencia entre los pines X+ y X-.
// En Shield TFT 2.4" LCD se mide entre los pines A2 y 6
// Instancia del panel tactil (Pin XP, YP, XM, YM, Resistencia del panel) 
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 654); 

short TS_MINX = 200; // Coordenadas del panel tactil para delimitar
short TS_MINY = 120; // el tamaño de la zona donde podemos presionar
short TS_MAXX = 850; // y que coincida con el tamaño del LCD
short TS_MAXY = 891; 

#define LCD_CS A3   // Definimos los pines del LCD
#define LCD_CD A2   // para poder visualizar elementos graficos
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define	BLACK   0x0000  // Definimos los colores 
#define	BLUE    0x001F  // que utilizaremos para 
#define	RED     0xF800  // el texto y los elementos graficos
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET); // Instancia LCD 

int X; // Variables que almacenaran la coordenada
int Y; // X, Y donde presionemos y la variable Z 
int Z; // almacenara la presion realizada

int a = 0; // variable "flag" para control rebotes

#define led 22


void setup(void) 
{ 
  tft.begin(0x9325); // Iniciamos el LCD especificando el controlador  
  
  tft.fillScreen(WHITE); // Pintamos la pantalla de Rojo

  pinMode(13, OUTPUT);
  pinMode(22, OUTPUT);//LED
  
  
  tft.drawRect(40, 20, 160, 60, RED); // Dibujamos un "boton"
  
////////////////////
  tft.setCursor(70,25); // Colocamos el cursor
        tft.setTextSize(3);   // Especificamos el tamaño del texto
        tft.setTextColor(BLUE); // Definimos el color del texto 
        tft.println("LED"); // Escribimos por pantalla
        tft.setCursor(60,50);  // Colocamos el cursor
        tft.println("APAGADO"); // Escribimos por pantalla  
}

void loop()
{          
    lecturaPanel(); // Realizamos lectura del panel para detectar presion y coordenadas
      
    // Si la pulsación del eje X se produce entre los puntos 40 y 160
    // Y la pulsacion del eje Y se produce entre los puntos 20 y 60
    // Y la presión realizada esta entre el margen determinado
    if((X > 40 && X < 200) && (Y > 20 && Y < 60) && (Z > MINPRESSURE && Z < MAXPRESSURE)) 
    {
      if (a == 0) // Si la variable flag esta en 0
      {
        tft.fillRect(40, 20, 160, 60, RED); // Dibujamos nuestro boton relleno de color
        
        tft.setCursor(70,25); // Colocamos el cursor
        tft.setTextSize(3);   // Especificamos el tamaño del texto
        tft.setTextColor(WHITE); // Definimos el color del texto 
        tft.println("LED"); // Escribimos por pantalla
        tft.setCursor(60,50);  // Colocamos el cursor
        tft.println("PRENDIDO"); // Escribimos por pantalla   
     
        digitalWrite(led, HIGH);
        

        a = 1; // Ponemos la variable flag en 1
        delay(150);
      }
      else if (a == 1) // Si la variable flag esta en 1
      {
         tft.fillRect(41, 21, 158, 58, CYAN); // Dibujamos el fondo de nuestro boton en cyan
         
         tft.setCursor(70,25); // Colocamos el cursor
        tft.setTextSize(3);   // Especificamos el tamaño del texto
        tft.setTextColor(BLUE); // Definimos el color del texto 
        tft.println("LED"); // Escribimos por pantalla
        tft.setCursor(60,50);  // Colocamos el cursor
        tft.println("APAGADO"); // Escribimos por pantalla 
         
        digitalWrite(led, LOW);
        
         
         a = 0; // Ponemos la variable flag en 0 para evitar los rebotes
         delay(150);
      }
    }    
}

void lecturaPanel()
{
    digitalWrite(13, HIGH); 
    TSPoint p = ts.getPoint(); // Realizamos lectura de las coordenadas
    digitalWrite(13, LOW);
  
    pinMode(XM, OUTPUT); // La librería utiliza estos pines como entrada y salida
    pinMode(YP, OUTPUT); // por lo que es necesario declararlos como salida justo
                         // despues de realizar una lectura de coordenadas.    
  
    // Mapeamos los valores analogicos leidos del panel tactil (0-1023)
    // y los convertimos en valor correspondiente a la medida del LCD 320x240
   // X = map(p.x, TS_MAXX, TS_MINX, tft.width(), 0);
    //Y = map(p.y, TS_MAXY, TS_MINY, tft.height(), 0);
    //si la configuracion anterior de pantalla no funciona
    //ensaya esta
    X= map(p.x, TS_MAXX, TS_MINX, tft.width(), 0);
    Y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
    Z = p.z;
}



