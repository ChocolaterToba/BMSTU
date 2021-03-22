REM '^' character is used for escaping - '|' has special behavior in ECHO

ECHO test.bat [y ^| n] [filename]
ECHO y ^| n - Необходимо ли очистить экран при закрытии программы? (n по умолчанию)
ECHO filename - Название файла справки (MY_help.bat по умолчанию)                       
ECHO Сделал студент группы ИУ5-41Б Агличеев Михаил
ECHO Вариант 2
EXIT /B