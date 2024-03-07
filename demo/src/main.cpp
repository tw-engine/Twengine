#include "../../lib/include/application.hpp"

int main(){
    auto app = te::Application::Create("Twengine Window", 800, 800, 60);

    while(app->IsRunning()){
        app->Update();
        app->Render();
    }

    return 0;
}