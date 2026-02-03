#pragma once
#include "vivid.h"
#include "stage_id.h"
#include "../../character_manager/character/character.h"

class ISwitch;

/*
 * IStage
 * ----------------------------
 * ステージ（床・ギミック）の基底クラス。
 *
 * 役割：
 *  - 横スクロールに伴う共通移動処理
 *  - サイズ・位置・IDなどの共通データ管理
 *  - キャラクターとの当たり判定の基盤提供
 *
 * 設計方針：
 *  - Update / Draw / MoveChange は派生クラスで拡張される前提
 *  - ステージ固有の挙動（落下・移動・反転など）は派生側で実装
 *  - 基底では「最低限の責務」のみを持たせる
 */
class IStage
{
public:
	// コンストラクタ
	// ステージサイズと識別用IDを受け取り、共通情報を初期化する
	IStage(int width, int height, STAGE_ID id);

	// デストラクタ
	// 派生クラスを正しく破棄するため virtual
	virtual ~IStage(void) = default;

	// 初期化
	// ステージ生成時または再配置時に呼ばれる
	// 位置・速度・状態を初期化する
	virtual void Initialize(const vivid::Vector2& position);

	// 更新
	// 横スクロール処理などの共通挙動を実装
	// 派生クラスでは override して追加処理を行う
	virtual void Update(void);

	// 描画
	// 基底クラスでは未実装
	// 各ステージが必ず override する前提
	virtual void Draw(void);

	// 解放
	// 共通で解放するものはないため空実装
	// 派生クラスで必要に応じて override
	virtual void Finalize(void);

	// スイッチによる状態変更通知
	// 動く床・反転床などが override して使用する
	virtual void MoveChange(ISwitch* sw);

	// ----- 基本情報取得 -----

	// ステージの幅取得（当たり判定用）
	int GetWidth(void);

	// ステージの高さ取得（当たり判定用）
	int GetHeight(void);

	// 現在位置の取得
	vivid::Vector2 GetPosition(void);

	// ステージIDの取得
	STAGE_ID GetStageID(void);

	// 落下状態の取得
	bool GetIsFalled(void);

	// 落下状態の設定
	void SetIsFalled(bool fall_flag);

	// 強制的に落下状態にする
	void Falled(void);

	// キャラクターとの当たり判定
	// position_x を参照渡しで補正し、横方向のめり込みを防ぐ
	// 派生クラスで挙動を変えたい場合は override 可能
	virtual bool CheckHitCharacter(ICharacter* character, float& position_x);

protected:
	// ----- 共通物理パラメータ -----

	static const float	m_scroll_speed;	// 横スクロール速度
	static const float	m_friction;		// 摩擦係数（慣性減衰）

	// ----- ステージ基本データ -----

	int					m_Width;		// 当たり判定の幅
	int					m_Height;		// 当たり判定の高さ
	STAGE_ID			m_StageID;		// ステージ種別ID
	vivid::Vector2		m_Position;		// 現在位置
	vivid::Vector2		m_StartPosition;// 初期位置（リセット用）
	vivid::Vector2		m_Velocity;		// 移動速度
	bool				m_IsFalled;		// 落下状態フラグ
};
