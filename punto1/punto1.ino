// GPIO pin for built in led
#define PIN22 4
#define BPIN 0

static int64_t counter;


void Task1code( void * parameter) {
  float valor;
  //double arreglo[10000];
  while(1){
    
    valor = analogRead(PIN22) * 3.2/4095.0;
    Serial.print("Voltaje = ");
    Serial.println(valor);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
  }

void Task2code( void * parameter) {
  while(1){

    int EstadoB = digitalRead(BPIN);
    if (EstadoB == 0){
      Serial.println("Boton presionado");
      //Serial.println(EstadoB);
    }else{
      Serial.println("Boton no presionado");
    }
    
    vTaskDelay(50/portTICK_PERIOD_MS);
    
  }
  }


void setup() {

  TaskHandle_t Task1,Task2;
  
  Serial.begin(115200);
  // Built in led pint as outpt
  pinMode(PIN22,INPUT);  
  Serial.print("setup() running on core ");
  Serial.println(xPortGetCoreID());

  counter=0;  

  xTaskCreatePinnedToCore(
      Task1code, /* Function to implement the task */
      "Task1", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      10,  /* Priority of the task */
      &Task1,  /* Task handle. */
      1); /* Core where the task should run */

  xTaskCreatePinnedToCore(
      Task2code, /* Function to implement the task */
      "Task2", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      10,  /* Priority of the task */
      &Task2,  /* Task handle. */
      0); /* Core where the task should run */
}

void loop() {
 // Clears loop function from OS
 vTaskDelete(NULL);
}