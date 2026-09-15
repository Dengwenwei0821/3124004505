#pragma once
#include <string>

class FileUtils
{
public:
    // 读取文件全部内容，返回GBK编码字符串
    static std::string readFile(const std::string& filePath);
    // 将查重结果写入文件，保留两位小数
    static void writeResult(const std::string& filePath, double result);
};
