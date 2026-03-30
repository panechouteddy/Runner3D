#pragma once
#include <map>

class Scene;

class SceneManager
{
	Scene* m_pCurrentScene = nullptr;
	std::map<const char*, Scene*> m_pScenes;

public:
	SceneManager();
	~SceneManager();

	Scene* GetCurrentScene() { return m_pCurrentScene; }
	template<typename T>
	T* GetScene();
	void AddScene(const char* name, Scene* scene);
	void ChangeScene(const char* name);
	void ResetCurrentScene();
};

template<typename T>
inline T* SceneManager::GetScene()
{
	for (auto it = m_pScenes.begin(); it != m_pScenes.end(); ++it)
	{
		if (T* t = dynamic_cast<T*>(it->second))
		{
			return t;
		}
	}

	return nullptr;
}

