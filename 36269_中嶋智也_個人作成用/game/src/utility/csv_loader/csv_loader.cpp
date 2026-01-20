#include "csv_loader.h"
#include <fstream>
#include <sstream>

// コンストラクタ
CCSVLoader::CCSVLoader(void)
	: m_Cols(0)
	, m_Rows(0)
{
	m_Data.clear();
}

// デストラクタ
CCSVLoader::~CCSVLoader(void)
{
}

// ファイルの読み込み
void CCSVLoader::Load(const std::string& file_name)
{
    Unload();

    FILE* fp = nullptr;
    if (fopen_s(&fp, file_name.c_str(), "r") != 0 || !fp)
        return;

    std::string item;
    int c = 0;

    while ((c = fgetc(fp)) != EOF)
    {
        char t = (char)c;

        if (t == ',')
        {
            m_Data.push_back(item);
            item.clear();
        }
        else if (t == '\n')
        {
            if (!item.empty() && item.back() == '\r')
                item.pop_back();

            m_Data.push_back(item);
            item.clear();
            ++m_Rows;
        }
        else
        {
            item += t;
        }
    }

    // 最終セル対策
    if (!item.empty())
    {
        m_Data.push_back(item);
        ++m_Rows;
    }

    fclose(fp);

    if (m_Rows > 0)
        m_Cols = (int)m_Data.size() / m_Rows;
}

// 解放
void CCSVLoader::Unload(void)
{
	m_Data.clear();

	m_Cols = m_Rows = 0;
}

// 横に並んでいる数を取得
int CCSVLoader::GetCols(void)
{
	return m_Cols;
}

// 縦に並んでいる数を取得
int CCSVLoader::GetRows(void)
{
	return m_Rows;
}

// データ数を取得
int CCSVLoader::GetDataCount(void)
{
	return (int)m_Data.size();
}

// 指定されたデータを文字列で取得
std::string CCSVLoader::GetString(int rows, int cols)
{
    return m_Data[(rows * m_Cols) + cols];
}

// 指定されたデータ
int CCSVLoader::GetInteger(int rows, int cols)
{
	return stoi(m_Data[(rows * m_Cols) + cols]);
}

// 指定されたデータを実数に変換して取得
float CCSVLoader::GetFloat(int rows, int cols)
{
	return stof(m_Data[(rows * m_Cols) + cols]);
}
