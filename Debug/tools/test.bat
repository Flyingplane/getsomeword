@echo off
rem ָ������ļ���Ŀ¼
set FolderName=%CD%
for /f "delims=\" %%a in ('dir /b /a-d /o-d "%FolderName%\*.PDF"') do (
  echo %%a
)
pause