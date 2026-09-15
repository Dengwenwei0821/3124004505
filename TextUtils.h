#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class TextUtils
{
public:
    // GBK字符串转换为宽字符字符串（适配Windows默认编码）
    static std::wstring gbkToWstring(const std::string& gbkStr);

    // 过滤非中文字符，仅保留Unicode中文范围内的字符
    static std::wstring filterNonChinese(const std::wstring& text);

    // 生成字符二元语法（Bigram）特征列表
    static std::vector<std::wstring> generateBigram(const std::wstring& text);

    // 统计特征的词频，返回词频映射
    static std::unordered_map<std::wstring, int> calcWordFreq(const std::vector<std::wstring>& features);
};
