@call "C:\Users\User\AppData\Roaming\MathWorks\MATLAB\R2012a\mexopts.bat"
@echo on
call "%VCINSTALLDIR%\vcvarsall.bat" x86_amd64
set MATLAB=C:\PROGRA~1\MATLAB~1
nmake -f q_rotpen_bal_student_ORIG.mk  GENERATE_REPORT=0 SHOW_TIMES=0 DEBUG=0 DEBUG_HEAP=0
