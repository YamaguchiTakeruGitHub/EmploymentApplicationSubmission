#pragma once
#include "../Component/Base/Component.h"
#include "../Component/Base/ComponentCommon.h"

/// <summary>
/// すべてのオブジェクトを仲介するクラス(別名Acter)
/// </summary>
class Entity
{
private:
	//マップで名前とポインタを指定できるようにしたコンポーネント
	std::unordered_map<std::string, std::shared_ptr<Component>> components;

protected:
	
	/// <summary>
	/// コンポーネントを生成する
	/// </summary>
	/// <typeparam name="T">任意のクラス</typeparam>
	/// <typeparam name="...Args">0個以上の可変パラメータ</typeparam>
	/// <param name="..._args">任意の引数</param>
	template<typename T, typename... Args>
	void AddComponent(Args&&... _args)
	{
		components[typeid(T).name()] = std::make_shared<T>(std::forward<Args>(_args)...);
	}

	/// <summary>
	/// コンポーネントを取得する
	/// </summary>
	/// <typeparam name="T">任意のクラス</typeparam>
	/// <returns>生成したコンポーネントへのインスタンス化</returns>
	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		//イテレーター
		auto it = components.find(typeid(T).name());
		if (it != components.end())
		{
			return std::dynamic_pointer_cast<T>(it->second);
		}
		return nullptr;
	}

	/// <summary>
	/// コンポーネントの初期化
	/// </summary>
	void InitComponent();

	/// <summary>
	/// コンポーネントの更新
	/// </summary>
	void UpdateComponent();
	
	/// <summary>
	/// コンポーネントの描画
	/// </summary>
	void DrawComponent();
	
	/// <summary>
	/// コンポーネントの解放
	/// </summary>
	void FinalComponent();
	

};
