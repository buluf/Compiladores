;first MASM code Lets bora!
;Note: declarcoes de variaveis globais devem ir no "dseg" segment:


sseg SEGMENT STACK   ;início seg. pilha  
    byte 4000h DUP(?)  ;dimensiona pilha 
sseg ENDS     ;fim seg. pilha
 
dseg SEGMENT PUBLIC         ;início seg. dados
    byte 4000h DUP(?)       ; temporários

    ; alguma declaraçõpes simples de variaveis e uso de typedef:
    integer typedef sword   ; tam == 2bytes
    char    typedef byte    ; tam == 1byte
    FarPtr  typedef dword   ;testando, ainda nao sei se necessario
    
    string1  byte "Hello world!$"    ;end 16.384D id <- Hello world!  
            byte 243 dup(?)
    string2 byte "||Ola mundo!$" 
            byte 243 dup(?)      
    
dseg ENDS

cseg    SEGMENT PUBLIC          ;inicio seg. código
        ASSUME CS:cseg, DS:dseg ; habilitar a vericação de erro para cseg,dseg


Main    proc 
;tentarei agora inicializar o segment register'dseg'

        mov ax, dseg            ; ax := dseg          
        mov ds, ax              ; ds := ax
        mov es, ax              ; es := ax


cseg ENDS

dseg SEGMENT PUBLIC
        byte "const.lex$" ;16.896D declarada um const do tipo string
        byte 246 dup(?)
dseg ENDS



cseg SEGMENT PUBLIC 
        ;iremos realizar a concatenação de duas strings
        ;e em seguida iremos printar o resultado da operacao que sera salvo no const.lex(isso sera definido pelo c, 
        ;pois poderia ser em qualquer lugar).
        ;o metodo de enderecamento que será utilizado chama-se Displacement-only(acesso direto a memoria).
        mov di, 16384D          ; loads di with string1->address       
        mov si, 16896D          ; loads si with the address of the result->address(o lugar onde voltaremos o valor da concatenação) 
        mov ax, 16640D          ; loads ax whit string2->address

        ;the style of addresing here it's going to be called indirect addressing mode
R1:     ;gerar rotulo, criarei um loop
        mov bl, ds:[di]           ;loads the bl register with a copy of the byte at memory location(di)
        add di, 1                 ;pular pro próximo byte da primeira string       
        cmp bl, 024h              ;verificar se fim da string($) se igual return 0                   
        je  R2                    ;if bl == 024h jump to R2(para concatenar a segunda string)
        mov ds:[si], bl           ;stores the value in the bl register to memory location(si).
        add si, 1                 ;pular pro próximo byte da string result_concatenacao
                                  ;usamos esse método de atribuir depois de verificar para não atribuir $ no meio da string
        jmp R1                    ;se não continue o loop
        ;obs: usamos bl por ser um registrador que se localiza na parte baixa do registrador(bx) poderia se usar al tmb
        ;gerar novo_rotulo, R2 R3        
R2:     mov di, ax              ;carregando di com a segunda string
R3:     ;começando novo loop            
        mov bl, ds:[di]         ;loads the bl register with a copy of the byte at memory location(di)
        mov ds:[si], bl         ;store the value in bl register to memory location(si)
        add di, 1               ;pular pro próximo byte da segunda string         
        add si, 1               ;pular pro próximo byte da string result_concatenacao 
        cmp bl, 024h            ;verificar se fim da string($) se igual return 0
        jne R3                  ;se nao igual continua o loop 
;fim metodo concatenação

        mov di, 16896D          ; endereco do result_concatenacao 
        mov dx, di                      
        mov ah, 09h             ; printar o valor em dx
        int 21h


Quit:   mov ah, 4ch             ;número magico para DOS
        int 21h                 ; para falar pra esse programa quitar.
Main    endp

cseg ENDS                       ;fim seg. código

end Main
