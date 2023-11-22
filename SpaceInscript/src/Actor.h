#pragma once
#include "Core.h"
#include "GameObject.h"
#include "Controller/Controller.h"

class Renderer;

/* Actors are derived from GameObject and can be possessed by a controller.
* It has basic functionalities for movement and collisions.
*/
class Actor: public GameObject
{
public:
	Actor(int id, std::string symbol): GameObject(id, symbol)
	{

	}


	// Called each frame
	void Update() override
	{
		if (!m_active)
		{
			return;
		}

		if (m_controller)
		{
			m_controller->Update();
		}

		OnUpdate();
	}

	// Subclasses can use it for additional behaviour 
	// called each game tick
	virtual void OnUpdate() 
	{
		
	}

	bool IsColliding(const Actor* otherActor)
	{
		Position otherPos = otherActor->GetPosition();
		Position thisPos = this->GetPosition();

		return (otherPos.x == thisPos.x) && (otherPos.y == thisPos.y);
	}


	void MoveUp()
	{
		this->SetY(this->GetY() - 1);
	}

	void MoveDown()
	{
		this->SetY(this->GetY() + 1);
	}

	void MoveLeft()
	{
		this->SetX(this->GetX() - 1);
	}

	void MoveRight()
	{
		this->SetX(this->GetX() + 1);
	}

	void SetController(Controller* controller)
	{
		m_controller = controller;
	}

	Controller* GetController()
	{
		return m_controller;
	}

	bool IsActive()
	{
		return m_active;
	}

	// If false, the ActorManager will ignore it
	// and the Update function will not be called
	void SetActive(bool isActive)
	{
		m_active = isActive;
	}

	bool IsDestroyed()
	{
		return m_isDestroyed;
	}

	// When called, the Actor will be marked as destroyed
	// and the object will be deleted in the next frame
	void Destroy()
	{
		m_isDestroyed = true;
	}


private:
	bool m_active = true;
	bool m_isDestroyed = false;

	Controller* m_controller = nullptr;
};



