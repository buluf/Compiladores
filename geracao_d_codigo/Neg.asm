;first MASM code Lets bora!
;Note: declarcoes de variaveis globais devem ir no "dseg" segment:


sseg SEGMENT STACK   ;início seg. pilha  
    byte 4000h DUP(?)  ;dimensiona pilha 
sseg ENDS     ;fim seg. pilha
 
dseg SEGMENT PUBLIC         ;início seg. dados
    byte 4000h DUP(?)       ; temporários
    byte 0h        ; bool id1 <- 1 (end. 16384D)
dseg ENDS

;Tentar aprender agora como meu programa acessará cada variavel acima

cseg    SEGMENT PUBLIC          ;inicio seg. código
        ASSUME CS:cseg, DS:dseg ; habilitar a vericação de erro para cseg,dseg


Main    proc 

    ; ============ Write(ln) Int ===========
    mov ax, dseg            ; ax := dseg          
    mov ds, ax              ; ds := ax
    mov es, ax              ; es := ax
    
    ; ============ neg() ===========
    mov ax, ds:[16384D]     ; ax <- MEM[id.address]
    ;mov ah, 0 ;(se MEM[id.address].type != integer)
    neg ax
    ;add ax, 255 ;(se MEM[id.address].type == boolean) 

    mov ds:[0D], ax ; MEM[temp.address] <- ax
    ; ============  fim_neg() ====================

    ; ============ Write(ln) Int ou Byte ===============
    mov bx, 0D  ; bx <- endereço do int ou byte que iremos printar
    mov ax, [bx]   ; ax <- MEM[bx] (do tamanho de um inteiro)
    ;mov ah, 0 (caso não seja inteiro e sim um byte)
    mov di, 2 ;end. string temp. 
    mov cx, 0 ;contador
    cmp ax, 0 ;verifica sinal(j <- ax - 0)
    jge R0 ;salta se número positivo
    mov bl, 2Dh ;senão, escreve sinal –
    mov ds:[di], bl
    add di, 1 ;incrementa índice
    neg ax ;toma módulo do número
R0:
    mov bx, 10 ;divisor
R1:
    add cx, 1 ;incrementa contador
    mov dx, 0 ;estende 32bits p/ div.
    idiv bx ;divide DXAX por BX
    push dx ;empilha valor do resto
    cmp ax, 0 ;verifica se quoc. é 0
    jne R1 ;se não é 0, continua

;agora, desemp. os valores e escreve o string
R2:
    pop dx ;desempilha valor
    add dx, 30h ;transforma em caractere
    mov ds:[di], dl ;escreve caractere
    add di, 1 ;incrementa base
    add cx, -1 ;decrementa contador
    cmp cx, 0 ;verifica pilha vazia
    jne R2 ;se não pilha vazia, loop

  ;grava fim de string
  mov dl, 024h ;fim de string
  mov ds:[di], dl ;grava '$'
  
  ;exibe string
  mov di, 2D
  mov dx, di 
  mov ah, 09h
  int 21h

; exibe string
Quit:   mov ah, 4ch             ;número magico para DOS
        int 21h                 ; para falar pra esse programa quitar.
Main    endp

cseg ENDS                       ;fim seg. código

end Main
