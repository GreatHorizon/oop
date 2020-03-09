SET MyProgram= "%~1"

if %myProgram%=="" (
	echo Please specify path to the programm
	exit /B 1
)

REM Недостаточное количество аргументов
%MyProgram% > "%TEMP%\output.txt" && goto err1
echo test 1 passed successfuly 

REM Некорректный режим
%MyProgram% "epack" "test/input.txt" "%TEMP%\output.txt" > "%TEMP%\output.txt" && goto err1
echo test 2 passed successfuly 

REM Пустой входной файл при упаковке
%MyProgram% "pack" "test/empty_input.txt" "%TEMP%\output.txt" && goto err1
echo test 3 passed successfuly

REM Пустой входной файл при распаковке
%MyProgram% "unpack" "test/empty_input.txt" "%TEMP%\output.txt" && goto err1
echo test 4 passed successfuly

REM Файл с нечетным количеством байт при распаковке
%MyProgram% "unpack" "test/unpack_odd_byte_amount_input.txt" "%TEMP%\output.txt" && goto err1
echo test 5 passed successfuly

REM Несуществующий входной файл
%MyProgram% "unpack" "test/inputFFF.txt" %TEMP%\output.txt && goto err1
echo test 6 passed successfuly

REM Запаковка 256 байтов 
%MyProgram% "pack" "test\pack_input_1.txt" %TEMP%\output.txt || goto err1
fc "test\pack_output_1.txt" %TEMP%\output.txt || goto err2
echo test 7 passed successfuly

REM Запаковка 255 байтов 
%MyProgram% "pack" "test\pack_input_2.txt" %TEMP%\output.txt || goto err1
fc "test\pack_output_2.txt" %TEMP%\output.txt || goto err2
echo test 8 passed successfuly

REM Распаковка 256 байов 
%MyProgram% "unpack" "test\unpack_input_1.txt" %TEMP%\output.txt || goto err1
fc "test\unpack_output_1.txt" %TEMP%\output.txt || goto err2
echo test 9 passed successfuly

REM Распаковка 255 байтов 
%MyProgram% "unpack" "test/unpack_input_2.txt" %TEMP%\output.txt || goto err1
fc "test\unpack_output_2.txt" %TEMP%\output.txt || goto err2
echo test 10 passed successfuly

REM Запаковка последовательностей из одного байта
%MyProgram% "pack" "test/pack_single_symbols_input.txt" %TEMP%\output.txt || goto err1
fc "test\pack_single_symbols_output.txt" %TEMP%\output.txt || goto err2
echo test 11 passed successfuly

REM Запаковка символа с кодом 255
%MyProgram% "pack" "test/pack_single_symbols_input.txt" %TEMP%\output.txt || goto err1
fc "test\pack_single_symbols_output.txt" %TEMP%\output.txt || goto err2
echo test 12 passed successfuly


echo All tests passed successuly
exit /B 0


:err1
echo fail with input
exit /B 0

:err2
echo fail with comparing files
exit /B 0