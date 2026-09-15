#include "FileUtils.h"
#include "common.h"
#include <fstream>
#include <sstream>
#include <iomanip>

std::string FileUtils::readFile(const std::string& filePath)
{
    std::ifstream ifs(filePath, std::ios::in);
    if (!ifs.is_open())
    {
        throw FileOpenException("无法打开文件：" + filePath);
    }

    // 一次性读取文件全部内容
    std::stringstream ss;
    ss << ifs.rdbuf();
    std::string content = ss.str();
    ifs.close();

    if (content.empty())
    {
        throw EmptyFileException("文件内容为空：" + filePath);
    }

    return content;
}

void FileUtils::writeResult(const std::string& filePath, double result)
{
    std::ofstream ofs(filePath, std::ios::out);
    if (!ofs.is_open())
    {
        throw FileOpenException("无法打开输出文件：" + filePath);
    }

    // 固定两位小数输出
    ofs << std::fixed << std::setprecision(2) << result;
    ofs.close();
}
