; change this to reference your copy of 64cube.inc
include /Users/abigailread/term/minicube/64cube.inc

; Testing zero page entry of Tokex words from the word list.
; Press Tab to see the debug view.  The words should pop in midway
;  down the page, with AAAA and EEEE delimiting.

; This program draws a diagonal line from x:0 y:0 to x:63 y:63
; I have it set to draw only one pixel per frame.


MACRO _setVideo page
	lda #$page
	sta VIDEO
	asl
	asl
	asl
	asl
	sta video_page
ENDM

ENUM $0
	xdisplay    db  0	; x and y coordinates in faked decimal for debug
	ydisplay    db  0
	xpos		db	0	; x and y coordinates as pure binary values
	ypos		db	0
	video_page 	db	0	; convenient for conversions to pixel address
	adrL		db	0	; pointer to an actual screen pixel address
	adrH		db	0
	value		db	0
	temp		db	0
	counter		db	0
	addToValue	db	0
ENDE

ENUM $fc
	tokexlut    dw  0
	decfakelut  dw  0
ENDE

white EQU $3f


org $200
init:
	sei	; disable interrupts
	ldx #$ff
	txs	; reset stack

	lda #$f0
	sta decfakelut + 1

	lda #$a0
	sta tokexlut + 1

	_setVideo 2
	_setw atVblank,VBLANK_IRQ
	
	; initialize adrL/H based on contents of xpos and ypos
	jsr XYposToAddress

	cli	; allow per-frame interrupts

; loop broken only by interrupts
idleLoop: 
	jmp idleLoop

; draw a pixel according to the address held in adrL/H
drawToScreen:
	lda #white
	ldx #0
	sta (adrL, x)
rts

;called once per frame
atVblank:
	jsr drawToScreen

	; move next potential pixel location down-right
	inc xpos
	inc ypos
	jsr validateXYpos	; prevent drawing outside of the screen
	jsr XYposToAddress	; prepare draw routine's input
	rti

validateXYpos
	lda xpos
	cmp #64
	bcs stopDrawing

	lda ypos
	cmp #64
	bcs stopDrawing

	ldy xpos
	jsr fakeDecimal
	sta xdisplay

	ldy ypos
	jsr fakeDecimal
	sta ydisplay
rts

stopDrawing:
	jsr insertTokex
	pla	; decrement the stack since it skips returning from subroutine
	sei	; disable interrupts to prevent more vblank interrupts
jmp idleLoop ; interrupts disabled means it just loops

addressToXYpos:
	lda adrH
	and #$0f
	sta ypos
	lda adrL
	asl
	rol ypos
	asl
	rol ypos
	lda adrL
	and #$3f
	sta xpos
rts

XYposToAddress:
	lda ypos
	sta adrH
	lda xpos
	asl
	asl
	lsr adrH
	ror
	lsr adrH
	ror
	sta adrL
	lda video_page
	ora adrH
	sta adrH
rts

fakeDecimal:			; parameter: Y, return: A
	lda (decfakelut), y
rts

insertTokex:
	ldy #0
	lda #$AA
	sta $20,y
	iny
	sta $20,y
	ldy #0

	@loop
	lda (tokexlut), y 
	sta $30, y
	iny
	lda (tokexlut), y
	cmp #$EE
	beq @end
	bne @loop
	@end
	tya ; store y
	and #$f0
	tay
	lda #$EE
	sta $40, y
	iny
	sta $40, y
rts 

org $a000
; hex A600A7A600A7E600A71600A9BA00A9DE00
; hex A92600A3E900E600E900E529001466001C
; hex E600176600195A004AC1004A96004E7600
; hex 4600CA7A00CA7A8A00CA8A00CA5100CE96
; hex 00CEBECE9600C14EDE5A9DACA72600C171
; hex 00C19600C1B15100C13E9600C600C69600
; hex C27E00C272B200C2DE007A007ABE007A56
; hex 007A3A007E96007EDE0071007171007194
; hex A60071B200764E0076960072CA0072C196
; hex 0072BA008A008A8A008A91008E71008100
; hex 86C2008671008695160082008296008251
; hex 0082DE009A9BA6009A5A009A5196009E9A
; hex 00910091810096CA0066006C6600671900
hex 69A6006BE900BACA7A00BA7100BA715A00
hex BA9600BA9A00B100B1719600B18E4A00B1
hex 9100B1B100B6CA00B6C100B69A005A8A00
hex 5E71005E76005E8E005E3100514E760051
hex CE00519600519A00519B190051DE7E9600
hex 569A00563E710052710052960052BA0052
hex 3100DA9600DA5600DA3A00DE7600DE9B66
hex 00D6C100D68600D20029BA002DA6002DA7
hex A6003A76003A96003A56003A3A003ECA00317EEEEE

org $f000
hex 00 01 02 03 04 05 06 07 08 09
hex 10 11 12 13 14 15 16 17 18 19
hex 20 21 22 23 24 25 26 27 28 29
hex 30 31 32 33 34 35 36 37 38 39
hex 40 41 42 43 44 45 46 47 48 49
hex 50 51 52 53 54 55 56 57 58 59
hex 60 61 62 63 64 65 66 67 68 69
hex 70 71 72 73 74 75 76 77 78 79
hex 80 81 82 83 84 85 86 87 88 89
hex 90 91 92 93 94 95 96 97 98 99
