#include "TextUtils.h"
#include <windows.h>

std::wstring TextUtils::gbkToWstring(const std::string& gbkStr)
{
    // 获取转换所需的宽字符缓冲区大小
    int wlen = MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, nullptr, 0);
    if (wlen <= 0)
    {
        return L"";
    }

    std::wstring wstr(wlen, L'\0');
    MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, &wstr[0], wlen);
    // 移除末尾自动添加的空字符
    wstr.pop_back();
    return wstr;
}

std::wstring TextUtils::filterNonChinese(const std::wstring& text)
{
    std::wstring result;
    result.reserve(text.size()); // 预分配空间，提升性能
    for (wchar_t ch : text)
    {
        // 常用中文字符Unicode范围：0x4E00 - 0x9FA5
        if (ch >= 0x4E00 && ch <= 0x9FA5)
        {
            result += ch;
        }
    }
    return result;
}

std::vector<std::wstring> TextUtils::generateBigram(const std::wstring& text)
{
    std::vector<std::wstring> bigrams;
    size_t len = text.size();
    if (len == 0)
    {
        return bigrams;
    }
    // 文本长度小于2时，直接返回单字特征
    if (len == 1)
    {
        bigrams.push_back(text);
        return bigrams;
    }

    bigrams.reserve(len - 1);
    for (size_t i = 0; i < len - 1; ++i)
    {
        std::wstring gram;
        gram.reserve(2);
        gram += text[i];
        gram += text[i + 1];
        bigrams.push_back(gram);
    }
    return bigrams;
}

std::unordered_map<std::wstring, int> TextUtils::calcWordFreq(const std::vector<std::wstring>& features)
{
    std::unordered_map<std::wstring, int> freqMap;
    freqMap.reserve(features.size()); // 预分配哈希表空间
    for (const auto& feat : features)
    {
        freqMap[feat]++;
    }
    return freqMap;
}
