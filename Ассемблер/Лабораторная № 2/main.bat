@ECHO OFF
SET CLSAFTER=%1
SHIFT

REM Processing filename (supposed to be second parameter)
SET FILENAME=%1
SHIFT
IF NOT (%FILENAME%) == () GOTO START
SET FILENAME=MY_help.bat

:START
REM Clearing screen (only initially, when starting the program)
CLS 
:MENU
REM Menu is displayed as simple plain text
ECHO.
ECHO Выберите опцию:
ECHO 1: Вывод содержимого переданной директории или её создание в случае отсутствия
ECHO 2: Вывод справки о команде CLS
ECHO 3: Вывод справки о команде GOTO
ECHO 4: Вывод справки о команде PAUSE        
ECHO 5: Вывод справки о данном командном файле                                                                    
ECHO 6: Выход
ECHO.

CHOICE /C 123456 /N /M "Введите номер выбранной опции (1-6): "
ECHO.

REM If user chose option 6, program is closed    
IF ERRORLEVEL 6 GOTO FINALLY

REM Otherwise, routing happens
GOTO M%ERRORLEVEL%

:M1
IF (%1) == () GOTO M1FAIL
IF EXIST %1 GOTO SHOWDIR
MKDIR %1
ECHO Создана папка по адресу %1
GOTO M1END

:SHOWDIR
DIR %1 
:M1END
SHIFT
GOTO MENU

:M1FAIL
ECHO Не было передано адресов папок либо они закончились
GOTO MENU         

:M2
HELP CLS
GOTO MENU

:M3
HELP GOTO
GOTO MENU

:M4
HELP PAUSE
GOTO MENU

:M5
REM Calling extra command file which displays supplementary documentation
CALL %FILENAME%
GOTO MENU

:FINALLY 
REM Checking if first parameter is "y" meaning "clear screen before closing"
IF NOT (%CLSAFTER%) == (y) GOTO FINISH
CLS
:FINISH  
EXIT /B