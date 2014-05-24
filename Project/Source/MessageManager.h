//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   MessageManager.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_MESSAGEMANAGER_H__
#define __IGFEB11_IG120_MESSAGEMANAGER_H__

// Library Includes
#include <windows.h>
#include <map>

// Local Includes

// Types
enum EMESSAGECODE
{
	MSG_INVALID = 0,
	MSG_MOUSE_MOVE = 1000,
	MSG_MOUSE_LBUTTONUP  = 1100,
	MSG_MOUSE_LBUTTONDWN = 1101,
	MSG_MOUSE_RBUTTONUP  = 1200,
	MSG_MOUSE_RBUTTONDWN = 1201,

	MSG_KEY_W_UP  = 1501,
	MSG_KEY_W_DWN = 1502,
	MSG_KEY_S_UP  = 1511,
	MSG_KEY_S_DWN = 1512,
	MSG_KEY_A_UP  = 1521,
	MSG_KEY_A_DWN = 1522,
	MSG_KEY_D_UP  = 1531,
	MSG_KEY_D_DWN = 1532,

	MSG_KEY_R_UP  = 1541,
	MSG_KEY_R_DWN = 1542,

	MSG_KEY_Q_DWN = 1601,
	MSG_KEY_E_DWN = 1602,
	MSG_KEY_T_DWN = 1603,
	MSG_KEY_Y_DWN = 1604,
	MSG_KEY_U_DWN = 1605,
	MSG_KEY_I_DWN = 1606,
	MSG_KEY_O_DWN = 1607,
	MSG_KEY_P_DWN = 1608,
	MSG_KEY_F_DWN = 1609,
	MSG_KEY_G_DWN = 1610,
	MSG_KEY_H_DWN = 1611,
	MSG_KEY_J_DWN = 1612,
	MSG_KEY_K_DWN = 1613,
	MSG_KEY_L_DWN = 1614,
	MSG_KEY_Z_DWN = 1615,
	MSG_KEY_X_DWN = 1616,
	MSG_KEY_C_DWN = 1617,
	MSG_KEY_V_DWN = 1618,
	MSG_KEY_B_DWN = 1619,
	MSG_KEY_N_DWN = 1620,
	MSG_KEY_M_DWN = 1621,

	MSG_KEY_ESC_DWN = 1700,
	MSG_KEY_BACKSPACE_DWN = 1701,
	MSG_KEY_ENTER_DWN = 1702,

	MSG_MAX
};

// Constants

// Prototypes
class IMessageTarget;

class CMessageManager
{
    // Member Functions
public:
	 CMessageManager();
	~CMessageManager();

	bool AddMsgTarget(EMESSAGECODE _iMsgCommand, IMessageTarget* _pLogTarget);
	bool RemoveMsgTarget(IMessageTarget* _pLogTarget);

	bool ClearMsgTargets();

	void SendMsgToTargets(EMESSAGECODE _eMessageCode, WPARAM _wParam, LPARAM _lParam); 

protected:

private:

    // Member Variables
public:

protected:

private:
	std::multimap<EMESSAGECODE, IMessageTarget*> m_mmapTargetContainer;

};

#endif // __IGFEB11_IG120_MESSAGEMANAGER_H__
