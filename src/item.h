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

#ifndef ITEM_H
#define ITEM_H

#include "cell.h"
#include "identifier.h"

namespace Item
{
	struct Actor
	{
		Actor();

		int actorId;
		AMX *amx;
		SharedCell cell;
		float comparableStreamDistance;
		float health;
		bool inverseAreaChecking;
		bool invulnerable;
		int modelId;
		float originalComparableStreamDistance;
		Eigen::Vector3f position;
		Eigen::Vector3f positionOffset;
		int priority;
		int references;
		float rotation;
		float streamDistance;

		struct Anim
		{
			Anim();

			float delta;
			bool freeze;
			std::string lib;
			bool loop;
			bool lockx;
			bool locky;
			std::string name;
			int references;
			int time;
		};

		std::shared_ptr<Anim> anim;

		std::unordered_set<int> areas;
		std::vector<int> extras;
		std::unordered_map<int, std::vector<int> > extraExtras;
		std::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		std::unordered_set<int> worlds;

		static Identifier identifier;

		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};

	struct Area
	{
		Area();

		AMX *amx;
		int areaId;
		SharedCell cell;
		float comparableSize;
		Eigen::Vector2f height;
		int priority;
		int references;
		float size;
		bool spectateMode;
		int type;

		std::variant<Polygon2d, Box2d, Box3d, Eigen::Vector2f, Eigen::Vector3f> position;

		struct Attach
		{
			Attach();

			Eigen::Vector2f height;
			std::tuple<int, int, int> object;
			int player;
			std::variant<Polygon2d, Box2d, Box3d, Eigen::Vector2f, Eigen::Vector3f> position;
			Eigen::Vector3f positionOffset;
			int references;
			int vehicle;

			EIGEN_MAKE_ALIGNED_OPERATOR_NEW
		};

		std::shared_ptr<Attach> attach;

		std::unordered_set<int> areas;
		std::vector<int> extras;
		std::unordered_map<int, std::vector<int> > extraExtras;
		std::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		std::unordered_set<int> worlds;

		static Identifier identifier;

		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};

	struct Checkpoint
	{
		Checkpoint();

		AMX *amx;
		SharedCell cell;
		int checkpointId;
		float comparableStreamDistance;
		bool inverseAreaChecking;
		float originalComparableStreamDistance;
		Eigen::Vector3f position;
		Eigen::Vector3f positionOffset;
		int priority;
		int references;
		float size;
		bool streamCallbacks;
		float streamDistance;

		std::unordered_set<int> areas;
		std::vector<int> extras;
		std::unordered_map<int, std::vector<int> > extraExtras;
		std::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		std::unordered_set<int> worlds;

		static Identifier identifier;

		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};

	struct MapIcon
	{
		MapIcon();

		AMX *amx;
		SharedCell cell;
		int color;
		float comparableStreamDistance;
		bool inverseAreaChecking;
		int mapIconId;
		float originalComparableStreamDistance;
		Eigen::Vector3f position;
		Eigen::Vector3f positionOffset;
		int priority;
		int references;
		bool streamCallbacks;
		float streamDistance;
		int style;
		int type;

		std::unordered_set<int> areas;
		std::vector<int> extras;
		std::unordered_map<int, std::vector<int> > extraExtras;
		std::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		std::unordered_set<int> worlds;

		static Identifier identifier;

		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};

	struct Object
	{
		Object();

		AMX *amx;
		SharedCell cell;
		float comparableStreamDistance;
		float drawDistance;
		bool inverseAreaChecking;
		int modelId;
		bool noCameraCollision;
		int objectId;
		float originalComparableStreamDistance;
		Eigen::Vector3f position;
		Eigen::Vector3f positionOffset;
		int priority;
		int references;
		int shootable;
		Eigen::Vector3f rotation;
		bool streamCallbacks;
		float streamDistance;

		struct Attach
		{
			Attach();

			int object;
			int player;
			Eigen::Vector3f position;
			Eigen::Vector3f positionOffset;
			int references;
			Eigen::Vector3f rotation;
			bool syncRotation;
			int vehicle;

			std::unordered_set<int> worlds;

			EIGEN_MAKE_ALIGNED_OPERATOR_NEW
		};

		std::shared_ptr<Attach> attach;

		struct Material
		{
			struct Main
			{
				Main();

				int materialColor;
				int modelId;
				int references;
				std::string textureName;
				std::string txdFileName;
			};

			std::shared_ptr<Main> main;

			struct Text
			{
				Text();

				int backColor;
				bool bold;
				int fontColor;
				std::string fontFace;
				int fontSize;
				int references;
				int materialSize;
				std::string materialText;
				int textAlignment;
			};

			std::shared_ptr<Text> text;
		};

		std::unordered_map<int, Material> materials;

		struct Move
		{
			Move();

			int duration;
			std::tuple<Eigen::Vector3f, Eigen::Vector3f, Eigen::Vector3f> position;
			int references;
			std::tuple<Eigen::Vector3f, Eigen::Vector3f, Eigen::Vector3f> rotation;
			float speed;
			std::chrono::steady_clock::time_point time;

			EIGEN_MAKE_ALIGNED_OPERATOR_NEW
		};

		std::shared_ptr<Move> move;

		std::unordered_set<int> areas;
		std::vector<int> extras;
		std::unordered_map<int, std::vector<int> > extraExtras;
		std::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		std::unordered_set<int> worlds;

		static Identifier identifier;

		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};

	struct Pickup
	{
		Pickup();

		AMX *amx;
		SharedCell cell;
		float comparableStreamDistance;
		bool inverseAreaChecking;
		int modelId;
		float originalComparableStreamDistance;
		int pickupId;
		Eigen::Vector3f position;
		Eigen::Vector3f positionOffset;
		int priority;
		int references;
		bool streamCallbacks;
		float streamDistance;
		int type;

		std::unordered_set<int> areas;
		std::vector<int> extras;
		std::unordered_map<int, std::vector<int> > extraExtras;
		std::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		std::unordered_set<int> worlds;

		static Identifier identifier;

		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};

	struct RaceCheckpoint
	{
		RaceCheckpoint();

		AMX *amx;
		SharedCell cell;
		float comparableStreamDistance;
		bool inverseAreaChecking;
		Eigen::Vector3f next;
		float originalComparableStreamDistance;
		Eigen::Vector3f position;
		Eigen::Vector3f positionOffset;
		int priority;
		int raceCheckpointId;
		int references;
		float size;
		bool streamCallbacks;
		float streamDistance;
		int type;

		std::unordered_set<int> areas;
		std::vector<int> extras;
		std::unordered_map<int, std::vector<int> > extraExtras;
		std::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		std::unordered_set<int> worlds;

		static Identifier identifier;

		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};

	struct TextLabel
	{
		TextLabel();

		AMX *amx;
		SharedCell cell;
		int color;
		float comparableStreamDistance;
		float drawDistance;
		bool inverseAreaChecking;
		float originalComparableStreamDistance;
		Eigen::Vector3f position;
		Eigen::Vector3f positionOffset;
		int priority;
		int references;
		bool streamCallbacks;
		float streamDistance;
		bool testLOS;
		std::string text;
		int textLabelId;

		struct Attach
		{
			Attach();

			int player;
			Eigen::Vector3f position;
			int references;
			int vehicle;

			std::unordered_set<int> worlds;

			EIGEN_MAKE_ALIGNED_OPERATOR_NEW
		};

		std::shared_ptr<Attach> attach;

		std::unordered_set<int> areas;
		std::vector<int> extras;
		std::unordered_map<int, std::vector<int> > extraExtras;
		std::unordered_set<int> interiors;
		std::bitset<MAX_PLAYERS> players;
		std::unordered_set<int> worlds;

		static Identifier identifier;

		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};
}

#endif
