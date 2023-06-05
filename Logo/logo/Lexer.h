#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <utility>

namespace logo {

enum TokenType {TokenSign, TokenNumber, TokenName, TokenKeyword};
typedef std::pair<TokenType, std::string> Token;
typedef std::vector<Token> TokenList;

char const kwRepeat[]   = "repete";
char const kwFctDecl[]  = "pour";
char const kwForward[]  = "avance";
char const kwBackward[] = "recule";
char const kwRight[]    = "droite";
char const kwLeft[]     = "gauche";
char const kwUp[]       = "leve";
char const kwDown[]     = "baisse";
char const kwEnd[]      = "fin";


TokenList getTokens(std::string const &s);

} // namespace logo

#endif // LEXER_H
