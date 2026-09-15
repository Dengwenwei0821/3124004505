#pragma once
#include <exception>
#include <string>

// 命令行参数数量异常
class ArgumentCountException : public std::exception
{
public:
    ArgumentCountException(const std::string& msg) : m_msg(msg) {}
    const char* what() const throw() { return m_msg.c_str(); }
private:
    std::string m_msg;
};

// 文件打开异常
class FileOpenException : public std::exception
{
public:
    FileOpenException(const std::string& msg) : m_msg(msg) {}
    const char* what() const throw() { return m_msg.c_str(); }
private:
    std::string m_msg;
};

// 文件为空异常
class EmptyFileException : public std::exception
{
public:
    EmptyFileException(const std::string& msg) : m_msg(msg) {}
    const char* what() const throw() { return m_msg.c_str(); }
private:
    std::string m_msg;
};

// 文本特征为空异常
class EmptyFeatureException : public std::exception
{
public:
    EmptyFeatureException(const std::string& msg) : m_msg(msg) {}
    const char* what() const throw() { return m_msg.c_str(); }
private:
    std::string m_msg;
};
