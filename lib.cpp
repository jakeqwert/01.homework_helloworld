#include "lib.h"

#include "version.h" //константы define

int version()
{
    return PROJECT_VERSION_PATCH; //константа
}

int travis_build_number()
{
    return TRAVIS_BUILD_NUMBER; //константа
}