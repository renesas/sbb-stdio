# Overview
This repo contains multiple instances of standard input output stream handlers provided as Software Building Block (SBB) as explained briefly in sections below.

***

# Buffered I/O over UART

[syscalls_picolib_stdio_to_uart.c](docs/README-BUFFERED-UART.md) module provides a **clean stdio abstraction** over FSP UART using:

* ByteQ buffering
* ISR-driven communication
* Minimal integration effort

It is best suited for:

* Debug console
* Development phase instrumentation

***

# Getting Started with steps for importing and running the SBB Projects

The Demo Evaluation section in [README-BUFFERED-UART.md](docs/README-BUFFERED-UART.md) explains the expected operation of this SBB.

Follow the guidelines to [install Renesas Visual Studio Code Extensions](https://tool-support.renesas.com/e2studio/vscode/docs/installation.html)

Examples which operate the SBB are provided in the `examples` folder. Acquire a copy of the relevant project on your local machine.

Open the your choice `*.code-workspace` file in VS Code.

Follow the instructions for [Building an RA Project created in Smart Configurator](https://tool-support.renesas.com/e2studio/vscode/docs/creating-and-building-project.html#building-an-ra-project-created-in-smart-configurator)

Instructions for [Debugging the opened project are provided here](https://tool-support.renesas.com/e2studio/vscode/docs/debugging-project.html).

# More Detailed Information

## Buffered I/O over UART

Please see [README-BUFFERED-UART.md](docs/README-BUFFERED-UART.md) for:
- Detailed description
- Public function description
- Integration notes
- Limitations
- Further enhancements
- References