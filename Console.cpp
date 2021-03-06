#include "Console.h"
#include "defines.h"

namespace star_w
{
	static const WORD MAX_CONSOLE_LINES = 500;

	void RedirectIOToConsole()
	{
		int32 hConHandle;
		long lStdHandle;

		CONSOLE_SCREEN_BUFFER_INFO conInfo;
		FILE * fp;

		// allocate a console for this app

		AllocConsole();

		// set the screen buffer to be big enough to let us scroll text

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conInfo);
		conInfo.dwSize.Y = MAX_CONSOLE_LINES;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),
			conInfo.dwSize);

		// redirect unbuffered STDOUT to the console

		lStdHandle = long(GetStdHandle(STD_OUTPUT_HANDLE));
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		fp = _fdopen(hConHandle, "w");
		*stdout = *fp;
		setvbuf(stdout, NULL, _IONBF, 0);

		// redirect unbuffered STDIN to the console

		lStdHandle = long(GetStdHandle(STD_INPUT_HANDLE));
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		fp = _fdopen(hConHandle, "r");
		*stdin = *fp;
		setvbuf(stdin, NULL, _IONBF, 0);

		// redirect unbuffered STDERR to the console

		lStdHandle = long(GetStdHandle(STD_ERROR_HANDLE));
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		fp = _fdopen(hConHandle, "w");
		*stderr = *fp;
		setvbuf(stderr, NULL, _IONBF, 0);

		// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
		// point to console as well

		std::ios::sync_with_stdio();
	}

	void CleanUpConsole()
	{
		FreeConsole();
	}
}
