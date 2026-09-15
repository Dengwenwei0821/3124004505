#include "SimilarityCalculator.h"
#include "common.h"
#include <cmath>

double SimilarityCalculator::calcCosineSimilarity(const std::unordered_map<std::wstring, int>& freq1,
                                                   const std::unordered_map<std::wstring, int>& freq2)
{
    if (freq1.empty() || freq2.empty())
    {
        throw EmptyFeatureException("文本特征为空，无法计算相似度");
    }

    // 遍历较短的哈希表，减少查找次数
    if (freq1.size() > freq2.size())
    {
        return calcCosineSimilarity(freq2, freq1);
    }

    // 计算两个向量的点积
    double dotProduct = 0.0;
    for (const auto& pair : freq1)
    {
        auto it = freq2.find(pair.first);
        if (it != freq2.end())
        {
            dotProduct += static_cast<double>(pair.second) * it->second;
        }
    }

    // 计算向量1的模长
    double norm1 = 0.0;
    for (const auto& pair : freq1)
    {
        norm1 += static_cast<double>(pair.second) * pair.second;
    }
    norm1 = std::sqrt(norm1);

    // 计算向量2的模长
    double norm2 = 0.0;
    for (const auto& pair : freq2)
    {
        norm2 += static_cast<double>(pair.second) * pair.second;
    }
    norm2 = std::sqrt(norm2);

    // 防止除零（前置校验已兜底，此处为双重保险）
    if (norm1 < 1e-6 || norm2 < 1e-6)
    {
        return 0.0;
    }

    return dotProduct / (norm1 * norm2);
}
