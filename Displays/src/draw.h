#ifndef DRAW_H
#define DRAW_H

#include <Arduino.h>
#include <CircularBuffer.h>
//3.5' display with 480x320 resolution using ili9486 driver

//Commonly used colours
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void display_init();
void display_clear();
void display_clear_panel(uint8_t position);
void display_clear_panel_title(uint8_t position);
void display_draw_graph(uint8_t position, CircularBuffer<uint8_t, 150>& datapoints, uint16_t colour);
void display_draw_double_graph(uint8_t position, CircularBuffer<uint8_t, 150>& datapoints1, CircularBuffer<uint8_t, 150>& datapoints2, uint16_t colour1, uint16_t colour2);
void display_draw_waiting_to_connect();
void display_draw_panel_title(uint8_t position, uint8_t offset, String title, uint16_t colour);
void display_draw_panel_border(uint8_t position, uint16_t colour);
void display_draw_bar_chart(uint8_t position, uint8_t bar_nr, uint8_t *datapoints, uint16_t colour);

#endif