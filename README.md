# Tokex
Toki Pona's alphabet is only made up of 14 Latin characters, so I made a way to represent them all using hexadecimal digits (hexits), including representation for some punctuation/separation characters.
```
    1 bit = one binary digit (0 or 1)
   1 byte = 8 bits
 1 nibble = 4 bits
2 nibbles = 1 byte

Bytes are generally represented in hexadecimal, for ease of reading by human beings.
Whereas decimal digits cover a range of 10 values (0-9),
  hexadecimal digits range 16 possible values (hexa: 6 and deci: 10 numerals).
Since we don't have more than 10 arabic numerals available to work with,
  the letters A-F are added to the roster: 0123456789ABCDEF (base values 0-15 in decimal).
A-F can also be represented in lowercase a-f, either way representing the same set of values.

As if stored in a byte of memory,
decimal value 12 in binary: 0000 1000;  in hex: 0C
decimal value 32 in binary: 0010 0000;  in hex: 20
```
Since a byte is 2 hexadecimal digits (2 nibbles of storage), every letter of the Tokex alphabet uses only half a byte.  Even the smallest, standard, plaintext representation uses 1 byte/character, minimum.  So, while you won't be able to read Tokex from a Notepad window, it is going to take up a lot less space while still being readable from a hexdump or a memory map view.

5ucur made an offshoot/alternative to Tokex called Hex sitelen Lasin.  Head on over and check it out! 👍🏻 https://github.com/5ucur/hex-sitelen-lasin/

```
 ------------------------------        ------------------------------
|       Toki Pona | Tokex      |      |       Toki Pona | Tokex      |
| Latin Character | Equivalent |      | Latin Character | Equivalent |
 ------------------------------        ------------------------------
|           A / a : `A`        |      |           N / n : `9`        |
|           I / i : `1`        |      |           L / l : `7`        |
|           U / u : `2`        |      |           S / s : `5`        |
|           E / e : `E`        |      |           J / j : `4`        |
|           O / o : `6`        |      |           W / w : `3`        |
|           P / p : `B`        |      |   byte-pad with : `0`        |
|           T / t : `D`        |      |           Space : `00`       |
|           K / k : `C`        |      |         Newline : `0FF0`     |
|           M / m : `8`        |      |             "." : `0F`       |
 ------------------------------        ------------------------------

Byte-padding:
Output a 0 hexit if an the word does not end in an even number of letters.
"jan li pona." 
becomes
4A90 0071 00B6 9A0F
```
![image](https://raw.githubusercontent.com/AbbyRead/Tokex/main/examples/Tokex%20in%20Minicube64.png)
