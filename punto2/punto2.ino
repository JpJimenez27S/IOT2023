#define PIN4 4
#define BUTTON_PIN 0

SemaphoreHandle_t pauseSemaphore;
bool taskPaused = false;

void Task1code( void * parameter) {
  (void)parameter;
  float valor;
  //double arreglo[10000];
  while(1){
    if (!taskPaused) {
      valor = analogRead(PIN4) * 3.2/4095.0;
      Serial.print("Voltaje = ");
      Serial.println(valor);
      
      }
      vTaskDelay(1000/portTICK_PERIOD_MS);
    }
  }


void Task2code(void *parameter) {
  (void)parameter;

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  while (1) {
    if (digitalRead(BUTTON_PIN) == LOW) {
      taskPaused = !taskPaused;
      if (taskPaused) {
        Serial.println("Button pressed, task paused.");
      } else {
        Serial.println("Button pressed, task resumed.");
      }
      delay(200); // Debounce delay
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup() {

  TaskHandle_t Task1, Task2;
  
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
      Task1code, /* Function to implement the task */
      "Task1", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      1,  /* Priority of the task */
      &Task1,  /* Task handle. */
      1); /* Core where the task should run */

    xTaskCreatePinnedToCore(
      Task2code, /* Function to implement the task */
      "Task2", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      2,  /* Priority of the task */
      &Task2,  /* Task handle. */
      0); /* Core where the task should run */



}

void loop() {
 // Clears loop function from OS
 vTaskDelete(NULL);
}