@echo off
.\scripts\timer.bat "submission.exe < input.temp > sub_output.temp \" > time.temp
taskkill /f /im submission.exe > NUL 2> NUL