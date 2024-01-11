/*
 * CLCD_interface.h
 *
 * Created: 10-Dec-23 11:45:17 AM
 *  Author: MICHAEL
 */ 


#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidSendCommand(u8 copy_u8Command);

void CLCD_voidSendCharacter(u8 copy_u8Char);

void CLCD_voidInit(void);

void CLCD_voidSendString(char *copy_pcString);

void CLCD_voidClearDisplay(void);

void CLCD_voidMoveCursor(u8 copy_u8Row, u8 copy_u8Col);

void CLCD_voidSendNum(s32 copy_u8Num);

void CLCD_Custom_Char (u8 loc, u8 *msg);

void CLCD_voidCursorShift(u8 copy_u8CursorDir);

void CLCD_voidSendCharPosition(u8 copy_u8Char,u8 copy_u8Row, u8 copy_u8Col);

void CLCD_voidSendNumPosition(s32 copy_u8Num,u8 copy_u8Row, u8 copy_u8Col);

void CLCD_voidSendStringPosition(char *copy_pcString,u8 copy_u8Row, u8 copy_u8Col);


#define CURSOR_LEFT		0
#define CURSOR_RIGHT	1
#define DISPLAY_LEFT	2
#define DISPLAY_RIGHT	3
	

#endif /* CLCD_INTERFACE_H_ */