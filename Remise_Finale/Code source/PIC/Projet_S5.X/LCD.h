/* 
 * File:   LCD.h
 * Author: François Brunet
 *
 * Created on 14 avril 2017, 17:07
 */

#ifndef LCD_H
#define	LCD_H

#include <spi.h>

//Function prototype
void LCD_init(void);
void LCD_Clear(void);
void LCD_WriteChar(char data);
void LCD_WriteString(char* data);
void LCD_SelectLine(char line);

#endif	/* LCD_H */

