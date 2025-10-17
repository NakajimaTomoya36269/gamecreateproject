#pragma once

class IScene
{
public:
	// コンストラクタ
	IScene(void);

	// デストラクタ
	virtual ~IScene(void);

	// 初期化
	virtual void Initialize(void);

	// 更新
	virtual void Update(void);

	// 描画
	virtual void Draw(void);

	// 解放
	virtual void Finalize(void);
};