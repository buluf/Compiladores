/**
 * 1. Nome: Leonardo Rothier Soares Cardoso  Matricula: 597690
 * 2. Nome: Henrique Hott                    Matricula: 565534
 *
 * */
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

/** 
 * *****************************************
 * ==============Headers====================
 * *****************************************
 *
 */

// Enumeracao dos tokens da linguagem
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

    // outros tokens indentificados em tempo de compilacao
    Id,
    Const,

    // enumeracoes especiais
    EndOfFile

};
// enumeracao para os tipos da lingugagem
enum Type : int
{
    Byte,
    Integer,
    Boolean,
    String,
    Undefined
};

// Fim da Enumeracao dos tokens da linguagem

// Definicao da celula da tabela de token
struct TSCell
{
    string lexeme;
    Token token;
    TSCell(string lexeme, Token token);
};

// Definicao da tabela de simbolos
class TableSymbols
{
private:
    // Estrutura std::map represetando a HashTable para o armazanamento dinanico da tabela de simbulos
    // Referencia:
    map<string, TSCell> tableSymbols;
    /** 
     * Metodo que inicia a tabela de simbulos com os tokens das palavras resevadas 
     * 
    */
    void setUp();

public:
    /** 
     * @param: string - lexeme a ser buscado na tabela 
     * @return: O ponteiro para a celula na posicao do lexeme pesquisa ou NULL 
    */
    TSCell *insert(string lexeme, TSCell element);

    /** 
     * @param: string - lexeme a ser buscado na tabela 
     * @return: O ponteiro para a celula na posicao do lexeme pesquisa ou NULL 
    */
    TSCell *search(string lexeme);

    /**
     * Imprime os elementos da tabela na saida padrao (apenas testes)
     *
     */
    void printTable();

    TableSymbols();
};

// Deficao do registrador lexico
struct LexerRegistry
{
    Token token;
    string lexeme;
    TSCell *addr;
    Type type;
    int length;
    // configurar valores do token - ids ou Keywords
    void set(Token token, string lexeme, TSCell *addr);
    // configurar valores do token - Constantes
    void set(Token token, string lexeme, Type type);
    /**
     *  Metodo para ler da entrada o proximo token valido da
     *  entrada ou reportar o primeiro erro encotrado
     * 
     */
    void nextToken();
};

// Classe do analisador lexico propriamente dito
struct Lexer
{

    /**
     *  iplementacao dos Estados do AFD 
     *  @param char: Caracter lido na entrada
     *  @param stringstream:  Lexema construido ate o momento
     * @return int: proximo estado  
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
    //static int state12(char c, stringstream &lexeme);
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

/**
 * ****************************************
 * ==========Variaveis globais=============
 * ****************************************
 * 
 */

LexerRegistry _lexreg_;
TableSymbols _tableSymbols_;
int _numLines_ = 1;

/**
 *  Implementacoes
 */

// TSCell Implementacao
TSCell::TSCell(string lexeme, Token token)
{
    this->lexeme = lexeme;
    this->token = token;
}
// Fim da TSCell Implementacao

// TableSymbols implementacao
TSCell *TableSymbols::insert(string lexeme, TSCell element)
{
    //  insert retorna: um iterador para posiciao inserida(fisrt) e um bool indicado sucesso ou falha para insercao
    //  iterador e um ponteiro com dois atributos first(key) e second(TSCell)
    return &this->tableSymbols.insert({lexeme, element}).first->second;
}

TSCell *TableSymbols::search(string lexeme)
{
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
    this->insert(",", TSCell(",", Token::Id));
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

void TableSymbols::printTable()
{
    for (map<string, TSCell>::iterator it = this->tableSymbols.begin(); it != this->tableSymbols.end(); ++it)
        cout << it->first << " " << it->second.token << "\n";
}
TableSymbols::TableSymbols()
{
    this->setUp();
}

// Fim da TableSymbols implementacao

// LexerRegistry implementecao
void LexerRegistry::nextToken()
{
    
    int state = 0; // estado inicial
    stringstream lexeme;
    char c;
    
    // ler entrada ate token reconhecido ou encontrar o primeiro erro
    while (state != 15)
    {
        // Ler caracter de entrada, se for encotrado EOF atribuir este valor ao char
        if (std::cin.get(c)){
            
            if (!Lexer::IsValid(c)) {
            
                stringstream errMsg;
                errMsg << _numLines_ << "\ncaractere invalido.\n";
                throw runtime_error(errMsg.str());
            }
        } else c = EOF; // Fim de entrada do arquivo
        
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
           // state = Lexer::state12(c, lexeme);
            break;
        case 13:
            state = Lexer::state13(c, lexeme);
            break;
        case 14:
            state = Lexer::state14(c, lexeme);
            break;
        }

    }
   // cout << _numLines_ << " ******* " << lexeme.str() << "\n";
}

void LexerRegistry::set(Token token, string lexeme, TSCell *addr)
{
    this->token = token;
    this->lexeme = lexeme;
    this->addr = addr;
    this->type = Type::Undefined;
}

void LexerRegistry::set(Token token, string lexeme, Type type)
{
    this->token = token;
    this->lexeme = lexeme;
    this->type = type;
    this->addr = NULL;
}
// Fim do LexRegistry implementecao

// Lexer implementacao

/**
 *  ESTADOS
 * 
 */
int Lexer::state0(char c, stringstream &lexeme)
{
    int nextState = 0;

    if (whitespace(c)){
        if(c == '\n')
        _numLines_++; // verificando se e uma quebra de linha 

        return nextState;
    }
        

    lexeme << c;

    if (isLetter(c))
        nextState = 1;
    else if (c == '"')
        nextState = 2;
    else if (isNumber(c) && c != '0')
        nextState = 3;
    else if (c == '0')
        nextState = 4;
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
    else if(unitKeywords(c)){
        TSCell *cell = _tableSymbols_.search(lexeme.str());
        _lexreg_.set(cell->token, cell->lexeme, cell);
        nextState = 15;
    } 
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

int Lexer::state1(char c, stringstream &lexeme)
{
    int nextState = 1;
    if (isLetter(c) || c == '_')
        lexeme << c;
    else
    {
        // buscar
        TSCell *cell = _tableSymbols_.search(lexeme.str());
        if (cell == NULL)
        {
            cell = _tableSymbols_.insert(lexeme.str(), TSCell(lexeme.str(), Token::Id)); //TODO TESTAR ISSO AQUI
        }
        else
        {
            if (cell->token == Token::Const)
                _lexreg_.set(cell->token, cell->lexeme, Type::Boolean);
            else
                _lexreg_.set(cell->token, cell->lexeme, cell);
        }
        _lexreg_.set(cell->token, cell->lexeme, cell);
        std::cin.putback(c);
        nextState = 15;
    }
    return nextState;
}

int Lexer::state2(char c, stringstream &lexeme)
{
    int nextState;
    
    if (c == EOF)
    {
        stringstream errMsg;
        errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
        throw runtime_error(errMsg.str());
    }

    if (c == '\n'){
        stringstream errMsg;
        errMsg << _numLines_ << "\nlexeme nao identificado [" << lexeme.str() << "].\n";
        throw runtime_error(errMsg.str());
    }
    else if (c == '"')
    {
        lexeme << c;
        _lexreg_.set(Token::Const, lexeme.str(), Type::String); 
        nextState = 15;
    }
    else
    {
        lexeme << c;
        nextState = 2;
    }
    
    return nextState;
}

int Lexer::state3(char c, stringstream &lexeme)
{
    int nextState = 3;

    if (isNumber(c))
    {
        lexeme << c; // se for número faz parte do lexema númerico
    }
    else
    {

        if (stoi(lexeme.str()) <= 255 || stoi(lexeme.str()) >= 0)
            _lexreg_.set(Token::Const, lexeme.str(), Type::Byte);
        else
            _lexreg_.set(Token::Const, lexeme.str(), Type::Integer);

        std::cin.putback(c);
        nextState = 15;
    }

    return nextState;
}
int Lexer::state4(char c, stringstream &lexeme)
{
    int nextState; //não tem loop no estado 4

    if (isNumber(c))
    {
        lexeme << c;
        nextState = 3; // se numero nao hex
    }
    else if (c == 'x')
    {
        lexeme << c;
        nextState = 11; // se numero for hex
    }
    else
    {
        //não é nenhum dos esperados, logo aceitamos 0 e voltamos com c pra entrada(devolver)
        //buscar
        if (stoi(lexeme.str()) <= 255 || stoi(lexeme.str()) >= 0)
            _lexreg_.set(Token::Const, lexeme.str(), Type::Byte);

        else
            _lexreg_.set(Token::Const, lexeme.str(), Type::Integer);

        std::cin.putback(c);
        nextState = 15;
    }

    return nextState;
}

int Lexer::state11(char c, stringstream &lexeme)
{
    int nextState;

    if (isHex(c))
    {
        lexeme << c;
        nextState = 11;
        if(lexeme.str().length() == 4){ // pendente
            nextState = 15; //limite 0xDD
        }
    }
    else
    {
        if(lexeme.str().length() != 4){
            if(c == EOF){
                stringstream errMsg;
                errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
                throw runtime_error(errMsg.str());
            }
            stringstream errMsg;
            errMsg << _numLines_ << "\nlexeme nao identificado [" << lexeme.str() << "].\n";
            throw runtime_error(errMsg.str());
        }
        std::cin.putback(c); // não hex, coloca o caracter de volta para leitura, e aceita o hex lido
        c = -1; // reseta c, pois voltou para entrada
        nextState = 15; // aceitar o hex que já lemos
        //henrique da o set aquiii
    }
    /*
    if (c == EOF)
    {
        stringstream errMsg;
        errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
        throw runtime_error(errMsg.str());
    }
    */

    return nextState;
}
/*
int Lexer::state12(char c, stringstream &lexeme)
{
    int nextState;

    if (c == EOF)
    {
        stringstream errMsg;
        errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
        throw runtime_error(errMsg.str());
    }

    if (isHex(c))
    {
        lexeme << c;
        _lexreg_.set(Token::Const, lexeme.str(), Type::Byte);
        nextState = 15;
    }
    else
    {
        stringstream errMsg;
        errMsg << _numLines_ << "\nlexema nao identificado [" << lexeme.str() << "].\n";
        throw runtime_error(errMsg.str());
    }
}
*/
int Lexer::state5(char c, stringstream &lexeme)
{
    int nextState = 15;

    if (c == '=')
        lexeme << c;
    else
        std::cin.putback(c);

    TSCell *cell = _tableSymbols_.search(lexeme.str());
    _lexreg_.set(cell->token, cell->lexeme, cell);

    return nextState;
}

int Lexer::state6(char c, stringstream &lexeme)
{
    int nextState = 15;

    if (c == '|')
        lexeme << c;
    else if (c == EOF)
    {
        stringstream errMsg;
        errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
        throw runtime_error(errMsg.str());
    }
    else
    {
        stringstream errMsg;
        errMsg << _numLines_ << "\nlexema nao identificado [" << lexeme.str() << "].\n";
        throw runtime_error(errMsg.str());
    }
    TSCell *cell = _tableSymbols_.search(lexeme.str());
    _lexreg_.set(cell->token, cell->lexeme, cell); // TODO TESTAR TESTAR
    return nextState;
}

int Lexer::state7(char c, stringstream &lexeme)
{
    int nextState = 15;

    if (c == '&')
        lexeme << c;
    else if (c == EOF)
    {
        stringstream errMsg;
        errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
        throw runtime_error(errMsg.str());
    }
    else
    {
        stringstream errMsg;
        errMsg << _numLines_ << "\nlexema nao identificado [" << lexeme.str() << "].\n";
        throw runtime_error(errMsg.str());
    }
    TSCell *cell = _tableSymbols_.search(lexeme.str());
    _lexreg_.set(cell->token, cell->lexeme, cell); // TODO TESTAR TESTAR

    return nextState;
}

int Lexer::state8(char c, stringstream &lexeme)
{
    int nextState = 15;
    
    if (c == '=')
        lexeme << c;
    else
        std::cin.putback(c);

    TSCell *cell = _tableSymbols_.search(lexeme.str());
    _lexreg_.set(cell->token, cell->lexeme, cell);

    return nextState;
}

int Lexer::state9(char c, stringstream &lexeme)
{
    int nextState = 15;

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

int Lexer::state10(char c, stringstream &lexeme)
{
    int nextState;

    if (c == '*'){
        lexeme.str("");
        nextState = 13;
    }    
    else{ 
        std::cin.putback(c);
        
        TSCell *cell = _tableSymbols_.search(lexeme.str());
        _lexreg_.set(cell->token, cell->lexeme, cell);
        nextState = 15;
    }
    
    return nextState;
}

int Lexer::state13(char c, stringstream &lexeme)
{
    int nextState;

    if (c == EOF)
    {
        stringstream errMsg;
        errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
        throw runtime_error(errMsg.str());
    }
    else if (c == '*')
        nextState = 14;

    else
    {
        if(c == '\n')
        _numLines_++; // verificando se e uma quebra de linha 

        nextState = 13;
    }
    return nextState;
}

int Lexer::state14(char c, stringstream &lexeme)
{
    int nextState;

    if (c == EOF)
    {
        stringstream errMsg;
        errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
        throw runtime_error(errMsg.str());
    }
    else if (c == '/')
        nextState = 0;

    else
        nextState = 13; // não fechou o comentário, volta para o estado 13

    return nextState;
}

/**
 * METODOS AUXIALIRES 
 * 
 */

bool Lexer::isLetter(char c)
{
    bool result = false;
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        result = true; // is a letter
    }

    return result;
}

bool Lexer::isNumber(char c)
{
    bool result = false;
    if(c >= '0' && c <='9'){
        result = true; // is a number
    }

    return result;
}

//para os byte que podem ser escritos na forma hex
bool Lexer::isHex(char c)
{
    bool result = false;
    if( (c >= 'A' && c <= 'F') || isNumber(c)){
        result = true; // is hex
    }

    return result;
}

bool Lexer::whitespace(char c)
{
    bool result = false;
    
    if(c == '\t' || c == '\n' || c == '\r' || c == ' '){ //todos os possiveis espacos em branco e quebra de linha
        result = true;
    }

    return result;
}

bool Lexer::unitKeywords(char c)
{
    bool result = false;

    if(c == '=' || c == '(' || c == ')' || c == ',' || c == '+' || c == '-' || c == '*' || c == ';'){
        result = true;
    }
    
    return result;
}

bool Lexer::IsValid(char c) //saber se tá na linguagem
{    
    bool extra = c == '.' || c == '\'' || c == '?' || c == ':' || c == '{' || c == '}' || c == '[' || c == ']' ||
    c == '&' || c == '_' || c == '<' || c == '>' || c == '!' || c == '/' || c == '"' || c == '|';
    //formar agora o domionio da linguagem, todas os simbolos pertecentes a ela
    return (isLetter(c) || isNumber(c) || whitespace(c) || unitKeywords(c) || extra);
}
// Fim do Lexer implementacao

int main(int argc, char const *argv[])
{
    //_tableSymbols_.printTable();
    //exit(1);
    while (_lexreg_.token != Token::EndOfFile)
    {
        try{
            _lexreg_.nextToken();
        }catch(runtime_error &e){
            cout << e.what();
            exit(0);
        }
    }
    cout << _numLines_ << " linhas compiladas.\n";
}