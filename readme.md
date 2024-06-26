# MiniPOV3 in 2024

This is a short tutorial on how to program your MiniPOV3 in 2024. 

### Hardware 

Apart from your MiniPOV3 (with the ATtiny2313) your will also need an AVR based Arduino board to upload it code to it, this example uses an Arduino Uno. 

### Software 
- [make](https://gnuwin32.sourceforge.net/packages/make.htm) to build the software 
- The AVR toolchain:
  - On Windows, [WinAVR](https://winavr.sourceforge.net/) is useful 
  - On deb-like Linux:
    - `sudo apt-get update`
    - `apt-get sudo apt-get install gcc-avr binutils-avr avr-libc gdb-avr avrdude`
  - On MacOS:
    - `brew tap osx-cross/avr`
    - `brew install avr-binutils avr-gcc avrdude`
- [Arduino IDE](https://www.arduino.cc/en/software) to flash your Arduino board with the ArduinoISP firmware 


## Steps 

### Create your edit

Start by cloning or downloading this repository, you will find severl C source files. 

In your favourite editor, open `mypov.c`, on line 32 you will find an array variable named `image`, which is assined to a list of binary numbers, thses represent which LEDs are on and off at each segment, with the rightermost bits being the lower LEDs (towards the battery connection), you can sit the bits to 1 or 0 to turn LEDs on or off, and even add more sections to the array. 

Here's a checkerboard pattern. 

```c
const static int image[] = {
  B8(10101010),
  B8(01010101),
  B8(10101010),
  B8(01010101),
  B8(10101010),
  B8(01010101),
  B8(10101010),
  B8(01010101),
  B8(10101010),
  B8(01010101),
  B8(10101010),
  B8(01010101)
};
```

You can use the attached `MiniPOV3 Generator.xlsx` spreadsheet that uses custom formatting and formulas that will let you play with setting and unsetting pixels and will give you a list of all the binary numbers down the side which you can copy and paste in. 

<img src="docs/googlesheet.png">

### Building 

Open this repository in a command line, with make and the AVR toolchain installed, run `make mypov.hex`, this will compile your code to the file `mypov.hex`.


### Create your uploader 

Connect your AVR based Arduino to your PC, opening the Arduino IDE, select the correct port and Arduino board then open the example sketch `File -> Examples -> 11.ArduinoISP -> ArduinoISP` and upload it. 

<img src="docs/ide.png">

#### Circuit 

Next, with your ATtiny2313 on a breadboard, connect pin 10 to Arduino ground, and pin 20 to arduino +5 volts. 

For the Arduino Uno, connect: 

- Arduino pin 13 -> ATtiny2313 pin 19
- Arduino pin 12 -> ATtiny2313 pin 18
- Arduino pin 11 -> ATtiny2313 pin 17
- Arduino pin 10 -> ATtiny2313 pin 1

<img src="docs/circuit.png">

### Upload

Edit your `avrdude.conf` file, check to see if `arduino_as_isp` is present, if not, add the following programmer configuration:

```conf
#------------------------------------------------------------
# arduino_as_isp
#------------------------------------------------------------

# Not to be confused with arduinoISP, this is the same as `-c stk500v1`
# but treats EEPROM r/w correctly for arduino_as_isp programmers
# See https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP/
# for details.

programmer # arduino_as_isp
    id                     = "arduino_as_isp";
    desc                   = "Arduino board as programmer using arduino as ISP firmware";
    type                   = "stk500";
    prog_modes             = PM_ISP;
    connection_type        = serial;
    baudrate               = 19200;
;
```

`avrdude.conf` is normally present in: 
- Windows; same directory (folder) as the executable (run `where avrdude` from the command line to find the file)
- MacOS (via brew); `/opt/homebrew/etc/avrdude.conf` 
- Linux; `/usr/local/etc/avrdude.conf`

In your command line, still in this repository's directory, run the following command:

```
avrdude -c arduino_as_isp -p t2313 -P [serial port] -U flash:w:"mypov.hex":a
```

Add your serial port that the Arduino is connected to. You can replace `"mypov.hex"` with whichever hex file you want to upload. 

You can now take the ATtiny2313 and put it in your MiniPOV3 and display your custom message!  
