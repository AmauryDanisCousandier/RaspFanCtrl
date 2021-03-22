# RaspFanCtrl
Fan control software for raspberry pi in C
Developed and tested with rapsberry pi4b running ubuntu server 20.04.2 LTS

PREREQUISITE:
bcm2835 library (bcm2835.h)
    https://www.airspayce.com/mikem/bcm2835/
GNU Compiler Collection (gcc)
    user@machine: sudo apt install gcc -y
make
    user@machine: sudo apt install make -y

USAGE:
1. Makefile build rule compiles programm with gcc and bcm2835 flag
    user@machine: make build
2. MAkefile exec rule fires binary in background
    user@machine: make exec


                                a8888b.
                               d888888b.
                               8P"YP"Y88
                               8|o||o|88
                               8'    .88
                               8`._.' Y8.
                              d/      `8b.
                            .dP   .     Y8b.
                           d8:'   "   `::88b.
                          d8"           `Y88b
                         :8P     '       :888
                          8a.    :      _a88P
                        ._/"Yaa_ :    .| 88P|
                        \    YP"      `| 8P  `.
                        /     \._____.d|    .'
                        `--..__)888888P`._.