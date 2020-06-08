;first MASM code Lets bora!
;Note: declarcoes de variaveis globais devem ir no "dseg" segment:


sseg SEGMENT STACK   ;início seg. pilha  
    byte 4000h DUP(?)  ;dimensiona pilha 
sseg ENDS     ;fim seg. pilha
 
dseg SEGMENT PUBLIC             ;início seg. dados
    byte 4000h DUP(?)           ; temporários
    sword 256 DUP(?)                     ; string id <- ?
dseg ENDS

;Tentar aprender agora como meu programa acessará cada variavel acima

cseg    SEGMENT PUBLIC          ;inicio seg. código
        ASSUME CS:cseg, DS:dseg ; habilitar a vericação de erro para cseg,dseg


Main    proc 

    mov ax, dseg            ; ax := dseg          
    mov ds, ax              ; ds := ax
    mov es, ax              ; es := ax
    
    ; ============ readln_string(id) ===========
    ;criar buffer para entrada(temporario do tipo caracter de tamanho 255, já q nao vamos mexer com vetor)
    mov dx, 0D              ; dx <- buffer.end
    mov al, 0FFh            ; tam do buffer (255)
    mov ds:[0D], al         ; MEM[buffer.end] <- al(tam do buffer)
    mov ah, 0Ah
    int 21h

    mov ah, 02h
    mov dl, 0Dh             
    int 21h                 
    mov dl, 0Ah
    int 21h

    mov di, 2D              ; di <- buffer.end + 2(posição do string)
    mov si, 16384D          ; si <- id.addr
R0: ;comecar loop para ler do buffer para nossa string
    mov bl, ds:[di]         ;bl <- MEM[di]
    cmp bx, 0Dh             ;verifica fim string
    je R1               
    mov ds:[si],bl     
    add di, 1               ; count buffer++
    add si, 1               ; count id++
    jmp R0            
   
R1: ;fim_loop
    mov cl, 024h        
    mov ds:[si], cl     ;MEM[si] <- $ (fim da string)
    ; ============  fim_readln_string() ====================

    ; ============ Write(ln) string ===============
  
  ;exibe string
  mov di, 16384D
  mov dx, di 
  mov ah, 09h
  int 21h

; exibe string
Quit:   mov ah, 4ch             ;número magico para DOS
        int 21h                 ; para falar pra esse programa quitar.
Main    endp

cseg ENDS                       ;fim seg. código

end Main
