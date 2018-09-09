#include "Framework.h"
using namespace Software;

int main()
{
	puts("#################################################################");
	puts("# Welcome to the framework that does everything but nothing :)! #");
	puts("#################################################################");
	puts("# Version 0.1 @ Github : Blackoutzz/CPP-Framework (GPL-V3)      #");
	puts("#################################################################");
	Process * CSGO = new Process("csgo.exe");
	if(CSGO->IsRunning())
	{
		Memory::Module * Client = new Memory::Module(CSGO->GetId(), "client_panorama.dll");
		Memory::Module * Engine = new Memory::Module(CSGO->GetId(), "engine.dll");
		puts(Client->GetName().c_str());
		puts(Engine->GetName().c_str());
	}
	Hardware::Keyboard * KB = new Hardware::Keyboard();
	while (!KB->IsPressedButton(KB->Return_Button)) Sleep(1000);
	return 0;
}
