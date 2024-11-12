cmake_minimum_required(VERSION 3.5)

# Название проекта
project(ExpoFinder)


find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    message(STATUS "Found OpenMP")
    add_definitions(-DOPENMP_SUPPORT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Указываем файлы исходного кода
set(SOURCES
    main.cpp
    DataController.cpp
)

# Указываем заголовочные файлы для IDE (не обязательно для сборки)
set(HEADERS
    DataController.h
)

# Подключаем фреймворк Drogon
find_package(Drogon CONFIG REQUIRED)

# Создаем исполняемый файл из исходных файлов
add_executable(ExpoFinder ${SOURCES} ${HEADERS})

# Линкуем фреймворк Drogon к исполняемому файлу
target_link_libraries(ExpoFinder PRIVATE Drogon::Drogon)

if(OpenMP_CXX_FOUND)
    target_link_libraries(ExpoFinder PUBLIC OpenMP::OpenMP_CXX)
endif()
