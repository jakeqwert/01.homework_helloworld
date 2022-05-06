#include "lib.h"
#include <iostream>

//#include <spdlog/spdlog.h> // для локальной сборки sudo apt install libspdlog-dev
                           // travis CI подготовит образ с пакетом нужным

int main()
{
//    auto logger = spdlog::stdout_logger_mt("console"); //пишем в console
//    logger->info("version {} was started", version());

//    std::cout << "build " << version() << "\n";
    std::cout << "build " << travis_build_number() << "\n";
    std::cout << "Hello, World!";

    return 0;
}
