#pragma once
#include <unordered_map>
#include <string>

class SimilarityCalculator
{
public:
    // 计算两个词频向量的余弦相似度，返回值范围[0,1]
    static double calcCosineSimilarity(const std::unordered_map<std::wstring, int>& freq1,
                                       const std::unordered_map<std::wstring, int>& freq2);
};
