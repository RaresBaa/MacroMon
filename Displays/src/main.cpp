#include "draw.h"

/*
There are multiple tft screens, each with it's own microcontroller:
  1. Cpu screen: on the top panel it shows individual cpu core usage
                on the bottom panel it shows total cpu usage over time
  2. Memory, gpu: on the top panel it shows the ram usage over time
                  on the bottom panel it shows the gpu usage over time
  3. IO: on the top panel it shows the network usage over time
        on the bottom panel it shows the disk usage over time
  4: Temperature: it has multiple graphs for temperature.
In order to program the microcontrollers more easily, we will use defines
*/
#define CPU_SCREEN 1
//#define MEMORY_GPU_SCREEN 1
//#define IO_SCREEN 1
//#define TEMPERATURE_SCREEN 1



#ifdef CPU_SCREEN
  //for the cpu screen , over serial we will receive cpu core numbers and their usage separated by a space

  //We store 150 datapoints for the average cpu usage over time in a circular buffer
  CircularBuffer<uint8_t, 150> average_cpu_usage;
#endif
#ifdef MEMORY_GPU_SCREEN
  //for the memory gpu screen, over serial we will receive the ram usage and gpu usage

#endif
#ifdef IO_SCREEN
  // for the io screen, over serial we will receive the network and disk write and read speed.

#endif
#ifdef TEMPERATURE_SCREEN
  //for the temperature screen, over serial we will receive temperature probes number and individual temperatures

#endif

void setup() {
  Serial.begin(9600);
  display_init();
  //Display the waiting message until we get serial data
  display_draw_waiting_to_connect();
  //while(!Serial.available()) {
  //  delay(100);
  //}
  //Clear the display
  display_clear();
  #ifdef CPU_SCREEN
    //Add panel border
    display_draw_panel_border(0, WHITE);
    display_draw_panel_border(1, WHITE);
    //Fill the average cpu usage buffer with 0
    for(uint8_t i = 0; i < 150; i++){
      average_cpu_usage.push(0);
    }

  #endif
  #ifdef MEMORY_GPU_SCREEN

  #endif
  #ifdef IO_SCREEN

  #endif
  #ifdef TEMPERATURE_SCREEN

  #endif
}

void loop() {
  #ifdef CPU_SCREEN
    if(Serial.available()){
      //First we read the number of cores and after that we read the usage of each core
      uint8_t cores_number = 0;
      cores_number = Serial.parseInt();
      uint8_t current_usage[cores_number];
      //As we read we also sum individual usage to get the average
      uint16_t average = 0;
      for(uint8_t i = 0; i < cores_number; i++){
        current_usage[i] = Serial.parseInt();
        average += current_usage[i];
      }
      average /= cores_number; // divide by the number of cores to get the average
      // We add the average to the circular buffer
      average_cpu_usage.push(average);
      // On the top panel we draw the average over time
      display_clear_panel(0);
      display_draw_graph(0, average_cpu_usage, RED);
      // We draw the title of the panel, including Total CPU usage
      display_clear_panel_title(0);
      display_draw_panel_title(0, 0, "Total CPU usage:", BLUE);
      display_draw_panel_title(0, 18, String(average), YELLOW);

      // On the bottom panel we draw the individual core usage
      display_clear_panel(1);
      display_draw_bar_chart(1, cores_number, current_usage, MAGENTA);

    }

  #endif
  #ifdef MEMORY_GPU_SCREEN

  #endif
  #ifdef IO_SCREEN

  #endif
  #ifdef TEMPERATURE_SCREEN

  #endif
}

/*
void test(){
      uint8_t data[150];
    for (uint8_t i = 0; i < 150; i++ ){
      data[i] = random(0, 100);
    }
    uint8_t bars = random(1, 16);
    uint8_t bars_d[bars];
    for(uint8_t i = 0; i < bars; i++) {
      bars_d[i] = random(0, 100);
    }
    display_draw_graph(0, data, RED);
    display_draw_bar_chart(1, bars, bars_d, GREEN);
    display_draw_panel_title(0, 0, "Graph:", BLUE);
    display_draw_panel_title(1, 0, "Dinamic title:", MAGENTA);
    display_draw_panel_title(1, 18, String(random(0, 100)), YELLOW);
    delay(1000);
    display_clear_panel(0);
    display_clear_panel(1);
    display_clear_panel_title(1);
}
*/