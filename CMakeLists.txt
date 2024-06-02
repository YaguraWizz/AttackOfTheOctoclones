cmake_minimum_required(VERSION 3.0)
project(AttackOfTheOctoclones)

# Установка версии языка C++
set(CMAKE_CXX_STANDARD 20)

# Добавление исходных файлов к проекту
set(SOURCE_FILES main.cpp octopus.h ptrvector.h scopedptr.h)

# Создание директории для сборки
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/project) 
file(MAKE_DIRECTORY ${BUILD_DIR})

# Переход в директорию сборки
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
