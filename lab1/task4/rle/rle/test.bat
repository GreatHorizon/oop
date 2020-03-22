SET MyProgram= "%~1"

if %myProgram%=="" (
	echo Please specify path to the programm
	exit /B 1
)

REM Недостаточное количество аргументов
%MyProgram% > "%TEMP%\output.txt" && goto err1
echo test 1 passed successfully 

REM Некорректный режим
%MyProgram% "epack" "test/input.txt" "%TEMP%\output.txt" > "%TEMP%\output.txt" && goto err1
echo test 2 passed successfully 

REM Пустой входной файл при упаковке
%MyProgram% "pack" "test/empty.txt" "%TEMP%\output.txt" || goto err1
fc "test\empty.txt" %TEMP%\output.txt || goto err2
echo test 3 passed successfully

REM Файл с нечетным количеством байт при распаковке
%MyProgram% "unpack" "test/unpack_odd_byte_amount_input.txt" "%TEMP%\output.txt" && goto err1
echo test 4 passed successfully

REM Несуществующий входной файл
%MyProgram% "unpack" "test/inputFFF.txt" %TEMP%\output.txt && goto err1
echo test 5 passed successfully

REM Пустой входной файл при распаковке
%MyProgram% "unpack" "test/empty.txt" "%TEMP%\output.txt" || goto err1
fc "test\empty.txt" %TEMP%\output.txt || goto err2
echo test 6 passed successfully

REM Запаковка 256 байтов 
%MyProgram% "pack" "test\pack_input_1.txt" %TEMP%\output.txt || goto err1
fc "test\pack_output_1.txt" %TEMP%\output.txt || goto err2
echo test 7 passed successfully

REM Запаковка 255 байтов 
%MyProgram% "pack" "test\pack_input_2.txt" %TEMP%\output.txt || goto err1
fc "test\pack_output_2.txt" %TEMP%\output.txt || goto err2
echo test 8 passed successfully

REM Распаковка 256 байов 
%MyProgram% "unpack" "test\unpack_input_1.txt" %TEMP%\output.txt || goto err1
fc "test\unpack_output_1.txt" %TEMP%\output.txt || goto err2
echo test 9 passed successfully

REM Распаковка 255 байтов 
%MyProgram% "unpack" "test/unpack_input_2.txt" %TEMP%\output.txt || goto err1
fc "test\unpack_output_2.txt" %TEMP%\output.txt || goto err2
echo test 10 passed successfully

REM Запаковка последовательностей из одного байта
%MyProgram% "pack" "test/pack_single_symbols_input.txt" %TEMP%\output.txt || goto err1
fc "test\pack_single_symbols_output.txt" %TEMP%\output.txt || goto err2
echo test 11 passed successfully

REM Распаковка последовательностей из одного байта
%MyProgram% "unpack" "test/pack_single_symbols_output.txt" %TEMP%\output.txt || goto err1
fc "test\pack_single_symbols_input.txt" %TEMP%\output.txt || goto err2
echo test 12 passed successfully

REM Запаковка 1 байта
%MyProgram% "pack" "test/pack_input_3.txt" %TEMP%\output.txt || goto err1
fc "test\pack_output_3.txt" %TEMP%\output.txt || goto err2
echo test 13 passed successfully

REM Распаковка 1 байта
%MyProgram% "unpack" "test/pack_output_3.txt" %TEMP%\output.txt || goto err1
fc "test\pack_input_3.txt" %TEMP%\output.txt || goto err2
echo test 14 passed successfully

%MyProgram% "pack" "test/pack_input_4.txt" %TEMP%\output.txt || goto err1
fc "test\pack_output_4.txt" %TEMP%\output.txt || goto err2
echo test 15 passed successfully

%MyProgram% "unpack" "test/pack_output_4.txt" %TEMP%\output.txt || goto err1
fc "test\pack_input_4.txt" %TEMP%\output.txt || goto err2
echo test 16 passed successfully

echo All tests passed successfully
exit /B 0

:err1
echo fail with input
exit /B 0

:err2
echo fail with comparing files
exit /B 0