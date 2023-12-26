#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

enum TokenType {
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    LITERAL,
    NEWLINE
};

struct Token {
    TokenType type;
    std::string value;
};

std::vector<Token> simpleLexer(const std::string& code) {
    std::vector<Token> tokens;

    std::istringstream stream(code);
    std::string line;

    while (std::getline(stream, line)) {
        std::istringstream lineStream(line);
        std::string token;

        while (lineStream >> token) {
            Token t;
            t.value = token;

            // Identify token type (very basic, you might need to extend it)
            if (token == "int" || token == "void") {
                t.type = KEYWORD;
            } else if (token == "main" || token == "add") {
                t.type = IDENTIFIER;
            } else if (token == "{" || token == "}" || token == ";" || token == "(" || token == ")") {
                t.type = OPERATOR;
            } else if (token.find_first_not_of("0123456789") == std::string::npos) {
                t.type = LITERAL;
            } else {
                t.type = IDENTIFIER; // Assuming anything else is an identifier
            }

            tokens.push_back(t);
        }

        // Add a newline token
        tokens.push_back({ NEWLINE, "\n" });
    }

    return tokens;
}

int main() {
    std::ofstream archivo("result.cpp");
    std::string includes  = "#include <iostream>\n";
    std::string main = R"#(
        int add(int a, int b) {
            return a + b;
        }

        int main(void) {
            std::cout << "Hello from main!" << std::endl;
            std::cout << "Sum of 3 and 2 is: " << add(3, 2) << std::endl;
            return 0;
        }
    )#";

    if(archivo.is_open())  { 
        archivo << includes << std::endl;
        archivo << main << std::endl;
        archivo.close();
    } else {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    // Read "result.cpp" and tokenize its content
    std::ifstream file("result.cpp");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string code = buffer.str();

    std::vector<Token> tokens = simpleLexer(code);

    // Print the tokens
    for (const auto& token : tokens) {
        std::cout << "Type: " << token.type << ", Value: " << token.value << std::endl;
    }

    // Compile and run result.cpp
    int compileResult = std::system("clang++ result.cpp -o result && ./result && rm result");

    if (!compileResult) {
        std::cout << "Compilation and execution successful." << std::endl;
    } else {
        std::cerr << "Error during compilation or execution." << std::endl;
    }

    return 0;
}

