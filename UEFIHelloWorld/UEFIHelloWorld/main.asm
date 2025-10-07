

; Configuration Properties > Linker > Advanced property page > Randomized Base Address property> NO
; Configuration Properties > Linker > Advanced property page > Data Execution Prevention (DEP) > NO
; 
.DATA

EFI_TABLE_HEADER STRUCT
  Signature		DQ ?

  Revision		DD ? ;08H
  HeaderSize	DD ? ;0C:
  CRC			DD ? ;10H
  Reserved		DD ? ;14H
EFI_TABLE_HEADER ENDS

SYSTEM_TABLE STRUCT
	HDR						EFI_TABLE_HEADER <?> ; 00H
	FIRMWARE_VENDOR_PTR		DQ ? ; 18H
	FIRMWARE_REVISION_PTR	DQ ? ; 20HH
	CONSOLE_INPUT_HANDLE	DQ ? ; 28H
	ConIn					DQ ? ; 30H
	CONSOLE_OUTPUT_HANDLE	DQ ? ; 38H
	ConOut					DQ ? ; 40H
	StandardErrorHandle		DQ ? ; 48H
	STD_ERR					DQ ? ; 50H
	RuntimeServices			DQ ? ; 58H
	BootServices			DQ ? ; 50
	NumberOfTableEntries	DD ? ; 58H
	ConfigurationTable		DQ ? ; 60H
SYSTEM_TABLE ENDS

TEXT_OUTPUT_INTERFACE STRUCT
	Reset				DQ	?	;00H
	OutputString		DQ	?	;08H
	TestString			DQ	?
	QueryMode			DQ	?
	SetMode				DQ	?
	SetAttribute		DQ	?
	ClearScreen			DQ	?
	SetCursorPosition	DQ	?
	EnableCursor		DQ	?
	Mode				DQ	?
TEXT_OUTPUT_INTERFACE ENDS

TEXT_INPUT_PROTOCOL STRUCT
	Reset			DQ ?	;	EFI_INPUT_RESET
	ReadKeyStroke	DQ ?	;	EFI_INPUT_READ_KEY
	WaitForKey		DQ ?	;	EFI_EVENT
TEXT_INPUT_PROTOCOL ENDS

EFI_INPUT_KEY STRUCT
	ScanKey			DW	?
	UnicodeChar		DW	?
EFI_INPUT_KEY ENDS



CONOUT DQ ?
; Pointers to System Functions
systemTable DQ ?
hImage DQ ?
szHelloWorld DW 'H','e','l','l','o',' ','W','o','r','l','d',13,10, 0
szKeyReadPrefix DW 13, 10, 'R','e','a','d',' ','t','h','e',' ','['
szKeyRead DW ' '
szKeyReadSuffix DW ']',0
szGoodByeWorld DW 13, 10, 'G','o','o','d',' ','B','y','e','!',0

.CODE

waitForKey PROC
		SUB RSP, 8
	waitForEnter_Retry:
		MOV RCX, [systemTable]
		MOV RCX, [RCX + SYSTEM_TABLE.ConIn]
		MOV RDX, RSP
		CALL QWORD PTR [ECX+TEXT_INPUT_PROTOCOL.ReadKeyStroke]
		CMP EAX, 0
		JNZ waitForEnter_Retry
		MOV AX, WORD PTR [RSP+2]
		MOV WORD PTR [szKeyRead], AX
		;CMP AL, 13
		;JNZ waitForEnter_Retry
		ADD RSP, 8
		RET
waitForKey ENDP

printString PROC
		PUSH RAX
		PUSH RCX
		PUSH RDX

		MOV RCX, [systemTable]
		MOV RCX, [RCX + SYSTEM_TABLE.ConOut]
		MOV RDX, RAX
		CALL QWORD PTR [RCX+TEXT_OUTPUT_INTERFACE.OutputString]

		POP RDX
		POP RCX
		POP RAX
		RET
printString ENDP


main PROC
		SUB RSP, 10H*8	
		mov [systemTable], RDX
		LEA RAX, [szHelloWorld]
		CALL printString

		MOV RCX, [RDX + SYSTEM_TABLE.ConOut] ; Get ConOut function address
		LEA RDX, [szHelloWorld]
		CALL QWORD PTR [RCX + TEXT_OUTPUT_INTERFACE.OutputString] ;Output String

		CALL waitForKey


		LEA RAX, [szKeyReadPrefix]
		CALL printString
		
		;MOV RCX, [systemTable]
		;MOV RCX, [RCX + SYSTEM_TABLE.ConOut]
		;LEA RDX, [szKeyReadPrefix]
		;CALL QWORD PTR [RCX+TEXT_OUTPUT_INTERFACE.OutputString]

		MOV RCX, [systemTable]
		MOV RCX, [RCX + SYSTEM_TABLE.ConOut]
		LEA RDX, [szGoodByeWorld]
		CALL QWORD PTR [RCX+TEXT_OUTPUT_INTERFACE.OutputString]

	
		MOV RCX, 1000000000H
	delay_loop:
		DEC RCX
		JNZ delay_loop
		ADD RSP, 10H*8	
		XOR RAX, RAX
		RET 

main ENDP

END