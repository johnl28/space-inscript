#include <iostream>

#include "src/Application.h"

int main()
{
    Application* app = new Application(100, 20);
    app->Run();
}

