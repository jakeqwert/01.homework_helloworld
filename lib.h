#pragma once   //круче, чем  #include, трюк компилятор запомнит этот файл
//если встретит его еще раз то не будет его включать второй раз в проект
// отличие #include от #pragma once

int version();

int travis_build_number();

int github_run_number();
