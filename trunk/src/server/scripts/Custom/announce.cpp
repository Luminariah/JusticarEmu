#include "ScriptPCH.h"
 
class Announce_NewPlayer : public PlayerScript
{
public:
        Announce_NewPlayer() : PlayerScript("Announce_NewPlayer") {}
 
        void OnLogin(Player * player)
        {
                std::ostringstream ss;
 
                if(player->GetTotalPlayedTime() < 5)
                {
            	ss << "|cff54b5ffPlease welcome the newest Justicar WoW player, |r " << ChatHandler(player->GetSession()).GetNameLink() << " |cff54b5ff!|r";
           	sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
                        player->CastSpell(player, 55420);
                        return;
                }
                else
                {
                }
        }
 
};
void AddSC_Announce_NewPlayer()
{
        new Announce_NewPlayer;
}