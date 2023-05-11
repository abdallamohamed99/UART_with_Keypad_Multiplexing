# UART with Keypad Multiplexing

With a keypad connected to port B and port D of the microcontroller, the program first initiates port B as an input and then enables the pull-up resistors. 
Then, the program initiates port D as output and sets it to drive high. Then it initiates the USART module. 
The program then scans the 4x4 keypadby multiplexing the pins to determine if a key is pressed and then transmits the pressed key value over USART. 

### Demo
https://youtube.com/shorts/DyNgIsC5euc?feature=share