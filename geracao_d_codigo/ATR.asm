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
    
    string  byte "Hello world!$"    ;end 16.384D id <- Hello world!  
            byte 243 dup(?)
            
    


    
dseg ENDS

;Tentar aprender agora como meu programa acessará cada variavel acima

cseg    SEGMENT PUBLIC          ;inicio seg. código
        ASSUME CS:cseg, DS:dseg ; habilitar a vericação de erro para cseg,dseg


Main    proc 
;tentarei agora inicializar o segment register'dseg'

        mov ax, dseg            ; ax := dseg          
        mov ds, ax              ; ds := ax
        mov es, ax              ; es := ax


cseg ENDS

dseg SEGMENT PUBLIC
        byte "const.lex$" ;16.640‬D declarada um const do tipo string
dseg ENDS


cseg SEGMENT PUBLIC 
        ;agora iremos realizar a atribuição do const no id string(hello world)
        ;e em seguida iremos printar o id e ver se o valor foi alterado do id
        ;o metodo de enderecamento que será utilizado chama-se Displacement-only(acesso direto a memoria).
        mov di, 16384D          ; loads di with id->address        
        mov si, 16640D          ; lodas si whit const->address

R1:     ;gerar rotulo, criarei um loop
        mov bl, ds:[si]           ;loads the bl register with a copy of the byte at memory location(si)
        mov ds:[di], bl           ;stores the value in the bl register to memory location(di)
        add si, 1                 ;pular pro próximo byte do const
        add di, 1                 ;pular pro próximo byte do id      
        cmp bl, 024h              ;verificar se fim da string($) se igual return 0                   
        jne R1                    ;if != 0 jump to R1    
        ;obs: usamos bl por ser um registrador que se localiza na parte baixa do registrador(bx)

        mov di, 16384D          ;aponto pro endereço da string
        mov dx, di                      
        mov ah, 09h             ; printar o valor em dx
        int 21h


Quit:   mov ah, 4ch             ;número magico para DOS
        int 21h                 ; para falar pra esse programa quitar.
Main    endp

cseg ENDS                       ;fim seg. código

end Main
