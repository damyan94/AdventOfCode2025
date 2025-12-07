#include "stdafx.h"

#include "Application/Application.h"

int32_t main(int32_t argC, char** argV)
{
	Application app;
	ReturnIf(!app.Init({argC, argV}), EXIT_FAILURE);

	app.Run();

	return EXIT_SUCCESS;
}