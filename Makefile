# MPLAB IDE generated this makefile for use with GNU make.
# Project: 111Demo_Project.mcp
# Date: Thu Jan 04 13:24:34 2018

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

111Demo_Project.cof : main.o Init_IO.o Time.o Uart.o Test_function.o HC595_function.o Key_function.o ST75320-8080.o Ziku.o String.o Show_function.o
	$(LD) /l"C:\MCC18\lib" "18f46j50_g.lkr" "main.o" "Init_IO.o" "Time.o" "Uart.o" "Test_function.o" "HC595_function.o" "Key_function.o" "ST75320-8080.o" "Ziku.o" "String.o" "Show_function.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"111Demo_Project.cof" /M"111Demo_Project.map" /W

main.o : main.c C:/MCC18/h/stdio.h Uart.h Time.h Test_function.h HC595_function.h ST75320-8080.h Show_function.h main.c Includeh.h C:/MCC18/h/stdarg.h C:/MCC18/h/stddef.h p18f46j50.h Init_IO.h Key_function.h Ziku.h String.h
	$(CC) -p=18F46J50 "main.c" -fo="main.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

Init_IO.o : Init_IO.c C:/MCC18/h/stdio.h Uart.h Time.h Test_function.h HC595_function.h ST75320-8080.h Show_function.h Init_IO.c Includeh.h C:/MCC18/h/stdarg.h C:/MCC18/h/stddef.h p18f46j50.h Init_IO.h Key_function.h Ziku.h String.h
	$(CC) -p=18F46J50 "Init_IO.c" -fo="Init_IO.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

Time.o : Time.c C:/MCC18/h/stdio.h Uart.h Time.h Test_function.h HC595_function.h ST75320-8080.h Show_function.h Time.c Includeh.h C:/MCC18/h/stdarg.h C:/MCC18/h/stddef.h p18f46j50.h Init_IO.h Key_function.h Ziku.h String.h
	$(CC) -p=18F46J50 "Time.c" -fo="Time.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

Uart.o : Uart.c C:/MCC18/h/stdio.h Uart.h Time.h Test_function.h HC595_function.h ST75320-8080.h Show_function.h Uart.c Includeh.h C:/MCC18/h/stdarg.h C:/MCC18/h/stddef.h p18f46j50.h Init_IO.h Key_function.h Ziku.h String.h
	$(CC) -p=18F46J50 "Uart.c" -fo="Uart.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

Test_function.o : Test_function.c C:/MCC18/h/stdio.h Uart.h Time.h Test_function.h HC595_function.h ST75320-8080.h Show_function.h Test_function.c Includeh.h C:/MCC18/h/stdarg.h C:/MCC18/h/stddef.h p18f46j50.h Init_IO.h Key_function.h Ziku.h String.h
	$(CC) -p=18F46J50 "Test_function.c" -fo="Test_function.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

HC595_function.o : HC595_function.c C:/MCC18/h/stdio.h Uart.h Time.h Test_function.h HC595_function.h ST75320-8080.h Show_function.h HC595_function.c Includeh.h C:/MCC18/h/stdarg.h C:/MCC18/h/stddef.h p18f46j50.h Init_IO.h Key_function.h Ziku.h String.h
	$(CC) -p=18F46J50 "HC595_function.c" -fo="HC595_function.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

Key_function.o : Key_function.c C:/MCC18/h/stdio.h Uart.h Time.h Test_function.h HC595_function.h ST75320-8080.h Show_function.h Key_function.c Includeh.h C:/MCC18/h/stdarg.h C:/MCC18/h/stddef.h p18f46j50.h Init_IO.h Key_function.h Ziku.h String.h
	$(CC) -p=18F46J50 "Key_function.c" -fo="Key_function.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

ST75320-8080.o : ST75320-8080.c C:/MCC18/h/stdio.h Uart.h Time.h Test_function.h HC595_function.h ST75320-8080.h Show_function.h ST75320-8080.c Includeh.h C:/MCC18/h/stdarg.h C:/MCC18/h/stddef.h p18f46j50.h Init_IO.h Key_function.h Ziku.h String.h
	$(CC) -p=18F46J50 "ST75320-8080.c" -fo="ST75320-8080.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

Ziku.o : Ziku.c ziku.h
	$(CC) -p=18F46J50 "Ziku.c" -fo="Ziku.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

String.o : String.c C:/MCC18/h/stdio.h Uart.h Time.h Test_function.h HC595_function.h ST75320-8080.h Show_function.h String.c Includeh.h C:/MCC18/h/stdarg.h C:/MCC18/h/stddef.h p18f46j50.h Init_IO.h Key_function.h Ziku.h String.h
	$(CC) -p=18F46J50 "String.c" -fo="String.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

Show_function.o : Show_function.c C:/MCC18/h/stdio.h Uart.h Time.h Test_function.h HC595_function.h ST75320-8080.h Show_function.h Show_function.c Includeh.h C:/MCC18/h/stdarg.h C:/MCC18/h/stddef.h p18f46j50.h Init_IO.h Key_function.h Ziku.h String.h
	$(CC) -p=18F46J50 "Show_function.c" -fo="Show_function.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "main.o" "Init_IO.o" "Time.o" "Uart.o" "Test_function.o" "HC595_function.o" "Key_function.o" "ST75320-8080.o" "Ziku.o" "String.o" "Show_function.o" "111Demo_Project.cof" "111Demo_Project.hex"

