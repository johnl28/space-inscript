#pragma once
#include "Core.h"
#include "GameObject.h"
#include "Controller/Controller.h"


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

	bool IsColliding(Actor* otherActor)
	{
		auto otherPos = otherActor->GetPosition();
		auto thisPos = this->GetPosition();

		auto thisWidth = this->GetWidth();
		auto otherWidth = otherActor->GetWidth();

		bool isColliding = (otherPos.x < thisPos.x + thisWidth) &&
			(thisPos.x < otherPos.x + otherWidth) &&
			(to_int(otherPos.y) == to_int(thisPos.y));

		if (isColliding) 
		{
			OnCollide(otherActor);
			return true;
		}

		return false;
	}

	virtual void OnCollide(Actor* otherActor)
	{

	}


	void MoveUp()
	{
		this->SetY(this->GetY() - m_speed);
	}

	void MoveDown()
	{
		this->SetY(this->GetY() + m_speed);
	}

	void MoveLeft()
	{
		this->SetX(this->GetX() - m_speed);
	}

	void MoveRight()
	{
		this->SetX(this->GetX() + m_speed);
	}

	void SetSpeed(float speed)
	{
		m_speed = speed;
	}

	void IncreaseSpeed(float speedAmount)
	{
		m_speed += speedAmount;
	}

	void SetController(Controller* controller)
	{
		m_controller = std::unique_ptr<Controller>(controller);
	}

	Controller* GetController()
	{
		return m_controller.get();
	}

	bool IsActive() const
	{
		return m_active;
	}

	// If false, the ActorManager will ignore it
	// and the Update function will not be called
	void SetActive(bool isActive)
	{
		m_active = isActive;
	}

	bool IsDestroyed() const
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
	float m_speed = 1.0f;

	std::unique_ptr<Controller> m_controller = nullptr;
};



