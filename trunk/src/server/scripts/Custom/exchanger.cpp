#include "ScriptPCH.h"

#define TEXT_NO "I am unable to complete this exchange, you do not have the necessary funds."
#define TEXT_COMBAT "You cannot exchange Honor or Arena Points while in combat!"
#define TEXT_YES "You have successfully exchanged your currency points!"
#define GOSSIP_TEXT_1 "Exchange 30K Honor for 300 Arena Points?"
#define GOSSIP_TEXT_2 "Exchange 300 Arena for 30K Honor Points?"

#define HONOR 30000  //Honor Change
#define ARENA 300 //Arena Point Change

class npc_modify_price : public CreatureScript

{
    public: 
    npc_modify_price() : CreatureScript("npc_modify_price") { }

                bool OnGossipHello(Player *player, Creature *creature)
                        {
							player->PlayerTalkClass->ClearMenus();
                            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_1, GOSSIP_SENDER_MAIN, 1);
							player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_2, GOSSIP_SENDER_MAIN, 2);
							player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                            return true;
                        }

                bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action )
                        {
                               if (!player->getAttackers().empty())
							   {
                                      player->CLOSE_GOSSIP_MENU();
                                      creature->MonsterTextEmote(TEXT_COMBAT, 0, true);
                                      return false;	  
                                     }
                               

  switch(action)
  {
       case 1:
        if (player->GetHonorPoints() < HONOR)
                    {
						  player->CLOSE_GOSSIP_MENU();
                          creature->MonsterWhisper(TEXT_NO, player->GetGUID());
                    }else{
                          player->ModifyArenaPoints(+ ARENA);					
                          player->ModifyHonorPoints(- HONOR);
                          player->CLOSE_GOSSIP_MENU();
						  break;
					     }
	   case 2:		
        if (player->GetArenaPoints() < ARENA)
                    {
                          player->CLOSE_GOSSIP_MENU();
                          creature->MonsterWhisper(TEXT_NO, player->GetGUID());
                    }else{
	   					  player->ModifyArenaPoints(- ARENA);
                          player->ModifyHonorPoints(+ HONOR);
                          player->CLOSE_GOSSIP_MENU();
                          break;									  
               			 }
					
    }
  return false;
                        }
};

void AddSC_npc_modify_price()

{

    new npc_modify_price;

}