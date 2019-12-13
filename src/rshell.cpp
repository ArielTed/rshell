#include "../header/parser.hpp"
#include "../header/base.hpp"
#include "../header/operator.hpp"
#include "../header/semicolon.hpp"
#include "../header/and.hpp"
#include "../header/or.hpp"
#include "../header/pipe.hpp"
#include "../header/input.hpp"
#include "../header/output.hpp"
#include "../header/command.hpp"

bool verifyInput(const std::string &input)
{
    bool condition = false;

    if (input.empty())
    {
        condition = true;
    }
    else if (input.find_first_not_of(" \t#") == std::string::npos)
    {
        condition = true;
    }
    else if (input.front() == '#')
    {
        condition = true;
    }
    else if (input[input.find_first_not_of(" \t")] == '#')
    {
        condition = true;
    }
    else if (input.find('"') != std::string::npos)
    {
        if (input.find_first_of('"', input.find_first_of('"') + 1) == std::string::npos)
        {
            std::cout << "Error: invalid input\n";
            condition = true;
        }
    }
    else if (input.front() == ')')
    {
        std::cout << "Error: invalid input - parentheses unbalanced\n";
        condition = true;
    }
    else if (!areParanthesesBalanced(input))
    {
        std::cout << "Error: invalid input - parentheses unbalanced\n";
        condition = true;
    }
    else if (input.front() == ';' || input.front() == '&' || input.front() == '|' || input.front() == '<' || input.front() == '>') 
    {
        std::cout << "Error: invalid input - can't begin command line with connector\n";
        condition = true;
    }
    else if (input.back() == '&' || input.back() == '|' || input.back() == '<' || input.back() == '>') 
    {
        std::cout << "Error: invalid input - can't end command line with connector other than semicolon\n";
        condition = true;
    }
    else if (input.find_first_not_of(" \t;&&||<>|()#") == std::string::npos)
    {
        std::cout << "Error: invalid input\n";
        condition = true;
    }
    else if (isThereParentheses(input))
    {
        for (int i = 0; i < input.length(); i++)
        {
            if (input[i] == '(' && i + 1 < input.length() && input[i + 1] == ')')
            {
                std::cout << "Error: invalid input - empty parentheses\n";
                condition = true;
                break;
            }
            else if (input[i] == '(' && i + 2 < input.length() && (input[i + 2] == ';' || input[i + 2] == '&' || input[i + 2] == '|' || input[i + 2] == '<' || input[i + 2] == '>'))
            {
                std::cout << "Error: invalid input\n";
                condition = true;
                break;
            }
            else if (input[i] == ')' && i - 2 >= 0 && (input[i - 2] == '&' || input[i - 2] == '|' || input[i - 2] == '<' || input[i - 2] == '>'))
            {
                std::cout << "Error: invalid input\n";
                condition = true;
                break;
            }
            else if (input[i] == '(' && i + 1 < input.length() && input[i + 1] == '#')
            {
                std::cout << "Error: invalid input - # in parentheses\n";
                condition = true;
                break;
            }
        }
        
        std::vector<std::string> tokens = Parser(input);
        if (!areParanthesesBalanced(tokens.back()))
        {
            std::cout << "Error: invalid input - # in parentheses\n";
            condition = true;
        }
    }
    else if (input != "exit")
    {
        std::string temp = input;
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        if (temp == "exit")
        {
            std::cout << "Please write 'exit' in lowercase to exit program\n";
            condition = true;
        }
    }

    return condition;
}

int priority(const std::string &str)
{
    int priority = 0;

    if (isOperator(str))
    {
        if (str == "|" || str == "<" || str == ">" || str == ">>")
            priority = 2;
        else priority = 1;
    }

    return priority;
}

std::vector<std::string> infixToPostfix(const std::vector<std::string> &infix)
{
    std::stack<std::string> s;
    std::vector<std::string> postfix;
    std::string str;
    for (int i = 0; i < infix.size(); i++)
    {
        str = infix[i];
        if (isOperator(str))
        {
            while (!s.empty() && priority(str) <= priority(s.top()))
            {
                postfix.push_back(s.top());
                s.pop();
            }
            s.push(str);
        }
        else
        {
            postfix.push_back(str);
        }
    }
    while (!s.empty())
    {
        postfix.push_back(s.top());
        s.pop();
    }
    return postfix;
}

Base* buildTree(const std::vector<std::string> &infix)
{
    std::vector<std::string> postfix = infixToPostfix(infix);
    
    std::stack<Base*> s;
    std::string str;
    Base* node;
    
    for (int i = 0; i < postfix.size(); ++i)
    {
        str = postfix[i];
        if (isOperator(str))
        {
            if (str == ";")
            {
                node = new Semicolon();
            }
            else if (str == "&&")
            {
                node = new And();
            }
            else if (str == "||")
            {
                node = new Or();
            }
            else if (str == "|")
            {
                node = new Pipe();
            }
            else if (str == "<")
            {
                node = new Input();
            }
            else 
            {
                node = new Output(str);
            }
            if (s.size() > 1)
            {
                Base* temp1 = s.top();
                s.pop();
                Base* temp2 = s.top();
                s.pop();
                node->setLeft(temp2);
                node->setRight(temp1);
            }
            else
            {
                Base* temp = s.top();
                s.pop();
                node->setLeft(temp);
            }
            s.push(node);
        }
        else
        {
            if (isThereParentheses(str))
            {
                removeFirstAndLastParentheses(str);
                std::vector<std::string> tokens = Parser(str);
                Base* temp = buildTree(tokens);
                s.push(temp);
            }
            else
            {
                Base* temp = new Command(str);
                s.push(temp);
            }
        }
    }
    
    Base* root = s.top();
    s.pop();

    return root;
}

int main(int argv, char** argc)
{
    std::cout << "\n\t___ Welcome to RSHELL ___\n";

    char* userName = getlogin();       

    char hostName[1000];
    gethostname(hostName, sizeof hostName);
    std::string host = hostName;
    int index;
    for (int i = 0; i < host.length(); i++)
    {
        if (host[i] == '.')
        {
            index = i;
            break;
        }
    }
    host.erase(index);

    char currentDirectory[1000];

    while (true)
    {
        getcwd(currentDirectory, sizeof currentDirectory);
        std::string cwd = currentDirectory;
        for (int i = cwd.length() - 1; i > 0; i--)
        {
            if (cwd[i] == '/')
            {
                index = i;
                break;
            }
        }
        cwd.erase(0, index + 1);
        
        std::cout << "\n[rshell " << userName << "@" <<  host << " " << cwd << "]$ ";
    
        std::string userInput;               
        getline(std::cin, userInput);

        bool condition = verifyInput(userInput);

        if (!condition)
        {
            std::vector<std::string> infix = Parser(userInput);
            Base* root = buildTree(infix);
            root->Execute();
            delete root;
        }
    }

    return 0;
}
