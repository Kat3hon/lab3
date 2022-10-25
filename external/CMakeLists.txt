cmake_minimum_required(VERSION 3.21) # Проверка версии CMake.
# Если версия установленой программы
# старее указаной, произайдёт аварийный выход.

project(logicalElement_lib)				# Название проекта

set(SOURCE_LIB logicalElement.cpp)		# Установка переменной со списком исходников

add_library(logicalElement_lib STATIC ${SOURCE_LIB})