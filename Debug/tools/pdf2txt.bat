@echo off
rem 指定存放文件的目录
set FolderName=%CD%
for /f "delims=\" %%a in ('dir /b /a-d /o-d "%FolderName%\*.PDF"') do (
  echo %%a
  set FileName=%%a
)
echo on
set dirFileName=%FileName:~0,-4%.txt
pdftotext.exe -enc "GBK" %FileName% %dirFileName%
DemoGtest.exe %dirFileName%
pause