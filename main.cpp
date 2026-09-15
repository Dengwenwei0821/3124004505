#include <iostream>
#include <iomanip>
#include "common.h"
#include "FileUtils.h"
#include "TextUtils.h"
#include "SimilarityCalculator.h"

int main(int argc, char* argv[])
{
    try
    {
        // 校验命令行参数数量：程序名 + 原文路径 + 抄袭版路径 + 输出路径 = 4个参数
        if (argc != 4)
        {
            throw ArgumentCountException(
                "参数数量错误！\n用法：PaperChecker.exe [原文文件绝对路径] [抄袭版文件绝对路径] [输出答案文件绝对路径]"
            );
        }

        std::string origPath = argv[1];
        std::string plagPath = argv[2];
        std::string outputPath = argv[3];

        // 1. 读取两篇文本文件
        std::string origContent = FileUtils::readFile(origPath);
        std::string plagContent = FileUtils::readFile(plagPath);

        // 2. GBK编码转换为宽字符，便于中文处理
        std::wstring origWstr = TextUtils::gbkToWstring(origContent);
        std::wstring plagWstr = TextUtils::gbkToWstring(plagContent);

        // 3. 文本清洗：过滤标点、数字等非中文字符
        std::wstring origClean = TextUtils::filterNonChinese(origWstr);
        std::wstring plagClean = TextUtils::filterNonChinese(plagWstr);

        if (origClean.empty() || plagClean.empty())
        {
            throw EmptyFileException("文件中未检测到有效中文字符");
        }

        // 4. 提取Bigram文本特征
        std::vector<std::wstring> origBigrams = TextUtils::generateBigram(origClean);
        std::vector<std::wstring> plagBigrams = TextUtils::generateBigram(plagClean);

        // 5. 统计词频
        auto origFreq = TextUtils::calcWordFreq(origBigrams);
        auto plagFreq = TextUtils::calcWordFreq(plagBigrams);

        // 6. 计算余弦相似度（重复率）
        double similarity = SimilarityCalculator::calcCosineSimilarity(origFreq, plagFreq);

        // 7. 将结果写入输出文件
        FileUtils::writeResult(outputPath, similarity);

        // 控制台输出提示
        std::cout << "查重完成，重复率为：" << std::fixed << std::setprecision(2) << similarity << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "运行错误：" << e.what() << std::endl;
        return 1;
    }

    return 0;
}
