@echo off 
SET program="%1" 
if %program% == "" goto err 

echo Test1 > out.txt 
%program% 12 9 4.3 » out.txt 
if NOT ERRORLEVEL 1 goto testFailed 
fc.exe out.txt out1.txt 
if ERRORLEVEL 1 goto testFailed 

echo Test2 > out.txt 
%program% 6 9 3 » out.txt 
if NOT ERRORLEVEL 0 goto testFailed 
fc.exe out.txt out2.txt 
if ERRORLEVEL 1 goto testFailed 

echo Test3 > out.txt 
%program% 2.64 19 32 » out.txt 
if NOT ERRORLEVEL 0 goto testFailed 
fc.exe out.txt out3.txt 
if ERRORLEVEL 1 goto testFailed 

echo Test4 > out.txt 
%program% 254 123 » out.txt 
if NOT ERRORLEVEL 0 goto testFailed 
fc.exe out.txt out4.txt 
if ERRORLEVEL 1 goto testFailed 

echo Test5 > out.txt 
%program% 3 1 » out.txt 
if ERRORLEVEL 1 goto testFailed 
fc.exe out.txt out5.txt 
if ERRORLEVEL 1 goto testFailed 

echo Test6 > out.txt 
%program% 8 » out.txt 
if NOT ERRORLEVEL 1 goto testFailed 
fc.exe out.txt out6.txt 
if ERRORLEVEL 1 goto testFailed 

echo OK 
pause 
exit /B 

:testFailed 
echo Testing failed 
pause 
exit /B 

:err 
echo Usage: test.bat <Path to program>