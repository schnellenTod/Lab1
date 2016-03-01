@echo off
echo Debug Version Compare
code\Debug\invert.exe input\input1.txt output\output1.txt
code\Debug\invert.exe input\input2.txt output\output2.txt 
code\Debug\invert.exe input\input3.txt output\output3.txt 

Call :COMPARE tests\original1.txt output\output1.txt 
Call :COMPARE tests\original2.txt output\output2.txt 
Call :COMPARE tests\original3.txt output\output3.txt 

echo Release Version Compare
code\Release\invert.exe input\input1.txt output\output1.txt 
code\Release\invert.exe input\input2.txt output\output2.txt 
code\Release\invert.exe input\input3.txt output\output3.txt 

Call :COMPARE tests\original1.txt output\output1.txt 
Call :COMPARE tests\original2.txt output\output2.txt 
Call :COMPARE tests\original3.txt output\output3.txt 

echo DebugX64 Version Compare
code\x64\Debug\invert.exe input\input1.txt output\output1.txt 
code\x64\Debug\invert.exe input\input2.txt output\output2.txt 
code\x64\Debug\invert.exe input\input3.txt output\output3.txt 

Call :COMPARE tests\original1.txt output\output1.txt 
Call :COMPARE tests\original2.txt output\output2.txt 
Call :COMPARE tests\original3.txt output\output3.txt 

echo ReleaseX64 Version Compare
code\x64\Release\invert.exe input\input1.txt output\output1.txt 
code\x64\Release\invert.exe input\input2.txt output\output2.txt 
code\x64\Release\invert.exe input\input3.txt output\output3.txt 

Call :COMPARE tests\original1.txt output\output1.txt 
Call :COMPARE tests\original2.txt output\output2.txt 
Call :COMPARE tests\original3.txt output\output3.txt 
pause
exit /b 


:COMPARE 
echo %1 %2 
fc %1 %2 > nul 
if ERRORLEVEL 1 goto Fail 
if ERRORLEVEL 2 goto OF
echo done 
exit /b  
:Fail 
echo fail 
exit /b
:OF
echo Can not open file
exit /b