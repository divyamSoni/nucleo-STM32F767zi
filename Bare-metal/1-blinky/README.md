## Blinking an LED on Nucleo - STM32f767zi

For bare metal programming of LED blinking we need to find particular things in the resource documents of the nucleo board. 

#### Where is the user LED connected?
To do that we need to see the [User_Manual](https://www.st.com/content/ccc/resource/technical/document/user_manual/group0/26/49/90/2e/33/0d/4a/da/DM00244518/files/DM00244518.pdf/jcr:content/translations/en.DM00244518.pdf) of Nucleo-STM32f767zi and on page 75 we can see LED2 (blue) is connected to PB7 (i.e Port B pin 7) meaning, LED2 is connected to GPIOB (General Purpose I/O port B).

#### To which bus GPIOB is connected to?
We need to enable the clock access for particular ports we need to use. If you see the [STM32f767zi_datasheet](https://www.st.com/resource/en/datasheet/stm32f767zi.pdf) on page 19 there is a block diagram, where one can see that GPIOB is connected to AHB1 (Advanced High performance Bus)

#### Configuring the registers
To configure the registers we need to see the [Reference_Manual](https://www.st.com/content/ccc/resource/technical/document/reference_manual/group0/96/8b/0d/ec/16/22/43/71/DM00224583/files/DM00224583.pdf/jcr:content/translations/en.DM00224583.pdf) modify some registers-

RCC_AHB1 - This is peripheral Reset and Clock Control register. On page 182 of the Reference Manual we can see we need to enable bit 1 of AHB1ENR register to give clock access to GPIOB from AHB1 bus. 


GPIO_MODER - GPIO Mode register is to set different modes (direction) of GPIO. Here we need to set the MODER7 as 01 for General Purpose Output Mode, i.e we need to set bit 15 of GPIO_MODER register.

GPIO_ODR - GPIO Output Data Register is what we need to toggle to make the LED blink (with some delay in between). To toggle/blink LED2 (blue) we need to toggle bit 7 (ODR7) high and low in our code.
