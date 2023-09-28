#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include "draw.h"

MCUFRIEND_kbv tft;

/*
    Each display is divided into 2 panels, which have their own titles and data.
    Each panel has a padding on each side of 10px, and can optionally have a title.
    Each panel's data can be updated and cleared independently of the other panel.
    Each panel can have a 1px border around it
    Each panel has a height of 200px and a width of 300px
    When there is a position argument in a function, 0 is the upper panel and 1 is the lower panel
*/

void display_init(){
    uint16_t ID=tft.readID();
    tft.begin(ID);
    tft.fillScreen(BLACK);
}

void display_clear(){
    tft.fillScreen(BLACK);
}

void display_clear_panel(uint8_t position){
    // This function only clears the data in the panel, not the title of other decorations.
    if(!position){
        tft.fillRect(10, 30, 300, 200, BLACK);
    }else{
        tft.fillRect(10, 270, 300, 200, BLACK);
    }
}

void display_clear_panel_title(uint8_t position){
    // This function only clears the title of the panel, not the data or other decorations.
    if(!position){
        tft.fillRect(10, 0, 320, 25, BLACK);
    }else{
        tft.fillRect(10, 240, 320, 25, BLACK);
    }
}

void display_draw_panel_border(uint8_t position, uint16_t colour){
    // This function draws a 1px border around the panel
    // It also has free space between the border and the panel
    if(!position){
        tft.drawFastHLine(5, 25, 310, colour);
        tft.drawFastHLine(5, 235, 310, colour);
        tft.drawFastVLine(5, 25, 210, colour);
        tft.drawFastVLine(315, 25, 210, colour);
    }else{
        tft.drawFastHLine(5, 265, 310, colour);
        tft.drawFastHLine(5, 475, 310, colour);
        tft.drawFastVLine(5, 265, 210, colour);
        tft.drawFastVLine(315, 265, 210, colour);
    }

}

void display_draw_waiting_to_connect(){
    // This function draws the waiting for connection message
    // The text will be at the center of the screen
    tft.setTextSize(2);
    tft.setTextColor(MAGENTA);
    tft.setCursor(20, 240);
    tft.println("Waiting for connection");
}

void display_draw_panel_title(uint8_t position, uint8_t offset, String title, uint16_t colour){
    // This function draws the title for each half of the panels
    // The offset argument is used to offset the title by a certain amount of pixels, so there can be different colours in the title.
    // Also pads the title with 10px on the left
    tft.setTextSize(2);
    tft.setTextColor(colour);
    offset *= 10; // Multiply the offset by 10 to get the correct amount of pixels
    if(!position){
        tft.setCursor(10 + offset, 0);
    }else{
        tft.setCursor(10 + offset, 240);
    }
    tft.println(title);
}

void display_draw_graph(uint8_t position, CircularBuffer<uint8_t, 150>& datapoints, uint16_t colour){
    // This function draws a graph constrained by the panel
    // The graph is 300px wide and contains 150 so each datapoint is 2px wide
    //The graph will be 200px tall, so we need to multiply the datapoints by 2 to get the correct height
    if(!position){
        for(uint8_t i = 0; i < 150; i++){
            tft.drawFastVLine(10 + (i*2), 235 - (datapoints[i]*2), datapoints[i]*2, colour);
            tft.drawFastVLine(11 + (i*2), 235 - (datapoints[i]*2), datapoints[i]*2, colour);
        }
    }else{
        for(uint8_t i = 0; i < 150; i++){
            tft.drawFastVLine(10 + (i*2), 475 - (datapoints[i]*2), datapoints[i]*2, colour);
            tft.drawFastVLine(11 + (i*2), 475 - (datapoints[i]*2), datapoints[i]*2, colour);
        }
    }
}

void display_draw_double_graph(uint8_t position, CircularBuffer<uint8_t, 150>& datapoints1, CircularBuffer<uint8_t, 150>& datapoints2, uint16_t colour1, uint16_t colour2){
    // This function draws a graph constrained by the panel
    // The graph is 300px wide and contains 150 so each datapoint is 2px wide
    //The graph will be 200px tall, so we need to multiply the datapoints by 2 to get the correct height
    if(!position){
        for(uint8_t i = 0; i < 150; i++){
            // Need to check which graph point is higher, so we can draw the longer bar in the background
            if(datapoints1[i] > datapoints2[i]){
                tft.drawFastVLine(10 + (i*2), 235 - (datapoints2[i]*2), datapoints2[i]*2, colour2);
                tft.drawFastVLine(11 + (i*2), 235 - (datapoints2[i]*2), datapoints2[i]*2, colour2);
                // Now we draw just the tip of the longer bar starting from where the shorter bar ended
                tft.drawFastVLine(10 + (i*2), 235 + (datapoints2[i] - datapoints1[i])*2, (datapoints1[i] - datapoints2[i])*2, colour1);
                tft.drawFastVLine(11 + (i*2), 235 + (datapoints2[i] - datapoints1[i])*2, (datapoints1[i] - datapoints2[i])*2, colour1);
            }else{
                tft.drawFastVLine(10 + (i*2), 235 - (datapoints1[i]*2), datapoints1[i]*2, colour1);
                tft.drawFastVLine(11 + (i*2), 235 - (datapoints1[i]*2), datapoints1[i]*2, colour1);
                tft.drawFastVLine(10 + (i*2), 235 + (datapoints1[i] - datapoints2[i])*2, (datapoints2[i] - datapoints1[i])*2, colour2);
                tft.drawFastVLine(11 + (i*2), 235 + (datapoints1[i] - datapoints2[i])*2, (datapoints2[i] - datapoints1[i])*2, colour2);
            }
        }
    }else{
        for(uint8_t i = 0; i < 150; i++){
            if(datapoints1[i] > datapoints2[i]){
                tft.drawFastVLine(10 + (i*2), 475 - (datapoints2[i]*2), datapoints2[i]*2, colour2);
                tft.drawFastVLine(11 + (i*2), 475 - (datapoints2[i]*2), datapoints2[i]*2, colour2);
                tft.drawFastVLine(10 + (i*2), 475 + (datapoints2[i] - datapoints1[i])*2, (datapoints1[i] - datapoints2[i])*2, colour1);
                tft.drawFastVLine(11 + (i*2), 475 + (datapoints2[i] - datapoints1[i])*2, (datapoints1[i] - datapoints2[i])*2, colour1);
            }else{
                tft.drawFastVLine(10 + (i*2), 475 - (datapoints1[i]*2), datapoints1[i]*2, colour1);
                tft.drawFastVLine(11 + (i*2), 475 - (datapoints1[i]*2), datapoints1[i]*2, colour1);
                tft.drawFastVLine(10 + (i*2), 475 + (datapoints1[i] - datapoints2[i])*2, (datapoints2[i] - datapoints1[i])*2, colour2);
                tft.drawFastVLine(11 + (i*2), 475 + (datapoints1[i] - datapoints2[i])*2, (datapoints2[i] - datapoints1[i])*2, colour2);
            }
        }
    }
}

void display_draw_bar_chart(uint8_t position, uint8_t bar_nr, uint8_t *datapoints, uint16_t colour){
    // This function draws a bar chart constrained by the panel
    // The bar chart is 300px wide and contains bar_nr bars with 10px between each bar
    // The bar chart will be 200px tall, so we need to multiply the datapoints by 2 to get the correct height
    
    uint8_t bar_width = (300 - (bar_nr*10)) / bar_nr;

    if(!position){
        for(uint8_t i = 0; i < bar_nr; i++){
            tft.fillRect(10 + (i*bar_width) + (i*10), 235 - (datapoints[i]*2), bar_width, datapoints[i]*2, colour);
        }
    }else{
        for(uint8_t i = 0; i < bar_nr; i++){
            tft.fillRect(10 + (i*bar_width) + (i*10), 475 - (datapoints[i]*2), bar_width, datapoints[i]*2, colour);
        }
    }
}