/*
 * Copyright (C) 2017 Incognito
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "main.h"

#include "core.h"

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
		if (p == core->getData()->players.end())
		{
			Player player(playerid);
			core->getData()->players.insert(std::make_pair(playerid, player));
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	core->getData()->players.erase(playerid);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid)
{
	std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		p->second.requestingClass = false;
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid)
{
	std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		p->second.requestingClass = true;
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterCheckpoint(int playerid)
{
	std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeCheckpoint != p->second.visibleCheckpoint)
		{
			int checkpointid = p->second.visibleCheckpoint;
			p->second.activeCheckpoint = checkpointid;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnPlayerEnterDynamicCP", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(checkpointid));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveCheckpoint(int playerid)
{
	std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeCheckpoint == p->second.visibleCheckpoint)
		{
			int checkpointid = p->second.activeCheckpoint;
			p->second.activeCheckpoint = 0;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnPlayerLeaveDynamicCP", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(checkpointid));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterRaceCheckpoint(int playerid)
{
	std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeRaceCheckpoint != p->second.visibleRaceCheckpoint)
		{
			int checkpointid = p->second.visibleRaceCheckpoint;
			p->second.activeRaceCheckpoint = checkpointid;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnPlayerEnterDynamicRaceCP", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(checkpointid));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveRaceCheckpoint(int playerid)
{
	std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
	if (p != core->getData()->players.end())
	{
		if (p->second.activeRaceCheckpoint == p->second.visibleRaceCheckpoint)
		{
			int checkpointid = p->second.activeRaceCheckpoint;
			p->second.activeRaceCheckpoint = 0;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnPlayerLeaveDynamicRaceCP", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(checkpointid));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickUpPickup(int playerid, int pickupid)
{
	for (std::unordered_map<std::pair<int, int>, int, pair_hash>::iterator i = core->getData()->internalPickups.begin(); i != core->getData()->internalPickups.end(); ++i)
	{
		if (i->second == pickupid)
		{
			int dynPickupId = i->first.first;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnPlayerPickUpDynamicPickup", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(dynPickupId));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ)
{
	if (playerobject)
	{
		std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
		if (p != core->getData()->players.end())
		{
			for (std::unordered_map<int, int>::iterator i = p->second.internalObjects.begin(); i != p->second.internalObjects.end(); ++i)
			{
				if (i->second == objectid)
				{
					int dynObjectId = i->first;
					if (response == EDIT_RESPONSE_CANCEL || response == EDIT_RESPONSE_FINAL)
					{
						std::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(dynObjectId);
						if (o != core->getData()->objects.end())
						{
							if (o->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF && o->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
							{
								o->second->comparableStreamDistance = o->second->originalComparableStreamDistance;
								o->second->originalComparableStreamDistance = -1.0f;
							}
						}
						p->second.selectObject = 0;
					}
					for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
					{
						int amxIndex = 0;
						cell amxRetVal = 0;
						if (!amx_FindPublic(*a, "OnPlayerEditDynamicObject", &amxIndex))
						{
							amx_Push(*a, amx_ftoc(fRotZ));
							amx_Push(*a, amx_ftoc(fRotY));
							amx_Push(*a, amx_ftoc(fRotX));
							amx_Push(*a, amx_ftoc(fZ));
							amx_Push(*a, amx_ftoc(fY));
							amx_Push(*a, amx_ftoc(fX));
							amx_Push(*a, static_cast<cell>(response));
							amx_Push(*a, static_cast<cell>(dynObjectId));
							amx_Push(*a, static_cast<cell>(playerid));
							amx_Exec(*a, &amxRetVal, amxIndex);
							if (amxRetVal)
							{
								break;
							}
						}
					}
					return true;
				}
			}
		}
	}
	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float x, float y, float z)
{
	if (type == SELECT_OBJECT_PLAYER_OBJECT)
	{
		std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
		if (p != core->getData()->players.end())
		{
			for (std::unordered_map<int, int>::iterator i = p->second.internalObjects.begin(); i != p->second.internalObjects.end(); ++i)
			{
				if (i->second == objectid)
				{
					int dynObjectId = i->first;
					for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
					{
						int amxIndex = 0;
						cell amxRetVal = 0;
						if (!amx_FindPublic(*a, "OnPlayerSelectDynamicObject", &amxIndex))
						{
							amx_Push(*a, amx_ftoc(z));
							amx_Push(*a, amx_ftoc(y));
							amx_Push(*a, amx_ftoc(x));
							amx_Push(*a, static_cast<cell>(modelid));
							amx_Push(*a, static_cast<cell>(dynObjectId));
							amx_Push(*a, static_cast<cell>(playerid));
							amx_Exec(*a, &amxRetVal, amxIndex);
							if (amxRetVal)
							{
								break;
							}
						}
					}
					return true;
				}
			}
		}
	}
	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerWeaponShot(int playerid, int weaponid, int hittype, int hitid, float x, float y, float z)
{
	bool retVal = true;
	if (hittype == BULLET_HIT_TYPE_PLAYER_OBJECT)
	{
		std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
		if (p != core->getData()->players.end())
		{
			if (!p->second.shotObjects || hitid < 0 || hitid >= MAX_OBJECTS)
				return retVal;

			int internalObjectId = p->second.playerObjectsIndex[hitid];

			if (internalObjectId != 0 && p->second.playerObjectShootable[hitid])
			{
				for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
				{
					int amxIndex = 0;
					cell amxRetVal = 0;
					if (!amx_FindPublic(*a, "OnPlayerShootDynamicObject", &amxIndex))
					{
						amx_Push(*a, amx_ftoc(z));
						amx_Push(*a, amx_ftoc(y));
						amx_Push(*a, amx_ftoc(x));
						amx_Push(*a, static_cast<cell>(internalObjectId));
						amx_Push(*a, static_cast<cell>(weaponid));
						amx_Push(*a, static_cast<cell>(playerid));
						amx_Exec(*a, &amxRetVal, amxIndex);
						if (!amxRetVal)
						{
							retVal = false;
						}
					}
				}
			}
		}
	}
	return retVal;
}


PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerGiveDamageActor(int playerid, int actorid, float amount, int weaponid, int bodypart)
{
	for (std::unordered_map<std::pair<int, int>, int, pair_hash>::iterator i = core->getData()->internalActors.begin(); i != core->getData()->internalActors.end(); ++i)
	{
		if (i->second == actorid)
		{
			int dynActorId = i->first.first;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				cell amxRetVal = 0;
				if (!amx_FindPublic(*a, "OnPlayerGiveDamageDynamicActor", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(bodypart));
					amx_Push(*a, static_cast<cell>(weaponid));
					amx_Push(*a, amx_ftoc(amount));
					amx_Push(*a, static_cast<cell>(dynActorId));
					amx_Push(*a, static_cast<cell>(playerid));
					amx_Exec(*a, &amxRetVal, amxIndex);
					if (amxRetVal)
					{
						break;
					}
				}
			}
			return true;
		}
	}
	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnActorStreamIn(int actorid, int forplayerid)
{
	for (std::unordered_map<std::pair<int, int>, int, pair_hash>::iterator i = core->getData()->internalActors.begin(); i != core->getData()->internalActors.end(); ++i)
	{
		if (i->second == actorid)
		{
			int dynActorId = i->first.first;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnDynamicActorStreamIn", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(forplayerid));
					amx_Push(*a, static_cast<cell>(dynActorId));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnActorStreamOut(int actorid, int forplayerid)
{
	for (std::unordered_map<std::pair<int, int>, int, pair_hash>::iterator i = core->getData()->internalActors.begin(); i != core->getData()->internalActors.end(); ++i)
	{
		if (i->second == actorid)
		{
			int dynActorId = i->first.first;
			for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*a, "OnDynamicActorStreamOut", &amxIndex))
				{
					amx_Push(*a, static_cast<cell>(forplayerid));
					amx_Push(*a, static_cast<cell>(dynActorId));
					amx_Exec(*a, NULL, amxIndex);
				}
			}
			break;
		}
	}
	return true;
}
