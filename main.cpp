#include "lib.h"
#include <iostream>

//#include <spdlog/spdlog.h> // для локальной сборки sudo apt install libspdlog-dev
                           // travis CI подготовит образ с пакетом нужным

// git status
// .gitignore
// git add .
// git commit -m "CI-CD GitHubAction"
// git remote set-url origin git@github.com:jakeqwert/01.homework_helloworld.git  //на ssh перешли
// ключ добавил от сюда cat ~/.ssh/github.pub
// git push origin

int main()
{
//    auto logger = spdlog::stdout_logger_mt("console"); //пишем в console
//    logger->info("version {} was started", version());

//    std::cout << "build " << version() << "\n";
//    std::cout << "build " << travis_build_number() << "\n";
    std::cout << "build " << github_run_number() << "\n";
    std::cout << "Hello, World!";

    return 0;
}
