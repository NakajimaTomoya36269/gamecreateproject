#pragma once
#include "../scene.h"
#include "vivid.h"

//---------------------------------------------------------
// ゲームオーバーシーンクラス
// IScene を継承し、GameOver画面の処理を担当する
//---------------------------------------------------------
class CGameOver
	: public IScene
{
public:
	// コンストラクタ
	CGameOver(void);

	// デストラクタ
	~CGameOver(void) = default;

	//========================================
	// IScene インターフェース実装
	//========================================

	// 初期化処理（フォント生成・タイマーリセットなど）
	void Initialize(void) override;

	// 毎フレーム更新処理（入力判定・シーン遷移判定）
	void Update(void) override;

	// 描画処理（背景・GameOver画像・テキスト表示）
	void Draw(void) override;

	// 終了処理（必要ならリソース解放）
	void Finalize(void) override;

private:

	//========================================
	// 定数
	//========================================

	static const int	m_enter_font_size;		// 「Push Enter」表示用フォントサイズ
	static const float	m_scene_change_time;	// 自動でタイトルへ戻るまでの時間（フレーム）

	//========================================
	// メンバ変数
	//========================================

	vivid::Vector2		m_Position;				// 基本位置（未使用なら削除可）
	vivid::Vector2		m_EnterPosition;		// 「Push Enter」文字の表示位置
	float				m_SceneChangeTimer;		// シーン切り替え用タイマー（フレームカウント）
};
