![](https://img.shields.io/github/issues/divyamSoni/nucleo-STM32F767zi)
![](https://img.shields.io/github/stars/divyamSoni/nucleo-STM32F767zi)
![](https://img.shields.io/github/forks/divyamSoni/nucleo-STM32F767zi)
![](https://img.shields.io/github/license/divyamSoni/nucleo-STM32F767zi)
### Basic Bare-Metal Embedded Code

This is a guide for newbies to bare metal programming using nucleo-STM32F767zi board. Bare metal code i.e. configuring registers directly to achieve desired behaviour without using various abstraction layers. One can use any board of there choice because in bare-metal programming we are interacting on a hardware level, main thing to learn here is how to go through a datasheet and configure various registers hence making one adaptable to different microcontrollers. The only thing that differs from one manufacturer to another is the architecture, which should be kept in mind while programming a partucular microcontroller.

[![nucleo-Stm32f767zi](https://img.shields.io/badge/Board-nucleo_STM32f767zi-informational?style=flat&logo=data:image/svg%2bxml;base64,PHN2ZyByb2xlPSJpbWciIHZpZXdCb3g9IjAgMCAyNCAyNCIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj48dGl0bGU+U1RNaWNyb2VsZWN0cm9uaWNzIGljb248L3RpdGxlPjxwYXRoIGQ9Ik0gMjMuODE4IDUuNjEgTCA2LjQwMiA1LjYxIEMgNS4xMjUgNS42MDkgMy45NjggNi4zNjIgMy40NTIgNy41MjkgTCAwLjAxNCAxNS44MTEgQyAtMC4wMzYgMTUuOTMxIDAuMDUyIDE2LjA2MyAwLjE4MiAxNi4wNjEgTCA4LjA0NiAxNi4wNjEgQyA4LjYwMSAxNi4wNjEgOC44NDggMTUuNTIzIDguNDEyIDE1LjA5MyBMIDUuNTI0IDEyLjM4OCBDIDQuMDA4IDEwLjkgNC42NTggNy40NSA3LjgxIDcuNDUgTCAyMy4yMDYgNy40NSBDIDIzLjI4MyA3LjQ1MSAyMy4zNTIgNy40MDIgMjMuMzc4IDcuMzI5IEwgMjMuOTg3IDUuODU3IEMgMjMuOTk2IDUuODM1IDI0LjAwMSA1LjgxMSAyNCA1Ljc4NyBDIDIzLjk5NyA1LjY4OSAyMy45MTcgNS42MSAyMy44MTggNS42MSBNIDIyLjA4MiA5LjgyNiBMIDE5LjEyNiA5LjgyNiBDIDE4LjkzMiA5LjgyNSAxOC43NTYgOS45NCAxOC42ODEgMTAuMTE4IEwgMTUuMzY5IDE4LjExOCBDIDE1LjM1NSAxOC4xNDQgMTUuMzQ3IDE4LjE3MyAxNS4zNDcgMTguMjAyIEMgMTUuMzQ4IDE4LjMwMiAxNS40MjkgMTguMzgzIDE1LjUyOSAxOC4zODEgTCAxNi42MzIgMTguMzgxIEMgMTcuOTMgMTguMzg3IDE5LjEwNSAxNy42MTMgMTkuNjEyIDE2LjQxOCBMIDIyLjI0NCAxMC4wNjMgQyAyMi4yNTIgMTAuMDQyIDIyLjI1NyAxMC4wMTkgMjIuMjU3IDkuOTk2IEMgMjIuMjUzIDkuOTAyIDIyLjE3NiA5LjgyOCAyMi4wODIgOS44MjYgTSAxNi4yNzEgMTAuMDA1IEMgMTYuMjcxIDkuOTA1IDE2LjE4OSA5LjgyNSAxNi4wODkgOS44MjUgTCA3LjcwNiA5LjgyNSBDIDcuMjUxIDkuODI1IDYuODUzIDEwLjM4IDcuMzM1IDEwLjgyNSBMIDEwLjEwNCAxMy40MDQgQyAxMC4xMDQgMTMuNDA0IDExLjIyNCAxNC40MzcgMTAuOTg0IDE1LjkxNiBDIDEwLjc3OCAxNy4yMTkgOS44ODkgMTguMDE2IDkuMjQxIDE4LjMwMiBDIDkuMjA4IDE4LjMxIDkuMTk2IDE4LjM1MSA5LjIxOSAxOC4zNzYgQyA5LjIzIDE4LjM4NyA5LjI0NiAxOC4zOTIgOS4yNjEgMTguMzg4IEwgMTIuNDg5IDE4LjM4OCBDIDEyLjY4MyAxOC4zOSAxMi44NTkgMTguMjc1IDEyLjkzNCAxOC4wOTUgTCAxNi4yNTYgMTAuMDY4IEMgMTYuMjY2IDEwLjA0OSAxNi4yNzEgMTAuMDI3IDE2LjI3MSAxMC4wMDUiLz48L3N2Zz4=)](https://www.st.com/en/evaluation-tools/nucleo-f767zi.html)
[![MDK-Arm](https://img.shields.io/badge/Tool-Keil_uVision_5-informational?style=flat&color=darkgreen&logo=data:image/svg%2bxml;base64,<BASE64_DATA>)](https://www.keil.com/demo/eval/arm.htm)

Mainly 2 documents are required to program a particular microcontroller.

[Datasheet](https://www.st.com/resource/en/datasheet/stm32f767zi.pdf) | View block diagram, bus connections etc.
---|---
[Reference Manual](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwjX-MnG16DvAhW-yzgGHc5wBqoQFjAAegQIAhAD&url=https%3A%2F%2Fwww.st.com%2Fresource%2Fen%2Freference_manual%2Fdm00224583-stm32f76xxx-and-stm32f77xxx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf&usg=AOvVaw0uMnwqVhzsZ7fMyUFT-C1q) | To configure specific register bits.

### Keil µVision Settings
#### Run-Time Environment

[![CMSIS Core](https://img.shields.io/badge/CMSIS-Core-informational?style=flat&color=yellowgreen&logo=data:image/svg%2bxml)](https://www.keil.com/pack/doc/CMSIS/Core/html/index.html)
[![Startup](https://img.shields.io/badge/Device-Startup-informational?style=flat&color=important&logo=data:image/svg%2bxml)](https://www.keil.com/support/man/docs/uv4/uv4_ca_config_start_code.htm)

#### Target options

[![Frequency](https://img.shields.io/badge/Frequency-16_MHz-informational?style=flat&color=9cf&logo=data:image/svg%2bxml)](https://www.keil.com/support/man/docs/uv4/uv4_ca_tool_options.htm)
[![Debugger](https://img.shields.io/badge/Debugger-ST_Link_Debugger-informational?style=flat&color=blue&logo=data:image/svg%2bxml)](https://www.keil.com/support/man/docs/uv4/uv4_debugging.htm)

#### Flash Download
[![Download Function](https://img.shields.io/badge/Download_Function-Erase_Sectors,Program,Verify,Reset_&_Run-informational?style=flat&color=blueviolet&logo=data:image/svg%2bxml)](https://www.keil.com/support/man/docs/ulinkme/ulinkme_su_download_functions.htm)
