pushd %~dp0

@echo off

call cmake -B ./build

pause
popd