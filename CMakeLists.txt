cmake_minimum_required(VERSION 3.0)
project(AttackOfTheOctoclones)

# ��������� ������ ����� C++
set(CMAKE_CXX_STANDARD 20)

# ���������� �������� ������ � �������
set(SOURCE_FILES main.cpp octopus.h ptrvector.h scopedptr.h)

# �������� ���������� ��� ������
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/project) 
file(MAKE_DIRECTORY ${BUILD_DIR})

# ������� � ���������� ������
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})

# �������� ������������ �����
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
