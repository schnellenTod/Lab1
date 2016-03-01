@echo off
echo Debug Version Compare
code\Debug\replace.exe input\input1.txt output\output1.txt 1231234 0
code\Debug\replace.exe input\input2.txt output\output2.txt 123 000000000000000000000
code\Debug\replace.exe input\input3.txt output\output3.txt ANPR "A N P R"

Call :COMPARE tests\original1.txt output\output1.txt 
Call :COMPARE tests\original2.txt output\output2.txt 
Call :COMPARE tests\original3.txt output\output3.txt 

echo Release Version Compare
code\Release\replace.exe input\input1.txt output\output1.txt 1231234 0
code\Release\replace.exe input\input2.txt output\output2.txt 123 000000000000000000000
code\Release\replace.exe input\input3.txt output\output3.txt ANPR "A N P R"

Call :COMPARE tests\original1.txt output\output1.txt 
Call :COMPARE tests\original2.txt output\output2.txt 
Call :COMPARE tests\original3.txt output\output3.txt 

echo DebugX64 Version Compare
code\x64\Debug\replace.exe input\input1.txt output\output1.txt 1231234 0
code\x64\Debug\replace.exe input\input2.txt output\output2.txt 123 000000000000000000000
code\x64\Debug\replace.exe input\input3.txt output\output3.txt ANPR "A N P R"

Call :COMPARE tests\original1.txt output\output1.txt 
Call :COMPARE tests\original2.txt output\output2.txt 
Call :COMPARE tests\original3.txt output\output3.txt 

echo ReleaseX64 Version Compare
code\x64\Release\replace.exe input\input1.txt output\output1.txt 1231234 0
code\x64\Release\replace.exe input\input2.txt output\output2.txt 123 000000000000000000000
code\x64\Release\replace.exe input\input3.txt output\output3.txt ANPR "A N P R"

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