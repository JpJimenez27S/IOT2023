#define TIME_TO_SLEEP 1
#define PIN4 4
#define BUTTON_PIN 0

SemaphoreHandle_t pauseSemaphore;

bool buttonPressedLong  = false;
bool estado = false;
RTC_DATA_ATTR bool taskPaused = false;

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
  int contador = 0;
  while (1) {
    if (digitalRead(BUTTON_PIN) == LOW) {
      
        estado = true;
        contador++;
      if (contador >= 40){
          Serial.println("Button pressed, task paused.");
          esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * 1000000 * 20);
          esp_deep_sleep_start();
      }
    }else{
      contador = 0;
    }

    if (estado == true && digitalRead(BUTTON_PIN) == HIGH){
      taskPaused =!taskPaused;
      estado = false;
    }

    Serial.print(" status: ");
    Serial.println(digitalRead(BUTTON_PIN));
    vTaskDelay(250 / portTICK_PERIOD_MS);
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