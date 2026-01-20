#pragma once

#include "vivid.h"
#include <vector>
#include <string>

class CCSVLoader
{
public:
	// コンストラクタ
	CCSVLoader(void);

	// デストラクタ
	~CCSVLoader(void);

	// 読み込み
	void Load(const std::string& file_name);

	// 解放
	void Unload(void);

	// 横に並んでいる数を取得
	int GetCols(void);

	// 縦に並んでいる数を取得
	int GetRows(void);

	// データ数を取得
	int GetDataCount(void);

	// 指定されたデータを文字列で取得
	std::string GetString(int rows, int cols);

	// 指定されたデータ
	int GetInteger(int rows, int cols);

	// 指定されたデータを実数に変換して取得
	float GetFloat(int rows, int cols);

private:
	using CSV_DATA = std::vector<std::string>;

	CSV_DATA    m_Data;     // データ
	int         m_Cols;     // 横に並んでいる数
	int         m_Rows;     // 縦に並んでいる数
};