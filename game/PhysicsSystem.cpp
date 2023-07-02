#include "PhysicsSystem.h"


void PhysicsSystem::update() {
	for (auto& entity : enteties) {

		auto& body = Coordinator::getInstance()->GetComponent<Body>(entity).body;
		auto& transform = Coordinator::getInstance()->GetComponent<Transform>(entity);
		
		transform.rect.x = body->GetPosition().x - transform.rect.w/2;
		transform.rect.y = body->GetPosition().y - transform.rect.h / 2;

	}
}