/*
 * Created by WebLuke <https://github.com/WebLuke>
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"


// Add player scripts
class GrowUp : public PlayerScript
{
public:
    GrowUp() : PlayerScript("GrowUp", { 
        PLAYERHOOK_ON_LOGIN,
        PLAYERHOOK_ON_FIRST_LOGIN,
        PLAYERHOOK_ON_LEVEL_CHANGED
    }) { }

    void OnPlayerLogin(Player* player) override
    {
        if (sConfigMgr->GetOption<bool>("GrownUp.Announce", true))
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00Grown Up |rmodule.");
        if (sConfigMgr->GetOption<bool>("GrownUp.Enable", true) && sConfigMgr->GetOption<bool>("GrownUp.LoginCheck", true))
        {
            uint8 level = player->getLevel();
            float newScale = 1.0f;

            if (level < 5)
                newScale = 0.5f;
            else if (level < 10)
                newScale = 0.65f;
            else if (level < 15)
                newScale = 0.85f;
            else
                newScale = 1.0f;

            player->SetObjectScale(newScale);
        }
    }

    void OnPlayerFirstLogin(Player* player) override
    {
        if (sConfigMgr->GetOption<bool>("GrownUp.Enable", true))
        {
            player->SetObjectScale(0.5f);
            ChatHandler(player->GetSession()).SendSysMessage("Your adventure begins young one!");
        }
    }

    void OnPlayerLevelChanged(Player* player, uint8 /*oldLevel*/) override
    {
        if (sConfigMgr->GetOption<bool>("GrownUp.Enable", true))
        {
            uint8 newLevel = player->getLevel();
            float newScale = 1.0f; // default full size

            if (newLevel < 5)
                newScale = 0.5f;
            else if (newLevel < 10)
                newScale = 0.65f;
            else if (newLevel < 15)
                newScale = 0.85f;
            else
                newScale = 1.0f;

            player->SetObjectScale(newScale);
            ChatHandler(player->GetSession())
                .PSendSysMessage("Your adventure has grown to %.0f%%!", newScale * 100.0f);
        }
    }
};

// Add all scripts in one
void AddGrowUpScripts()
{
    new GrowUp();
}
