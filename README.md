# STM32-MCU-Bare Metal Demo Code
In this repository I will upload a few demo examples of how to code [**STM32 MCU**](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html) without using [*HAL*](https://en.wikipedia.org/wiki/Hardware_abstraction). We will use only the peripheral driver provided by STMicroelectronics but in the first example we have showed how to write one by yourself using technical documentation.

## Used MCU's 📟
1. [**STM32F103C8T6**](https://www.st.com/content/st_com/en/products/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus/stm32-mainstream-mcus/stm32f1-series/stm32f103/stm32f103c8.html) - ARM®Cortex®-M3 32-bit RISC core based MCU. Used only in the *first demo* of writing peripheral drivers. 
2. [**STM32F722ZET6**](https://www.st.com/en/microcontrollers-microprocessors/stm32f722ze.html) - ARM® Cortex®-M7 32-bit RISC core based MCU. Used in all demos apart from the frist one. We will use it in NUCLEO-DEVELOPMENT Board.

## Project Resolution 🚀
This repository was created only for educational purposes. At the end of the course I will consider doing a real-life example of Embedded Device and uploading it's code here. Our goal is to write Bare Metal Code using C and the technical documentation provided by [*STMicroelectronics*](https://www.st.com/content/st_com/en.html). We will not use the provided HAL but we will use the provided peripheral driver for registers of the device.

## Demo Projects 💡
1. [**LED Toggle - Writing own Peripheral Driver**](https://github.com/KrIsKa7a/STM32-MCU-BareMetalDemoCode/tree/main/1_led_toggle_reg_struct) - In this project we have written a code for toggling built-in LED. We created structs that represents GPIO and RCC registers structure.
2. [**GPIO Output**](https://github.com/KrIsKa7a/STM32-MCU-BareMetalDemoCode/tree/main/2_gpio_output) - In this project we are setting GPIO ports and pins as output pins using the provided GPIO struct from STM32CubeF7 Development package.
3. [**GPIO Input and Output**](https://github.com/KrIsKa7a/STM32-MCU-BareMetalDemoCode/tree/main/3_gpio_toggle_led_with_button) - In this project we are using GPIO ports and pins as input and output. We are doing a simple toggle LED with a button.
4. [**USART-TX**](https://github.com/KrIsKa7a/STM32-MCU-BareMetalDemoCode/tree/main/4_usart_tx) - In this project we are configuring USART-TX data transmission. Our device will work as a transmitter and will send data to a terminal inside our computer using [*Serial/TCP Terminal*](https://sourceforge.net/projects/realterm/).

## Technical Documentation Used 🗎
1. [**STM32F7x2 Datasheet**](https://www.st.com/resource/en/datasheet/stm32f722ze.pdf)
2. [**STM32F7x2 Reference Manual**](https://www.st.com/resource/en/reference_manual/rm0431-stm32f72xxx-and-stm32f73xxx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
3. [**NUCLEO DEVELOPMENT Board Datasheet**](https://www.st.com/resource/en/data_brief/nucleo-f722ze.pdf)
