#pragma once
#include "Singleton.h"
#include "Core.h"
#include "GameObject.h"

static HANDLE hout = nullptr;

inline void PrintToCoordinates(int x, int y, const char* format, ...);
inline void ClearConsole();


class Renderer: public Singleton<Renderer>
{
public:
	void Initialise(int width, int height);

	bool AddGameObject(std::shared_ptr<GameObject> object);
	bool DeleteGameObject(std::shared_ptr<GameObject> object);

	bool IsObjectClipped(const GameObject* object);


	void Update();

private:
	void RenderGameObject(const GameObject* object);
	void RenderGameObjects();
	void DrawWindowFrame();

private:
	int m_width;
	int m_height;

	std::map<int, std::shared_ptr<GameObject>> m_objects;

};


