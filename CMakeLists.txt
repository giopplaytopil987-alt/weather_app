cmake_minimum_required(VERSION 3.10)
project(WeatherClient)
set(CMAKE_CXX_STANDARD 17)

# Загрузка httplib
# include(FetchContent)
# FetchContent_Declare(httplib
#     GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
#     GIT_TAG v0.11.3
# )
# FetchContent_MakeAvailable(httplib)

# Поиск nlohmann/json
find_package(nlohmann_json 3.10.5 REQUIRED)

# Указываем исходники
add_executable(weather_client 
    src/main.cpp
    src/WeatherClient.cpp
    src/AppMenu.cpp
)

# Подключаем директорию с заголовками
target_include_directories(weather_client PRIVATE src)

# Подключаем библиотеки
target_link_libraries(weather_client 
    # httplib 
    nlohmann_json::nlohmann_json 
    ssl 
    crypto 
    pthread
)