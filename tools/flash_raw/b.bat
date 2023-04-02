@echo off
if not defined DevEnvDir (
   call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
)
cl -c *.c
link *.obj user32.lib -nodefaultlib:libc.lib -out:flashRAW.exe
del *.obj
