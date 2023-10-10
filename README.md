# Tokex
Toki Pona's alphabet is only made up of 14 Latin characters, so I made a way to represent them all using hexadecimal digits (hexits), including representation for some punctuation/separation characters.
```
1 bit represents one binary digit (0 or 1)
1 byte = 8 bits
1 nibble = 4 bits
2 nibbles = 1 byte

Bytes are generally represented in hexadecimal, for ease of reading by human beings.
Where as decimal digits cover a range of 10 values (0 to 9), hexadecimal digits range 16 possible values.
(hexa: 6 and deci: 10 numerals)
Since we don't have more than 10 arabic numerals available to work with, A-F make up the additional 6.
0-9 and then A-F, with A-F having base values of 10-15.
A-F can also be represented in lowercase a-f, either way representing the same set of values.

As if stored in a byte of memory,
decimal value 12 in binary: 0000 1000;  in hex: 0C
decimal value 32 in binary: 0010 0000;  in hex: 20
```
Since a byte is 2 hexadecimal digits (2 nibbles of storage), every letter of the Tokex alphabet uses only half a byte.  Even the smallest, standard, plaintext representation uses 1 byte/character, minimum.  So, while you won't be able to read Tokex from a Notepad window, it is going to take up a lot less space while still being readable from a hexdump or a memory map view.

5ucur made an offshoot/alternative to Tokex called Hex sitelen Lasin.  Head on over and check it out! 👍🏻 https://github.com/5ucur/hex-sitelen-lasin/

![image](https://github.com/AbbyRead/Tokex/blob/c15dd30cc2e2f21eb22cd17ee8af7b8fdc93fada/Tokex%20in%20Minicube64.png)
| Toki Pona<br>Latin Phoneme | Tokex<br>Equivalent |
|---:|:---|
| A / a | `A` |
| I / i | `1` |
| U / u | `2` |
| E / e | `E` |
| O / o | `6` |
| P / p | `B` |
| T / t | `D` |
| K / k | `C` |
| M / m | `8` |
| N / n | `9` |
| L / l | `7` |
| S / s | `5` |
| J / j | `4` |
| W / w | `3` |
| Space | `00` |
| Newline | `0FF0` |
| "." | `0F` |
| Pad | `0` |

Use 0 to pad out a full byte if the word ends halfway through a one (words with odd-numbered letters).
Following a padded byte, use the F0 version of space if encountered, so as to distinguish it from newlines and sentence ends.
Example:
`jan li pona.` becomes
`4A90 7100 B69A 0F`
