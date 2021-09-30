int salida = 5; // declaramos una variable entera que representa el número del pin de salida
int entrada = 0; // declaramos una variable entera que representa el número del pin análogo de entrada 
void setup() {
  // esta sección sólo ejecutada una sóla vez
  pinMode(salida, OUTPUT); // confuramos el pin 5 como salida
}

void loop() {
  // todo lo que ocurre dentro de esta sección ocurre de manera indefinida
  int valor = analogRead(entrada); // declaramos un variable valor que es igual a leer el valor de entrada (puerto 0 en este caso)
  int ct = -0.25 * valor + 255; //esta variable entrera se calcula por medio de la ecuación de la recta.
  //m = -025 y puede ser calculado de la siguiente manera:
  /* AnalogRead entrega números que son prooporcionales al voltaje de entrada. puede enviar números 
   desde 0 hasta 1023. Por otro lado la función que enviará el voltaje de salida sólo puede aceptar
   números desde 0 hasta 255. Por esa razón es necesario hacer la función de línea recta que haga 
   esa adaptación de números. Nos basamos en los siguientes dos puntos:
   P1(0,255) y P2(1023,0) con base en esto calculamos la pendiente de la recta: m = (y2-y1)/(x2-x1)
  Ya tenemos m de la ecuación de la recta y= mx + b. Ahora hallamos b teniendo de la siguoente manera:
  evaluando la ecuación de la recta cuando x=0.
  y= m*0 +b ---> y=b
  gracias al punto inicial sabemos que b es igual a 255 porque es el valor que y tiene cuando la ecuación es evaluada con x=0 */
  analogWrite(salida, ct); // esta función es la que envía un voltaje proporcional a la variable ct. Sólo se puede usar esta función
  // en lso pines que tenan el símbolo ´~´ al lado de su número.
}
