#include <iostream>

#include "Application.h"

int main()
{

    Application* app = new Application();
    app->Run();

    std::cout << "Hello World!\n";
}

