#include "GamePCH.h"

#include "PlayerController.h"

using namespace fw;

PlayerController::PlayerController()
{
    m_Up = false;
    m_Down = false;
    m_Left = false;
    m_Right = false;
	m_Select = false;
}

PlayerController::~PlayerController()
{
}

void PlayerController::OnEvent(fw::Event* pEvent)
{
    //unsigned char keys[2][4] = { { 'W', 'S', 'A', 'D' }, { VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT } };

    if( pEvent->GetType() == "InputEvent" )
    {
        InputEvent* pIE = (InputEvent*)pEvent;

        if( pIE->GetState() == InputState::Pressed )
        {
            if( pIE->GetKeyCode() == 'W' ) m_Up = true;
            if( pIE->GetKeyCode() == 'S' ) m_Down = true;
            if( pIE->GetKeyCode() == 'A' ) m_Left = true;
            if( pIE->GetKeyCode() == 'D' ) m_Right = true;
			if (pIE->GetKeyCode() == VK_SPACE) m_Select = true; 
        }

        if( pIE->GetState() == InputState::Released )
        {
            if( pIE->GetKeyCode() == 'W' ) m_Up = false;
            if( pIE->GetKeyCode() == 'S' ) m_Down = false;
            if( pIE->GetKeyCode() == 'A' ) m_Left = false;
            if( pIE->GetKeyCode() == 'D' ) m_Right = false;
			if (pIE->GetKeyCode() == VK_SPACE) m_Select = false;
        }
    }
}
