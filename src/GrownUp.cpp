/*
 * Created by WebLuke <https://github.com/WebLuke>
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
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
        {
            ChatHandler(player->GetSession())
                .SendSysMessage("This server is running the |cff4CFF00Grown Up|r module.");
        }

        if (sConfigMgr->GetOption<bool>("GrownUp.LoginCheck", true))
            ApplyScale(player, false); // ensure consistency
    }

    void OnPlayerFirstLogin(Player* player) override
    {
        // On very first login, set to the configured StarterMinScale
        float starterMin =
            sConfigMgr->GetOption<float>("GrownUp.StarterMinScale", 0.5f);

        player->SetObjectScale(starterMin);

        ChatHandler(player->GetSession())
            .PSendSysMessage("Your adventure begins small!");
    }

    void OnPlayerLevelChanged(Player* player, uint8 /*oldLevel*/) override
    {
        ApplyScale(player, true);
    }

private:
    void ApplyScale(Player* player, bool notify)
    {
        uint32 starterMax =
            sConfigMgr->GetOption<uint32>("GrownUp.StarterMaxLevel", 15);
        uint32 highStart =
            sConfigMgr->GetOption<uint32>("GrownUp.HighLevelStart", 65);
        float highPercent =
            sConfigMgr->GetOption<float>("GrownUp.HighLevelScalePercent", 0.5f);
        float maxScale =
            sConfigMgr->GetOption<float>("GrownUp.MaxScale", 1.2f); 
        float starterMin =
            sConfigMgr->GetOption<float>("GrownUp.StarterMinScale", 0.6f);

        uint32 level = player->GetLevel();
        float newScale = 1.0f;

        if (level <= starterMax)
        {
            // Linear growth from StarterMin → 100%
            if (starterMax > 1)
                newScale = starterMin +
                           ((level - 1) / float(starterMax - 1)) *
                               (1.0f - starterMin);
            else
                newScale = 1.0f;
        }
        else if (level >= highStart)
        {
            // Beyond highStart: +X% per level
            uint32 aboveLevels = level - highStart;
            newScale = 1.0f + (aboveLevels * (highPercent / 100.0f));
        }
        else
        {
            // Between starterMax and highStart → stagnant at 100%
            newScale = 1.0f;
        }

        // Cap scale
        newScale = std::min(newScale, maxScale);

        player->SetObjectScale(newScale);

        if (notify && sConfigMgr->GetOption<bool>("GrownUp.GrownAnnounce", true))
        {
            ChatHandler(player->GetSession())
                .PSendSysMessage("You have grown adventure.");
        }
    }
};

void AddGrowUpScripts()
{
    new GrowUp();
}
