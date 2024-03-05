#include "../../lib/include/application.hpp"

int main(){
    auto app = te::Application::Create("Twengine Window", 800, 800);

    while(app->IsRunning()){
        app->Update();
        app->Render();
    }

    return 0;
}