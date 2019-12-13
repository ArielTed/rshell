#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <cstddef> 
#include <stack>

bool isOperator(const std::string &str)
{
    bool verif = false;

    if (str == ";" || str == "&&" || str == "||" || str == "|" || str == "<" || str == ">" || str == ">>")
        verif = true;
    
    return verif;
}

bool areParanthesesBalanced(const std::string &str) 
{ 
    std::stack<char> s; 
  
    for (int i = 0; i < str.length(); i++) 
    { 
        if (str[i] == ')' && s.empty())
            return false;

        if (str[i] == '(') 
        { 
            s.push(str[i]); 
            continue; 
        } 
  
        if (str[i] == ')' && !s.empty())
        {
            s.pop();
        }
    } 

    return (s.empty()); 
}

bool isThereParentheses(const std::string &str)
{
    bool verif = false;

    if (str.find('(') != std::string::npos || str.find(')') != std::string::npos)
    {
        verif = true;
    }

    return verif;
}

void removeSpacesBetweenParentheses(std::string &str)
{
    for (int j = 0; j < str.length(); j++)
    {
        if (str[j] == '(' && j + 1 < str.length() && str[j + 1] == ' ')
            str.erase(str.begin() + j + 1);
        if (str[j] == ' ' && j + 1 < str.length() && str[j + 1] == ')')
            str.erase(str.begin() + j);
    }
}

void removeFirstAndLastParentheses(std::string &str)
{
    if (str.front() == '(')
        str.erase(str.begin() + 0);
    if (str.back() == ')')
        str.pop_back();
}

void split(const std::string &str, std::vector<std::string> &vector_tokens)
{
    std::string const delims = " \t";

    size_t begin, pos = 0;
    while ((begin = str.find_first_not_of(delims, pos)) != std::string::npos)
    {
        pos = str.find_first_of(delims, begin + 1);
        vector_tokens.push_back(str.substr(begin, pos - begin));
    }
}

std::vector<std::string> parserHelper(const std::string &str)
{
    std::vector<std::string> tokens;
    std::vector<std::string> vector_tokens;
        
    split(str, vector_tokens);

    for (int i = 0; i < vector_tokens.size(); i++)
    {
        if (vector_tokens[i].front() == '#')
        {
            break;
        }
        if (isThereParentheses(vector_tokens[i]))
        {
            std::string str = vector_tokens[i] + " ";
            i++;
            while (i < vector_tokens.size() && !areParanthesesBalanced(str))
            {
                if (vector_tokens[i].front() == '#')
                {
                    tokens.push_back(str);
                    return tokens;
                }
                str += vector_tokens[i] + " ";
                i++;
            }
            while (str.back() == ' ')
                str.pop_back();
            if (str.back() == ';' && str.size() > 1)
            {
                str.pop_back();
                while (str.back() == ' ')
                    str.pop_back();
                tokens.push_back(str);
                tokens.push_back(";");
            }
            else tokens.push_back(str);
            if (i >= vector_tokens.size())
                break;
        }
        if (vector_tokens[i].front() == '\"')
        {
            std::string str;
            while (vector_tokens[i].back() != '\"' && vector_tokens[i][vector_tokens[i].length() - 2] != '\"')
            {
                str += vector_tokens[i] + " ";
                i++;
            }
            str += vector_tokens[i];
            i++;
            while (str.back() == ' ')
                str.pop_back();
            if (str.back() == ';' && str.size() > 1)
            {
                str.pop_back();
                tokens.push_back(str);
                tokens.push_back(";");
            }
            else tokens.push_back(str);
            if (i >= vector_tokens.size())
                break;
        }
        if (vector_tokens[i].back() == ';' && vector_tokens[i].size() > 1)
        {
            vector_tokens[i].pop_back();
            tokens.push_back(vector_tokens[i]);
            tokens.push_back(";");
        }
        else tokens.push_back(vector_tokens[i]);
    }
    
    return tokens;
}

std::vector<std::string> Parser(const std::string &str)
{
    std::vector<std::string> vector_tokens = parserHelper(str);
    
    std::vector<std::string> tokens;

    int i = 0;
    while (i < vector_tokens.size())
    {
        std::string str;
        while (i < vector_tokens.size() && !isOperator(vector_tokens[i]))
        {
            str += vector_tokens[i] + " ";
            i++;
        }
        if (str.size() > 0)
        {
            while (str.back() == ' ')
                str.pop_back();
            removeSpacesBetweenParentheses(str);
            tokens.push_back(str);
        }

        if (i >= vector_tokens.size())
            break;

        if (isOperator(vector_tokens[i]))
        {
            tokens.push_back(vector_tokens[i]);
            i++;
        }
    }

    return tokens;
}

#endif
