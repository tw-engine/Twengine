#include "../../lib/include/application.hpp"

int main(){
    auto app = te::Application::Create("Twengine Window", 800, 800);

    app->Run();

    return 0;
}