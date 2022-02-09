set SCRIPT_DIR="%~d0%~p0"
cd %SCRIPT_DIR%



call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\Common7\Tools\VsDevCmd.bat" -arch=amd64

if not exist "out" mkdir "out"
cd out &&  cl.exe "/Zi" "/EHsc" "/nologo" "/Fe:" dlldependverify.exe ../dlldependverify.cc

