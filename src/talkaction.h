/**
 * The Forgotten Server - a free and open-source MMORPG server emulator
 * Copyright (C) 2014  Mark Samman <mark.samman@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef FS_TALKACTION_H_E6AABAC0F89843469526ADF310F3131C
#define FS_TALKACTION_H_E6AABAC0F89843469526ADF310F3131C

#include "luascript.h"
#include "baseevents.h"
#include "const.h"

enum TalkActionResult_t {
	TALKACTION_CONTINUE,
	TALKACTION_BREAK,
	TALKACTION_FAILED
};

class TalkAction;

class TalkActions : public BaseEvents
{
	public:
		TalkActions();
		~TalkActions();

		TalkActionResult_t playerSaySpell(Player* player, SpeakClasses type, const std::string& words) const;

	protected:
		LuaScriptInterface& getScriptInterface() final;
		std::string getScriptBaseName() const final;
		Event* getEvent(const std::string& nodeName) final;
		bool registerEvent(Event* event, const pugi::xml_node& node) final;
		void clear() final;

		// TODO: Store TalkAction objects directly in the list instead of using pointers
		std::list<TalkAction*> talkActions;

		LuaScriptInterface m_scriptInterface;
};

class TalkAction : public Event
{
	public:
		TalkAction(LuaScriptInterface* _interface);
		~TalkAction();

		bool configureEvent(const pugi::xml_node& node) override;

		std::string getWords() const {
			return words;
		}
		char getSeparator() const {
			return separator;
		}

		//scripting
		bool executeSay(Player* player, const std::string& words, const std::string& param, SpeakClasses type) const;
		//

	protected:
		std::string getScriptEventName() const override;

		std::string words;
		char separator;
};

#endif
