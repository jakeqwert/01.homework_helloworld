cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
    set(PATCH_NUM $ENV{GITHUB_RUN_NUMBER})
else()
    set(PATCH_NUM 1)
endif()

# перед запуском кода на локальном компьютере,
# создать переменную окружения TRAVIS_BUILD_NUMBER, а на TRAVIS CI будет такая переменная
#project(helloworld_project VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
# GitHub Action
project(helloworld_project
        LANGUAGES CXX
        VERSION 1.1.${PATCH_NUM}
        )
#project(helloworld_project VERSION 0.0.1$ENV{TRAVIS_BUILD_NUMBER})
# имя проекта = cmake
# автоматом сформировалось 3 переменные
# ${PROJECT_VERSION_MAJOR}  0
# ${PROJECT_VERSION_MINOR}  0
# ${PROJECT_VERSION_PATCH}  1

#set(TRAVIS_BUILD_NUMBER "$ENV{TRAVIS_BUILD_NUMBER}")
set(TRAVIS_BUILD_NUMBER "${PATCH_NUM}")
set(GITHUB_RUN_NUMBER "${PATCH_NUM}")


# подключаем зависимости, cmake попытается найти в системе зависимости
# если они не устанвовлена, то будет ошибка что он не смог найти, нужно установить в систему эти зависимости
find_package(Threads REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# взять шаблон version.h.in и получить из него файл ${PROJECT_SOURCE_DIR}/version.h
configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)
# файл 'version.h'
##pragma once
##define PROJECT_VERSION_PATCH 1
#// кодогенератор сформировал этот файл


add_executable(helloworld_cli main.cpp)
# исполняемый файл helloworld_cli
# артифакт сборки helloworld_cli
# для MS VS сюда еще нужно добавить файлы .h, там будет solution


add_library(helloworld lib.cpp)
# статическая библиотека (по-умолчанию) helloworld исполняемый файл

# add_library(helloworld shared lib.cpp)
# shared динамическая библиотека helloworld исполняемый файл


add_executable(test_version test_version.cpp)
# test_version исполняемый файл, тесты собираются в бинарник

#для сборки артифактов helloworld_cli helloworld test_version, нужны настройки конфигуратора
set_target_properties(helloworld_cli helloworld test_version PROPERTIES
    CXX_STANDARD 17               # стандарт cpp
    CXX_STANDARD_REQUIRED ON      # если не дотягиваем до 17 стандарт, то ошибка
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"   # опции компиляции, для линукс тут параметры
                     # pedantic; -all;-extra ворнинги при компиляции
)

# для сборки test_version нужно задать свойста компилятора
set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

# прилинковать статическую библиотеку helloworld и Threads
target_link_libraries(helloworld_cli
    helloworld        # статическая библиотека libhelloworld.a под линуксом
    Threads::Threads  #
)

# к test_version прилинковать статическую библиотеку helloworld и Boost_LIBRARIES
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    helloworld          # статическая библиотека libhelloworld.a под линуксом
)

# установить helloworld_cli в user\bin
install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

# собрать пакет DEB для Линукс
set(CPACK_GENERATOR DEB)

# указываем версии пакета из версии программы
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}") # переменная ${PROJECT_VERSION_PATCH}


# ответственный за пакет
set(CPACK_PACKAGE_CONTACT eliseevz@mail.ru)

# inna setup для windows, система сборки для windows
# включить опцию CPACK_DEBIAN_PACKAGE_SHLIBDEPS для Debian, т.е. включит информацию
# о зависимых библиотек, найдет в каких они пакетах и добавит информацию о зависимости в данный пакет
# т.е. при установке данного пакета будет установлен boost пакет
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
# либо если не использовать эту опции, то вручную вписывать зависимые пакеты

#собрать пакет
include(CPack)

# добавляет новую виртуальную цель сборки test
enable_testing()
# последовательно будут запущены все тесты helloworld_tests test_version
add_test(helloworld_tests test_version)
# задача с именем helloworld_tests, за выполнение задачи отвечает бинарник test_version
