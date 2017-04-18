/* 
 * File:   Keyboard.h
 * Author: François Brunet
 *
 * Created on April 16, 2017, 3:21 PM
 */

#ifndef KEYBOARD_H
#define	KEYBOARD_H

#include <stdbool.h> 

bool Keyboard_NewData = false;
char Keyboard_Data;

void Keyboard_init(void);
void Keyboard_Read(void);

#endif	/* KEYBOARD_H */

