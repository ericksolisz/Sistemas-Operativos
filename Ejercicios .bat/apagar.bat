@echo off
setlocal

set TiempoDeApagado=1800
set TiempoDeEspera=10

echo Aviso: La computadora se apagara en %TiempoDeApagado% segundos.


shutdown /s /t %TiempoDeApagado%

timeout %TiempoDeEspera%

shutdown /a

echo Aviso: La computadora ya no se apagara.

pause