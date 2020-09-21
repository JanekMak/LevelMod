#include "pch.h"
#include "Settings.h"

using namespace LevelModSettings;
extern std::map<DWORD, OverrideOption> overrideOptions;


namespace Network
{

    bool OnServer()
    {
        typedef bool(__cdecl* const pOnServer)();
        return pOnServer(0x00421FD0)();
    }

    void SendMessageToClients(unsigned char msg_id, DWORD len, void* data, int prio, int queue, int flag1, int flag2, bool include_observers)
    {
        NetHandler* net_handler = NetHandler::Instance();

        if (net_handler->InNetGame() && net_handler->OnServer())
        {
            net_handler->SendMessageToClients(msg_id, len, data);
        }
    }


    int Handle_HostOption_Changed(HostOptionMsg* msg)
    {
        NetHandler* net_handler = NetHandler::Instance();
        if (!net_handler->OnServer())
        {
            auto it = LevelModSettings::overrideOptions.find(msg->option);
            if (it != LevelModSettings::overrideOptions.end())
            {
                _printf("Host changed HostOption %s %d\n", FindChecksumName(msg->option), msg->value);
                it->second.value = msg->value;
                if (it->second.type == OverrideOption::Type::OVERRIDE ||
                    (it->second.type == OverrideOption::Type::OVERRIDE_TRUE && !it->second.value) ||
                    (it->second.type == OverrideOption::Type::OVERRIDE_FALSE && it->second.value))
                    UpdateOption(it->second.option, it->second.value);
            }
            else
                _printf("Couldn't find HostOption %s...\n", FindChecksumName(msg->option));
        }
        return HANDLER_CONTINUE;
    }

    int Handle_Test(TestMsg* msg)
    {
        _printf("Host sent testmsg %s\n", msg->test);
        return HANDLER_CONTINUE;
    }


    //Messages sent by host
    void MessageHandler::AddServerMessages(unsigned char msg_id, void* pCallback, int flags, NetHandler* net_handler, int prio)
    {
        MessageHandler* handler;
        _asm mov handler, ecx;
        //Add the original message that we have replaced with our hook
        handler->AddMessage(msg_id, pCallback, flags, net_handler, prio);
        //When host change a HostOption the host will send out a message
        //When the client gets the message the option linked to the HostOption should get overriden
        //It's possible to override only true, only false, or both
        //To add a new HostOption, add them to the struct in settings.q
        handler->AddMessage(MSG_ID_LM_HOSTOPTION_CHANGED, Handle_HostOption_Changed, HANDLER_LATE, net_handler);
        handler->AddMessage(MSG_ID_LM_TEST, Handle_Test, HANDLER_LATE, net_handler);
    }

    //Messages sent by clients
    void MessageHandler::AddClientMessages(unsigned char msg_id, void* pCallback, int flags, NetHandler* net_handler, int prio)
    {
        MessageHandler* handler;
        _asm mov handler, ecx;
        //Add the original message that we have replaced with our hook
        handler->AddMessage(msg_id, pCallback, flags, net_handler, prio);

        //TODO add new client messages here
    }
};