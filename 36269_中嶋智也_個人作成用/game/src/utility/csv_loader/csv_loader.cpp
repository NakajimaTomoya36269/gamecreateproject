#include "csv_loader.h"
#include <fstream>
#include <sstream>

//============================================================
// コンストラクタ
//============================================================
CCSVLoader::CCSVLoader(void)
    : m_Cols(0)
    , m_Rows(0)
{
    m_Data.clear();
}

//============================================================
// デストラクタ
//============================================================
CCSVLoader::~CCSVLoader(void)
{
}

//============================================================
// CSVファイル読み込み
// file_name : 読み込むCSVファイルのパス
// ・コンマ区切りをセルとして扱い、1行ごとに m_Data に格納
// ・行数、列数を自動計算
//============================================================
void CCSVLoader::Load(const std::string& file_name)
{
    Unload(); // 既存データをクリア

    FILE* fp = nullptr;
    if (fopen_s(&fp, file_name.c_str(), "r") != 0 || !fp)
        return;

    std::string item;
    int c = 0;

    while ((c = fgetc(fp)) != EOF)
    {
        char t = (char)c;

        if (t == ',') // セル区切り
        {
            m_Data.push_back(item);
            item.clear();
        }
        else if (t == '\n') // 行区切り
        {
            if (!item.empty() && item.back() == '\r') // Windows改行対策
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

    // 列数計算
    if (m_Rows > 0)
        m_Cols = (int)m_Data.size() / m_Rows;
}

//============================================================
// データ解放
//============================================================
void CCSVLoader::Unload(void)
{
    m_Data.clear();
    m_Cols = m_Rows = 0;
}

//============================================================
// 列数取得
//============================================================
int CCSVLoader::GetCols(void)
{
    return m_Cols;
}

//============================================================
// 行数取得
//============================================================
int CCSVLoader::GetRows(void)
{
    return m_Rows;
}

//============================================================
// データ総数取得
//============================================================
int CCSVLoader::GetDataCount(void)
{
    return (int)m_Data.size();
}

//============================================================
// 指定セルの文字列取得
// rows : 行番号
// cols : 列番号
//============================================================
std::string CCSVLoader::GetString(int rows, int cols)
{
    return m_Data[(rows * m_Cols) + cols];
}

//============================================================
// 指定セルを整数として取得
// 範囲外・空文字・変換失敗時は 0 を返す
//============================================================
int CCSVLoader::GetInteger(int rows, int cols)
{
    if (m_Cols <= 0)
        return 0;

    int index = rows * m_Cols + cols;
    if (index < 0 || index >= (int)m_Data.size())
        return 0;

    const std::string& s = m_Data[index];
    if (s.empty())
        return 0;

    // 改行コード除去
    std::string temp = s;
    if (temp.back() == '\r')
        temp.pop_back();

    try
    {
        return std::stoi(temp);
    }
    catch (...)
    {
        return 0;
    }
}

//============================================================
// 指定セルを浮動小数点として取得
// 範囲外・空文字・変換失敗時は 0.0f を返す
//============================================================
float CCSVLoader::GetFloat(int rows, int cols)
{
    if (m_Cols <= 0)
        return 0.0f;

    int index = rows * m_Cols + cols;
    if (index < 0 || index >= (int)m_Data.size())
        return 0.0f;

    const std::string& s = m_Data[index];
    if (s.empty())
        return 0.0f;

    std::string temp = s;
    if (temp.back() == '\r')
        temp.pop_back();

    try
    {
        return std::stof(temp);
    }
    catch (...)
    {
        return 0.0f;
    }
}
