@echo off

if "%2" == "-r" (
	clear
)

if not exist "build" (
	mkdir "build"
)
gcc -std=c11 -c CConsole_lib.c
ar -cr .\build\CConsole.lib CConsole_lib.o

rm CConsole_lib.o

if "%1" == "test" (
	gcc -std=c11 .\test\test.c -l:CConsole.lib -L.\build -lm -o .\test\test.exe
	if "%2" == "-r" (
		cd .\test\
		.\test.exe
		cd ..
	)
)
