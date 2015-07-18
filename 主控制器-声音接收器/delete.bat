@echo off 
echo 正在清除系统垃圾文件，请稍等...... 
del /f /s /q .\obj\*.*
del /f /s /q .\Project\*.lst
del /f /s /q .\Project\*.map
del /f /s /q .\Project\*.plg
del /f /s /q .\Project\*.Administrator
del /f /s /q .\Project\*.bak
del /f /s /q .\Project\*.uvopt
del /f /s /q .\Project\*.dep
del /f /s /q .\Project\*.txt
del /f /s /q .\Project\*.ini
del /f /s /q .\Project\*.htm