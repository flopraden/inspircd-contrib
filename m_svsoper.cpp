/*       +------------------------------------+
 *       | Inspire Internet Relay Chat Daemon |
 *       +------------------------------------+
 *
 *  InspIRCd: (C) 2002-2009 InspIRCd Development Team
 * See: http://wiki.inspircd.org/Credits
 *
 * This program is free but copyrighted software; see
 *            the file COPYING for details.
 *
 * ---------------------------------------------------
 */

#include "inspircd.h"

/* $ModDesc: Allows services to oper up a given user via SVSOPER. e.g. SVSOPER 00AAAAAAA Network_Administrator. */
/* $ModAuthor: w00t */
/* $ModAuthorMail: w00t@inspircd.org */
/* $ModDepends: core 1.2 */

class CommandSVSOper : public Command
{
private:
public:
	CommandSVSOper (InspIRCd* Instance) : Command(Instance, "SVSOPER", "o", 2)
	{
		this->source = "m_svsoper.so";
		syntax.clear();
	}

	CmdResult Handle (const std::vector<std::string> &parameters, User *user)
	{
		if (!ServerInstance->ULine(user->server))
			return CMD_FAILURE;

		User *u = ServerInstance->FindNick(parameters[0]);
		if (!u)
			return CMD_FAILURE;

		u->Oper(parameters[1], "SVSOPER");

		/* Dont send to the network, not needed. */
		return CMD_LOCALONLY;
	}
};

class ModuleSVSOper : public Module
{
public:
	ModuleSVSOper(InspIRCd* Me) : Module(Me)
	{
		ServerInstance->AddCommand(new CommandSVSOper(ServerInstance));
	}

	virtual ~ModuleSVSOper()
	{
	}


	virtual Version GetVersion()
	{
		return Version("$Id: f25ba0553346baa4180eb912e8506880c206bcee $", VF_VENDOR, API_VERSION);
	}
};

MODULE_INIT(ModuleSVSOper)
