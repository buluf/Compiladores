#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/**
 *  @author Henrique Ribeiro Hott(565534)
 *  @author Leonardo Rothier Soares Cardoso(597690) 
 * 
 * 
 *  Trabalho Pratico de compiladoes parte 1 (TP1 + TP2)
 *  Disciplina: Compiladores 2020/1 
 *  Turma: Ciencia da Computacao/Manha
 * 
 *  O codigo esta divido na forma de cabecalho(conjuntos de declaracoes)
 *  e implementacao onde cada modulo do compilador possui seu header(hpp)
 *  e sua respectiva implementacao (.cpp).
 * 
 *    Sumario:
 *          - Token.hpp
 *          - Type.hpp
 *          - TableSymbols.hpp
 *          - LexRegister.hpp
 *          - Lexer.hpp
 *          - Parser.hpp
 *          - globals.cpp
 *          - TableSymbols.cpp
 *          - LexRegister.cpp
 *          - Lexer.cpp
 *          - Parser.cpp
 *          - main.cpp
 * 
 *   OBS: Para vizualizar algum modulo do trabalho pesquise no arquivo o nome 
 *        indicado sumario utilizando a ferramenta de busca de palavras
 *        de seu editor texto(caso tenha essa opcao).
 *  
 *   OBS: Os modulos .hpp contem a descricao das funcionaldiades do metodo/funcao.
 *        Ja os .cpp contem os detlahes de implementacao.
 * /



/** 
 * **********************************************
 * ===============Token.hpp======================
 * Tipo enumerado declaracao dos tokens da
 * linguagem.
 * ***********************************************
 *
 */
enum Token : int
{
    // palavras reservadas
    Final, 
    Int,  
    B,    
    Str, 
    While, 
    If, 
    Else, 
    And, 
    Or, 
    Not, 
    Attr, 
    Equal, 
    OpenParentheses, 
    CloseParentheses, 
    LessThen, 
    GreaterThen, 
    Comma, 
    NotEquals, 
    GreaterEquals, 
    LessEquals, 
    Sum, 
    Dif, 
    Multi, 
    Div, 
    EndCmd, 
    Begin, 
    Endwhile, 
    Endif, 
    Endelse, 
    Readln, 
    Write, 
    WriteLn, 
    Bool, 

    // Tokens indentificados em tempo de compilacao
    Id, 
    Const, 

    // enumeracoes especiais
    EndOfFile 

};
/** 
 * **********************************************
 * ===============Type.hpp======================
 * Tipo enumerado para declaracao dos tipos pri-
 * mivos da lingugagem L.
 * ***********************************************
 *
 */
enum Type : int
{
    Byte,
    Integer,
    Boolean,
    String,
    Undefined
};

// =================END=====================
 

/** 
 * ***********************************************
 * ==============TableSymbols.hpp==================
 * Classe para criacao da tabela simbolos.Foi uti-
 * lizado a biblioteca <map> do cojunto padrao do 
 * C++ para construcao da HashTable usada na classe.
 * ************************************************
 *
 */


// Declaracao da celula armazenada na tabela de simbolos
struct TSCell {
    string lexeme;
    Token token;
    TSCell(string lexeme, Token token);
};

// Declaracao da tabela de simbolos
class TableSymbols {
    private:
        // Estrutura std::map represetando a HashTable para o armazanamento dinanico da tabela de simbolos
        map<string, TSCell> tableSymbols;
        
        /** 
         * @brief  Metodo que inicia a tabela de simbolos com os tokens das palavras resevadas 
         * 
        */
        void setUp();

    public:
        /** 
         * @brief Insere um novo token indentificado na tabela.
         * @param: string lexema - chave na tabela.
         * @param: TSCell element  - Novo Elemento a ser inserido.
         * @return: O ponteiro para celula do novo elemento inserido.
        */
        TSCell *insert(string lexeme, TSCell element);

        /**
         * @brief Pesquisa um elemento na tabela.
         * @param: string - lexema a ser buscado na tabela .
         * @return: O ponteiro para a celula na posicao do lexeme pesquisa ou NULL. 
        */
        TSCell *search(string lexeme);

        /**
         * @brief Imprime os elementos da tabela na saida padrao (apenas testes)
         *
         */
        void printTable();

        TableSymbols();
};

// =================END=====================

/** 
 * **************************************************
 * ==================LexRegister.hpp================
 * Classe do Registrador lexico que armazena o 
 * ultimo token reconhecido.
 * **************************************************
 *
 */

struct LexRegister
{
    Token token; // Referecia ao tipo do token.
    string lexeme; // Lexema do reconhecido.
    TSCell *addr; // Ponteiro para posicao do token na tabela de simbolos (Tokens ou identificadores).
    Type type; // Tipo da constante reconhecida (apenas para constantes).
    int length; // tamanho do lexema(ainda nao usado).

    /** 
    * @brief Configura o registrador para uma keyword ou um indentificador.
    * @param: Token token - Tipo do token.
    * @param: string lexeme - lexema do token.
    * @param: TSCell* addr - ponteiro para celula elemento na tabela de simbolos.
    */
    void set(Token token, string lexeme, TSCell *addr);
    
    /** 
    * @brief Configura o registrador para uma constante.
    * @param: Token token - Tipo do token.
    * @param: string lexeme - lexema do token.
    * @param: Type type - Tipo da constante.
    */
    void set(Token token, string lexeme, Type type);
    
    /**
     *  @brief Metodo para ler o proximo token valido ou reportar o primeiro erro encotrado
     * 
     */
    void nextToken();
};

// =================END=====================

/** 
 * **************************************************
 * ====================Lexer.hpp======================
 * Classe do analisador lexico propriamente dito. 
 * Contem os estados do AFD responsavel pelo reconheci-
 * mento dos tokens na entrada.
 * ***************************************************
 *
 */


struct Lexer
{

    /**
     *  @brief Implementacao dos Estados do AFD 
     *  @param char: Caracter lido na entrada
     *  @param stringstream:  Lexema construido ate o momento
     *  @return int: proximo estado  
     */
    static int state0(char c, stringstream &lexeme);
    static int state1(char c, stringstream &lexeme);
    static int state2(char c, stringstream &lexeme);
    static int state3(char c, stringstream &lexeme);
    static int state4(char c, stringstream &lexeme);
    static int state5(char c, stringstream &lexeme);
    static int state6(char c, stringstream &lexeme);
    static int state7(char c, stringstream &lexeme);
    static int state8(char c, stringstream &lexeme);
    static int state9(char c, stringstream &lexeme);
    static int state10(char c, stringstream &lexeme);
    static int state11(char c, stringstream &lexeme);
    static int state12(char c, stringstream &lexeme);
    static int state13(char c, stringstream &lexeme);
    static int state14(char c, stringstream &lexeme);

    // metodos auxialiares
    static bool isLetter(char c);
    static bool isNumber(char c);
    static bool isHex(char c);
    static bool whitespace(char c);
    static bool unitKeywords(char c);
    static bool IsValid(char c);
};

// ====================END============================

/** 
 * **************************************************
 * ==================Parser.hpp======================
 * Classe do analisador sintatico propriamente dito. 
 * Contem as regras da gramatica em forma de procedimen-
 * tos para cada simbulos nao-terminal.
 * ***************************************************
 *
 */

struct Parser{
    /**
     *  @brief Compara um token esperado com o que existe no registrador lexico global
     *  @param: Token expected - Token epserado no registrador lexico
     */   
    static void matchToken(Token expected);

    // Regras da gramatica
    static void S(); // Start
    static void Cmd(); // Comando
    static void D(); // Declaracao
    static void A(); // Atribuicao
    static void IO(); // Entrada/Saida
    static void L(); // Loop (estrutura de repitricao)
    static void T(); // Teste
    static void C(); // Decleracao de constante
    static void Exp(); // Exepressao
    static void ExpS(); // Exepressao primeiro nivel de operadores
    static void I(); //  Exepressao segundo nivel de operadores
    static void J(); //  Exepressao terceiro nivel de operadores

};


/**
 * **************************************************
 * ==================globals.cpp=====================
 * Todas as variaveis globais devem ser
 * declaradas neste trecho.
 * *************************************************
 * 
 */

LexRegister _lexreg_;
TableSymbols _tableSymbols_;
int _numLines_ = 1;

// =================END=====================

/** 
 * **************************************************
 * ===============TableSymbols.cpp===================
 * Classe para criacao da tabela simbolos.Foi uti-
 * lizado a biblioteca <map> do cojunto padrao do 
 * C++ para construcao da HashTable usada na classe.
 * **************************************************
 *
 */


TSCell::TSCell(string lexeme, Token token)
{
    this->lexeme = lexeme;
    this->token = token;
}

TSCell *TableSymbols::insert(string lexeme, TSCell element) {
    //  insert retorna: um iterador para posiciao inserida(fisrt) e um bool indicado sucesso ou falha para insercao
    //  iterador e um ponteiro com dois atributos first(key) e second(TSCell)
    return &this->tableSymbols.insert({lexeme, element}).first->second;
}

TSCell *TableSymbols::search(string lexeme) {
    map<string, TSCell>::iterator it = this->tableSymbols.find(lexeme);
    return it != this->tableSymbols.end() ? &it->second : NULL;
}

void TableSymbols::setUp()
{
    this->insert("final", TSCell("final", Token::Final));
    this->insert("int", TSCell("int", Token::Int));
    this->insert("byte", TSCell("byte", Token::B));
    this->insert("string", TSCell("string", Token::Str));
    this->insert("while", TSCell("while", Token::While));
    this->insert("if", TSCell("if", Token::If));
    this->insert("else", TSCell("else", Token::Else));
    this->insert("&&", TSCell("&&", Token::And));
    this->insert("||", TSCell("||", Token::Or));
    this->insert("!", TSCell("!", Token::Not));
    this->insert("<-", TSCell("<-", Token::Attr));
    this->insert("=", TSCell("=", Token::Equal));
    this->insert("(", TSCell("(", Token::OpenParentheses));
    this->insert(")", TSCell(")", Token::CloseParentheses));
    this->insert("<", TSCell("<", Token::LessThen));
    this->insert(">", TSCell(">", Token::GreaterThen));
    this->insert("!=", TSCell("!=", Token::NotEquals));
    this->insert(">=", TSCell(">=", Token::GreaterEquals));
    this->insert("<=", TSCell("<=", Token::LessEquals));
    this->insert(",", TSCell(",", Token::Comma));
    this->insert("-", TSCell("-", Token::Dif));
    this->insert("+", TSCell("+", Token::Sum));
    this->insert("*", TSCell("*", Token::Multi));
    this->insert("/", TSCell("/", Token::Div));
    this->insert(";", TSCell(";", Token::EndCmd));
    this->insert("begin", TSCell("begin", Token::Begin));
    this->insert("endwhile", TSCell("endwhile", Token::Endwhile));
    this->insert("endif", TSCell("endif", Token::Endif));
    this->insert("endelse", TSCell("endelse", Token::Endelse));
    this->insert("readln", TSCell("readln", Token::Readln));
    this->insert("write", TSCell("write", Token::Write));
    this->insert("writeln", TSCell("writeln", Token::WriteLn));
    this->insert("TRUE", TSCell("TRUE", Token::Const)),
    this->insert("FALSE", TSCell("FALSE", Token::Const));
    this->insert("boolean", TSCell("boolean", Token::Bool));
}

void TableSymbols::printTable() {
    for (map<string, TSCell>::iterator it = this->tableSymbols.begin(); it != this->tableSymbols.end(); ++it)
        cout << it->first << " " << it->second.token << "\n";
}

TableSymbols::TableSymbols() {
    this->setUp();
}

// =================END==========================

/** 
 * *************************************************
 * =================LexRegister.cpp=================
 * Classe do Registrador lexico que armazena o 
 * ultimo token reconhecido.
 * *************************************************
 *
 */

void LexRegister::nextToken()
{

    int state = 0; // estado inicial
    stringstream lexeme;
    char c;

    // ler entrada ate token reconhecido (estado 15) ou encontrar o primeiro erro
    while (state != 15)
    {
        // Ler caracter de entrada, se for encotrado EOF atribuir este valor ao char
        if (std::cin.get(c))
        {
            // Verificar se o char e valido
            if (!Lexer::IsValid(c))
            {

                stringstream errMsg;
                errMsg << _numLines_ << "\ncaractere invalido.\n";
                throw runtime_error(errMsg.str());
            }
        }
        else
            c = EOF; // Fim de entrada do arquivo

        //cout << state << " ******* " << lexeme.str() << c << "\n";
        switch (state)
        {
        case 0:
            state = Lexer::state0(c, lexeme);
            break;
        case 1:
            state = Lexer::state1(c, lexeme);
            break;
        case 2:
            state = Lexer::state2(c, lexeme);
            break;
        case 3:
            state = Lexer::state3(c, lexeme);
            break;
        case 4:
            state = Lexer::state4(c, lexeme);
            break;
        case 5:
            state = Lexer::state5(c, lexeme);
            break;
        case 6:
            state = Lexer::state6(c, lexeme);
            break;
        case 7:
            state = Lexer::state7(c, lexeme);
            break;
        case 8:
            state = Lexer::state8(c, lexeme);
            break;
        case 9:
            state = Lexer::state9(c, lexeme);
            break;
        case 10:
            state = Lexer::state10(c, lexeme);
            break;
        case 11:
            state = Lexer::state11(c, lexeme);
            break;
        case 12:
            state = Lexer::state12(c, lexeme);
            break;
        case 13:
            state = Lexer::state13(c, lexeme);
            break;
        case 14:
            state = Lexer::state14(c, lexeme);
            break;
        }
    }
    //cout << _numLines_ << " ++++++++ " << lexeme.str() << "\n";
}

void LexRegister::set(Token token, string lexeme, TSCell *addr)
{
    this->token = token;
    this->lexeme = lexeme;
    this->addr = addr;
    this->type = Type::Undefined;
}

void LexRegister::set(Token token, string lexeme, Type type)
{
    this->token = token;
    this->lexeme = lexeme;
    this->type = type;
    this->addr = NULL;
}


/** 
 * **************************************************
 * ===================Lexer.cpp=======================
 * Classe do analisador lexico propriamente dito. 
 * Contem os estados do AFD responsavel pelo reconheci-
 * mento dos tokens na entrada.
 * **************************************************
 *
 */


/**
 *  ESTADOS
 * 
 */

int Lexer::state0(char c, stringstream &lexeme) {
    int nextState = 0;

    // Se for branco continua realizando 0 sem acrescentar ao lexema
    if (whitespace(c))
    {
        if (c == '\n')
            _numLines_++; // verificando se e uma quebra de linha

        return nextState;
    } 

    lexeme << c;
    // Identficador
    if (isLetter(c) || c == '_')
        nextState = 1;
    
    //Constante String
    else if (c == '"')
        nextState = 2;
    
    // Constantes numericas
    else if (isNumber(c) && c != '0')
        nextState = 3; 
    else if (c == '0')
        nextState = 4;
    
    // Palavras Reservadas derivadas de um char
    else if (c == '!')
        nextState = 5;
    else if (c == '|')
        nextState = 6;
    else if (c == '&')
        nextState = 7;
    else if (c == '>')
        nextState = 8;
    else if (c == '<')
        nextState = 9;
    else if (c == '/')
        nextState = 10;
    
    // Palavra Reservada formada um por um unico char
    else if (unitKeywords(c))
    {
        TSCell *cell = _tableSymbols_.search(lexeme.str());
        _lexreg_.set(cell->token, cell->lexeme, cell);
        nextState = 15;
    }

    // Entende-se que ao achar EOF no estado 0 todas o arquivo tece
    // todos os tokens reconhecidos corretamente.
    else if (c == EOF)
    {
        _lexreg_.set(Token::EndOfFile, "", NULL);
        cin.putback(c);
        nextState = 15;
    }
    else
    {

        stringstream errMsg;
        errMsg << _numLines_ << "\nlexema nao identificado [" << lexeme.str() << "].\n";
        throw runtime_error(errMsg.str());
    }

    return nextState;
}


int Lexer::state1(char c, stringstream &lexeme) {
    int nextState = 1;
    // Equanto for uma letra, digito ou sublinhado continuar no estado 1 e adcionar char lido ao lexema.
    if (isLetter(c) || isNumber(c) || c == '_')
        lexeme << c;

    else {
        // Senao buscar na tabela de simbulos ou inserir o lexema caso nao seja encontrado
        TSCell *cell = _tableSymbols_.search(lexeme.str());
        if (cell == NULL) {
            cell = _tableSymbols_.insert(lexeme.str(), TSCell(lexeme.str(), Token::Id)); //TODO TESTAR ISSO AQUI
        
        } 
        else {
            if (cell->token == Token::Const)
                _lexreg_.set(cell->token, cell->lexeme, Type::Boolean);
            else
                _lexreg_.set(cell->token, cell->lexeme, cell);
        }
        
        _lexreg_.set(cell->token, cell->lexeme, cell);
        std::cin.putback(c); // Devolver o char para leitura novamente
        nextState = 15;
    
    }
    return nextState;
}

int Lexer::state2(char c, stringstream &lexeme)
{
    int nextState;

    // Encotrado um fim de arquivo antes de ter a string corretamente fechada
    if (c == EOF)
    {
        stringstream errMsg;
        errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
        throw runtime_error(errMsg.str());
    }

    // Caracter invalido para string.
    if (c == '\n')
    {
        stringstream errMsg;
        errMsg << _numLines_ << "\nlexema nao identificado [" << lexeme.str() << "].\n";
        throw runtime_error(errMsg.str());
    }
    
    // Crescer lexema
    lexeme << c;
    nextState = 2; // Continuar no estado 2 ate achar aspas

    // Fim da constante string
    if (c == '"')
    {
        _lexreg_.set(Token::Const, lexeme.str(), Type::String);
        nextState = 15;
    }

    return nextState;
}

int Lexer::state3(char c, stringstream &lexeme)
{
    int nextState = 3; // Continuar no estado 3 enquanto achar digito

    if (isNumber(c)) {
        lexeme << c; // Crescer lexema caso seja um numero
    }
    else {
        // Configurar o registrador lexico de acordo com o valor das constante
        if (stoi(lexeme.str()) <= 255 || stoi(lexeme.str()) >= 0)
            _lexreg_.set(Token::Const, lexeme.str(), Type::Byte);
        else
            _lexreg_.set(Token::Const, lexeme.str(), Type::Integer);

        std::cin.putback(c); // Devolver o char para leitura novamente
        nextState = 15;
    }

    return nextState;
}
int Lexer::state4(char c, stringstream &lexeme)
{
    int nextState; // nao tem loop no estado 4

    if (isNumber(c)){
        lexeme << c;
        nextState = 3; // se numero nao hex vai para o estado 3
    
    } else if (c == 'x'){
        lexeme << c;  
        nextState = 11; // se for uma notacao para Hex ir para o estado 11
    
    } else {
        //Senao aceitar 0 como digito
        _lexreg_.set(Token::Const, lexeme.str(), Type::Byte);
        std::cin.putback(c); // Desvolver char lido
        nextState = 15;
    }

    return nextState;
}

int Lexer::state11(char c, stringstream &lexeme) {
    int nextState = 12; // Ir para o estado 12 para reconhecimento do proximo digito hex 

    // Fim de arquivo encontrado antes do lexema hexadecimal ser corretamente escrito
    if (c == EOF) {
        stringstream errMsg;
        errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
        throw runtime_error(errMsg.str());
    }

    // A entrada nao corresponde a um digito hexadecimal, nao podendo ser considerado um lexema valido 
    else if (!isHex(c)) {
        stringstream errMsg;
        errMsg << _numLines_ << "\nlexema nao identificado [" << lexeme.str() << "].\n";
        throw runtime_error(errMsg.str());
    }
    
    lexeme << c; // Crescer lexema
    
    return nextState;
}

int Lexer::state12(char c, stringstream &lexeme)
{
       
    int nextState = 15; // Estado final
    
    // Fim de arquivo encontrado antes do lexema hexadecimal ser corretamente escrito
    if (c == EOF){
        stringstream errMsg;
        errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
        throw runtime_error(errMsg.str());
    }
    
    // A entrada nao corresponde a um digito hexadecimal, nao podendo ser considerado um lexema valido 
    if (!isHex(c)) {
        stringstream errMsg;
        errMsg << _numLines_ << "\nlexema nao identificado [" << lexeme.str() << "].\n";
        throw runtime_error(errMsg.str());
    }
    
    lexeme << c; // Crescer lexema
    // Lexema corretamente reconhecido
    _lexreg_.set(Token::Const, lexeme.str(), Type::Byte);
    
    return nextState;
}

int Lexer::state5(char c, stringstream &lexeme) {
    int nextState = 15; // Estado final
    
    // Se o char for '=' crescer o lexema, senao devolver o char para analise do proximo token
    if (c == '=')
        lexeme << c;
    else
        std::cin.putback(c);

    // Buscar a palavra reservada correspondente
    TSCell *cell = _tableSymbols_.search(lexeme.str());
    _lexreg_.set(cell->token, cell->lexeme, cell);

    return nextState;
}

int Lexer::state6(char c, stringstream &lexeme) {
    int nextState = 15; // Estado final

    // Fim de arquivo encontrado, antes de completar a palavra reservada
    if (c == EOF) {
        stringstream errMsg;
        errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
        throw runtime_error(errMsg.str());
    }
    // Se nao for a segunda | do lexema || o lexema sera considerado invalido
    if(c != '|') {
        stringstream errMsg;
        errMsg << _numLines_ << "\nlexema nao identificado [" << lexeme.str() << "].\n";
        throw runtime_error(errMsg.str());
    }
    
    lexeme << c; // Crescer lexema
    // Buscar palavra reservada
    TSCell *cell = _tableSymbols_.search(lexeme.str());
    _lexreg_.set(cell->token, cell->lexeme, cell);
    
    return nextState;
}

int Lexer::state7(char c, stringstream &lexeme) {
    int nextState = 15; // Estado final
    
    // Fim de arquivo encontrado, antes de completar a palavra reservada
    if (c == EOF){
        stringstream errMsg;
        errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
        throw runtime_error(errMsg.str());
    }
    
    // Se nao for a segunda & do lexema && o lexema sera considerado invalido
    if(c != '&'){
        stringstream errMsg;
        errMsg << _numLines_ << "\nlexema nao identificado [" << lexeme.str() << "].\n";
        throw runtime_error(errMsg.str());
    }
    
    lexeme << c; // Crescer lexema
    // Buscar palavra reservada
    TSCell *cell = _tableSymbols_.search(lexeme.str());
    _lexreg_.set(cell->token, cell->lexeme, cell);
    
    return nextState;
}

int Lexer::state8(char c, stringstream &lexeme) {
    int nextState = 15; // Estado final
    
    // Se o char for '=' crescer o lexema, senao devolver o char para analise do proximo token
    if (c == '=')
        lexeme << c; 
    else
        std::cin.putback(c);

    // Buscar o lexema correspodente
    TSCell *cell = _tableSymbols_.search(lexeme.str());
    _lexreg_.set(cell->token, cell->lexeme, cell);

    return nextState;
}

int Lexer::state9(char c, stringstream &lexeme) {
    int nextState = 15; // Estado final

    // Se o char for '=' '-' ou crescer o lexema, senao devolver o char para analise do proximo token
    if (c == '=')
        lexeme << c;
    else if (c == '-')
        lexeme << c;
    else
        std::cin.putback(c);

    TSCell *cell = _tableSymbols_.search(lexeme.str());
    _lexreg_.set(cell->token, cell->lexeme, cell);

    return nextState;
}

int Lexer::state10(char c, stringstream &lexeme) {
    int nextState; // Vai para estado 13 casi seja um comentario
                   // Senao devolve a palavra reservada '/'

    if (c == '*')
    {
        lexeme.str(""); // Limpa lexema
        nextState = 13;
    }
    else {
        std::cin.putback(c); // Devolve o char para a proxima analise
        // Buscar palavra reservada
        TSCell *cell = _tableSymbols_.search(lexeme.str());
        _lexreg_.set(cell->token, cell->lexeme, cell);
        nextState = 15;
    }

    return nextState;
}

int Lexer::state13(char c, stringstream &lexeme) {
    int nextState; // Se for '*' mandar para o estado 14 para verificar fim de comentario
                   // Senao continua no estado 13

    // Fim de arquivo encotrado antes de de fechar o comentario
    if (c == EOF) {
        stringstream errMsg;
        errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
        throw runtime_error(errMsg.str());
    }

    else if (c == '*')
        nextState = 14;
    else{
        if (c == '\n')
            _numLines_++; // verificando se e uma quebra de linha

        nextState = 13;
    }

    return nextState;
}

int Lexer::state14(char c, stringstream &lexeme)
{
    int nextState; // Caso comentario seja fechado com a '/' voltar para o estado 0
                   // senao retornar ao estado 13
    
    // Fim de arquivo encotrado antes de de fechar o comentario
    if (c == EOF){
        stringstream errMsg;
        errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
        throw runtime_error(errMsg.str());
    }
    
    if (c == '/')
        nextState = 0;
    else if(c == '*'){  
        nextState = 14;
    }
    else{
        if (c == '\n')
            _numLines_++; // verificando se e uma quebra de linha
        nextState = 13; // não fechou o comentário, volta para o estado 13
    }
    
    return nextState;
}

/**
 * METODOS AUXIALIRES 
 * 
 */

bool Lexer::isLetter(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool Lexer::isNumber(char c) {
    return (c >= '0' && c <= '9');
}

bool Lexer::isHex(char c) {
    return ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || isNumber(c));
}

bool Lexer::whitespace(char c) {
    return (c == '\t' || c == '\n' || c == '\r' || c == ' ');
}

bool Lexer::unitKeywords(char c) {
    return (c == '=' || c == '(' || c == ')' || c == ',' || c == '+' || c == '-' || c == '*' || c == ';');
}

bool Lexer::IsValid(char c) {
    bool extra = c == '.' || c == '\'' || c == '?' || c == ':' || c == '{' || c == '}' || c == '[' || c == ']' ||
                 c == '&' || c == '_' || c == '<' || c == '>' || c == '!' || c == '/' || c == '"' || c == '|';
    
    //formar agora o domionio da linguagem, todas os simbolos pertecentes a ela
    return (isLetter(c) || isNumber(c) || whitespace(c) || unitKeywords(c) || extra);
}

// =================END=====================

/** 
 * *************************************************
 * ====================Parser.cpp===================
 * Classe do analisador sintatico propriamente dito. 
 * Contem as regras da gramatica em forma de procedimen-
 * tos para cada simbulos nao-terminal.
 * *************************************************
 *
 */

void Parser::matchToken(Token expected) {
    //cout << "Esperado:" << expected << " Tenho: " << _lexreg_.token << "| Lex: " <<  _lexreg_.lexeme << "| Linha: " << _numLines_ << "\n"; 
    if (_lexreg_.token == expected)
        _lexreg_.nextToken();

    // Fim de arquivo encotrando antes do fim parse
    else if (_lexreg_.token == Token::EndOfFile) {
        stringstream errMsg;
        errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
        throw runtime_error(errMsg.str());
    }
    // Token nao esperado
    else
    {
        stringstream errMsg;
        errMsg << _numLines_ << "\ntoken nao esperado [" << _lexreg_.lexeme << "].\n";
        throw runtime_error(errMsg.str());
    }
}

void Parser::S()
{
    //cout << "ENTREI NO S\n";

    // Equanto _lexreg_.token pertece a FISRT(S) Repita CmD
    while (_lexreg_.token == Token::EndCmd ||
           _lexreg_.token == Token::Bool || _lexreg_.token == Token::Str || _lexreg_.token == Token::Int || _lexreg_.token == Token::B ||
           _lexreg_.token == Token::Readln || _lexreg_.token == Token::Write || _lexreg_.token == Token::WriteLn ||
           _lexreg_.token == Token::While ||
           _lexreg_.token == Token::If ||
           _lexreg_.token == Token::Id ||
           _lexreg_.token == Token::Final)
    {Cmd();}
}
// Regra de Comando
void Parser::Cmd() {
    //cout << "ENTREI NO Cmd\n";
    // Executa regra de comando correspondente ao FIRST(CmD)
    if (_lexreg_.token == Token::EndCmd) 
        matchToken(Token::EndCmd);
    else if (_lexreg_.token == Token::Bool || _lexreg_.token == Token::Str || _lexreg_.token == Token::Int || _lexreg_.token == Token::B)
        D();
    else if (_lexreg_.token == Token::Id) 
        A();
    else if (_lexreg_.token == Token::Readln || _lexreg_.token == Token::Write || _lexreg_.token == Token::WriteLn) 
        IO();
    else if (_lexreg_.token == Token::While) 
        L();
    else if (_lexreg_.token == Token::If)
        T();
    else 
        C();
}

// Regra de declaracao
void Parser::D() {
    //cout << "ENTREI NO D\n";
    // Verificar Token do tipo
    if (_lexreg_.token == Token::Bool)
        matchToken(Token::Bool);
    else if (_lexreg_.token == Token::Str)
        matchToken(Token::Str);
    else if (_lexreg_.token == Token::Int)
        matchToken(Token::Int);
    else
        matchToken(Token::B);

    matchToken(Token::Id); 
    
    // Caso _lexreg_.token tem um sinal de atribuicao realizar a verificao para constante
    if (_lexreg_.token == Token::Attr) {
        
        matchToken(Token::Attr);
        // Teste de sinal na constante
        if (_lexreg_.token == Token::Dif)
            matchToken(Token::Dif);
        
        matchToken(Token::Const);
    }

    // Repetir enquanto _lexreg_.token  e igual a ','
    while (_lexreg_.token == Token::Comma)  {
        // Declaracao de outro Identificador
        matchToken(Token::Comma);
        matchToken(Token::Id);
        // Caso _lexreg_.token tem um sinal de atribuicao realizar a verificao para constante
        if (_lexreg_.token == Token::Attr)
        { 
            matchToken(Token::Attr);
            if (_lexreg_.token == Token::Dif)
                matchToken(Token::Dif);

            matchToken(Token::Const);
        }
    }

    matchToken(Token::EndCmd);
}

// Regra de atribuicao
void Parser::A()
{
    //cout << "ENTREI NO A\n";
    matchToken(Token::Id);
    matchToken(Token::Attr);
    Exp(); // Expressao a ser atribuida ao identificador
    matchToken(Token::EndCmd);
}

// Regra de escrita
void Parser::IO() {   
    //  _lexreg_.token  corresponde ao inicio do comando de leitura
    if (_lexreg_.token == Token::Readln) {
        matchToken(Token::Readln);
        matchToken(Token::OpenParentheses);
        matchToken(Token::Id);
        matchToken(Token::CloseParentheses);
        matchToken(Token::EndCmd);
    }
    else if (_lexreg_.token == Token::Write) {
        //  _lexreg_.token  corresponde ao inicio do comando de escrita sem quebra de linha
        matchToken(Token::Write);
        matchToken(Token::OpenParentheses);
        Exp();
        
        // Equanto _lexreg_.token  igual ',' repita
        while (_lexreg_.token == Token::Comma) {
            // Outra expressao para ser realizada
            matchToken(Token::Comma);
            Exp();
        }
        
        matchToken(Token::CloseParentheses);
        matchToken(Token::EndCmd);
    }
    else {
       
//  _lexreg_.token  corresponde ao inicio do comando de escrita com quebra de linha
        matchToken(Token::WriteLn);
        matchToken(Token::OpenParentheses);
        Exp();

        // Equanto _lexreg_.token  igual ',' repita
        while (_lexreg_.token == Token::Comma) {
            // Outra expressao para ser realizada
            matchToken(Token::Comma);
            Exp();
        }

        matchToken(Token::CloseParentheses);
        matchToken(Token::EndCmd);
    }
}

void Parser::L() {
    matchToken(Token::While);
    matchToken(Token::OpenParentheses);
    Exp();
    matchToken(Token::CloseParentheses);
    
    // Se _lexreg_.token for Begin, espera-se uma sequencia de 0 ou mais comandos
    // Senao espera-se apenas um comando
    if (Token::Begin) {
        matchToken(Token::Begin);

        // Enqunato Token pertencer a FISRT(C) repita
        while (_lexreg_.token == Token::EndCmd ||
               _lexreg_.token == Token::Bool || _lexreg_.token == Token::Str || _lexreg_.token == Token::Int || _lexreg_.token == Token::B ||
               _lexreg_.token == Token::Readln || _lexreg_.token == Token::Write || _lexreg_.token == Token::WriteLn ||
               _lexreg_.token == Token::While ||
               _lexreg_.token == Token::If ||
               _lexreg_.token == Token::Id ||
               _lexreg_.token == Token::Final)
        {Cmd();}
        matchToken(Token::Endwhile);
    }
    else
        Cmd();
}

// Regra de Teste
void Parser::T() {
    matchToken(Token::If);
    matchToken(Token::OpenParentheses);
    Exp();
    matchToken(Token::CloseParentheses);

    // Se _lexreg_.token for Begin, espera-se uma sequencia de 0 ou mais comandos
    // Senao espera-se apenas um comando
    if (_lexreg_.token == Token::Begin) {
        matchToken(Token::Begin);

        // Enqunato Token pertencer a FISRT(C) repita
        while (_lexreg_.token == Token::EndCmd ||
               _lexreg_.token == Token::Bool || _lexreg_.token == Token::Str || _lexreg_.token == Token::B ||
               _lexreg_.token == Token::Readln || _lexreg_.token == Token::Write || _lexreg_.token == Token::WriteLn ||
               _lexreg_.token == Token::While ||
               _lexreg_.token == Token::If ||
               _lexreg_.token == Token::Id ||
               _lexreg_.token == Token::Final)
        {Cmd();}
        matchToken(Token::Endif);
    } 
    else
        Cmd();
    

    // Se encontrado um  Else
    if (_lexreg_.token == Token::Else) {
        matchToken(Token::Else);
        // Se _lexreg_.token for Begin, espera-se uma sequencia de 0 ou mais comandos
        // Senao espera-se apenas um comando
        if (_lexreg_.token == Token::Begin) {
            matchToken(Token::Begin);

            // Enqunato Token pertencer a FISRT(C) repita
            while (_lexreg_.token == Token::EndCmd ||
                   _lexreg_.token == Token::Bool || _lexreg_.token == Token::Str || _lexreg_.token == Token::Int || _lexreg_.token == Token::B ||
                   _lexreg_.token == Token::Readln || _lexreg_.token == Token::Write || _lexreg_.token == Token::WriteLn ||
                   _lexreg_.token == Token::While ||
                   _lexreg_.token == Token::If ||
                   _lexreg_.token == Token::Id ||
                   _lexreg_.token == Token::Final)
            {Cmd();}
            matchToken(Token::Endelse);
        }
        else
            Cmd();
    }
}

// Regra de constante
void Parser::C() {
    matchToken(Token::Final);
    matchToken(Token::Id);
    matchToken(Token::Attr);
    // Verificar se existe sinal na constante
    if (_lexreg_.token == ::Dif)
        matchToken(Token::Dif);

    matchToken(Token::Const);
    matchToken(Token::EndCmd);
}

// Regra da expressao
void Parser::Exp(){
    
    ExpS();
    // Enquanto '>', '<', '<=', '>=' ou '=' realizar nova expressao para ser comparada
    while(_lexreg_.token == Token::Equal ||_lexreg_.token == Token::NotEquals || _lexreg_.token == Token::GreaterThen || 
       _lexreg_.token == Token::LessThen || _lexreg_.token == Token::GreaterEquals ||  _lexreg_.token == Token::LessEquals) {
        
        if(_lexreg_.token == Token::Equal) matchToken(Token::Equal);
        else if(_lexreg_.token == Token::NotEquals)  matchToken(Token::NotEquals);
        else if(_lexreg_.token == Token::GreaterThen) matchToken(Token::GreaterThen);   
        else if (_lexreg_.token == Token::LessThen) matchToken(Token::LessThen);
        else if (_lexreg_.token == Token::GreaterEquals) matchToken(Token::GreaterEquals);
        else matchToken(Token::LessThen);

        ExpS();
    }
}

// Regra do primeiro nivel de precedencia
void Parser::ExpS(){
    // Precidencia no primeiro operador
    if(_lexreg_.token == Token::Sum ||_lexreg_.token == Token::Dif){
        if(_lexreg_.token == Token::Sum) matchToken(Token::Sum);
        else matchToken(Token::Dif);
    }
    
    I(); 
    // Enquanto '+', '-' ou '||' realizar a opercao com a segunda expressao
    while(_lexreg_.token == Token::Sum ||_lexreg_.token == Token::Dif || _lexreg_.token == Token::Or) {
        // Match token
        if(_lexreg_.token == Token::Sum) matchToken(Token::Sum);
        else if(_lexreg_.token == Token::Dif)  matchToken(Token::Dif);
        else matchToken(Token::Or);

        I();
    }

}

// Regra do segundo nivel de precedencia
void Parser::I(){
    
    J(); 
    // Enquanto '*', '/' ou '&&' realizar a opercao com a segunda expressao
    while(_lexreg_.token == Token::Multi ||_lexreg_.token == Token::Div || _lexreg_.token == Token::And) {
        // Match token
        if(_lexreg_.token == Token::Multi) matchToken(Token::Multi);
        else if(_lexreg_.token == Token::Div)  matchToken(Token::Div);
        else matchToken(Token::And);

        J();
    }
}
// Regra do terceiro nivel de precedencia
void Parser::J(){
    //cout << "ENTREI NO J\n";
    // Buscar operacap
    if(_lexreg_.token == Token::Not) {
        matchToken(Token::Not);
        J();
    }
    else if(_lexreg_.token == Token::OpenParentheses){  
        matchToken(Token::OpenParentheses);
        Exp();
        matchToken(Token::CloseParentheses);
    }
    else if(_lexreg_.token == Token::Id) 
        matchToken(Token::Id);
    else {
        matchToken(Token::Const);
    }
}
// =================END=====================


/** 
 * ***************************************************
 * ===================main.cpp=======================
 * Modulo contendo a chamada principal do programa
 * de compilcacao.
 * ***************************************************
 *
 */

// TESTE DO ANALISADOR SINTATICO + LEXICO
int main(int argc, char const *argv[]){
    
    try{
        _lexreg_.nextToken();
        Parser::S();
        if(cin.peek() != EOF){
            cout <<  _numLines_ << "\ntoken nao esperado [" << _lexreg_.lexeme << "].\n";
            exit(1);
        }
    } catch(runtime_error &e){
        cout << e.what();
        exit(1);
    }

     cout << _numLines_ << " linhas compiladas.\n";
}


/*
// TESTE DO ANALISADOR LEXICO APENAS
int main(int argc, char const *argv[])
{
    //_tableSymbols_.printTable();
    //exit(1);
    while (_lexreg_.token != Token::EndOfFile)
    {
        try
        {
            _lexreg_.nextToken();
        }
        catch (runtime_error &e)
        {
            cout << e.what();
            exit(0);
        }
    }
    cout << _numLines_ << " linhas compiladas.\n";
}
*/

// =================END=====================