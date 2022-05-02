/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#include "flag.h"
#include <game/server/teams.h>

#include <game/server/gamecontext.h>

CFlag::CFlag(CGameWorld *pGameWorld, int Team, int ddraceTeam)
: CEntity(pGameWorld, CGameWorld::ENTTYPE_FLAG)
{
	m_Team = Team;
	m_ProximityRadius = ms_PhysSize;
	m_pCarryingCharacter = NULL;
	m_GrabTick = 0;
	m_DDrTeam = ddraceTeam;

	Reset();
}

void CFlag::Reset()
{
	m_pCarryingCharacter = NULL;
	m_AtStand = 1;
	m_Pos = m_StandPos;
	m_Vel = vec2(0,0);
	m_GrabTick = 0;
}

void CFlag::TickPaused()
{
	++m_DropTick;
	if(m_GrabTick)
		++m_GrabTick;
}

void CFlag::Snap(int SnappingClient)
{
	if(NetworkClipped(SnappingClient))
		return;
	int64_t TeamMask = -1LL;
	CGameTeams * teams = m_pGameWorld->GameServer()->m_pController->p_Teams;
		TeamMask = teams->TeamMask(m_DDrTeam, -1, SnappingClient);

	// return;
	if(SnappingClient != SERVER_DEMO_CLIENT && !CmaskIsSet(TeamMask, SnappingClient))
		return;

	if(teams->m_Core.Team(SnappingClient) != m_DDrTeam)
		return;

	CNetObj_Flag *pFlag = (CNetObj_Flag *)Server()->SnapNewItem(NETOBJTYPE_FLAG, m_Team, sizeof(CNetObj_Flag));
	if(!pFlag)
		return;

	pFlag->m_X = (int)m_Pos.x;
	pFlag->m_Y = (int)m_Pos.y;
	pFlag->m_Team = m_Team;
}

