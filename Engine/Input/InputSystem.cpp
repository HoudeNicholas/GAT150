#include "pch.h"
#include "InputSystem.h"

nc::InputSystem::eButtonState nc::InputSystem::GetButtonState(int id)
{
	eButtonState state = eButtonState::IDLE;

	bool buttonDown = GetButtonDown(id);
	bool prevButtonDown = GetPreviousButtonDown(id);

	if (prevButtonDown == 0 && buttonDown == 1) {
		state = eButtonState::PRESSED;
	} else if (prevButtonDown == 1 && buttonDown == 1) {
		state = eButtonState::HELD;
	} else if (prevButtonDown == 1 && buttonDown == 0) {
		state = eButtonState::RELEASED;
	}

	return state;

}

bool nc::InputSystem::GetButtonDown(int id)
{
	return m_keystate[id];
}

bool nc::InputSystem::GetPreviousButtonDown(int id)
{
	return m_prevKeystate[id];
}

bool nc::InputSystem::startup()
{
	const Uint8* keystate = SDL_GetKeyboardState(&m_numKeys);

	m_keystate = new Uint8[m_numKeys];
	m_prevKeystate = new Uint8[m_numKeys];

	// copy current keystate (source) to m_keystate (destination)
	memcpy(m_keystate, keystate, m_numKeys);
	// copy current keystate to m_prevKeystate
	memcpy(m_prevKeystate, keystate, m_numKeys);

	return true;
}

void nc::InputSystem::shutdown()
{
	delete m_keystate;
	delete m_prevKeystate;
}

void nc::InputSystem::update()
{
	// copy m_keystate (source) to m_prevKeystate (destination)
	memcpy(m_prevKeystate, m_keystate, m_numKeys);
	// get current keystate
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	// copy current keystate to m_keystate
	memcpy(m_keystate, keystate, m_numKeys);

}
