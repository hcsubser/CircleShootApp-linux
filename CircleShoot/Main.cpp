#include "Zuma_Prefix.pch"

#include "CircleShootApp.h"
#include "../SexyAppFramework/Common.h"

#include <cstring>
#include <cstdlib>
#include <iostream>

#include <sys/stat.h>

//#ifdef _WIN32
//#if 0
//int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
//#else
int main(int argc, char** argv){
//#endif

	if(std::getenv("XDG_CONFIG_HOME")==nullptr){
		std::string homedir = std::getenv("HOME");
		if(homedir.back()=='/')
			Sexy::SetAppDataFolder(homedir+".config/zuma_deluxe");
		else
			Sexy::SetAppDataFolder(homedir+"/.config/zuma_deluxe");
	} else
		Sexy::SetAppDataFolder(std::getenv("XDG_CONFIG_HOME"));

	//configdir="default";
	if(argc==2 && strcmp(argv[1],"--help")==0){
		printf("Zuma Deluxe: linux Port\nArguments:\n    --help: Print this help\n    --configdir: Set config dir(example: ./zuma --configdir $HOME/zuma)");
		printf("\n\nDefault config dir is ~/.config/zuma_deluxe");
		return 0;
	} else if (argc==3 && strcmp(argv[1],"--configdir")==0){
		Sexy::SetAppDataFolder(argv[2]);
	} else if(argc>1){
		printf("Unknown arguments.\n");
		printf("Zuma Deluxe: linux Port\nArguments:\n    --help: Print this help\n    --configdir: Set config dir(example: ./zuma --configdir $HOME/zuma)");
		printf("\n\nDefault config dir is ~/.config/zuma_deluxe");
		return 0;	
	}
	mkdir(Sexy::GetAppDataFolder().c_str(), 0777);



    Sexy::CircleShootApp app;

    app.Init();
    app.Start();
    app.Shutdown();
    
    return 0;
}