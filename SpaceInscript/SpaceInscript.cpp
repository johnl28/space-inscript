#include <iostream>

#include "src/Application.h"

int main()
{

    Application* app = new Application();
    app->Run();

    std::cout << "Hello World!\n";
}

