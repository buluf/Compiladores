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
  static void S();                  // Start
  static void Cmd();                // Comando
  static void D();                  // Declaracao
  static void A();                  // Atribuicao
  static void IO();                 // Entrada/Saida
  static void L();                  // Loop (estrutura de repitricao)
  static void T();                  // Teste
  static void C();                  // Decleracao de constante
  static void Exp(Type &ExpType);   // Exepressao
  static void ExpS(Type &ExpSType); // Exepressao primeiro nivel de operadores
  static void I(Type &IType);       //  Exepressao segundo nivel de operadores
  static void J(Type &JType);       //  Exepressao terceiro nivel de operadores
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

  static Writer writer;
  /**
   * @brief Inicia um segmento de memoria
  */
  static void start_dseg();
  /**
   * @brief Inicia um segmento de código
  */
  static void start_cseg();
    /**
   * @brief finaliza um segmento de memoria
  */
  static void end_dseg();
    /**
   * @brief finaliza um segmento de código
  */
  static void end_cseg();
    /**
   * @brief Starta o nosso assembly com os atributos essenciais e iniciais
   * Para o funcionamento do nosso programa
  */
  static void start();
    /**
   * @brief Inicia um segmento de pilha(outro segmento de memoria)
  */
  static void create_sseg();
    /**
   * @brief aloca um endereço disponivel para uma variavel
  */
  static int allocId(Type idType, string constLex);
    /**
   * @brief aloca um endereco disponivel para uma expressao
  */
 static int allocTemp(Type expType, string constLex);
     /**
   * @brief cria um novo temporario atualiza espaço disponivel e retorna o endereco
  */
 static int CodeGen::new_tmp(Type type);
    /**
   * @brief reset espaco disponivel temp
  */
 static void reset_temp();
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
int _numLines_ = 1;
int _counTemp_ = 0;
int _tamTemp_ = 16384; //temporarios termina na posição 4000h
int _tempRestant_ = 16384; //tamanho da memoria restante disponível
int _local_ = 0;       //localização na memória depois dos temp.
int _rotulos_ = 0;
int _temporarios_ =0;

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
  this->addr = NULL;
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
  this->insert("writer.writeln", TSCell("writeln", Token::Writeln));
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
 * =================writer.cpp=================
 * Escrever no arquivo.
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
  start_dseg();
  writer.writeln("\tbyte 4000h DUP(?)\t;temporários");
  writer.writeln("\tinteger typedef sword\t;tam == 2bytes");
  writer.writeln("\tbool typedef byte\t;tam == 1byte");
  end_dseg();
}
void CodeGen::start_dseg()
{
  writer.writeln("dseg SEGMENT PUBLIC\t\t;inicio seg. dados");
}
void CodeGen::end_dseg()
{
  writer.writeln("dseg ENDS\t\t; Fim seg. dados\n");
}
void CodeGen::start_cseg()
{
  writer.writeln("cseg SEGMENT PUBLIC\t\t;inicio seg. código");
  writer.writeln("\tASSUME CS:cseg, DS:dseg\t;habilitar a vericação de erro para cseg,dseg\n");
  writer.writeln("Main proc\n");
  writer.writeln(";inicializar o segment register.");
  writer.writeln("\tmov ax, dseg");
  writer.writeln("\tmov ds, ax");
  writer.writeln("\tmov es, ax");
}

void CodeGen::end_cseg()
{
  writer.writeln("Quit:\tmov ah, 4ch\t;número mágico para DOS");
  writer.writeln("\tint 21h\t;fala para este programa quitar.");
  writer.writeln("Main endp\n");
  writer.writeln("cseg ENDS\t\t;fim seg. código\n");
  writer.writeln("end Main");
}
void CodeGen::create_sseg()
{
  writer.writeln("sseg SEGMENT STACK\t\t;Início seg. pilha");
  writer.writeln("\tbyte 4000h DUP(?)\t;Dimensiona pilha");
  writer.writeln("sseg ENDS\t\t;Fim seg. pilha\n");
}

// int CodeGen::allocid(Type idType, string lexeme)
// {
//   int size = 0; // Type == undefined

//   if (idType == Type::Byte)
//   {
//     size = 1;
//   }
//   else if (idType == Type::Integer)
//   {
//     size = 2;
//   }
//   else if (idType == Type::Boolean)
//   {
//     size = 1;
//   }
//   else if (idType == Type::String)
//   {
//     size = 256;
//   }

//   return size;
// }
int CodeGen::new_tmp(Type type)
{
  int newAddr = _tamTemp_ - _tempRestant_; //tamanho da memoria de temp - o restante disponivel == end da nova temp

  if (type == Type::Byte || type == Type::Boolean)
    _tempRestant_ -= 1; 
  else
    _tempRestant_ -= 2; //inteiro(sword)
  return newAddr;
}
void CodeGen::reset_tmp()
{
  _tempRestant_ = 16384; //reseta pra 0(espaço ocupado)
}
int CodeGen::allocTemp(Type expType, string constLex){
  stringstream line;

  int newAddr = new_tem(expType); //novo enderço temp alocado
  _counTemp_ += 1; //novo temporario

  if(expType == Type::Integer){

  }
  else if(expType == Type::Byte){

  }
  else{

  }
  return newAddr;

}
int CodeGen::allocId(Type idType, string constLex)
{
  stringstream line;

  int newAddr = _tamTemp_ + _local_;

  if (idType == Type::Integer)
  {
    _local_ += 2; 
    if (constLex.empty())
    {
      line << "\tinteger " << '?' << "\t;valor alocado na pos(" << newAddr << "D)";
      writer.writeln(line.str()); // alocar valor do tipo inteiro(sword) na memoria em pos
    }
    else
    {
      // alocar valor do tipo inteiro(sword) na memoria em pos
      line << "\tinteger " << constLex << "\t;valor alocado na pos(" << newAddr << "D)";
      writer.writeln(line.str());
    }
  }
  else if (idType == Type::Boolean)
  {
    _local_ += 1;
    if(constLex.empty()){
      line << "\tbool " << '?' << "\t;valor alocado na pos(" << newAddr << "D)";
    }
    else{
      if(constLex.compare("TRUE") == 0){
        line << "\tbool " << 'FFh' << "\t;valor alocado na pos(" << newAddr << "D)"; // se verdadeiro ocupa um byte na memoria com o valor de 'FFh'
      }
      else{
        line << "\tbool " << '0h' << "\t;valor alocado na pos(" << newAddr << "D)"; // se falso ocupa um byte na memoria com o valor de '0h'
      }
      
    }
    writer.writeln(line.str()); 
  }
  else if (id->type == Type::Byte)
  {
    _local_ += 1;
    if (!constLex.empty())
    {
      if (constLex.at(1) == 'x')
      {
        // se na segunda posição tiver um x o valor do byte tá em hex, logo:
        constLex.at(1) = '0';
        line << "\tbyte " << valor << "H\t;valor alocado na pos(" << newAddr << "D)";// declarando byte na posicao(newAddr)
      }
      else
      {
        line << "\tbyte " << valor << "\t;valor alocado na pos(" << newAddr << "D)";// declarando byte na posicao(newAddr)
      }
    }
    else{
      line << "\tbyte " << '?' << "\t;valor alocado na pos(" << newAddr << "D)";

    }
    writer.writeln(line.str());
  }
  else
  {
    _local_ += 256;
    //declarando String
    if (!constLex.empty())
    {
      int alocar_resto = 256 - (valor.length()+1); // tamanho da string + 1 do cifrão
      line << "\tbyte \"" << valor << "$" << "\"\t;string alocada na pos(" << newAddr << "D)"; // byte "valor". cada caracter do valor
                                                                                              // ocupara um byte
      writer.writeln(line.str());                                                                                        
      line.str(""); //limpando
      line << "\tbyte " << alocar_resto << "DUP(?)" << "\t;alocando resto do espaco(" << newAddr << "D)"; //resto
    }
    else
    {
      line << "\tbyte " << to_string(256) << "DUP(?)" << "\t;string alocada na pos(" << newAddr << "D)"; // 256 bytes
                                                                                                        
    }
    writer.writeln(line.str());
  }

  return newAddr;
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
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\nfim de arquivo nao esperado.\n";
    throw runtime_error(errMsg.str());
  }
  // Token nao esperado
  else
  {
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\ntoken nao esperado [" << _lexreg_.lexeme << "].\n";
    throw runtime_error(errMsg.str());
  }
}

void Parser::S()
{
  //std::cout << "ENTREI NO S\n";
  // Equanto _lexreg_.token pertece a FISRT(D) Repita
  while (_lexreg_.token == Token::Bool || _lexreg_.token == Token::Str || _lexreg_.token == Token::Int || _lexreg_.token == Token::B ||
         _lexreg_.token == Token::Final)
  {
    CodeGen::start_dseg(); //inicio meu data segment
    D();
    CodeGen::end_dseg(); //fecho meu segmento de dados
  }

  // Equanto _lexreg_.token pertece a FISRT(CmD) Repita
  while (_lexreg_.token == Token::EndCmd ||
         _lexreg_.token == Token::Readln || _lexreg_.token == Token::Write || _lexreg_.token == Token::Writeln ||
         _lexreg_.token == Token::While ||
         _lexreg_.token == Token::If ||
         _lexreg_.token == Token::Id)
  {
    Cmd();
  }
}
// Regra de Comando
void Parser::Cmd()
{
  //std::cout << "ENTREI NO Cmd\n";
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
  string constLex;

  bool signal;

  if (_lexreg_.token == Token::Final)
  {
    matchToken(Token::Final);
    id = _lexreg_.addr;
    matchToken(Token::Id);

    if (id->cl != Class::Empty)
    {
      remove("file.asm");
      stringstream errMsg;
      errMsg << _numLines_ << "\nidentificador ja declarado. [" << id->lexeme << "].\n";
      throw runtime_error(errMsg.str());
    }

    id->cl = Class::ConstClass;

    matchToken(Token::Attr);

    signal = false;
    // Verificar se existe sinal na constante
    if (_lexreg_.token == Token::Dif)
    {
      matchToken(Token::Dif);
      signal = true;
    }

    constType = _lexreg_.type;
    constLex = _lexreg_.lexeme;
    //std::cout << "SIGNAL: " << signal << " CONSTYPE: " << constType << " CONSTLEX: " << constLex << "\n";

    matchToken(Token::Const);
    if (signal)
    {
      if (constType != Type::Integer && constType != Type::Byte)
      {
        remove("file.asm");
        stringstream errMsg;
        errMsg << _numLines_ << "\ntipos incompativeis. 1\n";
        throw runtime_error(errMsg.str());
      }

      constType = Type::Integer;
      // REVERTER SINAL
      constLex =  "-" + constLex;
    }
    //discutir
    id->type = constType;
    //------Assembly--------------------------------------
    id->addr = CodeGen::allocId(id->type, constLex); //declarando variável
    //----------------------------------------------------
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
    if (id->cl != Class::Empty)
    {
      remove("file.asm");
      stringstream errMsg;
      errMsg << _numLines_ << "\nidentificador ja declarado. [" << id->lexeme << "].\n";
      throw runtime_error(errMsg.str());
    }

    id->cl = Class::VarClass;
    id->type = idType;

    // Caso _lexreg_.token tem um sinal de atribuicao realizar a verificao para constante
    if (_lexreg_.token == Token::Attr)
    {
      matchToken(Token::Attr);
      // Teste de sinal na constante
      signal = false;
      if (_lexreg_.token == Token::Dif)
      {
        signal = true;
        matchToken(Token::Dif);
      }

      constType = _lexreg_.type;
      constLex = _lexreg_.lexeme;
      matchToken(Token::Const);
      // Verificar compatibilidade dos tipos
      if (signal)
      {
        if (constType != Type::Integer && constType != Type::Byte)
        {
          remove("file.asm");
          stringstream errMsg;
          errMsg << _numLines_ << "\ntipos incompativeis. 1\n";
          throw runtime_error(errMsg.str());
        }

        constType = Type::Integer;
        // REVERTER SINAL
        constLex = "-" + constLex;

      }
      if (id->type == Type::Integer && (constType != Type::Byte || constType != Type::Integer))
      {
        remove("file.asm");
        stringstream errMsg;
        errMsg << _numLines_ << "\ntipos incompativeis. 3\n";
        throw runtime_error(errMsg.str());
      }
      else if (id->type != Type::Integer && id->type != constType)
      {
        remove("file.asm");
        stringstream errMsg;
        errMsg << _numLines_ << "\ntipos incompativeis. 3\n";
        throw runtime_error(errMsg.str());
      }
        //------Assembly--------------------------------------
        id->addr = CodeGen::allocId(id->type, constLex); //declarando variável
        //----------------------------------------------------
    }
    

    // Repetir enquanto _lexreg_.token e igual a ','
    while (_lexreg_.token == Token::Comma)
    {
      // Declaracao de outro Identificador
      matchToken(Token::Comma);

      id = _lexreg_.addr;
      matchToken(Token::Id);
      if (id->cl != Class::Empty)
      {
        remove("file.asm");
        stringstream errMsg;
        errMsg << _numLines_ << "\nidentificador ja declarado. [" << id->lexeme << "].\n";
        throw runtime_error(errMsg.str());
      }

      id->cl = Class::VarClass;
      id->type = idType;

      // Caso _lexreg_.token tem um sinal de atribuicao realizar a verificao para constante
      if (_lexreg_.token == Token::Attr)
      {
        matchToken(Token::Attr);

        // Teste de sinal na constante
        signal = false;
        if (_lexreg_.token == Token::Dif)
        {
          signal = true;
          matchToken(Token::Dif);
        }

        constType = _lexreg_.type;
        constLex = _lexreg_.lexeme;
        matchToken(Token::Const);
        // Verificar compatibilidade dos tipos
        //std::cout << "ConstType: " << constType << " ConstLex: " << constLex << "\n";
        if (signal)
        {
          if (constType != Type::Integer && constType != Type::Byte)
          {
            remove("file.asm");
            stringstream errMsg;
            errMsg << _numLines_ << "\ntipos incompativeis. 1\n";
            throw runtime_error(errMsg.str());
          }

          constType = Type::Integer;
          // REVERTER SINAL
          constLex = "-" + constLex;
        }

        if (id->type == Type::Integer && (constType != Type::Byte || constType != Type::Integer))
        {
          remove("file.asm");
          stringstream errMsg;
          errMsg << _numLines_ << "\ntipos incompativeis. 3\n";
          throw runtime_error(errMsg.str());
        }
        else if (id->type != Type::Integer && id->type != constType)
        {
          remove("file.asm");
          stringstream errMsg;
          errMsg << _numLines_ << "\ntipos incompativeis. 3\n";
          throw runtime_error(errMsg.str());
        }

        //------Assembly--------------------------------------
        id->addr = CodeGen::allocId(id->type, constLex); //declarando variável
        //----------------------------------------------------
      }
    }

    matchToken(Token::EndCmd);
  }
}

// Regra de atribuicao
void Parser::A()
{
  TSCell *id;
  Type ExpType;
  //std::cout << "ENTREI NO A\n";
  id = _lexreg_.addr;
  matchToken(Token::Id);
  if (id->cl == Class::Empty)
  {
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\nidentificador nao declarado [" << id->lexeme << "].\n";
    throw runtime_error(errMsg.str());
  }

  if (id->cl == Class::ConstClass)
  {
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\nclasse de identificador incompatível [" << id->lexeme << "].\n";
    throw runtime_error(errMsg.str());
  }

  matchToken(Token::Attr);
  std::cout << "IDTYPE: " << id->type << "\n";
  _temporarios_ = 0; // contador de temporarios renicializado
  Exp(ExpType); // Expressao a ser atribuida ao identificador

  // Verificar Tipos de expressao
  if (id->type == Type::Integer && (ExpType != Type::Byte || ExpType != Type::Integer))
  {
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\ntipos incompativeis. 3\n";
    throw runtime_error(errMsg.str());
  }
  else if (id->type != Type::Integer && id->type != id->type)
  {
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\ntipos incompativeis. 3\n";
    throw runtime_error(errMsg.str());
  }

  matchToken(Token::EndCmd);
}

// Regra de escrita
void Parser::IO()
{
  TSCell *id;
  Type ExpType;
  //  _lexreg_.token  corresponde ao inicio do comando de leitura
  if (_lexreg_.token == Token::Readln)
  {

    matchToken(Token::Readln);
    matchToken(Token::OpenParentheses);

    id = _lexreg_.addr;
    matchToken(Token::Id);
    if (id->cl == Class::Empty)
    {
      remove("file.asm");
      stringstream errMsg;
      errMsg << _numLines_ << "\nidentificador nao declarado [" << id->lexeme << "].\n";
      throw runtime_error(errMsg.str());
    }
    if (id->cl == Class::ConstClass)
    {
      remove("file.asm");
      stringstream errMsg;
      errMsg << _numLines_ << "\nclasse de identificador incompatível [" << id->lexeme << "].\n";
      throw runtime_error(errMsg.str());
    }

    if (id->type == Type::Boolean)
    {
      remove("file.asm");
      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis. 7\n";
      throw runtime_error(errMsg.str());
    }

    matchToken(Token::CloseParentheses);
    matchToken(Token::EndCmd);
  }
  else if (_lexreg_.token == Token::Write)
  {
    //  _lexreg_.token  corresponde ao inicio do comando de escrita sem quebra de linha
    matchToken(Token::Write);
    matchToken(Token::OpenParentheses);
    Exp(ExpType);
    if (ExpType == Type::Boolean)
    {
      remove("file.asm");
      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis. 8\n";
      throw runtime_error(errMsg.str());
    }
    // Equanto _lexreg_.token  igual ',' repita
    while (_lexreg_.token == Token::Comma)
    {
      // Outra expressao para ser realizada
      matchToken(Token::Comma);

      Exp(ExpType);
      if (ExpType == Type::Boolean)
      {
        remove("file.asm");
        stringstream errMsg;
        errMsg << _numLines_ << "\ntipos incompativeis. 9\n";
        throw runtime_error(errMsg.str());
      }
    }

    matchToken(Token::CloseParentheses);
    matchToken(Token::EndCmd);
  }
  else
  {

    //  _lexreg_.token  corresponde ao inicio do comando de escrita com quebra de linha
    matchToken(Token::Writeln);
    matchToken(Token::OpenParentheses);

    Exp(ExpType);
    if (ExpType == Type::Boolean)
    {
      remove("file.asm");
      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis. 10\n";
      throw runtime_error(errMsg.str());
    }

    // Equanto _lexreg_.token  igual ',' repita
    while (_lexreg_.token == Token::Comma)
    {
      // Outra expressao para ser realizada
      matchToken(Token::Comma);

      Exp(ExpType);
      if (ExpType == Type::Boolean)
      {
        remove("file.asm");
        stringstream errMsg;
        errMsg << _numLines_ << "\ntipos incompativeis. 11\n";
        throw runtime_error(errMsg.str());
      }
    }

    matchToken(Token::CloseParentheses);
    matchToken(Token::EndCmd);
  }
}

void Parser::L()
{
  Type ExpType;
  matchToken(Token::While);

  matchToken(Token::OpenParentheses);
  Exp(ExpType);
  if (ExpType != Type::Boolean)
  {
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\ntipos incompativeis. 12\n";
    throw runtime_error(errMsg.str());
  }

  matchToken(Token::CloseParentheses);

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
}

// Regra de Teste
void Parser::T()
{
  Type ExpType;
  // std::cout << "Entrei no T\n"
  matchToken(Token::If);
  matchToken(Token::OpenParentheses);

  Exp(ExpType);
  if (ExpType != Type::Boolean)
  {
    remove("file.asm");
    stringstream errMsg;
    errMsg << _numLines_ << "\ntipos incompativeis. 13\n";
    throw runtime_error(errMsg.str());
  }

  matchToken(Token::CloseParentheses);

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
    matchToken(Token::Endif);
  }
  else
    Cmd();

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
}

// Regra da expressao
void Parser::Exp(Type &ExpType)
{

  Type ExpSType;
  Type ExpS1Type;
  Token op;
  bool typeError;

  ExpS(ExpSType);
  ExpType = ExpSType;

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
      matchToken(Token::LessThen);
    }

    ExpS(ExpS1Type);

    typeError = false;
    // Se for uma operacao de comparacao de igualdade
    if (op == Token::Equal)
    {
      if ((ExpType == Type::Integer || ExpType == Type::Byte) && (ExpS1Type == Type::Byte || ExpS1Type == Type::Integer))
      {
      }
      else if (ExpType == Type::String && ExpS1Type == Type::String)
      {
      }
      else
        typeError = true;
    }
    else
    {
      // Se for uma operacao de comparacao artimetica
      if (!((ExpType == Type::Integer || ExpType == Type::Byte) && (ExpS1Type == Type::Byte || ExpS1Type == Type::Integer)))
        typeError = true;
    }
    // Se tiver sido encotrado algum erro de tipo
    if (typeError)
    {
      remove("file.asm");
      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis. 14\n";
      throw runtime_error(errMsg.str());
    }

    // Novo tipo para o resultado da expressao
    ExpType = Type::Boolean;
  }
}

// Regra do primeiro nivel de precedencia
void Parser::ExpS(Type &ExpSType)
{
  Type Itype;
  Type I1type;
  Token op;
  int signal = 0;
  bool typeError;

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

  I(Itype);
  // Executar mudanca de sinal caso seja necessario
  if (signal == 1)
  {
    if (Itype == Type::Boolean)
    {
      remove("file.asm");
      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis. 15\n";
      throw runtime_error(errMsg.str());
    }
  }
  else if (signal == -1)
  {
    if (Itype != Type::Integer || Itype != Type::Byte)
    {
      remove("file.asm");
      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis. 16\n";
      throw runtime_error(errMsg.str());
    }
    Itype = Type::Integer;
    // Negativar valor aqui
  }

  ExpSType = Itype;

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

    I(I1type);

    typeError = false;
    // Verificar tipo para cada tipo operador
    if (op == Token::Sum)
    {
      if ((ExpSType == Type::Integer || ExpSType == Type::Byte) && (I1type == Type::Integer || I1type == Type::Byte))
      {
        // Soma aritemetica
        ExpSType = Type::Integer;
      }
      else if (ExpSType == Type::String && I1type == Type::String)
      {
        // Concatencao de string
        ExpSType = Type::String;
      }
      else
        typeError = true;
    }
    else if (op == Token::Dif)
    {
      if ((ExpSType == Type::Integer || ExpSType == Type::Byte) && (I1type == Type::Integer || I1type == Type::Byte))
      {
        // Diferenca aritmetica
        ExpSType = Type::Integer;
      }
      else
        typeError = true;
    }
    else
    {
      // Adicao logica (OR)
      if (ExpSType != Type::Boolean && I1type != Type::Boolean)
        typeError = true;
    }

    if (typeError)
    {
      remove("file.asm");
      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis. 17\n";
      throw runtime_error(errMsg.str());
    }
    // EXPS.ADDR = RESULTADO
  }
}

// Regra do segundo nivel de precedencia
void Parser::I(Type &Itype)
{
  Type Jtype;
  Type J1type;
  Token op;
  bool typeError;

  J(Jtype);
  Itype = Jtype;

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

    J(J1type);
    std::cout << "Itype: " << Itype << "  J1type " << J1type << "\n";
    typeError = false;
    if (op == Token::Multi)
    {
      // Operacao de multiplicao arimetica
      if ((Itype == Type::Integer || Itype == Type::Byte) && (J1type == Type::Integer || J1type == Type::Byte))
        Itype = Type::Integer;
      else
      {
        typeError = true;
      }
    }
    else if (op == Token::Div)
    {
      // Operacao de divisao aritimetica
      // Realizar o castig para inteiro casi um dos membros seja byte
      if (Itype == Type::Byte)
      {
        Itype = Type::Integer;
      }
      if (J1type == Type::Byte)
      {
        J1type = Type::Integer;
      }

      if (Itype != Type::Integer || J1type != Type::Integer)
        typeError = true;
    }
    else
    {
      // Multiplicao Logica (AND)
      if (Itype != Type::Boolean && J1type != Type::Boolean)
        typeError = true;
    }
    if (typeError)
    {
      stringstream errMsg;
      errMsg << _numLines_ << "\ntipos incompativeis. 18\n";
      throw runtime_error(errMsg.str());
    }
  }
}

// Regra do terceiro nivel de precedencia
void Parser::J(Type &Jtype)
{
  TSCell *id;
  Type constType;
  string constLex;
  Type J1Type;
  Type ExpType;
  bool typeError;

  if (_lexreg_.token == Token::Not)
  {
    // Negacao logica
    matchToken(Token::Not);
    J(J1Type);

    if (J1Type == Type::Boolean)
      Jtype = J1Type;
    else
      typeError = true;
  }
  else if (_lexreg_.token == Token::OpenParentheses)
  {
    // Nova expresao com maior prioridade
    matchToken(Token::OpenParentheses);
    Exp(ExpType);
    matchToken(Token::CloseParentheses);
    Jtype = ExpType;
  }
  else if (_lexreg_.token == Token::Id)
  {
    // Indentificador
    id = _lexreg_.addr;
    matchToken(Token::Id);
    if (id->cl == Class::Empty)
    {
      stringstream errMsg;
      errMsg << _numLines_ << "\nidentificador nao declarado [" << id->lexeme << "].\n";
      throw runtime_error(errMsg.str());
    }

    Jtype = id->type;
  }
  else
  {
    // Constante
    constLex = _lexreg_.lexeme;
    constType = _lexreg_.type;
    matchToken(Token::Const);
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
    CodeGen::start(); //segmentos principais do assembly
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
  if (file.is_open())
  {
    file.close();
  }
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