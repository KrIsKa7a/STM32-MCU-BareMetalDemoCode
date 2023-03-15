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
4. [**USART-RX-TX**](https://github.com/KrIsKa7a/STM32-MCU-BareMetalDemoCode/tree/main/4_usart_tx) - In this project we are configuring USART-RX-TX data transmission. Our device will work as a receiver and transmitter and will send data to a terminal inside our computer using [*Serial/TCP Terminal*](https://sourceforge.net/projects/realterm/). We will also toggle the built-in LED using commands from the computer terminal.
5. [**ADC**](https://github.com/KrIsKa7a/STM32-MCU-BareMetalDemoCode/tree/main/5_adc_singleconversion) - In this project we are configuring ADC Module. This allows us to read analog values from sensors measuring surrounding world parameters - Temperature, Pressure, Humidity, etc. We are configuring single channel in Single Conversion and Continious Conversion Mode. You can also add Multiple Channels easily to the written code.
6. [**SysTick Timer**](https://github.com/KrIsKa7a/STM32-MCU-BareMetalDemoCode/tree/main/6_systick_delay) - In this project we are using the Cortex-Mx built-in System Tick Timer. We are showing how to create a simple but very useful delay function.
7. [**Timers**](https://github.com/KrIsKa7a/STM32-MCU-BareMetalDemoCode/tree/main/7_timers) - In this project we are developing driver for using Timer module in different modes - General-Purpose Mode, Input Capture Mode and Output Compare Mode. We show their usage for measuring time and creating interrupts, for toggling output and for measuring the frequency of input signal.
8. [**Interrupts**](https://github.com/KrIsKa7a/STM32-MCU-BareMetalDemoCode/tree/main/8_interrupts) - In this project we are enabling interrupt programming model for different peripheral drivers we have already written. We are enabling EXTI handlers for GPIOs, UART, ADC, SysTick and TIM interrupts. 
9. [**DMA**](https://github.com/KrIsKa7a/STM32-MCU-BareMetalDemoCode/tree/main/9_dma) - In this project we are enabling DMA data transfer from the internal memory to the USART3 peripheral. We are using USART-TX in order to send data using our USB connection but this time we have enabled DMA for the transfer in order to speed-up the process. 

## Technical Documentation Used 🗎
1. [**STM32F7x2 Datasheet**](https://www.st.com/resource/en/datasheet/stm32f722ze.pdf)
2. [**STM32F7x2 Reference Manual**](https://www.st.com/resource/en/reference_manual/rm0431-stm32f72xxx-and-stm32f73xxx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
3. [**NUCLEO DEVELOPMENT Board Datasheet**](https://www.st.com/resource/en/data_brief/nucleo-f722ze.pdf)
4. [**ARM Cortex-M7 User Guide**](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwinvJj-iZL9AhVQXfEDHRtXB1sQFnoECBcQAQ&url=https%3A%2F%2Fdocumentation-service.arm.com%2Fstatic%2F61efd6602dd99944d051417b%3Ftoken%3D&usg=AOvVaw1YBkWATMHYU38uiW5bUc0A)
