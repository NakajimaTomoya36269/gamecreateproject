#pragma once

#include "vivid.h"
#include "scene/scene.h"
#include "scene/scene_id.h"

class IScene;

class CSceneManager
{
public:
	// インスタンスの取得
	static CSceneManager& GetInstance(void);

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// 解放
	void Finalize(void);

	// シーンの切り替え
	void ChangeScene(SCENE_ID next_scene);

	// シーンのエフェクト描画
	void DrawSceneEffect(void);

private:
	// 切り替え
	void Change(SCENE_ID id);

	// コンストラクタ
	CSceneManager(void);

	// コピーコンストラクタ
	CSceneManager(const CSceneManager& rhs) = delete;

	// デストラクタ
	~CSceneManager(void) = default;

	// 代入演算子
	CSceneManager operator=(const CSceneManager& rhs) = delete;

	// フェードインの更新
	void UpdateFadeIn(void);

	// シーン更新
	void SceneUpdate(void);

	// フェードアウトの更新
	void UpdateFadeOut(void);

	// シーン変更
	void SceneChange(void);

	enum class SCENE_STATE
	{
		FADEIN,					// フェードイン
		SCENE_UPDATE,			// シーン更新
		FADE_OUT,				// フェードアウト
		SCENE_CHANGE,			// シーン変更
	};

	static const int				m_fade_speed;		// フェード速度
	static const vivid::Vector2		m_fade_position;	// フェード位置
	static const unsigned int		m_fade_color;		// フェードカラー
	static const int				m_min_fade_alpha;   // フェード用アルファの最小値
	static const int				m_max_fade_alpha;   // フェード用アルファの最大値

	IScene*	m_Scene;				// シーンクラス
	SCENE_ID	m_NextSceneID;		// 次のシーンID
	SCENE_ID	m_CurrentSceneID;	// 現在のシーンID
	SCENE_STATE	m_SceneState;		// シーンの状態
	bool		m_ChangeScene;		// シーン変更フラグ
	int			m_FadeAlpha;		// フェード時のアルファ値
};