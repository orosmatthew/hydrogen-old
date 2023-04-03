#pragma once

enum class TokenType { none, i64, add, sub, multi, div, left_paren, right_paren };

std::string to_string(TokenType type)
{
    switch (type) {
    case TokenType::none:
        return "none";
    case TokenType::i64:
        return "pos_i64";
    case TokenType::add:
        return "add";
    case TokenType::sub:
        return "sub";
    case TokenType::multi:
        return "multi";
    case TokenType::div:
        return "div";
    case TokenType::left_paren:
        return "left_paren";
    case TokenType::right_paren:
        return "right_paren";
    default:
        return "invalid";
    }
}

struct Token {
    TokenType type;
    std::string value;
};

std::vector<Token> tokenize_file(const std::filesystem::path& path)
{
    std::fstream file(path.c_str(), std::ios::in);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    std::vector<Token> tokens;
    for (size_t i = 0; i < source.size(); i++) {
        if (isdigit(source[i])) {
            std::string num_buf;
            do {
                num_buf.push_back(source[i]);
                i++;
            } while (isdigit(source[i]));
            i--;
            tokens.push_back({ TokenType::i64, num_buf });
        }
        else if (source[i] == '+') {
            tokens.push_back({ TokenType::add, "+" });
        }
        else if (source[i] == '-') {
            tokens.push_back({ TokenType::sub, "-" });
        }
        else if (source[i] == '*') {
            tokens.push_back({ TokenType::multi, "*" });
        }
        else if (source[i] == '/') {
            tokens.push_back({ TokenType::div, "/" });
        }
        else if (source[i] == '(') {
            tokens.push_back({ TokenType::left_paren, "(" });
        }
        else if (source[i] == ')') {
            tokens.push_back({ TokenType::right_paren, ")" });
        }
        else if (source[i] != ' ' && source[i] != '\n' && source[i] != '\r') {
            std::cerr << "[Error] Unexpected token: `" << source[i] << "`" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return tokens;
}