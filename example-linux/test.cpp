#include <iostream>
#include <unistd.h>
#include <string>

std::string name(){
    return "mahadi";
}

int getScore() {
    return 10; 
}
float getHelth(){
    return 10.5486f;
}
bool isAdmin(){
    return false;
}
bool isPlayer(){
    return true;
}

int main() {
    while (true) {
        std::cout << "current activity" << std::endl << std::endl;
        std::cout << "Current Score: " << getScore() << std::endl;
        std::cout << "Current helth: " << getHelth() << std::endl;
        std::cout << "is admin: " << isAdmin() << std::endl;
        std::cout << "is player: " << isPlayer() << std::endl;
        std::cout << "name is: " << name() << std::endl;
        sleep(1);
    }
    return 0;
}
