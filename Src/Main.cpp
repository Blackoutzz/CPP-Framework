#include "Framework.h"
using namespace Software;

int main()
{
	puts("#################################################################");
	puts("# Welcome to the framework that does everything but nothing :)! #");
	puts("#################################################################");
	puts("# Version 0.1 @ Github : Blackoutzz/CPP-Framework (GPL-V3)      #");
	puts("#################################################################");
	
	Hardware::Keyboard * KB = new Hardware::Keyboard();
	while (!KB->IsPressedButton(KB->Return_Button)) Sleep(1000);
	return 0;
}
