;first MASM code Lets bora!
;Note: declarcoes de variaveis globais devem ir no "dseg" segment:


sseg SEGMENT STACK   ;início seg. pilha  
    byte 4000h DUP(?)  ;dimensiona pilha 
sseg ENDS     ;fim seg. pilha
 
dseg SEGMENT PUBLIC             ;início seg. dados
    byte 4000h DUP(?)           ; temporários
    sword ?                 ;   int id <- ?
dseg ENDS

;Tentar aprender agora como meu programa acessará cada variavel acima

cseg    SEGMENT PUBLIC          ;inicio seg. código
        ASSUME CS:cseg, DS:dseg ; habilitar a vericação de erro para cseg,dseg


Main    proc 

    mov ax, dseg            ; ax := dseg          
    mov ds, ax              ; ds := ax
    mov es, ax              ; es := ax
    
    ; ============ readln_int(id) ===========
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
    mov ax, 0               ;acumulador
    mov cx, 10              ;base decimal(sera usado pra multiplicar)
    mov dx, 1               ;valor sinal +
    mov bh, 0  
    mov bl, ds:[di]         ;caractere
    cmp bx, 2Dh             ;verifica sinal(2D é o valor do negativo '-' em hexadecimal na tabela asc ii)
    jne R3                  ;se não negativo
    mov dx, -1              ;valor sinal -
    add di, 1               ;proximo valor da string
    mov bl, ds:[di]         ;bl <- proximo caracter
R3:
    push dx                 ;empilha sinal
    mov dx, 0               ;reg. multiplicação
R4:
    cmp bx, 0dh             ;verifica fim string
    je R5                   ;salta se fim string   
    imul cx                 ;mult. 10
    sub bx, 48              ;subtract 48 from ASCII value of char to get integer
    add ax, bx              ;soma valor caractere
    add di, 1               ;incrementa base
    mov bh, 0               
    mov bl, ds:[di]         ;próximo caractere
    jmp R4                  ;loop
R5:
    pop cx                  ;desempilha sinal
    imul cx                 ;mult. sinal
    mov ds:[16384], ax      ;
    ; ============  fim_readln_int() ====================

   

   
    ; ============ Write(ln) Int ou Byte ===============
    mov bx, 16384D  ; bx <- endereço do int ou byte que iremos printar
    mov ax, [bx]   ; ax <- MEM[bx] (do tamanho de um inteiro)
    ;mov ah, 0 (caso não seja inteiro e sim um byte)
    mov di, 0D ;end. string temp. 
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
  mov di, 0D
  mov dx, di 
  mov ah, 09h
  int 21h

; exibe string
Quit:   mov ah, 4ch             ;número magico para DOS
        int 21h                 ; para falar pra esse programa quitar.
Main    endp

cseg ENDS                       ;fim seg. código

end Main
