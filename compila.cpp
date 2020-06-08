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
  Writeln,
  Bool,

  // Tokens indentificados em tempo de compilacao
  Id,
  Const,

  // enumeracoes especiais
  EndOfFile,
  None

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

/** 
 * **********************************************
 * ===============Class.hpp======================
 * Tipo enumerado para declaracao dos tipos pri-
 * mivos da lingugagem L.
 * ***********************************************
 *
 */
enum Class : int
{
  VarClass,
  ConstClass,
  Empty
};

// =================END=====================

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
struct TSCell
{
  string lexeme;
  Token token;
  Class cl;
  int addr;
  int length;
  Type type;
  TSCell(string lexeme, Token token);
};

// Declaracao da tabela de simbolos
class TableSymbols
{
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
  Token token;   // Referecia ao tipo do token.
  string lexeme; // Lexema do reconhecido.
  TSCell *addr;  // Ponteiro para posicao do token na tabela de simbolos (Tokens ou identificadores).
  Type type;     // Tipo da constante reconhecida (apenas para constantes).
  int length;    // tamanho do lexema(ainda nao usado).

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

struct Parser
{
  /**
     *  @brief Compara um token esperado com o que existe no registrador lexico global
     *  @param: Token expected - Token epserado no registrador lexico
  */
  static void matchToken(Token expected);

  // Regras da gramatica
  static void S();                                 // Start
  static void Cmd();                               // Comando
  static void D();                                 // Declaracao
  static void A();                                 // Atribuicao
  static void IO();                                // Entrada/Saida
  static void L();                                 // Loop (estrutura de repitricao)
  static void T();                                 // Teste
  static void C();                                 // Decleracao de constante
  static void Exp(Type &ExpType, int &ExpAddr);    // Exepressao
  static void ExpS(Type &ExpSType, int &ExpSAddr); // Exepressao primeiro nivel de operadores
  static void I(Type &IType, int &Iaddr);          //  Exepressao segundo nivel de operadores
  static void J(Type &JType, int &Jaddr);          //  Exepressao terceiro nivel de operadores
};
/** 
 * **************************************************
 * ==================codeGen.hpp======================
 * 
 * ***************************************************
 *
 */

struct CodeGen
{
  static void start();
  static void start_dseg();
  static void create_sseg();
  static void end_dseg();
  static void init_cseg();
  static void start_cseg();
  static void end_cseg();
  static void end();

  static int new_tmp(Type type);
  static void reset_tmp();
  static void new_line();
  static int alloc_id(Type idType, string constLex);
  static int alloc_const(string constLex, Type constType);

  static int new_label();
  static void write_label(int label);

  static int write_I(int Jaddr, int J1Addr, Type Jtype, Type J1Type, Type Itype, Token op);
  static int write_ExpS(int Iaddr, int I1addr, Type IType, Type I1type, Type ExpStype, Token op);
  static int write_Exp(int ExPSAddr, int ExPS1Addr, Type ExpSType, Type ExS1Type, Type ExpType, Token op);
  static int write_neg(int addr, Type type);

  static void assign(int targetAddr, int sourceAddr, Type addrType);
  static void write_while(int ExpAddr,int labelEnd);
  static void write_end_while(int labelBegin, int labelEnd);
  static void write_if(int ExpAddr, int labelFalse);
  static void write_if_end(int labelEnd);
  static void write_ln(int addr, Type type);
  static void write_output(int addr, Type type);
  static void read_ln(int idAddr, Type Idtype);
  static void read_int(int idAddr);
  static void read_string(int idAddr);
};

/** 
 * **************************************************
 * ==================writer.hpp======================
 * Classe responsavel por escrever o arquivo com o 
 * codigo assembly gerado
 * ***************************************************
 *
 */
class Writer
{
private:
  ofstream buffer; // Buffer de escrita

public:
  /**
    *  @brief Abre o arquivo de escrita o assembly code gerado
  */
  void open();

  /**
    *  @brief Escreve uma linha no arquivo de codigo assembly
    *  @param: string: String a ser escrita no arquivo
  */
  void writeln(string str);

  /**
    *  @brief Fecha o arquivo gerado
  */
  void close();
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
Writer writer;
int _numLines_ = 1;
int _labels_ = 0;
int _local_ = 16384; //localização na memória depois dos temp.
int _temp_ = 0;

// ======================END=============================

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
  this->addr = -1;
  this->cl = Class::Empty;
  this->type = Type::Undefined;
}

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
  this->insert("writeln", TSCell("writeln", Token::Writeln));
  this->insert("TRUE", TSCell("TRUE", Token::Const));
  this->insert("FALSE", TSCell("FALSE", Token::Const));
  this->insert("boolean", TSCell("boolean", Token::Bool));
}

void TableSymbols::printTable()
{
  for (map<string, TSCell>::iterator it = this->tableSymbols.begin(); it != this->tableSymbols.end(); ++it)
    std::cout << it->first << " " << it->second.token << "\n";
}

TableSymbols::TableSymbols()
{
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
        remove("file.asm");
        stringstream errMsg;
        errMsg << _numLines_ << "\ncaractere invalido.\n";
        throw runtime_error(errMsg.str());
      }
    }
    else
      c = EOF; // Fim de entrada do arquivo

    //std::cout << state << " ******* " << lexeme.str() << c << "\n";
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
  //std::cout << _numLines_ << " ++++++++ " << lexeme.str() << "\n";
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

int Lexer::state0(char c, stringstream &lexeme)
{
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
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\nlexema nao identificado [" << lexeme.str() << "].\n";
    throw runtime_error(errMsg.str());
  }

  return nextState;
}

int Lexer::state1(char c, stringstream &lexeme)
{
  int nextState = 1;
  // Equanto for uma letra, digito ou sublinhado continuar no estado 1 e adcionar char lido ao lexema.
  if (isLetter(c) || isNumber(c) || c == '_')
    lexeme << c;

  else
  {
    // Senao buscar na tabela de simbulos ou inserir o lexema caso nao seja encontrado
    TSCell *cell = _tableSymbols_.search(lexeme.str());
    if (cell == NULL)
    {
      cell = _tableSymbols_.insert(lexeme.str(), TSCell(lexeme.str(), Token::Id));
      _lexreg_.set(cell->token, cell->lexeme, cell);
    }
    else
    {

      if (cell->token == Token::Const)
      {
        _lexreg_.set(cell->token, cell->lexeme, Type::Boolean);
      }
      else
      {
        _lexreg_.set(cell->token, cell->lexeme, cell);
      }
    }

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
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
    throw runtime_error(errMsg.str());
  }

  // Caracter invalido para string.
  if (c == '\n')
  {
    remove("file.asm");
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

  if (isNumber(c))
  {
    lexeme << c; // Crescer lexema caso seja um numero
  }
  else
  {
    // Configurar o registrador lexico de acordo com o valor das constante
    if (stoi(lexeme.str()) <= 255 && stoi(lexeme.str()) >= 0)
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

  if (isNumber(c))
  {
    lexeme << c;
    nextState = 3; // se numero nao hex vai para o estado 3
  }
  else if (c == 'x')
  {
    lexeme << c;
    nextState = 11; // se for uma notacao para Hex ir para o estado 11
  }
  else
  {
    //Senao aceitar 0 como digito
    _lexreg_.set(Token::Const, lexeme.str(), Type::Byte);
    std::cin.putback(c); // Desvolver char lido
    nextState = 15;
  }

  return nextState;
}

int Lexer::state11(char c, stringstream &lexeme)
{
  int nextState = 12; // Ir para o estado 12 para reconhecimento do proximo digito hex

  // Fim de arquivo encontrado antes do lexema hexadecimal ser corretamente escrito
  if (c == EOF)
  {
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
    throw runtime_error(errMsg.str());
  }

  // A entrada nao corresponde a um digito hexadecimal, nao podendo ser considerado um lexema valido
  else if (!isHex(c))
  {
    remove("file.asm");
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
  if (c == EOF)
  {
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
    throw runtime_error(errMsg.str());
  }

  // A entrada nao corresponde a um digito hexadecimal, nao podendo ser considerado um lexema valido
  if (!isHex(c))
  {
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\nlexema nao identificado [" << lexeme.str() << "].\n";
    throw runtime_error(errMsg.str());
  }

  lexeme << c; // Crescer lexema
  // Lexema corretamente reconhecido
  _lexreg_.set(Token::Const, lexeme.str(), Type::Byte);

  return nextState;
}

int Lexer::state5(char c, stringstream &lexeme)
{
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

int Lexer::state6(char c, stringstream &lexeme)
{
  int nextState = 15; // Estado final

  // Fim de arquivo encontrado, antes de completar a palavra reservada
  if (c == EOF)
  {
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
    throw runtime_error(errMsg.str());
  }
  // Se nao for a segunda | do lexema || o lexema sera considerado invalido
  if (c != '|')
  {
    remove("file.asm");
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

int Lexer::state7(char c, stringstream &lexeme)
{
  int nextState = 15; // Estado final

  // Fim de arquivo encontrado, antes de completar a palavra reservada
  if (c == EOF)
  {
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
    throw runtime_error(errMsg.str());
  }

  // Se nao for a segunda & do lexema && o lexema sera considerado invalido
  if (c != '&')
  {
    remove("file.asm");
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

int Lexer::state8(char c, stringstream &lexeme)
{
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

int Lexer::state9(char c, stringstream &lexeme)
{
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

int Lexer::state10(char c, stringstream &lexeme)
{
  int nextState; // Vai para estado 13 casi seja um comentario
                 // Senao devolve a palavra reservada '/'

  if (c == '*')
  {
    lexeme.str(""); // Limpa lexema
    nextState = 13;
  }
  else
  {
    std::cin.putback(c); // Devolve o char para a proxima analise
    // Buscar palavra reservada
    TSCell *cell = _tableSymbols_.search(lexeme.str());
    _lexreg_.set(cell->token, cell->lexeme, cell);
    nextState = 15;
  }

  return nextState;
}

int Lexer::state13(char c, stringstream &lexeme)
{
  int nextState; // Se for '*' mandar para o estado 14 para verificar fim de comentario
                 // Senao continua no estado 13

  // Fim de arquivo encotrado antes de de fechar o comentario
  if (c == EOF)
  {
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
    throw runtime_error(errMsg.str());
  }

  else if (c == '*')
    nextState = 14;
  else
  {
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
  if (c == EOF)
  {
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
    throw runtime_error(errMsg.str());
  }

  if (c == '/')
    nextState = 0;
  else if (c == '*')
  {
    nextState = 14;
  }
  else
  {
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

bool Lexer::isLetter(char c)
{
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool Lexer::isNumber(char c)
{
  return (c >= '0' && c <= '9');
}

bool Lexer::isHex(char c)
{
  return ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || isNumber(c));
}

bool Lexer::whitespace(char c)
{
  return (c == '\t' || c == '\n' || c == '\r' || c == ' ');
}

bool Lexer::unitKeywords(char c)
{
  return (c == '=' || c == '(' || c == ')' || c == ',' || c == '+' || c == '-' || c == '*' || c == ';');
}

bool Lexer::IsValid(char c)
{
  bool extra = c == '.' || c == '\'' || c == '?' || c == ':' || c == '{' || c == '}' || c == '[' || c == ']' ||
               c == '&' || c == '_' || c == '<' || c == '>' || c == '!' || c == '/' || c == '"' || c == '|';

  //formar agora o domionio da linguagem, todas os simbolos pertecentes a ela
  return (isLetter(c) || isNumber(c) || whitespace(c) || unitKeywords(c) || extra);
}

// =================END=====================

/** 
 * *************************************************
 * =================writer.cpp====================
 * Escrever no arquivo.
 * ==============================================
 * *************************************************
 *
 */

void Writer::open()
{
  this->buffer.open("file.asm", ios::out);
}

void Writer::writeln(string s)
{
  this->buffer << s << endl; // escrever no arquivo
}
void Writer::close()
{
  this->buffer.close();
}
// =================END=====================

/** 
 * *************************************************
 * =================codegen.cpp=================
 * Parte da geração de código.
 * Converter os comandos da nossa linguagem para
 * Assembly.
 * *************************************************
 *
 */

void CodeGen::start()
{
  writer.open();
  create_sseg();
  start_dseg();
  writer.writeln("\tbyte 4000h DUP(?)\t; temporários");
}
void CodeGen::end()
{
  writer.writeln("\nQuit:\tmov ah, 4ch\t ;numero mágico para DOS");
  writer.writeln("\tint 21h\t;fala para este programa quitar.");
  writer.writeln("Main endp\n");
  writer.writeln("cseg ENDS\t\t;fim seg. código\n");
  writer.writeln("end Main");
}

void CodeGen::start_dseg()
{
  writer.writeln("\ndseg SEGMENT PUBLIC\t\t;inicio seg. dados");
}
void CodeGen::end_dseg()
{
  writer.writeln("\ndseg ENDS\t\t; Fim seg. dados\n");
}

void CodeGen::init_cseg()
{
  writer.writeln("cseg SEGMENT PUBLIC\t\t;inicio seg. código");
  writer.writeln("\tASSUME CS:cseg, DS:dseg\t;habilitar a vericação de erro para cseg,dseg\n");
  writer.writeln("Main proc\n");
  writer.writeln(";Inicializar o segmento de dados.");
  writer.writeln("\tmov ax, dseg");
  writer.writeln("\tmov ds, ax");
}

void CodeGen::start_cseg()
{
  writer.writeln("\ncseg SEGMENT PUBLIC\t\t;inicio seg. código");
}

void CodeGen::end_cseg()
{
  writer.writeln("\ncseg ENDS\t\t;fim seg. código\n");
}

void CodeGen::create_sseg()
{
  writer.writeln("sseg SEGMENT STACK\t\t;Início seg. pilha");
  writer.writeln("\tbyte 4000h DUP(?)\t;Dimensiona pilha");
  writer.writeln("sseg ENDS\t\t;Fim seg. pilha\n");
}

int CodeGen::new_tmp(Type type)
{
  int newAddr;
  if (type == Type::String)
  {
    newAddr = _local_;
    end_cseg();
    start_dseg();
    writer.writeln("\tbyte 100h DUP(?)\t;String tmp alocada na pos " + to_string(newAddr));
    end_dseg();
    start_cseg();
    _local_ += 256;
  }
  else
  {
    newAddr = _temp_;
    _temp_ = type == Type::Integer ? _temp_ + 2 : _temp_ + 1;
  }

  return newAddr;
}

void CodeGen::reset_tmp()
{
  _temp_ = 0;
}

int CodeGen::alloc_id(Type idType, string constLex)
{

  int newAddr = _local_;

  if (idType == Type::Integer)
  {

    string val = constLex.empty() ? "?" : constLex;
    writer.writeln("\tsword " + val + "\t;Int alocado na pos " + to_string(newAddr));
    _local_ += 2;
  }
  else if (idType == Type::Byte)
  {
    string val = constLex.empty() ? "?" : constLex;
    if(!constLex.empty()){
      if(constLex.length() == 4 && constLex.at(1) == 'x'){
        int dec;
        stringstream ss;
        ss << std::hex << constLex;
        ss >> dec;
        val = to_string(dec);
      }
      else
        val = constLex;
    }
    else
      val = "?";
    
    
    writer.writeln("\tbyte " + val + "\t;Byte alocado na pos " + to_string(newAddr));
    _local_ += 1;
  }
  else if (idType == Type::Boolean)
  {
    string val;
    if (!constLex.empty())
      val = constLex.compare("TRUE") == 0 ? "0FFh" : "0h";
    else
      val = "?";

    writer.writeln("\tbyte " + val + "\t;Boolean alocado na pos " + to_string(newAddr));
    _local_ += 1;
  }
  else if (idType == Type::String)
  {
    // Se a string acompanhar uma constante ENTAO
    //   Se consante.lenght() < 255 ENTAO alocar espaco vazio para o restante da string
    //   Senao alocar string completa
    // Se string nao acompanhar uma constante ENTAO
    //   alocar espaco vazio para string
    if (!constLex.empty())
    {
      stringstream ss;
      if (constLex.length() < 255)
      {
        ss << constLex.substr(0, constLex.length() - 1) << "$\"";
        writer.writeln("\tbyte " + ss.str());
        writer.writeln("\tbyte " + to_string(256 - constLex.length() + 1) + " DUP(?)\t;String alocada na pos " + to_string(newAddr));
      }
      else {
          ss << constLex.substr(0, constLex.length() - 1) << "$\"";
          writer.writeln("\tbyte " + ss.str()  + "\t;String alocada na pos " + to_string(newAddr));
      }

    }
    else
      writer.writeln("\tbyte 100h DUP(?) ;\tString alocada na pos(" + to_string(newAddr) + ")");

    _local_ += 256;
  }

  return newAddr;
}

void CodeGen::assign(int targetAddr, int sourceAddr, Type addrType)
{
  // Levamos em consideracao que a verificacao de tipos ja foi realizados
  if (addrType == Type::String)
  {
    writer.writeln("\n;--------------------- Atribuicao de string ---------------------------");
    writer.writeln("\tmov di, " + to_string(targetAddr) + "\t; Carregando di com valor do endereco alvo");
    writer.writeln("\tmov si, " + to_string(sourceAddr) + "\t; Carrengado si com valor do endereco fonte");
    int label = new_label();
    write_label(label);
    writer.writeln("\tmov bl, ds:[si]\t; Carregando com  si com Source[si]");
    writer.writeln("\tmov ds:[di], bl\t; Repassando para Target[di]");
    writer.writeln("\tadd si, 1\t;");
    writer.writeln("\tadd di, 1\t;");
    writer.writeln("\tcmp bl, 024h\t;");
    writer.writeln("jne R" + to_string(label));
  }
  else
  {
    writer.writeln("\n;--------------------- Atribuicao ---------------------------");
    string reg = addrType != Type::Integer ? "al" : "ax";
    writer.writeln("\tmov " + reg + ", ds:[" + to_string(sourceAddr) + "]\t; Carrendo " + reg + " com valor do endereco");
    writer.writeln("\tmov ds:[" + to_string(targetAddr) + "], " + reg + "\t; Movendo " + reg + " para valor o endereco");
  }
}

int CodeGen::alloc_const(string constLex, Type constType)
{
  int newAddr;
  if (constType != Type::String)
  {
    writer.writeln("\n;------------ Alocando constante numerica/Logica -------------");
    newAddr = new_tmp(constType);
    // escolher registro de acordo com o tipo
    string reg = constType != Type::Integer ? "al" : "ax";
    
    if(constType == Type::Boolean)
      constLex = constLex.compare("TRUE") == 0 ? "0FFh" : "0h";
    
    if(constType ==  Type::Byte && constLex.length() == 4 && constLex.at(1) == 'x'){
      int dec;
      stringstream ss;
      ss << std::hex << constLex;
      ss >> dec;
      
      constLex = to_string(dec);
    }

    writer.writeln("\tmov " + reg + ", " + constLex + "\t; Carregando " + reg + " com o lexema da constante");
    writer.writeln("\tmov ds:[" + to_string(newAddr) + "], " + reg + "\t; Movendo valor de " + reg + " para o endereco do novo tmp");
  }
  else
  {
    newAddr = _local_;
    end_cseg();
    start_dseg();
    writer.writeln(";--------------- Alocando constante String ----------------");
    stringstream ss;
    if (constLex.length() < 255)
    {
      ss << constLex.substr(0, constLex.length() - 1) << "$\"";
      writer.writeln("\tbyte " + ss.str());
      writer.writeln("\tbyte " + to_string(256 - constLex.length() + 1) + " DUP(?)\t;String alocada na pos " + to_string(newAddr));
    }
    else {
        ss << constLex.substr(0, constLex.length() - 1) << "$\"";
        writer.writeln("\tbyte " + ss.str()  + "\t;String alocada na pos " + to_string(newAddr));
    }
    _local_ += 256;
    end_dseg();
    start_cseg();
    
  }

  return newAddr;
}

int CodeGen::write_I(int Jaddr, int J1addr, Type Jtype, Type J1type, Type Itype, Token op)
{
  int newAddr = new_tmp(Itype);
  writer.writeln("\n;--------------- Escrevendo expressao I ----------------");
  writer.writeln("\tmov ax, ds:[" + to_string(Jaddr) + "]\t; Carregando ax com J");
  writer.writeln("\tmov bx, ds:[" + to_string(J1addr) + "]\t; Carregando bx com J1 ");
  cout << "Jtype: "  << Jtype << " J1type: " << J1type << "\n"; 
  if (Jtype != Type::Integer)
    writer.writeln("\tmov ah, 0\t; zerando registrador alto de ax");

  if (J1type != Type::Integer)
    writer.writeln("\tmov bh, 0\t; zerando registrador alto de bx");

  if (op == Token::Multi || op == Token::And)
  {
    writer.writeln("\timul bx\t; ax = ax * bx");
  }
  else
  {
    writer.writeln("\tcwd");
    writer.writeln("\tidiv bx\t; ax = ax / bx");
  }

  if (Itype == Type::Integer)
    writer.writeln("\tmov ds:[" + to_string(newAddr) + "], ax");
  else
    writer.writeln("\tmov ds:[" + to_string(newAddr) + "], al");

  return newAddr;
}

int CodeGen::write_ExpS(int Iaddr, int I1addr, Type Itype, Type I1type, Type ExpStype, Token op)
{

  int newAddr = new_tmp(ExpStype);
  if (ExpStype == Type::String)
  {
    writer.writeln("\n;----------- Escrevendo expressao ExpS - Concatenacao -------------");
    writer.writeln("\tmov di, " + to_string(Iaddr) + "\t; Movendo endereco de I para di");
    writer.writeln("\tmov si, " + to_string(newAddr) + "\t; Movendo si para o endereco do resultado");
    writer.writeln("\tmov ax, " + to_string(I1addr) + "\t; Movendo endereco de I1 para di");
    int rotCopia = new_label();
    int rotFimCopia = new_label();
    int rotConcat = new_label();
    write_label(rotCopia);
    writer.writeln("\tmov bl, ds:[di]\t; Carrega bl com o I[di]");
    writer.writeln("\tadd di, 1\t; Incrementa contador di");
    writer.writeln("\tcmp bl, 024h\t; Verifica se e final de string");
    writer.writeln("\tje R" + to_string(rotFimCopia) + "\t; se final de string pular para prox. rot");
    writer.writeln("\tmov ds:[si], bl\t; Mover bl para string resultado");
    writer.writeln("\tadd si, 1\t; Incrementa contador si");
    writer.writeln("\tjmp R" + to_string(rotCopia) + "\t; retorna a prox pos");
    write_label(rotFimCopia);
    writer.writeln("\tmov di, ax\t; Carrega di com o end armazenado em ax");
    write_label(rotConcat);
    writer.writeln("\tmov bl, ds:[di]\t; Carrega bl com o I1[di]");
    writer.writeln("\tmov ds:[si], bl\t; Carrega bl para srting resultado");
    writer.writeln("\tadd si, 1\t; Incrementa contador si");
    writer.writeln("\tadd di, 1\t; Incrementa contador di");
    writer.writeln("\tcmp bl, 024h ; Verica se e final de string");
    writer.writeln("\tjne R" + to_string(rotConcat) + "\t;voltar a concat se nao for final de string");
  }
  else if(ExpStype == Type::Boolean)
  {
    int labelTrue = new_label();
    writer.writeln("\n;------------ Escrevendo expressao ExpS (OR) --------------");
    writer.writeln("\tmov di, " + to_string(Iaddr) + "\t;di <- I");
    writer.writeln("\tmov si, " + to_string(I1addr)    + "\t;si <- I1");
    writer.writeln("\tmov bx, " +  to_string(newAddr)  + "\t;bx <- temp");
    writer.writeln("\tmov cl, ds:[di]\t;cl <- MEM[di]");
    writer.writeln("\tcmp cl, 0FFh\t;if cl == true");
    writer.writeln("\tje R"+ to_string(labelTrue) + "\t; se trus jump para verdade");
    writer.writeln("\tmov cl, ds:[si]\t; se I nao foi verdade I1 tem q ser verdade");
    write_label(labelTrue);
    writer.writeln("\tmov ds:[bx], cl\t; temp <- true");
  }
  else
  {

    writer.writeln("\n;--------------- Escrevendo expressao ExpS ----------------");
    writer.writeln("\tmov ax, ds:[" + to_string(Iaddr) + "]\t; Carregando ax com I");
    writer.writeln("\tmov bx, ds:[" + to_string(I1addr) + "]\t; Carregando bx com I1 ");

    if (Itype != Type::Integer)
      writer.writeln("\tmov ah, 0\t; zerando registrador alto de ax");

    if (I1type != Type::Integer)
      writer.writeln("\tmov bh, 0\t; zerando registrador alto de bx");

    if (op == Token::Sum)
      writer.writeln("\t add ax, bx\t; ax = ax + bx ");
    else 
      writer.writeln("\tsub ax, bx\t; ax = ax - bx ");

    if (ExpStype == Type::Integer)
      writer.writeln("\tmov DS:[" + to_string(newAddr) + "], ax");
    else
      writer.writeln("\tmov DS:[" + to_string(newAddr) + "], al");
  }
  return newAddr;
}

int CodeGen::write_Exp(int ExpSaddr, int ExpS1addr, Type ExpStype, Type ExpS1type, Type ExpType, Token op)
{

  int newAddr = new_tmp(ExpType);

  if (ExpStype == Type::String)
  {
    int labelCmp = new_label();
    int labelEndCmp = new_label();
    int labelEnd = new_label();
    writer.writeln("\n;------------- Escrevendo Comparacao STR --------------");
    writer.writeln("\tmov al, 0\t; Carregando falso em al");
    writer.writeln("\tmov ds:[" + to_string(newAddr) + "] , al\t; Movendo al para end. EXP");
    writer.writeln("\tmov di, " + to_string(ExpSaddr) + "\t; Carregando end. EXPS em di");
    writer.writeln("\tmov si, " + to_string(ExpS1addr) + "\t; Carregando end. EXPS1 em si");

    write_label(labelCmp);
    writer.writeln("\tmov al, ds:[di]\t;Carregar al com Exp[di]");
    writer.writeln("\tmov cl, ds:[si]\t;Carregar cl com Exp[si]");
    writer.writeln("\tadd di, 1\t; incre. di");
    writer.writeln("\tadd si, 1\t; incre. si");
    writer.writeln("\tcmp al, cl");
    writer.writeln("\tjne R" + to_string(labelEnd));
    writer.writeln("\tcmp al, 024h");
    writer.writeln("\tje R" + to_string(labelEndCmp));
    writer.writeln("\tjmp R" + to_string(labelCmp));

    write_label(labelEndCmp);
    writer.writeln("\tcmp cl, 024h");
    writer.writeln("\tjne R" + to_string(labelEnd));
    writer.writeln("\tmov al, 0FFh");
    writer.writeln("\tmov ds:[" + to_string(newAddr) + "], al");

    write_label(labelEnd);
  }
  else
  {
    int labelTrue = new_label();
    int labelEnd = new_label();
    writer.writeln("\n;--------------- Escrevendo expressao Exp ----------------");
    writer.writeln("\tmov ax, ds:[" + to_string(ExpSaddr) + "]\t; Carregando ax com ExPS");
    writer.writeln("\tmov bx, ds:[" + to_string(ExpS1addr) + "]\t; Carregando bx com ExPS1");

    if (ExpS1type != Type::Integer)
      writer.writeln("\tmov ah, 0\t; zerando registrador alto de ax");

    if (ExpS1type != Type::Integer)
      writer.writeln("\tmov bh, 0\t; zerando registrador alto de bx");

    writer.writeln("\tcmp ax, bx\t;Comparando ax com bx");
    if (op == Token::Equal)
      writer.writeln("\tje R" + to_string(labelTrue));
    else if (op == Token::NotEquals)
      writer.writeln("\tjne R" + to_string(labelTrue));
    else if (op == Token::GreaterThen)
      writer.writeln("\tjg R" + to_string(labelTrue));
    else if (Token::GreaterEquals)
      writer.writeln("\tjge R" + to_string(labelTrue));
    else if (Token::LessThen)
      writer.writeln("\tjl R" + to_string(labelTrue));
    else if (Token::LessEquals)
      writer.writeln("\tjle R" + to_string(labelTrue));

    writer.writeln("\tmov al, 0");
    writer.writeln("\tjmp R" + to_string(labelEnd) + "\t; pular o final com 0");

    write_label(labelTrue);
    writer.writeln("\tmov al, 0FFh\t; Atribuir 1 para o caso verdadeiro");

    write_label(labelEnd);
    writer.writeln("\tmov ds:[" + to_string(newAddr) + "], al\t; Mover al para endereco de ExP");
  }

  return newAddr;
}

int CodeGen::write_neg(int addr, Type type)
{
  int newAddr;
  if (type == Type::Boolean)
  {
    newAddr = new_tmp(Type::Boolean);
    writer.writeln("\n;-------------------- Negacao Logica ------------------------");
    writer.writeln("\tmov ax, ds:[" + to_string(addr) + "]\t; ax <- MEM[id.address]");
    writer.writeln("\tmov ah, 0");
    writer.writeln("\tneg ax");
    writer.writeln("\tadd ax, 255");
    writer.writeln("\tmov ds:[" + to_string(newAddr) + "D], ax\t;MEM[temp.address] <- ax");
  }
  else
  {
    newAddr = new_tmp(Type::Integer);
    writer.writeln("\n;----------------- Negacao Aritimetica ---------------------");
    writer.writeln("\tmov ax, ds:[" + to_string(addr) + "]\t;Carregando ax com valor do endereco J1");
    if (type == Type::Byte)
      writer.writeln("\tmov ah, 0\t; zerando registrador alto de ax");

    writer.writeln("\tneg ax\t;Negando valor em Ax");
    writer.writeln("\tmov ds:[" + to_string(newAddr) + "], ax\t;Mover para o endereco o valor de al");
  }
  return newAddr;
}

void CodeGen::write_output(int addr, Type type)
{
  if (type == Type::Byte || type == Type::Integer)
  {
    writer.writeln("\n;------------------ Saida Numerica ----------------------");
    writer.writeln("\tmov ax, ds:[" + to_string(addr) + "]\t; Carregando ax com valor no addr");
    if (type == Type::Byte)
      writer.writeln("\tmov ah, 0\t; zerando registrador alto de ax");
    
    int newTmp = _temp_;
    _temp_ += 256;
    int r0 = new_label();
    int r1 = new_label();
    int r2 = new_label();
    writer.writeln("\tmov di, " + to_string(newTmp) + "\t;end. string temp.");
    writer.writeln("\tmov cx, 0 ;contador");
    writer.writeln("\tcmp ax,0 ;verifica sinal");
    writer.writeln("\tjge R" + to_string(r0) + "\t;salta se número positivo");
    writer.writeln("\tmov bl, 2Dh ;senão, escreve sinal –");
    writer.writeln("\tmov ds:[di], bl");
    writer.writeln("\tadd di, 1 ;incrementa índice");
    writer.writeln("\tneg ax ;toma módulo do número");
    write_label(r0);
    writer.writeln("\tmov bx, 10 ;divisor");
    write_label(r1);
    writer.writeln("\tadd cx, 1 ;incrementa contador");
    writer.writeln("\tmov dx, 0 ;estende 32bits p/ div.");
    writer.writeln("\tidiv bx ;divide DXAX por BX");
    writer.writeln("\tpush dx ;empilha valor do resto");
    writer.writeln("\tcmp ax, 0 ;verifica se quoc. é 0");
    writer.writeln("\tjne R" + to_string(r1) + " ;se não é 0, continua");

    writer.writeln(";agora, desemp. os valores e escreve o string");
    write_label(r2);
    writer.writeln("\tpop dx ;desempilha valor");
    writer.writeln("\tadd dx, 30h ;transforma em caractere");
    writer.writeln("\tmov ds:[di], dl ;escreve caractere");
    writer.writeln("\tadd di, 1 ;incrementa base");
    writer.writeln("\tadd cx, -1 ;decrementa contador");
    writer.writeln("\tcmp cx, 0 ;verifica pilha vazia");
    writer.writeln("\tjne R" + to_string(r2) + " ;se não pilha vazia, loop");

    writer.writeln(";grava fim de string");
    writer.writeln("\tmov dl, 024h ;fim de string");
    writer.writeln("\tmov ds:[di], dl ;grava '$'");

    writer.writeln(";exibe string");
    writer.writeln("\tmov dx, " + to_string(newTmp));
    writer.writeln("\tmov ah, 09h");
    writer.writeln("\tint 21h");
  }
  else
  {
    writer.writeln("\n;------------------ Saida String ----------------------");
    writer.writeln("\tmov dx, " + to_string(addr));
    writer.writeln("\tmov ah, 09h");
    writer.writeln("\tint 21h");
  }
}

void CodeGen::new_line()
{
  writer.writeln(";Escrevendo quebra de linha");
  writer.writeln("\tmov ah, 02h");
  writer.writeln("\tmov dl, 0Dh");
  writer.writeln("\tint 21h");
  writer.writeln("\tmov DL, 0Ah");
  writer.writeln("\tint 21h");
}
void CodeGen::read_string(int idAddr){
  int r0 = new_label();
  int r1 = new_label();  
  int buffer  = _temp_;
  _temp_ += 256;
  writer.writeln("\n;----------------- Entrada String ---------------------");
  writer.writeln("\tmov dx," + to_string(buffer) + "\t;dx <- buffer.end ");
  writer.writeln("\tmov al, 0FFh\t ;tam do buffer(255)");
  writer.writeln("\tmov ds:[" + to_string(buffer)  + "D], al\t ; MEM[buffer.end] <- al(tam do buffer)");
  writer.writeln("\tmov ah, 0Ah");
  writer.writeln("\tint 21h");
  writer.writeln("");
  writer.writeln("\tmov ah, 02h");
  writer.writeln("\tmov dl, 0Dh");
  writer.writeln("\tint 21h");
  writer.writeln("\tmov dl, 0Ah");
  writer.writeln("\tint 21h");
  writer.writeln("");
  writer.writeln("\tmov di, " + to_string(buffer + 2) + "\t;di <- buffer.end + 2 (posicao do string)");
  writer.writeln("\tmov si, " + to_string(idAddr) + "\t;si <- id.addr");
  writer.writeln(";comecar loop para ler do buffer para nossa string");
  write_label(r0);
  writer.writeln("\tmov bl, ds:[di]\t;bl <- MEM[di]");
  writer.writeln("\tcmp bx, 0Dh\t;verifica fim string");
  writer.writeln("\tje R" + to_string(r1));
  writer.writeln("\tmov ds:[si], bl");
  writer.writeln("\tadd di, 1 \t; count buffer++");
  writer.writeln("\tadd si, 1 \t; count id++");
  writer.writeln("\tjmp R"+ to_string(r0));
  write_label(r1);
  writer.writeln(";fim_loop");
  writer.writeln("mov cl, 024h");
  writer.writeln("mov ds:[si], cl \t;MEM[si] <- $ (fim, da string)");

}
void CodeGen::read_int(int idAddr){
  int r0 = new_label();
  int r1 = new_label();
  int r2 = new_label();
  int buffer  = _temp_;
  _temp_ += 256;
  writer.writeln("\n;----------------- Entrada Int ---------------------");
  writer.writeln("\tmov dx," +  to_string(buffer) +"\t;dx <- buffer.end");
  writer.writeln("\tmov al, 0FFh\t ;tam do buffer(255)");
  writer.writeln("\tmov ds:[" + to_string(buffer) + "D], al\t ; MEM[buffer.end] <- al(tam do buffer)");
  writer.writeln("\tmov ah, 0Ah");
  writer.writeln("\tint 21h");
  writer.writeln("");
  writer.writeln("\tmov ah, 02h");
  writer.writeln("\tmov dl, 0Dh");
  writer.writeln("\tint 21h");
  writer.writeln("\tmov dl, 0Ah");
  writer.writeln("int 21h");
  writer.writeln("");
  writer.writeln("\tmov di, " + to_string(buffer + 2) + "\t;di <- buffer.end + 2(posicao do string)");
  writer.writeln("\tmov ax, 0 \t;acumulador");
  writer.writeln("\tmov cx, 10 \t;base decimal(sera usado para multiplicar)");
  writer.writeln("\tmov dx, 1\t;valor sinal +");
  writer.writeln("\tmov bh,0");
  writer.writeln("\tmov bl, ds:[di]\t;caractere");
  writer.writeln("\tcmp bx, 2Dh\t;verifica sinal(2D é o valor do negativo '-' em hexadecimal na tabela asc ii");
  writer.writeln("\tjne R"+ to_string(r0) + "\t; se nao negativo");
  writer.writeln("\tmov dx, -1 \t;valor sinal -");
  writer.writeln("\tadd di, 1\t;proximo valor da string");
  writer.writeln("\tmov bl, ds:[di]\t;bl <- proximo caracter");
  write_label(r0);
  writer.writeln("\tpush dx\t;empilha sinal");
  writer.writeln("\tmov dx, 0\t;reg. multiplicação");
  write_label(r1);
  writer.writeln("\tcmp bx, 0dh\t;verifica fim string");
  writer.writeln("\tje R" + to_string(r2) + "\t;salta se fim string" );
  writer.writeln("\timul cx \t;mult. 10");
  writer.writeln("\tsub bx, 48 \t;subtract 48 from ASCII value of char to get integer");
  writer.writeln("\tadd ax, bx\t;soma valor caractere");
  writer.writeln("\tadd di, 1\t;incrementa base");
  writer.writeln("\tmov bh, 0");
  writer.writeln("\tmov bl, ds:[di]\t;proximo caractere");
  writer.writeln("\tjmp R" + to_string(r1)  + "\t;loop");
  write_label(r2);
  writer.writeln("\tpop cx\t;desempilha sinal");
  writer.writeln("\timul cx\t;mult. sinal");
  writer.writeln("mov ds:[" + to_string(idAddr) + "], ax\t; guardar valor no idAddr");
}
void CodeGen::read_ln(int idAddr, Type Idtype){
  if(Idtype == Type::String){
    CodeGen::read_string(idAddr);
  }
  else
  {
    CodeGen::read_int(idAddr);
  }
}
void CodeGen::write_if(int ExpAddr, int labelFalse){
  writer.writeln("\n;--------------- Test if -------------------");
  writer.writeln("\tmov al, ds:[" + to_string(ExpAddr) + "]\t; Carregar");
  writer.writeln("\tcmp al, 0h;");
  writer.writeln("je R" + to_string(labelFalse));
}

void CodeGen::write_if_end(int labelEnd){
  writer.writeln("jmp R" + to_string(labelEnd));
}

int CodeGen::new_label()
{
  int newLabel = _labels_;
  _labels_++;
  return newLabel;
}

void CodeGen::write_while(int ExpAddr, int labelEnd){
  writer.writeln("\n;------------- Loop Test -----------------");
  writer.writeln("\tmov al, ds:[" + to_string(ExpAddr) + "]\t; Carregar ExP em al");
  writer.writeln("\tcmp al, 0h;");
  writer.writeln("je R" + to_string(labelEnd) + "\t; Pula para o final do loop caos exp seja FALSE");
}



void CodeGen::write_label(int label)
{
  writer.writeln("R" + to_string(label) + ":");
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

void Parser::matchToken(Token expected)
{
  //std::cout << "Esperado:" << expected << " Tenho: " << _lexreg_.token << "| Lex: " <<  _lexreg_.lexeme << "| Linha: " << _numLines_ << "\n";
  if (_lexreg_.token == expected)
    _lexreg_.nextToken();

  // Fim de arquivo encotrando antes do fim parse
  else if (_lexreg_.token == Token::EndOfFile)
  {

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
  // std::cout << "ENTREI NO S\n";
  // Equanto _lexreg_.token pertece a FISRT(D) Repita
  CodeGen::start();
  while (_lexreg_.token == Token::Bool || _lexreg_.token == Token::Str || _lexreg_.token == Token::Int || _lexreg_.token == Token::B ||
         _lexreg_.token == Token::Final)
  {
    D();
  }

  CodeGen::end_dseg();
  CodeGen::init_cseg();
  // Equanto _lexreg_.token pertece a FISRT(CmD) Repita
  while (_lexreg_.token == Token::EndCmd ||
         _lexreg_.token == Token::Readln || _lexreg_.token == Token::Write || _lexreg_.token == Token::Writeln ||
         _lexreg_.token == Token::While ||
         _lexreg_.token == Token::If ||
         _lexreg_.token == Token::Id)
  {
    Cmd();
  }
  CodeGen::end();
}
// Regra de Comando
void Parser::Cmd()
{
  // std::cout << "ENTREI NO Cmd\n";
  // Executa regra de comando correspondente ao FIRST(CmD)
  if (_lexreg_.token == Token::EndCmd)
    matchToken(Token::EndCmd);
  else if (_lexreg_.token == Token::Id)
    A();
  else if (_lexreg_.token == Token::Readln || _lexreg_.token == Token::Write || _lexreg_.token == Token::Writeln)
    IO();
  else if (_lexreg_.token == Token::While)
    L();
  else
    T();
}

// Regra de declaracao
void Parser::D()
{
  // std::cout << "Entrei no D\n";
  TSCell *id;
  Type idType;
  Class idClass;

  Type constType;
  string constLex = ""; //vazio caso nao exista

  int signal;

  if (_lexreg_.token == Token::Final)
  {
    matchToken(Token::Final);
    id = _lexreg_.addr;
    matchToken(Token::Id);

    //------Unicidade--------------------------------------
    if (id->cl != Class::Empty)
    {
      stringstream errMsg;
      errMsg << _numLines_ << "\nidentificador ja declarado [" << id->lexeme << "].\n";
      throw runtime_error(errMsg.str());
    }
    id->cl = Class::ConstClass;
    //-----------------------------------------------------

    matchToken(Token::Attr);

    // Verificar se existe sinal na constante
    signal = 0;
    if (_lexreg_.token == Token::Dif)
    {
      matchToken(Token::Dif);
      signal = -1;
    }

    constType = _lexreg_.type;
    constLex = _lexreg_.lexeme;
    //std::cout << "SIGNAL: " << signal << " CONSTYPE: " << constType << " CONSTLEX: " << constLex << "\n";

    matchToken(Token::Const);
    if (signal == -1)
    {
      //------Verificacao de tipos--------------------------------
      if (constType != Type::Integer && constType != Type::Byte)
      {
        stringstream errMsg;
        errMsg << _numLines_ << "\ntipos incompativeis.\n";
        throw runtime_error(errMsg.str());
      }
      constType = Type::Integer;
      constLex = to_string(signal * stoi(constLex));
      //---------------------------------------------------------
    }
    id->type = constType;
    id->addr = CodeGen::alloc_id(id->type, constLex);
    matchToken(Token::EndCmd);
  }
  else
  {
    // Verificar Token do tipo
    if (_lexreg_.token == Token::Bool)
    {
      idType = Type::Boolean;
      matchToken(Token::Bool);
    }
    else if (_lexreg_.token == Token::Str)
    {
      idType = Type::String;
      matchToken(Token::Str);
    }
    else if (_lexreg_.token == Token::Int)
    {
      idType = Type::Integer;
      matchToken(Token::Int);
    }
    else
    {
      idType = Type::Byte;
      matchToken(Token::B);
    }

    id = _lexreg_.addr;
    matchToken(Token::Id);

    //------Unicidade--------------------------------------
    if (id->cl != Class::Empty)
    {
      stringstream errMsg;
      errMsg << _numLines_ << "\nidentificador ja declarado [" << id->lexeme << "].\n";
      throw runtime_error(errMsg.str());
    }
    id->cl = Class::VarClass;
    //------------------------------------------------------

    id->type = idType;

    // Caso _lexreg_.token tem um sinal de atribuicao realizar a verificao para constante
    constLex = "";
    if (_lexreg_.token == Token::Attr)
    {
      matchToken(Token::Attr);
      signal = 1;
      if (_lexreg_.token == Token::Dif)
      {
        signal = -1;
        matchToken(Token::Dif);
      }

      constType = _lexreg_.type;
      constLex = _lexreg_.lexeme;
      matchToken(Token::Const);

      if (signal == -1)
      {
        //------Verificacao de tipos--------------------------------
        if (constType != Type::Integer && constType != Type::Byte)
        {
          stringstream errMsg;
          errMsg << _numLines_ << "\ntipos incompativeis.\n";
          throw runtime_error(errMsg.str());
        }
        constType = Type::Integer;
        //-----------------------------------------------------------

        constLex = to_string(signal * stoi(constLex));
      }

      //------Verificacao de tipos--------------------------------
      if (id->type == Type::Integer && (constType != Type::Byte && constType != Type::Integer))
      {
        stringstream errMsg;
        errMsg << _numLines_ << "\ntipos incompativeis.\n";
        throw runtime_error(errMsg.str());
      }

      if (id->type != Type::Integer && id->type != constType)
      {
        stringstream errMsg;
        errMsg << _numLines_ << "\ntipos incompativeis.\n";
        throw runtime_error(errMsg.str());
      }
      //-------------------------------------------------------------
    }

    id->addr = CodeGen::alloc_id(id->type, constLex);
    // Repetir enquanto _lexreg_.token e igual a ','
    while (_lexreg_.token == Token::Comma)
    {
      // Declaracao de outro Identificador
      matchToken(Token::Comma);

      id = _lexreg_.addr;
      matchToken(Token::Id);

      //------Unicidade--------------------------------------
      if (id->cl != Class::Empty)
      {
        stringstream errMsg;
        errMsg << _numLines_ << "\nidentificador ja declarado [" << id->lexeme << "].\n";
        throw runtime_error(errMsg.str());
      }
      id->cl = Class::VarClass;
      //------------------------------------------------------

      id->type = idType;

      // Caso _lexreg_.token tem um sinal de atribuicao realizar a verificao para constante
      constLex = "";
      if (_lexreg_.token == Token::Attr)
      {
        matchToken(Token::Attr);
        signal = 1;
        if (_lexreg_.token == Token::Dif)
        {
          signal = -1;
          matchToken(Token::Dif);
        }

        constType = _lexreg_.type;
        constLex = _lexreg_.lexeme;
        matchToken(Token::Const);

        if (signal == -1)
        {
          //------Verificacao de tipos--------------------------------
          if (constType != Type::Integer && constType != Type::Byte)
          {
            stringstream errMsg;
            errMsg << _numLines_ << "\ntipos incompativeis.\n";
            throw runtime_error(errMsg.str());
          }
          constType = Type::Integer;
          //-----------------------------------------------------------

          constLex = to_string(signal * stoi(constLex));
        }

        //------Verificacao de tipos--------------------------------
        if (id->type == Type::Integer && (constType != Type::Byte && constType != Type::Integer))
        {
          stringstream errMsg;
          errMsg << _numLines_ << "\ntipos incompativeis.\n";
          throw runtime_error(errMsg.str());
        }

        if (id->type != Type::Integer && id->type != constType)
        {
          stringstream errMsg;
          errMsg << _numLines_ << "\ntipos incompativeis.\n";
          throw runtime_error(errMsg.str());
        }
        //-------------------------------------------------------------
      }

      id->addr = CodeGen::alloc_id(id->type, constLex);
    }

    matchToken(Token::EndCmd);
  }
}

// Regra de atribuicao
void Parser::A()
{
  // std::cout << "ENTREI NO A\n";

  TSCell *id;

  Type ExpType;
  int ExpAddr;

  id = _lexreg_.addr;
  matchToken(Token::Id);

  //------------Unicidade-----------------------------------
  if (id->cl == Class::Empty)
  {

    stringstream errMsg;
    errMsg << _numLines_ << "\nidentificador nao declarado [" << id->lexeme << "].\n";
    throw runtime_error(errMsg.str());
  }

  if (id->cl == Class::ConstClass)
  {

    stringstream errMsg;
    errMsg << _numLines_ << "\nclasse de identificador incompatível [" << id->lexeme << "].\n";
    throw runtime_error(errMsg.str());
  }
  //-------------------------------------------------------

  matchToken(Token::Attr);
  Exp(ExpType, ExpAddr); // Expressao a ser atribuida ao identificador

  //------Verificacao de tipos-----------------------------------
  if (id->type == Type::Integer && (ExpType != Type::Byte && ExpType != Type::Integer))
  {

    stringstream errMsg;
    errMsg << _numLines_ << "\ntipos incompativeis.\n";
    throw runtime_error(errMsg.str());
  }
  else if (id->type != Type::Integer && id->type != ExpType)
  {

    stringstream errMsg;
    errMsg << _numLines_ << "\ntipos incompativeis.\n";
    throw runtime_error(errMsg.str());
  }
  //---------------------------------------------------------------
  CodeGen::assign(id->addr, ExpAddr, id->type);
  CodeGen::reset_tmp();
  matchToken(Token::EndCmd);
}

// Regra de escrita
void Parser::IO()
{
  // cout << "Entrei no IO\n";

  //  _lexreg_.token  corresponde ao inicio do comando de leitura
  if (_lexreg_.token == Token::Readln)
  {

    TSCell *id;
    matchToken(Token::Readln);
    matchToken(Token::OpenParentheses);

    id = _lexreg_.addr;
    matchToken(Token::Id);

    //------Unicidade------------------------------------------
    if (id->cl == Class::Empty)
    {

      stringstream errMsg;
      errMsg << _numLines_ << "\nidentificador nao declarado [" << id->lexeme << "].\n";
      throw runtime_error(errMsg.str());
    }
    if (id->cl == Class::ConstClass)
    {

      stringstream errMsg;
      errMsg << _numLines_ << "\nclasse de identificador incompativel [" << id->lexeme << "].\n";
      throw runtime_error(errMsg.str());
    }
    //----------------------------------------------------------------

    //------Verificacao de tipos-----------------------------------
    if (id->type == Type::Boolean)
    {

      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis.\n";
      throw runtime_error(errMsg.str());
    }
    //-------------------------------------------------------------------
    CodeGen::read_ln(id->addr, id->type);
    matchToken(Token::CloseParentheses);
    matchToken(Token::EndCmd);
  }
  else
  {
    Type ExpType;
    int ExpAddr;
    bool newLine = false;
    if (_lexreg_.token == Token::Write)
    {
      matchToken(Token::Write);
    }
    else
    {
      matchToken(Token::Writeln);
      newLine = true;
    }

    //  _lexreg_.token  corresponde ao inicio do comando de escrita sem quebra de linha
    matchToken(Token::OpenParentheses);
    Exp(ExpType, ExpAddr);
    if (ExpType == Type::Boolean)
    {

      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis.\n";
      throw runtime_error(errMsg.str());
    }

    CodeGen::write_output(ExpAddr, ExpType);

    // Equanto _lexreg_.token  igual ',' repita
    while (_lexreg_.token == Token::Comma)
    {
      // Outra expressao para ser realizada
      matchToken(Token::Comma);

      Exp(ExpType, ExpAddr);
      //------Verificacao de tipos-----------------------------------
      if (ExpType == Type::Boolean)
      {

        stringstream errMsg;
        errMsg << _numLines_ << "\ntipos incompativeis.\n";
        throw runtime_error(errMsg.str());
      }
      //--------------------------------------------------------------

      CodeGen::write_output(ExpAddr, ExpType);
      CodeGen::reset_tmp();
    }
    
    if (newLine){
      CodeGen::new_line();
    }

    matchToken(Token::CloseParentheses);
    matchToken(Token::EndCmd);
  }
}

void Parser::L()
{ 
  
  // cout << "Entrei no L\n";
  Type ExpType;
  int ExPAddr;
  // int labelBegin = CodeGen::new_label();
  //int labelEnd = CodeGen::new_label();
  matchToken(Token::While);
  matchToken(Token::OpenParentheses);
  //CodeGen::write_label(labelBegin);
  Exp(ExpType, ExPAddr);
  //------Verificacao de tipos-----------------------------------
  if (ExpType != Type::Boolean)
  {
    stringstream errMsg;
    errMsg << _numLines_ << "\ntipos incompativeis.\n";
    throw runtime_error(errMsg.str());
  }

  matchToken(Token::CloseParentheses);
  // CodeGen::write_while(ExPAddr, labelEnd);
  //--------------------------------------------------------------
  // Se _lexreg_.token for Begin, espera-se uma sequencia de 0 ou mais comandos
  // Senao espera-se apenas um comando
  if (_lexreg_.token == Token::Begin)
  {
    matchToken(Token::Begin);
    // Enqunato Token pertencer a FISRT(C) repita
    while (_lexreg_.token == Token::EndCmd ||
           _lexreg_.token == Token::Readln || _lexreg_.token == Token::Write || _lexreg_.token == Token::Writeln ||
           _lexreg_.token == Token::While ||
           _lexreg_.token == Token::If ||
           _lexreg_.token == Token::Id)
    {
      Cmd();
    }
    matchToken(Token::Endwhile);
  }
  else
  {
    Cmd();
  }
  // CodeGen::write_while_end(labelBegin);
}

// Regra de Teste
void Parser::T()
{
  // cout << "Entrei no T\n";
  Type ExpType;
  int ExPAddr;
  int labelEnd;
  int labelFalse;
  
  matchToken(Token::If);
  matchToken(Token::OpenParentheses);

  Exp(ExpType, ExPAddr);
  //------Verificacao de tipos-----------------------------------
  if (ExpType != Type::Boolean)
  {

    stringstream errMsg;
    errMsg << _numLines_ << "\ntipos incompativeis.\n";
    throw runtime_error(errMsg.str());
  }
  //--------------------------------------------------------------
  matchToken(Token::CloseParentheses);

  // Se _lexreg_.token for Begin, espera-se uma sequencia de 0 ou mais comandos
  // Senao espera-se apenas um comando
  labelFalse = CodeGen::new_label();
  labelEnd = CodeGen::new_label();
  CodeGen::write_if(ExPAddr, labelFalse);
  if (_lexreg_.token == Token::Begin)
  {
    matchToken(Token::Begin);

    // Enqunato Token pertencer a FISRT(C) repita
    while (_lexreg_.token == Token::EndCmd ||
           _lexreg_.token == Token::Readln || _lexreg_.token == Token::Write || _lexreg_.token == Token::Writeln ||
           _lexreg_.token == Token::While ||
           _lexreg_.token == Token::If ||
           _lexreg_.token == Token::Id)
    {
      Cmd();
    }
    matchToken(Token::Endif);
  }
  else
    Cmd();

  if(_lexreg_.token == Token::Else)
    CodeGen::write_if_end(labelEnd);

  CodeGen::write_label(labelFalse);
  // Se encontrado um  Else
  if (_lexreg_.token == Token::Else)
  {
    matchToken(Token::Else);
    // Se _lexreg_.token for Begin, espera-se uma sequencia de 0 ou mais comandos
    // Senao espera-se apenas um comando
    if (_lexreg_.token == Token::Begin)
    {
      matchToken(Token::Begin);

      // Enqunato Token pertencer a FISRT(C) repita
      while (_lexreg_.token == Token::EndCmd ||
             _lexreg_.token == Token::Readln || _lexreg_.token == Token::Write || _lexreg_.token == Token::Writeln ||
             _lexreg_.token == Token::While ||
             _lexreg_.token == Token::If ||
             _lexreg_.token == Token::Id)
      {
        Cmd();
      }
      matchToken(Token::Endelse);
    }
    else
      Cmd();
  }
  CodeGen::write_label(labelEnd);
}

// Regra da expressao
void Parser::Exp(Type &ExpType, int &ExpAddr)
{
  // cout << "Entrei no exp\n";
  Type ExpSType;
  int ExPSAddr;

  Type ExpS1Type;
  int ExPS1Addr;

  Token op;
  bool typeError;
  Type resultType;

  ExpS(ExpSType, ExPSAddr);
  ExpType = ExpSType;
  ExpAddr = ExPSAddr;

  // Se '>', '<', '<=', '>=' ou '=' realizar nova expressao para ser comparada
  if (_lexreg_.token == Token::Equal || _lexreg_.token == Token::NotEquals || _lexreg_.token == Token::GreaterThen ||
      _lexreg_.token == Token::LessThen || _lexreg_.token == Token::GreaterEquals || _lexreg_.token == Token::LessEquals)
  {
    // Buscar operadores
    if (_lexreg_.token == Token::Equal)
    {
      op = _lexreg_.token;
      matchToken(Token::Equal);
    }
    else if (_lexreg_.token == Token::NotEquals)
    {
      op = _lexreg_.token;
      matchToken(Token::NotEquals);
    }
    else if (_lexreg_.token == Token::GreaterThen)
    {
      op = _lexreg_.token;
      matchToken(Token::GreaterThen);
    }
    else if (_lexreg_.token == Token::LessThen)
    {
      op = _lexreg_.token;
      matchToken(Token::LessThen);
    }
    else if (_lexreg_.token == Token::GreaterEquals)
    {
      op = _lexreg_.token;
      matchToken(Token::GreaterEquals);
    }
    else
    {
      op = _lexreg_.token;
      matchToken(Token::LessEquals);
    }

    ExpS(ExpS1Type, ExPS1Addr);

    //------Verificacao de tipos-----------------------------------
    // Se for uma operacao de comparacao de igualdade
    typeError = false;
    resultType = Type::Boolean;
    if (op == Token::Equal)
    {
      if ((ExpType != Type::Integer && ExpType != Type::Byte) || (ExpS1Type != Type::Byte && ExpS1Type != Type::Integer))
      {
        if (ExpType != Type::String && ExpS1Type != Type::String)
          typeError = true;
      }
    }
    else
    {
      // Se for uma operacao de comparacao artimetica
      if ((ExpType != Type::Integer && ExpType != Type::Byte) || (ExpS1Type != Type::Byte && ExpS1Type != Type::Integer))
        typeError = true;
    }
    // Se tiver sido encotrado algum erro de tipo
    if (typeError)
    {

      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis.\n";
      throw runtime_error(errMsg.str());
    }
    //-----------------------------------------------------------

    //---------Assembly--------------------------------------------
    ExpAddr = CodeGen::write_Exp(ExpAddr, ExPS1Addr, ExpType, ExpS1Type, resultType, op);
    ExpType = resultType;
    //---------------------------------------------------------
  }
}

// Regra do primeiro nivel de precedencia
void Parser::ExpS(Type &ExpSType, int &ExpSAddr)
{
  // cout << "Entreino EXPS\n";
  Type Itype;
  int Iaddr;

  Type I1type;
  int I1addr;

  Token op;

  int signal = 0;
  bool typeError;
  Type resultType;

  // Precidencia no primeiro operador
  if (_lexreg_.token == Token::Sum || _lexreg_.token == Token::Dif)
  {
    // Verificar existencia de sinal
    if (_lexreg_.token == Token::Sum)
    {
      signal = 1;
      matchToken(Token::Sum);
    }
    else
    {
      signal = -1;
      matchToken(Token::Dif);
    }
  }

  I(Itype, Iaddr);
  // Executar mudanca de sinal caso seja necessario
  if (signal == 1)
  {
    //------Verificacao de tipos-----------------------------------
    if (Itype == Type::Boolean)
    {

      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis.\n";
      throw runtime_error(errMsg.str());
    }
    //--------------------------------------------------------------
  }
  else if (signal == -1)
  {
    //------Verificacao de tipos-----------------------------------
    if (Itype != Type::Integer && Itype != Type::Byte)
    {

      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis.\n";
      throw runtime_error(errMsg.str());
    }
    //--------------------------------------------------------------
    Iaddr = CodeGen::write_neg(Iaddr, Itype);
    Itype = Type::Integer;
  }

  ExpSType = Itype;
  ExpSAddr = Iaddr;

  // Enquanto '+', '-' ou '||' realizar a opercao com a segunda expressao
  while (_lexreg_.token == Token::Sum || _lexreg_.token == Token::Dif || _lexreg_.token == Token::Or)
  {

    // Buscar operados
    if (_lexreg_.token == Token::Sum)
    {
      op = Token::Sum;
      matchToken(Token::Sum);
    }
    else if (_lexreg_.token == Token::Dif)
    {
      op = Token::Dif;
      matchToken(Token::Dif);
    }
    else
    {
      op = Token::Or;
      matchToken(Token::Or);
    }

    I(I1type, I1addr);

    typeError = false;
    // Verificar tipo para cada tipo operador
    //------Verificacao de tipos-----------------------------------
    if (op == Token::Sum)
    {
      if ((ExpSType == Type::Integer || ExpSType == Type::Byte) && (I1type == Type::Integer || I1type == Type::Byte))
      {
        // Soma aritemetica
        resultType = Type::Integer;
      }
      else if (ExpSType == Type::String && I1type == Type::String)
      {
        // Concatencao de string
        resultType = Type::String;
      }
      else
        typeError = true;
    }
    else if (op == Token::Dif)
    {
      // Diferenca aritmetica
      if ((ExpSType != Type::Integer && ExpSType != Type::Byte) || (I1type && Type::Integer || I1type && Type::Byte))
        typeError = true;
      else
        resultType = Type::Integer;
    }
    else
    {
      // Adicao logica (OR)
      if (ExpSType != Type::Boolean && I1type != Type::Boolean)
        typeError = true;
      else
        resultType = Type::Boolean;
    }

    if (typeError)
    {

      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis.\n";
      throw runtime_error(errMsg.str());
      //-----------------------------------------------------------------
    }
    //------Assembly------------------------------------------------------
    ExpSAddr = CodeGen::write_ExpS(ExpSAddr, I1addr, ExpSType, I1type, resultType, op);
    ExpSType = resultType;
    //--------------------------------------------------------------------
  }
}

// Regra do segundo nivel de precedencia
void Parser::I(Type &Itype, int &Iaddr)
{
  // cout << "Entrei no I\n";
  Type Jtype;
  int Jaddr;

  Type J1type;
  int J1addr;

  Token op;

  bool typeError;
  Type resultType;

  J(Jtype, Jaddr);
  Itype = Jtype;
  Iaddr = Jaddr;

  // Enquanto '*', '/' ou '&&' realizar a opercao com a segunda expressao
  while (_lexreg_.token == Token::Multi || _lexreg_.token == Token::Div || _lexreg_.token == Token::And)
  {
    // Buscar operador
    if (_lexreg_.token == Token::Multi)
    {
      op = Token::Multi;
      matchToken(Token::Multi);
    }
    else if (_lexreg_.token == Token::Div)
    {
      op = Token::Div;
      matchToken(Token::Div);
    }
    else
    {
      op = Token::And;
      matchToken(Token::And);
    }

    J(J1type, J1addr);

    //------Verificacao de tipos-----------------------------------
    typeError = false;
    if (op == Token::Multi)
    {
      // Operacao de divisao aritimetica
      if ((Itype != Type::Integer && Itype != Type::Byte) || (J1type != Type::Integer && J1type != Type::Byte))
        typeError = true;
      else
        resultType = Type::Integer;
    }
    else if (op == Token::Div)
    {
      // Operacao de divisao aritimetica
      if ((Itype != Type::Integer && Itype != Type::Byte) || (J1type != Type::Integer && J1type != Type::Byte))
        typeError = true;
      else
        resultType = Type::Integer;
    }
    else
    {
      // Multiplicao Logica (AND)
      if (Itype != Type::Boolean && J1type != Type::Boolean)
        typeError = true;
      else
        resultType = Type::Boolean;
    }

    if (typeError)
    {
      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis.\n";
      throw runtime_error(errMsg.str());
    }
    //-----------------------------------------------

    //--------------Assembly-----------------------------
    Iaddr = CodeGen::write_I(Iaddr, J1addr, Itype, Jtype, resultType, op);
    Itype = resultType;
    //---------------------------------------------------
  }
}

// Regra do terceiro nivel de precedencia
void Parser::J(Type &Jtype, int &Jaddr)
{
  // cout << "Entrei no J\n";
  TSCell *id;

  Type constType;
  string constLex;

  Type J1Type;
  int J1addr;

  Type ExpType;
  int ExpAddr;

  if (_lexreg_.token == Token::Not)
  {
    // Negacao logica
    matchToken(Token::Not);
    J(J1Type, J1addr);

    //------Verificao de tipo-------------------------
    if (J1Type != Type::Boolean)
    {
      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis.\n";
      throw runtime_error(errMsg.str());
    }
    //-------------------------------------------------

    //------Assembly--------------------------------------------
    Jaddr = CodeGen::write_neg(J1addr, Type::Boolean);
    //----------------------------------------------------------
    Jtype = Type::Boolean;
  }
  else if (_lexreg_.token == Token::OpenParentheses)
  {
    // Nova expresao com maior prioridade
    matchToken(Token::OpenParentheses);
    Exp(ExpType, ExpAddr);
    matchToken(Token::CloseParentheses);

    Jtype = ExpType;
    Jaddr = ExpAddr;
  }
  else if (_lexreg_.token == Token::Id)
  {

    // Indentificador
    id = _lexreg_.addr;
    matchToken(Token::Id);
    //------Unicidade------------------------------------------
    if (id->cl == Class::Empty)
    {
      stringstream errMsg;
      errMsg << _numLines_ << "\nidentificador nao declarado [" << id->lexeme << "].\n";
      throw runtime_error(errMsg.str());
    }
    //----------------------------------------------------------

    Jtype = id->type;
    Jaddr = id->addr;
  }
  else
  {
    // Constante
    constLex = _lexreg_.lexeme;
    constType = _lexreg_.type;
    matchToken(Token::Const);

    //------Assembly--------------------------------------------
    Jaddr = CodeGen::alloc_const(constLex, constType);
    //----------------------------------------------------------
    Jtype = constType;
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
int main(int argc, char const *argv[])
{
  try
  {
    _lexreg_.nextToken();
    Parser::S();
    if (cin.peek() != EOF)
    {
      std::cout << _numLines_ << "\ntoken nao esperado2 [" << _lexreg_.lexeme << "].\n";
      exit(1);
    }
  }
  catch (runtime_error &e)
  {
    std::cout << e.what();
    remove("file.asm");
    exit(1);
  }

  std::cout << _numLines_ << " linhas compiladas.\n";
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
            std::cout << e.what();
            exit(0);
        }
    }
    std::cout << _numLines_ << " linhas compiladas.\n";
}
*/

// =================END=====================