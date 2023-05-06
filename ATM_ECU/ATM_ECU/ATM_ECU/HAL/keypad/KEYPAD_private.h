/*
 * File: keypad_private.h
 * Created Date: Tuesday, April 18th 2023, 11:14:37 pm
 * Author: Omar Taha
 * -----
 * Copyright (c) 2023 Omar Taha <<https://github.com/OmarAshrafTaha>>
 */

#ifndef KEYPAD_PRIVATE_H
#define KEYPAD_PRIVATE_H


/*Keypad initialization error*/
typedef enum KEYPAD_initError
{
    KEYPAD_initSuccess,KEYPAD_initFail
}KEYPAD_initError;

/*Keypad read error*/
typedef enum KEYPAD_readError
{
    KEYPAD_readSuccess,KEYPAD_readFail
}KEYPAD_readError;


 #endif /* KEYPAD_PRIVATE_H */