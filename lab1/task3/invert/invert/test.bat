@echo off
SET MyProgram= "%~1"

REM Запуск батника напрямую
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Недостаточное количество аргументов
%MyProgram% > "%TEMP%\out.txt" && goto err
fc test\too_few_arguments.txt "%TEMP%\out.txt" || goto err2
echo test 1 passed successfuly

REM Нечисловая матрица
%MyProgram% "test/invalid_matrix_elements_input.txt" > "%TEMP%\out.txt" && goto err
fc test\invalid_matrix_elements_output.txt "%TEMP%\out.txt" || goto err2
echo test 2 passed successfuly

REM Некорректное имя входного файла
%MyProgram% "test/input.xtx" > "%TEMP%\out.txt" && goto err
fc test\invalid_file_name.txt "%TEMP%\out.txt" || goto err2
echo test 3 passed successfuly

REM Некорректный размер матрицы
%MyProgram% "test/invalid_matrix_size_input.txt" > "%TEMP%\out.txt" && goto err
fc test\invalid_matrix_size_output.txt "%TEMP%\out.txt" || goto err2
echo test 4 passed successfuly

REM Матрица нулей
%MyProgram% "test/zero_matrix_input.txt" > "%TEMP%\out.txt" && goto err
fc test\zero_matrix_output.txt "%TEMP%\out.txt" || goto err2
echo test 5 passed successfuly

REM Единичная матрица
%MyProgram% "test/unit_matrix_input.txt" > "%TEMP%\out.txt" && goto err
fc test\unit_matrix_output.txt "%TEMP%\out.txt" || goto err2
echo test 6 passed successfuly

%MyProgram% "test/matrix1_input.txt" > "%TEMP%\out.txt" || goto err
fc test\matrix1_output.txt "%TEMP%\out.txt" && goto err2
echo test 7 passed successfuly

%MyProgram% "test/matrix2_input.txt" > "%TEMP%\out.txt" || goto err
fc test\matrix2_output.txt "%TEMP%\out.txt" && goto err2
echo test 8 passed successfuly

echo all tests have passed successfuly
exit /B 0

:err1
echo fail with input
exit /B 0

:err2
echo fail with comparing files
exit /B 0