;first MASM code Lets bora!
;Note: declarcoes de variaveis globais devem ir no "dseg" segment:


sseg SEGMENT STACK   ;início seg. pilha  
    byte 4000h DUP(?)  ;dimensiona pilha 
sseg ENDS     ;fim seg. pilha
 
dseg SEGMENT PUBLIC         ;início seg. dados
    byte 4000h DUP(?)       ; temporários
    sword 100D         ; int id1 <- 100D (end. 16384D)
    sword -100D             ; int id2 <- 10D (end. 16386D)
dseg ENDS

;Tentar aprender agora como meu programa acessará cada variavel acima

cseg    SEGMENT PUBLIC          ;inicio seg. código
        ASSUME CS:cseg, DS:dseg ; habilitar a vericação de erro para cseg,dseg


Main    proc 
;tentarei agora inicializar o segment register'dseg'
; alocados 4bytes
    ; ============ Write(ln) Int ===========
    mov ax, dseg            ; ax := dseg          
    mov ds, ax              ; ds := ax
    mov es, ax              ; es := ax
    
    ; ============ division_intOrByte() ===========
    
    mov dx, 0 ; dx <- 0
    mov bx, 16384D ; bx <- id1.address
    mov ax, ds:[bx]   ; ax <- MEM(bx)
    ;cwd        ;(quando o numerador tiver negativo)
    ;mov ah, 0 ;(if id1 is just one byte)
    mov bx, 16386D ; bx <- id2.address
    mov bx, ds:[bx]   ; bx <- MEM(bx)
    ;mov bh, 0 ;(if id2 is just one byte)
    idiv bx         ; ax <- Quotient(id1/id2)  


    mov bx, 0D     ;bx <- temp.address
    mov [bx], ax ; MEM[temp.address] <- ax
    ; ============  fim_division() ====================

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
