@echo off

if not exist "build" (
	mkdir "build"
	cd build
	if not exist "src" (
		mkdir src
	)
	cd ..
)

if "%2" == "-r" (
	clear
	cd build
	if not exist "test" (
		mkdir test
	)
	cd ..
)

gcc -std=c11 -c .\src\CConsole_lib.c
ar -cr .\build\src\CConsole.lib CConsole_lib.o

rm CConsole_lib.o

if "%1" == "test" (
	gcc -std=c11 .\test\test.c -l:CConsole.lib -L.\build\src -lm -o .\build\test\test.exe
	if "%2" == "-r" (
		cd .\build\test\
		.\test.exe
		cd ..
	)
)
