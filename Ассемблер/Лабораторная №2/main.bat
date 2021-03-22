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
ECHO �롥�� ����:
ECHO 1: �뢮� ᮤ�ন���� ��।����� ��४�ਨ ��� �� ᮧ����� � ��砥 ������⢨�
ECHO 2: �뢮� �ࠢ�� � ������� CLS
ECHO 3: �뢮� �ࠢ�� � ������� GOTO
ECHO 4: �뢮� �ࠢ�� � ������� PAUSE        
ECHO 5: �뢮� �ࠢ�� � ������ ��������� 䠩��                                                                    
ECHO 6: ��室
ECHO.

CHOICE /C 123456 /N /M "������ ����� ��࠭��� ��樨 (1-6): "
ECHO.

REM If user chose option 6, program is closed    
IF ERRORLEVEL 6 GOTO FINALLY

REM Otherwise, routing happens
GOTO M%ERRORLEVEL%

:M1
IF (%1) == () GOTO M1FAIL
IF EXIST %1 GOTO SHOWDIR
MKDIR %1
ECHO ������� ����� �� ����� %1
GOTO M1END

:SHOWDIR
DIR %1 
:M1END
SHIFT
GOTO MENU

:M1FAIL
ECHO �� �뫮 ��।��� ���ᮢ ����� ���� ��� �����稫���
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